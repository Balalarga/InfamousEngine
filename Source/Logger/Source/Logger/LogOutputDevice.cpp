#include "LogOutputDevice.h"
#include <iostream>

namespace Unk
{
void ILogOutputDevice::SetMinLogLevel(LogLevel level)
{
    _minLevel = level;
}

void CmdOutput::Write(const LogLevel& level, std::string &&text)
{
    std::cout << text << std::endl;
}
}
