#ifndef GPACKETCREATOR_H
#define GPACKETCREATOR_H

#include "GPacker/GPacket.h"
#include "GParser/GCode.h"

const float AXIS_DEFAULT_MAX_SPEED = 500.0f;

class PacketCreator
{
private:
    float axis_max_speed;

    void PerfomLeneralInterpolating(GPacket& packet, GCode& code);

public:
    PacketCreator();

    GPacket create(GCode& code);

};

#endif
