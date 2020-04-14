#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class SerialPort
{
private:
    static const int TIMEOUT = 10;

	HANDLE serialHandle;
	int currentBaud;

public:
    SerialPort() :  serialHandle(nullptr), currentBaud(0) {}
	~SerialPort();

    bool open(string port, int baud);
    void close();

    bool connected();
    int getBaud();

    bool write(string& data);
    bool write(const char* s, unsigned long  count);
    bool try_read(string& buff);
};

