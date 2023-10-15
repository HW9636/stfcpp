#pragma once

#include <iostream>

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
        inline static void log(const std::string& message, Color color) {
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
#endif
        }

    public:
        inline static void error(const std::string& message) { log(message, Color::RED); }
        inline static void warn(const std::string& message) { log(message, Color::YELLOW); }
        inline static void fine(const std::string& message) { log(message, Color::GREEN); }
        inline static void normal(const std::string& message) { log(message, Color::NORMAL); }
	};
}