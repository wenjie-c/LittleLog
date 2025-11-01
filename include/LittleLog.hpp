#ifndef LOGGER_H_
#define LOGGER_H_

#include <bits/types/FILE.h>
#include <iostream>
#include <iterator>
#include <string>
#include <chrono>
#include <mutex>
#include <ctime>
#include<fstream>


using namespace std;

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger
{
    protected:
    mutex logMutex;
    string logLevelToString(LogLevel level)
    {
        switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
            case LogLevel::INFO:
            return "INFO";
            case LogLevel::WARNING:
            return "WARNING";
            case LogLevel::ERROR:
            return "ERROR";
            case LogLevel::CRITICAL:
            return "CRITICAL";
            default:
                throw -1;
        }
    }

    public:
    virtual ~Logger() {}
    virtual void log(const string &messaje, LogLevel level, const char * file, int line) = 0;
    
    #define LOG(logger, level, message) (logger).log(message, level, __FILE__, __LINE__)
#define LOG_DEBUG(logger, message) LOG(logger, LogLevel::DEBUG, message)
#define LOG_INFO(logger, message) LOG(logger, LogLevel::INFO, message)
#define LOG_WARNING(logger, message) LOG(logger, LogLevel::WARNING, message)
#define LOG_ERROR(logger, message) LOG(logger, LogLevel::ERROR, message)
#define LOG_CRITICAL(logger, message) LOG(logger, LogLevel::CRITICAL, message)

};

/**
 * @brief Console logger, outputs everything in console. 
 * 
 */
class ConsoleLogger : Logger
{
    public:
    void log(const string &messaje, LogLevel level, const char * file, int line) override 
    {
        lock_guard<std::mutex> guard(logMutex);
        time_t t = time(0);
        string time = string(asctime(localtime(&t)));
        time.pop_back(); // erasing last newline
        time[sizeof(time) - 1] = '\0';
        string slevel = logLevelToString(level);

        printf("%s [%s] %s %i: %s\n" , time.c_str(), slevel.c_str(), file, line,messaje.c_str());
    }
};

/**
 * @brief File logger, outputs everything in file. It closes the ofstream when it is destroyed.
 * 
 */
class FileLogger : Logger
{
    ofstream logFile;
    public:
    #define LOG_BUFFER 1024
    
    FileLogger(const string & path)
    {
        logFile.open(path, std::ios::out | std::ios::app);
        if (!logFile.is_open()) 
    {
        std::cerr << "Failed to open log file: " << path << std::endl;
    }
    }
    void log(const string &messaje, LogLevel level, const char * file, int line) override 
    {
        lock_guard<std::mutex> guard(logMutex);
        time_t t = time(0);
        string time = string(asctime(localtime(&t)));
        time.pop_back(); // erasing last newline
        time[sizeof(time) - 1] = '\0';
        string slevel = logLevelToString(level);
        char buffer[LOG_BUFFER] = {0}; 
        sprintf(buffer,"%s [%s] %s %i: %s\n" , time.c_str(), slevel.c_str(), file, line,messaje.c_str());
        logFile << buffer;
    }
    ~FileLogger()
    {
        logFile.close();
    }
};


#endif // LOGGER_H_