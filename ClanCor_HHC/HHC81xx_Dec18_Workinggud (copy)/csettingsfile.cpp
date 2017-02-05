#include "csettingsfile.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QBuffer>
#include <QDebug>
CSettingsFile::CSettingsFile()
{
    m_StringFILEPATH = "/Settings/ClanCor/HHC80xxSDK.xml";
    m_bIsError = false;
    QDir dirExistCheck;
    if(!dirExistCheck.exists("/Settings"))
    {
        if(!dirExistCheck.mkdir("/Settings"))
        {
            m_bIsError = true;
            QMessageBox::critical(0, "Setting File", "Failed while creating directory-E01");
            return;
        }
    }
    if(!dirExistCheck.exists("/Settings/ClanCor"))
    {
        if(!dirExistCheck.mkdir("/Settings/ClanCor -p"))
        {
            m_bIsError = true;
            QMessageBox::critical(0, "Setting File", "Failed while creating directory-E02");
            return;
        }
    }
    QFile fileRead(m_StringFILEPATH);
    if(!fileRead.open(QIODevice::ReadWrite))
    {
        m_bIsError = true;
        QMessageBox::critical(0, "Setting File", "Failed while opening settings file-E01");
        return;
    }
    bytearrayContent = fileRead.readAll();
    fileRead.close();
}

CSettingsFile::CSettingsFile(QString stringOrganisationName, QString stringApplicationName)
{
    m_bIsError = false;
    QString stringSettingsBaseDir = "/Settings";
    QDir dirExistCheck;
    if(!dirExistCheck.exists(stringSettingsBaseDir))
    {
        if(!dirExistCheck.mkdir(stringSettingsBaseDir))
        {
            m_bIsError = true;
            QMessageBox::critical(0, "Setting File", "Failed while creating directory-E03");
            return;
        }
    }
    if(!dirExistCheck.exists(stringSettingsBaseDir + "/" + stringOrganisationName))
    {
        if(!dirExistCheck.mkdir(stringSettingsBaseDir + "/" + stringOrganisationName))
        {
            m_bIsError = true;
            QMessageBox::critical(0, "Setting File", "Failed while creating directory-E04");
            return;
        }
    }
    QFile fileRead(stringSettingsBaseDir + "/" + stringOrganisationName + "/" + stringApplicationName);
    if(!fileRead.open(QIODevice::ReadWrite))
    {
        m_bIsError = true;
        QMessageBox::critical(0, "Setting File", "Failed while opening settings file-E05");
        return;
    }
    bytearrayContent = fileRead.readAll();
    fileRead.close();
    m_StringFILEPATH = stringSettingsBaseDir + "/" + stringOrganisationName + "/" + stringApplicationName;
}

CSettingsFile::~CSettingsFile()
{
}

bool CSettingsFile::isError()
{
    return m_bIsError;
}

bool CSettingsFile::beginSettingsGroup(QString arg_stringGroupName)
{
    bytearrayContent.begin();
    m_stringGroupName = QString("<" + arg_stringGroupName.simplified() + ">");
    stringlistValue.clear();
    stringlistKey.clear();
    if(bytearrayContent.contains(m_stringGroupName.toLatin1()))
    {
        int nGroupIndex = bytearrayContent.indexOf(m_stringGroupName, 0);
        QTextStream textStreamParse(bytearrayContent);
        textStreamParse.seek(nGroupIndex);
        QString stringTemp = textStreamParse.readLine().simplified();
        if(textStreamParse.seek(nGroupIndex + stringTemp.size() + 1))
        {
            nGroupIndex = nGroupIndex + stringTemp.size() + 1;
            while(!textStreamParse.atEnd())
            {
                stringTemp = textStreamParse.readLine().simplified();
                if(!stringTemp.contains("</" + arg_stringGroupName + ">"))
                {
                    int nValueIndex = stringTemp.indexOf(">");
                    stringlistKey.append(stringTemp.section(">",0,0).mid(1));
                    stringlistValue.append(stringTemp.mid(nValueIndex + 1,stringTemp.indexOf("<",1) - nValueIndex - 1));
                }
                else
                {
                    break;
                }
                nGroupIndex = nGroupIndex + stringTemp.size() + 1;
                if((nGroupIndex + stringTemp.size() +1) < bytearrayContent.size() )
                    textStreamParse.seek(nGroupIndex );
            }
        }
    }
    else
    {
        QString stringLinebreak = "";
        if(bytearrayContent.size()>0)
        {
            stringLinebreak = "\n";
        }
        else
        {
            bytearrayContent.append("<ROOT>\n</ROOT>");
        }

        int nGroupIndex = bytearrayContent.indexOf("</ROOT>", 0);
        QBuffer textStreamParse(&bytearrayContent);
        textStreamParse.open(QIODevice::ReadWrite);
        if(textStreamParse.seek(nGroupIndex))
        {
            QByteArray bytearrayTempStrings = textStreamParse.readAll();
            textStreamParse.seek(nGroupIndex);
            bytearrayContent = bytearrayContent.left(bytearrayContent.size() - bytearrayTempStrings.size());
            textStreamParse.write(QString(stringLinebreak + "<" + arg_stringGroupName + ">\n</" + arg_stringGroupName + ">\n").toLatin1());
            bytearrayContent.append(bytearrayTempStrings);
        }

        QFile fileRead(m_StringFILEPATH);
        if(!fileRead.open(QIODevice::WriteOnly))
        {
            m_bIsError = true;
            QMessageBox::critical(0, "Setting File", "Failed while opening settings file-E02");
            return false;
        }
        fileRead.write(bytearrayContent);
        fileRead.close();
    }
    return true;
}

