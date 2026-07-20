

#include <string>


#include "ZE/Core/task.h"
namespace ZE::FH
{
    struct LoggingConfig
    {
        std::string filename;
        int logLevel;

    };

    enum Log
    {
        DEBUG, WARNING, INFO, ERROR
    };

    class Logger: public Core::Task
    {

    };
}