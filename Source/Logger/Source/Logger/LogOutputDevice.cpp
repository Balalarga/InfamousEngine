#include "LogOutputDevice.h"
#include <iostream>

namespace Inf
{
void ILogOutputDevice::SetMinLogLevel(LogLevel level)
{
    _minLevel = level;
}

void CmdOutput::Write(const LogLevel& level, std::string &&text)
{
    if (level == LogLevel::Error)
        std::cerr << text << std::endl;
    else
        std::cout << text << std::endl;
}
}