bool CSettingsFile::setValue(QString stringKey, QString stringValue)
{ 
    bool bValueUpdate = false;
    bytearrayContent.begin();
    if(stringlistKey.size() > 0)
    {
        int nCountlistKey = 0;
        int nKeyIndex = 0, nLineLength = 0;
        while(nCountlistKey < stringlistKey.size())
        {
            if(stringlistKey.at(nCountlistKey) == stringKey.simplified())
            {
                if(stringlistValue.at(nCountlistKey) == stringValue.simplified())
                {
                    break;
                }
                else
                {
                    nKeyIndex = bytearrayContent.indexOf(QString( "<" + stringKey.simplified() + ">"));
                    QTextStream textStreamParse(bytearrayContent);
                    textStreamParse.seek(nKeyIndex);
                    nLineLength = textStreamParse.readLine().length();
                    textStreamParse.seek(nKeyIndex);
                    bytearrayContent.replace( nKeyIndex, nLineLength , QString( "<" + stringKey.simplified() + ">" + stringValue.simplified() + "</" + stringKey.simplified() + ">").toLatin1());
                    bValueUpdate = true;
                    break;
                }
            }
            nCountlistKey++;
        }
        if(nCountlistKey == stringlistKey.size())
        {
            bytearrayContent.begin();
            QString stringTempEndGroup = m_stringGroupName;
            stringTempEndGroup = stringTempEndGroup.replace("<", "</");
            int nGroupIndex = bytearrayContent.indexOf(stringTempEndGroup, 0);
            QBuffer textStreamParse(&bytearrayContent);
            textStreamParse.open(QIODevice::ReadWrite);
            if(textStreamParse.seek(nGroupIndex))
            {
                QByteArray bytearrayTempStrings = textStreamParse.readAll();
                textStreamParse.seek(nGroupIndex);
                bytearrayContent = bytearrayContent.left(bytearrayContent.size() - bytearrayTempStrings.size());
                textStreamParse.write(QString( "<" + stringKey + ">" + stringValue + "</" + stringKey + ">\n").toLatin1());
                bytearrayContent.append(bytearrayTempStrings);
                bValueUpdate = true;
            }
        }
    }
    else
    {
        int nGroupIndex = bytearrayContent.indexOf(m_stringGroupName, 0);
        QBuffer textStreamParse(&bytearrayContent);
        textStreamParse.open(QIODevice::ReadWrite);
        textStreamParse.seek(nGroupIndex);
        QString stringTemp = textStreamParse.readLine().simplified();
        if(textStreamParse.seek(nGroupIndex + stringTemp.size() + 1))
        {
            QByteArray bytearrayTempStrings = textStreamParse.readAll();
            textStreamParse.seek(nGroupIndex + stringTemp.size() + 1);
            bytearrayContent = bytearrayContent.left(bytearrayContent.size() - bytearrayTempStrings.size());
            textStreamParse.write(QString( "<" + stringKey + ">" + stringValue + "</" + stringKey + ">\n").toLatin1());
            textStreamParse.write(bytearrayTempStrings);
            bValueUpdate = true;
        }
    }

    if(bValueUpdate)
    {
        QFile fileRead(m_StringFILEPATH);
        if(!fileRead.open(QIODevice::WriteOnly))
        {
            m_bIsError = true;
            QMessageBox::critical(0, "Setting File", "Failed while opening settings file-E04");
            return false;
        }
        fileRead.write(bytearrayContent);
        fileRead.close();
        beginSettingsGroup(m_stringGroupName.mid(1, m_stringGroupName.length() - 2));
    }
    return true;
}

