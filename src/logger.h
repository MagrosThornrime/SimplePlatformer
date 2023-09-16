#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <utility>

enum LogLevel{info, warning, error};

class Logger{
    std::string path;
    bool consoleUsed;
    LogLevel level;

    void logToFile(const std::string& text);
    void logToConsole(const std::string& text);
    std::string prepareMessage(const std::string& text);

public:
    explicit Logger(LogLevel level=error): path(), consoleUsed(true), level(level) {}

    explicit Logger(std::string  path, bool consoleUsed=true, LogLevel level=info)
    : path(std::move(path)), consoleUsed(consoleUsed), level(level) {}

    void log(const std::string& text, LogLevel level);

};