#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>

#define FUG_LOG (fug::Log::instance())

namespace fug {

    enum class LogLevel {
        Debug,
        Info,
        Warn,
        Error,
    };

    class LogInput {
    public:
        LogInput(bool doLog, FILE* logFp);
        void operator()(const char *fmt, ...);
        template <typename T>
        LogInput& operator<<(const T& x)
        {
            std::stringstream s;

            if (!_doLog)
                return *this;

            s << x;
            fputs(s.str().c_str(), _logFp);
            return *this;
        }

        LogInput& operator<<(std::ostream& (*f)(std::ostream& o));

    private:
        bool _doLog;
        FILE* _logFp;
    };

    class Log {
    public:
        Log(FILE* logFp);
        static Log& instance(void);
        void setLogLevel(LogLevel minLogLevel);
        LogInput& operator()(LogLevel logLevel);

    private:
        LogInput _log;
        LogInput _dummyLog;
        LogLevel _minLogLevel;
    };

};

#endif // LOGGER_HPP