QString CSettingsFile::value(QString stringKey)
{
    QString stringKeyValue = "";
    if(stringlistKey.size() > 0)
    {
        int nCountlistKey = 0;
        while(nCountlistKey < stringlistKey.size())
        {
            if(stringlistKey.at(nCountlistKey) == stringKey.simplified())
            {
                if(stringlistValue.size() > nCountlistKey)
                    stringKeyValue = stringlistValue.at(nCountlistKey);
            }
            nCountlistKey++;
        }
    }
    else
    {
//        qDebug()<<m_stringGroupName<<"Key"<<stringKey;
        QMessageBox::critical(0, "Read Value", "The selected group has no key or group not selected..");
    }
    return stringKeyValue;

}

bool CSettingsFile::contains(QString stringSearch)
{
    return bytearrayContent.contains(stringSearch.toLatin1());
}

int CSettingsFile::indexKey(QString stringSearch)
{
    int nLoopCount = 0, nIndex = -1;
    if(stringlistKey.size() > 0)
    {
        while(nLoopCount < stringlistKey.size())
        {
            if(QString(stringlistKey.at(nLoopCount)).simplified() == stringSearch)
            {
                nIndex = nLoopCount;
                break;
            }
        }
    }
    return nIndex;
}

bool CSettingsFile::deleteKey(QString stringKey)
{
    bytearrayContent.begin();
    QString stringTempEndKey = QString("</" + stringKey + ">");
    if(stringlistKey.size() > 0)
    {
        if(stringlistKey.contains(stringKey))
        {
            int nGroupIndex = bytearrayContent.indexOf(stringTempEndKey, 0);
            QBuffer textStreamParse(&bytearrayContent);
            textStreamParse.open(QIODevice::ReadWrite);
            nGroupIndex = nGroupIndex + stringTempEndKey.size() + 1;
            if(textStreamParse.seek(nGroupIndex))
            {
                QByteArray bytearrayTempStrings = textStreamParse.readAll();
                bytearrayContent.begin();
                stringTempEndKey = QString("<" + stringKey + ">");
                nGroupIndex = bytearrayContent.indexOf(stringTempEndKey, 0);
                textStreamParse.seek(nGroupIndex);

                bytearrayContent = bytearrayContent.left(bytearrayContent.size() - textStreamParse.readAll().size());
                bytearrayContent.append(bytearrayTempStrings);
            }
            QFile fileRead(m_StringFILEPATH);
            if(!fileRead.open(QIODevice::WriteOnly))
            {
                m_bIsError = true;
                QMessageBox::critical(0, "Setting File", "Failed while opening settings file-E05");
                return false;
            }
            fileRead.write(bytearrayContent);
            fileRead.close();
        }
        else
        {
            QMessageBox::critical(0, "Setting File", "Group not selected..!");
            return false;
        }
        beginSettingsGroup(m_stringGroupName.mid(1, m_stringGroupName.length() - 2));
    }
    else
    {
        QMessageBox::critical(0, "Setting File", "Group not selected (or) keys are not available..!");
        return false;
    }
    return true;
}

int CSettingsFile::size()
{
    if(stringlistKey.size() == stringlistValue.size())
    {
        return stringlistKey.size();
    }
    else
    {
        QMessageBox::critical(0, "Setting File", "Failed while decoding keys in group..!");
    }
    return -1;
}

QString CSettingsFile::atKey(int index)
{
    if(stringlistKey.size() > 0)
    {
        if(index < stringlistKey.size())
        {
            return QString(stringlistKey.at(index));
        }
    }
    else
    {
        QMessageBox::critical(0, "Setting File", "Group not selected (or) keys are not available..!");
    }
    return "";
}

QString CSettingsFile::atValue(int index)
{
    if(stringlistValue.size() > 0)
    {
        if(index < stringlistValue.size())
        {
            return QString(stringlistValue.at(index));
        }
    }
    else
    {
        QMessageBox::critical(0, "Setting File", "Group not selected (or) keys are not available..!");
    }
    return "";
}

QStringList CSettingsFile::keyList()
{
    return stringlistKey;
}
