#include "csymboldialog.h"
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
QString strSelectedText;

CSymbolDialog::CSymbolDialog()
{
    pushButton1 = new QPushButton("1");
    pushButtonAsteric = new QPushButton("*");
    pushButtonSlash = new QPushButton("/");
    pushButtonPlush = new QPushButton("+");
    pushButtonMinus = new QPushButton("-");
    pushButtonAmbersand = new QPushButton("&&");
    pushButtonUnderscore = new QPushButton("_");
    pushButtonAt = new QPushButton("@");
    pushButtonHash = new QPushButton("#");
    pushButtonPercentage = new QPushButton("%");
    pushButtonDollor = new QPushButton("$");
    pushButtonSingleQuote = new QPushButton("'");
    pushButtonSemiColon = new QPushButton(";");
    pushButtonEqualTo = new QPushButton("=");
    pushButtonOpenBrackets = new QPushButton("(");
    pushButtonCloseBrackets = new QPushButton(")");
    pushButtonComma = new QPushButton(",");
    pushButtonColon = new QPushButton(":");
    pushButtonExclamation = new QPushButton("!");
    pushButtonDoubleQuotes = new QPushButton("\"");

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(pushButton1,0,0);
    gridLayout->addWidget(pushButtonAsteric,0,1);
    gridLayout->addWidget(pushButtonSlash,0,2);
    gridLayout->addWidget(pushButtonPlush,0,3);
    gridLayout->addWidget(pushButtonMinus,0,4);
    gridLayout->addWidget(pushButtonAmbersand,1,0);
    gridLayout->addWidget(pushButtonUnderscore,1,1);
    gridLayout->addWidget(pushButtonAt,1,2);
    gridLayout->addWidget(pushButtonHash,1,3);
    gridLayout->addWidget(pushButtonPercentage,1,4);
    gridLayout->addWidget(pushButtonDollor,2,0);
    gridLayout->addWidget(pushButtonSingleQuote,2,1);
    gridLayout->addWidget(pushButtonSemiColon,2,2);
    gridLayout->addWidget(pushButtonEqualTo,2,3);
    gridLayout->addWidget(pushButtonOpenBrackets,2,4);
    gridLayout->addWidget(pushButtonCloseBrackets,3,0);
    gridLayout->addWidget(pushButtonComma,3,1);
    gridLayout->addWidget(pushButtonColon,3,2);
    gridLayout->addWidget(pushButtonExclamation,3,3);
    gridLayout->addWidget(pushButtonDoubleQuotes,3,4);
    gridLayout->setHorizontalSpacing(1);
    gridLayout->setVerticalSpacing(1);
    setLayout(gridLayout);
    QString styleSheet = QString::fromUtf8(
            "QPushButton{image: url(:/icons-png/letter.png);"
            "border-width: 0px; border-radius: 12px;color:black;font: 14pt;}"
            "QPushButton::focus {image: url(:/icons-png/letter_active.png);color:white;}");
    setStyleSheet(styleSheet);
    setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setGeometry(0,20,320,220);
    QList<QPushButton*> lst_qpbAllButtons = findChildren<QPushButton *>(); /* stores all the buttons in the list */

    for(int nPosition = 0; nPosition < lst_qpbAllButtons.count(); ++nPosition)
    {
        QPushButton *button = lst_qpbAllButtons.at(nPosition);
        button->setFixedSize(50,50);
        button->setAutoDefault(true);
        connect(button,SIGNAL(clicked()),this ,SLOT(on_pushButton_clicked()));
    }
}

/**
 * \fn CKeyboardForm *Instance()
 * \brief gets the instance of the keyboard widget.
 * \return the object of the keyboard widget.
 */
CSymbolDialog *CSymbolDialog::Instance()
{
    /* create the keyboard object and return the instance */
    static CSymbolDialog theInstance;
    return &theInstance;
}

/**
 * \fn showKeyboard(QWidget *pParent)
 * \brief adds the keyboard to the parent widget.
 * \param [in] parent object to add the virtual keyboard.
 */
QString CSymbolDialog::getSymbol(QWidget *pParent)
{
    /* add the keyboard widget to parent widget */

    strSelectedText = "";
    CSymbolDialog *pKeyboard = Instance();

    pKeyboard->setParent(pParent);
    pKeyboard->exec();
    pKeyboard->pushButton1->setFocus();
    return strSelectedText;
}

/**
 * \fn hideKeyboard()
 * \brief hides the keyboard widget.
 */
void CSymbolDialog::hideKeyboard()
{
    /* hide the keyboard from the parent window */
    Instance()->hide();
    Instance()->setParent(0);
}

void CSymbolDialog::on_pushButton_clicked()
{
    QPushButton *pushButtonSelected;
    pushButtonSelected = qobject_cast<QPushButton *>(sender());
    strSelectedText = pushButtonSelected->text();
    if ( "&&" == strSelectedText ) /* check & button is pressed or not */
    {
        strSelectedText = "&";
    }
    this->close();
}
