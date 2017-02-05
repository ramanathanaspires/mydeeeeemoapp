#ifndef CSETTINGSFILE_H
#define CSETTINGSFILE_H
#include <QWidget>

class CSettingsFile
{
public:
    CSettingsFile();
    CSettingsFile(QString stringOrganisationName, QString stringApplicationName);
    ~CSettingsFile();

    bool isError();
    bool beginSettingsGroup(QString stringGroupName);
    bool setValue(QString stringKey, QString stringValue);
    bool contains(QString stringSearch);
    int indexKey(QString stringSearch);
    bool deleteKey(QString stringKey);
    QString value(QString stringKey);
    int size();
    QString atKey(int index);
    QString atValue(int index);
    QStringList keyList();

private:
    bool m_bIsError;
    QStringList stringlistKey, stringlistValue;
    QString m_stringGroupName, m_StringFILEPATH;
    QByteArray bytearrayContent;
};

#endif // CSETTINGSFILE_H
