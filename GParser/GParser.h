#ifndef GPARSER_H
#define GPARSER_H

#include "GParser/GCode.h"
#include <QString>
#include <QVector>
#include <QFile>

const float FLOAT_TO_INT_PERSITION = 1000.0;

class GParser
{
private:
    QFile file;
    QVector<GCode> codes;
    void parseLine(QString& line);


public:
    GParser(QString path);
    ~GParser();

    bool parse();
    void normalize();
    QVector<GCode>& getCodes();
};

#endif
