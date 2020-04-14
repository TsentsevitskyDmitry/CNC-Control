#include "GStreamer/GSerialStream/Serial.h"

bool Serial::open(string port, int baud)
{
    return this->port.open(port, baud);
}

void Serial::close()
{
    this->port.close();
}

ostream& Serial::write( const char_type* s, std::streamsize count)
{
    port.write(s, static_cast<unsigned long>(count));
    return *this;
}

bool Serial::write(string data)
{
    return port.write(data);
}

bool Serial::try_read(string &buff)
{
    return this->port.try_read(buff);
}

Serial &operator <<(Serial &ser, GPacket &packet)
{
    ser.write(reinterpret_cast<const char*>(&packet.opcode), 1);

    ser.write(reinterpret_cast<const char*>(&packet.xDist), 4);
    ser.write(reinterpret_cast<const char*>(&packet.yDist), 4);
    ser.write(reinterpret_cast<const char*>(&packet.zDist), 4);

    ser.write(reinterpret_cast<const char*>(&packet.xVel), 2);
    ser.write(reinterpret_cast<const char*>(&packet.yVel), 2);
    ser.write(reinterpret_cast<const char*>(&packet.zVel), 2);

    return ser;
}
