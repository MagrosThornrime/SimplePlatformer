#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

enum LogLevel{info, warning, error};

class Logger{
    std::string path{};
    bool consoleUsed = true;
    LogLevel level;

    void logToFile(const std::string& text);
    void logToConsole(const std::string& text);
    std::string prepareMessage(const std::string& text);

public:
    Logger(LogLevel level=error);
    Logger(const std::string& path, bool consoleUsed=true, LogLevel level=info);
    void log(const std::string& text, LogLevel level);

};