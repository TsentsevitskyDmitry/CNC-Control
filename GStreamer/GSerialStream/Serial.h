#ifndef SERIAL_H
#define SERIAL_H

#include "GStreamer/GSerialStream/SerialAPI/SerialAPI.h"
#include "GPacker/GPacket.h"
#include <ostream>

class Serial : public std::ostream
{
private:
    SerialPort port;

public:
    bool open(string port, int baud);
    void close();

    ostream& write( const char_type* s, std::streamsize count);
    bool write(string data);
    bool try_read(string& buff);

    friend Serial& operator << (Serial& os, GPacket& packet);
};

#endif
