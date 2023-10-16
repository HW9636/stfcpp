#pragma once

#include <iostream>
#include <queue>

#ifdef _WIN32
	#include <Windows.h>
#endif

namespace stfcpp
{
    enum class Color
    {
        RED,
        GREEN,
        YELLOW,
        NORMAL
    };

	class logger
	{
   
    private:
        inline static void queue(const std::string& message, Color color) {
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD savedAttributes;

            // Save current attributes
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            savedAttributes = consoleInfo.wAttributes;

            switch (color) {
            case Color::RED:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                break;
            case Color::GREEN:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                break;
            case Color::YELLOW:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                break;
            case Color::NORMAL:
                break;
            }

            std::cout << message << std::endl;

            // Restore original attributes
            SetConsoleTextAttribute(hConsole, savedAttributes);
#elif defined(__APPLE__) || defined(__LINUX__)
            switch (color) {
            case Color::RED:
                std::cout << "\033[31m";
                break;
            case Color::GREEN:
                std::cout << "\033[32m";
                break;
            case Color::YELLOW:
                std::cout << "\033[33m";
                break;
            case Color::NORMAL:
                std::cout << "\033[0m";
                break;
            }

            std::cout << message << "\033[0m" << std::endl;
#else
#error "Unsupported platform"
#endif
        }

    public:
        inline static void error(const std::string& message) { queue(message, Color::RED); }
        inline static void warn(const std::string& message) { queue(message, Color::YELLOW); }
        inline static void fine(const std::string& message) { queue(message, Color::GREEN); }
        inline static void normal(const std::string& message) { queue(message, Color::NORMAL); }
	};
}