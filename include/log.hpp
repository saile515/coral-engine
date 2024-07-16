#pragma once

#include <cstdlib>
#include <format>
#include <iostream>

namespace coral {

template <class... Arguments>
void info(std::format_string<Arguments...> format, Arguments &&...arguments) {
    std::cout << "\033[37m[INFO] " << std::format(format, arguments...)
              << "\033[0m\n";
}

template <class... Arguments>
void warning(std::format_string<Arguments...> format,
             Arguments &&...arguments) {
    std::cout << "\033[33m[WARNING] " << std::format(format, arguments...)
              << "\033[0m\n";
}

template <class... Arguments>
void error(std::format_string<Arguments...> format, Arguments &&...arguments) {
    std::cout << "\033[31m[ERROR] " << std::format(format, arguments...)
              << "\033[0m\n";
}

template <class... Arguments>
void fatal(std::format_string<Arguments...> format, Arguments &&...arguments) {
    std::cout << "\033[1;31m[FATAL] " << std::format(format, arguments...)
              << "\033[0m\n";
    std::exit(EXIT_FAILURE);
}

} // namespace coral
