#ifndef UTILS_H
#define UTILS_H
#include <QString>

class Utils
{
private:
    Utils() = delete;
public:
    static QString getVersion();
    static QString getDescription();
    static QString getPublicher();
};

#endif // UTILS_H
