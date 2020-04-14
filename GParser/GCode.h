#ifndef GCODE_H
#define GCODE_H

#include <stdint.h>

struct GCode
{
    uint8_t opcode;

    uint32_t f;

    int32_t x;
    int32_t y;
    int32_t z;

    bool mx;
    bool my;
    bool mz;

    friend GCode& operator*=(GCode& self, const int num);
};

#endif
