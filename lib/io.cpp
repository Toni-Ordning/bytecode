#include "io.h"

#include <fstream>
#include <stdexcept>

std::vector<unsigned char> read_file(const char* filename)
{
    std::ifstream input{filename};
    if (!input.good())
    {
        input.close();
        throw std::runtime_error{std::string{"Failed to open input stream to "} + std::string{filename}};
    }

    std::vector<unsigned char> bytes;
    while (input.peek() != EOF)
    {
        bytes.push_back(static_cast<unsigned char>(input.get()));
    }

    return bytes;
}
