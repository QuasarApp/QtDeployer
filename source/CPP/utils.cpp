#include "utils.h"
#include <QFile>
#include <QFileInfo>


QString Utils::getVersion(){

    QFileInfo f(":/snapcraft/snapcraft");
    QFile file(f.absoluteFilePath());

    if(file.open(QIODevice::ReadOnly)){
        QString yamlFile = file.readAll();
        file.close();

        yamlFile.replace(" ", "");
        yamlFile.replace("'", "");

        int tempIndex = yamlFile.indexOf(QRegExp("version:"));
        if(tempIndex < 0){
            return "error in yaml version";
        }
        int beginTarget = tempIndex + 8;

        tempIndex = yamlFile.indexOf("\n", beginTarget);
        int longTraget = -1;

        if(tempIndex >= 0){
            longTraget = tempIndex - beginTarget;
        }

        return yamlFile.mid(beginTarget, longTraget);
    }

    return  file.errorString();
}
