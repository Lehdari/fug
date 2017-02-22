#include <cstdarg>
#include <cstdio>

#include "Core/Log.hpp"

fug::LogInput::LogInput(bool doLog, FILE* logFp) :
    _doLog(doLog),
    _logFp(logFp)
{
}

void fug::LogInput::operator()(const char *fmt, ...)
{
    va_list args;

    if (!_doLog)
        return;

    va_start(args, fmt);
    vfprintf(_logFp, fmt, args);
    va_end(args);
}

fug::Log::Log(FILE* logFp) :
    _log(true, logFp),
    _dummyLog(false, logFp),
    _minLogLevel(fug::LogLevel::Error)
{
}

fug::Log& fug::Log::instance(void)
{
    static fug::Log log(stderr);
    return log;
}

void fug::Log::setLogLevel(fug::LogLevel minLogLevel)
{
    _minLogLevel = minLogLevel;
}

fug::LogInput& fug::Log::operator()(fug::LogLevel logLevel)
{
    if (logLevel < _minLogLevel)
        return _dummyLog;
    return _log;
}

fug::LogInput& fug::LogInput::operator<<(std::ostream& (*f)(std::ostream& o))
{
    std::stringstream s;

    if (!_doLog)
        return *this;

    s << f;
    fputs(s.str().c_str(), stderr);
    return *this;
}
