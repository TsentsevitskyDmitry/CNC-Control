#include "GParser/GCode.h"

GCode &operator*=(GCode &self, const int num)
{
    self.x *= num;
    self.y *= num;
    self.z *= num;

    return self;
}
