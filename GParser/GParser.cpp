#include "GParser/GParser.h"
#include <limits>

GParser::GParser(QString path) : file(path)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
}

GParser::~GParser()
{
    file.close();
}

QVector<GCode> &GParser::getCodes()
{
    return codes;
}

bool GParser::parse()
{
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString sline = QString(line);
        parseLine(sline);
    }
    return codes.size();
}

void GParser::parseLine(QString &line)
{
    QStringList parts = line.split(" ");
    bool data = true;
    GCode code = {};

    foreach (auto part, parts)
    {
        switch (part.toStdString()[0]) {
        case 'G':
            code.opcode = static_cast<uint8_t>(part.mid(1).toUInt());
            break;

        case 'F':
            code.f = static_cast<uint32_t>(part.mid(1).toUInt());
            break;

        case 'X':
            code.x = static_cast<int32_t>(part.mid(1).toFloat() * FLOAT_TO_INT_PERSITION);
            code.mx = true;
            break;

        case 'Y':
            code.y = static_cast<int32_t>(part.mid(1).toFloat() * FLOAT_TO_INT_PERSITION);
            code.my = true;
            break;

        case 'Z':
            code.z = static_cast<int32_t>(part.mid(1).toFloat() * FLOAT_TO_INT_PERSITION);
            code.mz = true;
            break;

        default:
            data = false;
            break;
        }
    }

    if(data)
        codes.push_back(code);
}


void GParser::normalize()
{
    int32_t minX = INT32_MAX, minY = INT32_MAX;

    foreach (auto code, codes)
    {
        if(code.x < minX && code.x)
            minX = code.x;
        if(code.y < minY && code.y)
            minY = code.y;
    }

    for (int i = 0; i < codes.size(); ++i)
    {
        if(codes[i].x) codes[i].x -= minX;
        if(codes[i].y) codes[i].y -= minY;
    }
}
