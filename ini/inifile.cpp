#include "inifile.h"

IniFile::IniFile()
{
    c_path = "";
}

IniFile::IniFile(const QString &path):c_path(path)
{
    load(c_path);
}

bool    IniFile::load(const QString &in)
{
    QFile file(in);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "IniFile::load cant open destined file";
        return false;
    }

    bool loading = false;
    QStringList bufor;
    QString        buf;

    while ( !file.atEnd() ) {
        buf = file.readLine();
        buf.remove("\n");

        if( !isComment(buf) )
        {
            if( !loading )
            {
                loading = true;
            }
            bufor << buf;
        }
        else
        {
            if( loading )
            {
                if( bufor.count() == 1 )
                { c_offset = IniItem(bufor)["BaseOffset"]; }
                else
                {
                    bufor.removeAll(QString(""));
                    c_items << IniItem(bufor);
                    c_names << c_items.last()["Name"];
                    c_lines << c_names.last();
                }
                loading = false;
                bufor.clear();
            }
            c_lines << buf;
        }
    }

    file.close();
    return true;
}

bool    IniFile::save()
{
    QFile file(c_path);
    if( !file.open(QFile::WriteOnly | QFile::Text) )                            // 0. Make sure, were ready to write
    {
        qDebug() << "IniFile::save failure (can't open file for writing)";
        return false;
    }
    QTextStream ostr(&file);

    ostr << "BaseOffset: " + c_offset.string();
    for(int i=0; i<c_lines.count(); i++)
    {
        ostr << "\n";
        if( !isComment(c_lines[i]) )
        { /*qDebug() << item(c_lines[i]).toString();*/ ostr << item(c_lines[i]).toString(); }
        else
        { ostr << c_lines[i]; }
    }
    file.close();
    return true;
}

bool IniFile::isComment(const QString &line)
{ return line.contains(QRegExp("\\s*//[^\\n]*")); }

QList<IniItem *> IniFile::getAll()
{
    QList<IniItem*> all;
    for(int i=0; i<count(); i++)
    { all << &c_items[i]; }
    return all;
}
