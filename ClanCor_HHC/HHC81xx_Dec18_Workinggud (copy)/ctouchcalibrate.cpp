#include "ctouchcalibrate.h"

#include <QApplication>
#include <QtGui>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/fb.h>

/********************************************************************************
         This code is implemented by using sample called ts_calibrate.c as modal
*********************************************************************************/

extern "C"
{
    #include "cfbutils.h"
}

using namespace ClanCor;

typedef struct {
        int x[5], xfb[5];
        int y[5], yfb[5];
        int a[7];
} calibration;

static int palette[] =
{
        0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0x304050, 0x80b8c0
};

#define NR_COLORS (sizeof(palette) / sizeof(palette[0]))

static int sort_by_x(const void* a, const void *b)
{
        return (((struct ts_sample *)a)->x - ((struct ts_sample *)b)->x);
}

static int sort_by_y(const void* a, const void *b)
{
        return (((struct ts_sample *)a)->y - ((struct ts_sample *)b)->y);
}

void getxy(struct tsdev *ts, int *x, int *y)
{
#define MAX_SAMPLES 128
        struct ts_sample samp[MAX_SAMPLES];
        int index, middle;

        do {
                if (ts_read_raw(ts, &samp[0], 1) < 0) {
                        perror("ts_read");
                        close_framebuffer ();
                        return;
                }

        } while (samp[0].pressure == 0);

        /* Now collect up to MAX_SAMPLES touches into the samp array. */
        index = 0;
        do {
                if (index < MAX_SAMPLES-1)
                        index++;
                if (ts_read_raw(ts, &samp[index], 1) < 0) {
                        perror("ts_read");
                        close_framebuffer ();
                        return;
                }
        } while (samp[index].pressure > 0);
        printf("Took %d samples...\n",index);

        /*
         * At this point, we have samples in indices zero to (index-1)
         * which means that we have (index) number of samples.  We want
         * to calculate the median of the samples so that wild outliers
         * don't skew the result.  First off, let's assume that arrays
         * are one-based instead of zero-based.  If this were the case
         * and index was odd, we would need sample number ((index+1)/2)
         * of a sorted array; if index was even, we would need the
         * average of sample number (index/2) and sample number
         * ((index/2)+1).  To turn this into something useful for the
         * real world, we just need to subtract one off of the sample
         * numbers.  So for when index is odd, we need sample number
         * (((index+1)/2)-1).  Due to integer division truncation, we
         * can simplify this to just (index/2).  When index is even, we
         * need the average of sample number ((index/2)-1) and sample
         * number (index/2).  Calculate (index/2) now and we'll handle
         * the even odd stuff after we sort.
         */
        middle = index/2;
        if (x) {
                qsort(samp, index, sizeof(struct ts_sample), sort_by_x);
                if (index & 1)
                        *x = samp[middle].x;
                else
                        *x = (samp[middle-1].x + samp[middle].x) / 2;
        }
        if (y) {
                qsort(samp, index, sizeof(struct ts_sample), sort_by_y);
                if (index & 1)
                        *y = samp[middle].y;
                else
                        *y = (samp[middle-1].y + samp[middle].y) / 2;
        }
}

void ts_flush (struct tsdev *ts)
{
        /* Read all unread touchscreen data,
         * so that we are sure that the next data that we read
         * have been input after this flushing.
         */

#define TS_BUFFER_MAX 32768
        static char buffer [TS_BUFFER_MAX];
        read (ts_fd (ts), buffer, TS_BUFFER_MAX);
}


CTouchCalibrate::CTouchCalibrate()
{
    m_dialogTouch = new QDialog;
    QLabel *labelBackground = new QLabel(m_dialogTouch);
    QVBoxLayout *v = new QVBoxLayout;
    labelBackground->setAlignment(Qt::AlignCenter);
    labelBackground->setWordWrap(true);
    labelBackground->setText("<font color=yellow><b>80xx calibration utility </b><br><font color=white> Touch crosshair to calibrate</font>");
    int width = QApplication::desktop()->width();
    width = width -200;

    v->setAlignment(Qt::AlignTop);
    v->setMargin(6);
    v->addSpacing(70);
    v->addWidget(labelBackground);

    m_dialogTouch->setLayout(v);
    m_dialogTouch->setStyleSheet("background-color:black;");
    m_dialogTouch->setWindowFlags(Qt::FramelessWindowHint);
    m_dialogTouch->setWindowModality(Qt::ApplicationModal);
    m_dialogTouch->setCursor(QCursor(Qt::BlankCursor));
    m_dialogTouch->setFixedSize((int)QApplication::desktop()->width(),(int)QApplication::desktop()->height());
    m_dialogTouch->show();
    QCursor cursor;
    cursor.setPos(QPoint(0,0));
    QEventLoop loop;
    QTimer tim;
    tim.start(500);
    connect(&tim,SIGNAL(timeout()),&loop,SLOT(quit()));
    loop.exec();
}

