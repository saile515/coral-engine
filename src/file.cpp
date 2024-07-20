#include "file.hpp"

#include "log.hpp"
#include <filesystem>
#include <fstream>

namespace coral
{

std::string read_file(std::string path)
{
    if (!std::filesystem::exists(path))
    {
        error("File \"{}\" does not exist.", path);
        return "";
    }

    std::ifstream file(path);
    std::stringstream filebuffer;
    filebuffer << file.rdbuf();

    return filebuffer.str();
}

} // namespace coral
