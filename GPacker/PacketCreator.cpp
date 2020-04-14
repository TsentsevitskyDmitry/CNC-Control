#include "GPacker/PacketCreator.h"
#include <algorithm>
#include <cmath>


PacketCreator::PacketCreator()
{
    axis_max_speed = AXIS_DEFAULT_MAX_SPEED;
}

void PacketCreator::PerfomLeneralInterpolating(GPacket &packet, GCode &code)
{
    float max = std::max({code.x, code.y, code.z});

    packet.xVel = static_cast<uint16_t>(abs(code.x) / max * axis_max_speed);
    packet.yVel = static_cast<uint16_t>(abs(code.y) / max * axis_max_speed);
    packet.zVel = static_cast<uint16_t>(abs(code.z) / max * axis_max_speed);
}

GPacket PacketCreator::create(GCode &code)
{
    const int DEL = 100;

    GPacket packet;
    PerfomLeneralInterpolating(packet, code);
    packet.xDist = code.x / DEL;
    packet.yDist = code.y / DEL;
    packet.zDist = code.z / DEL;

    return packet;
}