CTouchCalibrate::~CTouchCalibrate()
{
    delete m_dialogTouch;
}

int perform_calibration(calibration *cal) {
        int j;
        float n, x, y, x2, y2, xy, z, zx, zy;
        float det, a, b, c, e, f, i;
        float scaling = 65536.0;

// Get sums for matrix
        n = x = y = x2 = y2 = xy = 0;
        for(j=0;j<5;j++) {
                n += 1.0;
                x += (float)cal->x[j];
                y += (float)cal->y[j];
                x2 += (float)(cal->x[j]*cal->x[j]);
                y2 += (float)(cal->y[j]*cal->y[j]);
                xy += (float)(cal->x[j]*cal->y[j]);
        }

// Get determinant of matrix -- check if determinant is too small
        det = n*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
        if(det < 0.1 && det > -0.1) {
                printf("ts_calibrate: determinant is too small -- %f\n",det);
                return 0;
        }

// Get elements of inverse matrix
        a = (x2*y2 - xy*xy)/det;
        b = (xy*y - x*y2)/det;
        c = (x*xy - y*x2)/det;
        e = (n*y2 - y*y)/det;
        f = (x*y - n*xy)/det;
        i = (n*x2 - x*x)/det;

// Get sums for x calibration
        z = zx = zy = 0;
        for(j=0;j<5;j++) {
                z += (float)cal->xfb[j];
                zx += (float)(cal->xfb[j]*cal->x[j]);
                zy += (float)(cal->xfb[j]*cal->y[j]);
        }

// Now multiply out to get the calibration for framebuffer x coord
        cal->a[0] = (int)((a*z + b*zx + c*zy)*(scaling));
        cal->a[1] = (int)((b*z + e*zx + f*zy)*(scaling));
        cal->a[2] = (int)((c*z + f*zx + i*zy)*(scaling));

        printf("%f %f %f\n",(a*z + b*zx + c*zy),
                                (b*z + e*zx + f*zy),
                                (c*z + f*zx + i*zy));

// Get sums for y calibration
        z = zx = zy = 0;
        for(j=0;j<5;j++) {
                z += (float)cal->yfb[j];
                zx += (float)(cal->yfb[j]*cal->x[j]);
                zy += (float)(cal->yfb[j]*cal->y[j]);
        }

// Now multiply out to get the calibration for framebuffer y coord
        cal->a[3] = (int)((a*z + b*zx + c*zy)*(scaling));
        cal->a[4] = (int)((b*z + e*zx + f*zy)*(scaling));
        cal->a[5] = (int)((c*z + f*zx + i*zy)*(scaling));

        printf("%f %f %f\n",(a*z + b*zx + c*zy),
                                (b*z + e*zx + f*zy),
                                (c*z + f*zx + i*zy));

// If we got here, we're OK, so assign scaling to a[6] and return
        cal->a[6] = (int)scaling;
        return 1;
/*
// This code was used originally to just insert default calibration values
        for(j=0;j<7;j++) {
                c->a[j]=0;
        }
        c->a[1] = c->a[5] = c->a[6] = 1;
        return 1;
*/

}

static void get_sample (struct tsdev *ts, calibration *cal,
                        int index, int x, int y, char *name)
{
        static int last_x = -1, last_y;

        if (last_x != -1) {
#define NR_STEPS 10
                int dx = ((x - last_x) << 16) / NR_STEPS;
                int dy = ((y - last_y) << 16) / NR_STEPS;
                int i;
                last_x <<= 16;
                last_y <<= 16;
                for (i = 0; i < NR_STEPS; i++) {
                        put_cross (last_x >> 16, last_y >> 16, 2 | XORMODE);
                        usleep (1000);
                        put_cross (last_x >> 16, last_y >> 16, 2 | XORMODE);
                        last_x += dx;
                        last_y += dy;
                }
        }

        put_cross(x, y, 2 | XORMODE);
        getxy (ts, &cal->x [index], &cal->y [index]);
        put_cross(x, y, 2 | XORMODE);

        last_x = cal->xfb [index] = x;
        last_y = cal->yfb [index] = y;

        printf("%s : X = %4d Y = %4d\n", name, cal->x [index], cal->y [index]);
}


