#include "logger.h"

#ifdef DEBUG_MODE
void logToFile(const std::string &message)
{
    const std::string &filename = "D:\\DMSI_log.txt";

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    struct tm *ti;
    std::time(&time);
    ti = std::localtime(&time);

    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open())
    {
        file << std::put_time(ti, "%Y-%m-%d %H:%M:%S : ") << message << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to open file for logging" << std::endl;
    }
}
#else
void logToFile(const std::string &message) {}
#endif
