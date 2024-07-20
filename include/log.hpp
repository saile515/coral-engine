#pragma once

#include <cstdlib>
#include <format>
#include <iostream>

namespace coral
{

template <class... Arguments>
void info(std::format_string<Arguments...> format, Arguments &&...arguments)
{
    std::cout << "\033[37m[INFO] "
              << std::vformat(format.get(), std::make_format_args(arguments...))
              << "\033[0m\n";
}

template <class... Arguments>
void warning(std::format_string<Arguments...> format, Arguments &&...arguments)
{
    std::cout << "\033[33m[WARNING] "
              << std::vformat(format.get(), std::make_format_args(arguments...))
              << "\033[0m\n";
}

template <class... Arguments>
void error(std::format_string<Arguments...> format, Arguments &&...arguments)
{
    std::cout << "\033[31m[ERROR] "
              << std::vformat(format.get(), std::make_format_args(arguments...))
              << "\033[0m\n";
}

template <class... Arguments>
void fatal(std::format_string<Arguments...> format, Arguments &&...arguments)
{
    std::cout << "\033[1;31m[FATAL] "
              << std::vformat(format.get(), std::make_format_args(arguments...))
              << "\033[0m\n";
    std::exit(EXIT_FAILURE);
}

} // namespace coral
