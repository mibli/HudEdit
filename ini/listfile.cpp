#include "listfile.h"

ListFile::ListFile(const QString &pathIn)
{
    c_path = pathIn;
    if(!load())
    { qDebug() << "ListFile::ListFile failure (failed to load)"; }
}

bool ListFile::load()
{
    c_files.clear();

    QFile file(c_path);
    if( !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "ListFile::ListFile failure (cant read file)";
        return false;
    }

    QTextStream in(&file);
    QStringList fileNames;

    while(!in.atEnd())
    { fileNames << in.readLine(); }
    file.close();

    QFileInfo info(file);
    QDir dir(info.absolutePath());
    dir.cd("elements");
    fileNames.removeAll("");

    if(fileNames.count() > 0)
    {
        for(int i=0;i<fileNames.count();i++)
        {
            fileNames[i].remove("\\s");
            QString fileName = dir.absoluteFilePath(fileNames[i].toLower());
            c_files << IniFile(fileName);
        }
        return true;
    }
    qDebug() << "ListFile::Listfile failed to read file names from list file";
    return false;
}

bool ListFile::save()
{
    if(c_files.count() > 0)
    {
        for(int i=0;i<c_files.count();i++)
        { c_files[i].save(); }
        return true;
    }
    qDebug() << "ListFile::save() - no files to save";
    return false;
}

IniFile* ListFile::operator[](int i)
{
    return &c_files[i];
}

QList<IniItem *> ListFile::getAll()
{
    QList<IniItem*> all;
    for(int i=0; i<count(); i++)
    { all << c_files[i].getAll(); }
    return all;
}
