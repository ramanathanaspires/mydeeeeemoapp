#ifndef CSYMBOLDIALOG_H
#define CSYMBOLDIALOG_H

#include <QDialog>
#include <QString>

class CSymbolDialog : public QDialog
{
    Q_OBJECT
public:    
    static CSymbolDialog *Instance();
    static QString getSymbol(QWidget *pParent=0);
    static void hideKeyboard();
    QPushButton *pushButton1;
private:
    explicit CSymbolDialog();
    QPushButton *pushButtonAsteric;
    QPushButton *pushButtonSlash;
    QPushButton *pushButtonPlush;
    QPushButton *pushButtonMinus;
    QPushButton *pushButtonAmbersand;
    QPushButton *pushButtonUnderscore;
    QPushButton *pushButtonAt;
    QPushButton *pushButtonHash;
    QPushButton *pushButtonPercentage;
    QPushButton *pushButtonDollor;
    QPushButton *pushButtonSingleQuote;
    QPushButton *pushButtonSemiColon;
    QPushButton *pushButtonEqualTo;
    QPushButton *pushButtonOpenBrackets;
    QPushButton *pushButtonComma;
    QPushButton *pushButtonCloseBrackets;
    QPushButton *pushButtonColon;
    QPushButton *pushButtonExclamation;
    QPushButton *pushButtonDoubleQuotes;

private slots:
    void on_pushButton_clicked();

};

#endif // CSYMBOLDIALOG_H
