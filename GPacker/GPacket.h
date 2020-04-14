#ifndef GPACKET_H
#define GPACKET_H

#include <stdint.h>
#include <ostream>

struct GPacket
{
    uint8_t opcode;

    int32_t xDist;
    int32_t yDist;
    int32_t zDist;

    int16_t xVel;
    int16_t yVel;
    int16_t zVel;
};

#endif
