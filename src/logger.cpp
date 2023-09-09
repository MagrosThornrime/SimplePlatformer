
#include "logger.h"


std::string Logger::prepareMessage(const std::string &text) {
    namespace clk = std::chrono;
    std::time_t now = clk::system_clock::to_time_t(clk::system_clock::now());
    std::string timestamp = std::ctime(&now);
    timestamp.pop_back();
    return timestamp + " : " + text;

}

void Logger::logToConsole(const std::string &text) {
    std::cout << text << std::endl;
}

void Logger::logToFile(const std::string &text) {
    std::ofstream logFile;

    logFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try{
        logFile.open(path.c_str(), std::ios_base::app);
        logFile << text << std::endl;
        logFile.close();
    }
    catch(std::ofstream::failure& e) {
        logToConsole(prepareMessage("failed to log to file"));
    }
}

void Logger::log(const std::string &text, LogLevel level) {
    if(level == warning and this->level == info)
        return;
    if(level == error and this->level != error)
        return;

    std::string toLog = prepareMessage(text);
    if(consoleUsed)
        logToConsole(toLog);
    if(!path.empty())
        logToFile(toLog);
}

Logger::Logger(LogLevel level) {
    this->level = level;
}

Logger::Logger(const std::string &path, bool consoleUsed, LogLevel level) {
    this->path = path;
    this->consoleUsed = consoleUsed;
    this->level = level;
}