bool CTouchCalibrate::getTouchval()
{
    struct tsdev *ts;
    calibration cal;
    int cal_fd;
    char cal_buffer[256];
    char *tsdevice = NULL;
    char *calfile = NULL;
    unsigned int i;

    if( (tsdevice = getenv("TSLIB_TSDEVICE")) != NULL ) {
            ts = ts_open(tsdevice,0);
    } else {
#ifdef USE_INPUT_API
            ts = ts_open("/dev/input/event0", 0);
#else
            ts = ts_open("/dev/touchscreen/ucb1x00", 0);
#endif /* USE_INPUT_API */
    }

    if (!ts) {
            perror("ts_open");
            ts_close(ts);
            m_dialogTouch->close();
            return false;
    }
    if (ts_config(ts)) {
            perror("ts_config");
            ts_close(ts);
            m_dialogTouch->close();
            return false;
    }

    if (open_framebuffer()) {
        ts_close(ts);
        close_framebuffer();
        m_dialogTouch->close();
        return false;
    }


    for (i = 0; i < NR_COLORS; i++)
            setcolor (i, palette [i]);
    get_sample (ts, &cal, 0, 50,        50,        (char*) "Top left");
    get_sample (ts, &cal, 1, xres - 50, 50,        (char*) "Top right");
    get_sample (ts, &cal, 2, xres - 50, yres - 50, (char*) "Bot right");
    get_sample (ts, &cal, 3, 50,        yres - 50, (char*) "Bot left");
    get_sample (ts, &cal, 4, xres / 2,  yres / 2,  (char*) "Center");

    QMessageBox mgsbox;
    mgsbox.setWindowTitle("Touch Calibration Utility");
    mgsbox.setText("Took 5 samples... ");
//    mgsbox.setInformativeText("To continue with Calibration click <b>Restart</b> \nTo Cancel Calibration click <b>Cancel</b>");
    mgsbox.setInformativeText("To continue with Calibration click <b>Shutdown</b> \nTo Cancel Calibration click <b>Cancel</b>");//Changes OCT17 2013
//    mgsbox.addButton("Restart",QMessageBox::AcceptRole);//old
    mgsbox.addButton("Shutdown",QMessageBox::AcceptRole);//Changed on OCT 17 2013
    mgsbox.addButton(QMessageBox::Cancel);
    int pval=mgsbox.exec();
    if(pval==QMessageBox::Cancel)
    {
        ts_close(ts);
        close_framebuffer();
        QMessageBox::critical(0,"Error", "Calibration Failed");
        m_dialogTouch->close();
        return false;
    }

    if (perform_calibration (&cal)) {
            printf("Calibration constants: ");
            for (i = 0; i < 7; i++) printf("%d ", cal.a [i]);
            printf("\n");
            if ((calfile = getenv("TSLIB_CALIBFILE")) != NULL) {
                    cal_fd = open (calfile, O_CREAT | O_RDWR);
            } else {
                    cal_fd = open ("/etc/pointercal", O_CREAT | O_RDWR);
            }
            sprintf (cal_buffer,"%d %d %d %d %d %d %d",
                     cal.a[1], cal.a[2], cal.a[0],
                     cal.a[4], cal.a[5], cal.a[3], cal.a[6]);
            write (cal_fd, cal_buffer, strlen (cal_buffer) + 1);
            close (cal_fd);
            i = 0;
    } else {            
            i = -1;
            ts_close(ts);
            close_framebuffer();
            QMessageBox::critical(0,"Error", "Calibration Failed");
            m_dialogTouch->close();
            return false;
    }
    QTimer t;
    t.setSingleShot(true);
    QEventLoop e;
    connect(&t,SIGNAL(timeout()),&e,SLOT(quit()));
    t.start(200);
    e.exec();
    ts_close(ts);
    close_framebuffer();
    m_dialogTouch->close();
    return true;
}
