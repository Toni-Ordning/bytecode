#include <cassert>
#include <iostream>

#include "lex.h"
#include "parse.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " {input}" << std::endl;
        return 1;
    }

    std::vector<token> tokens;
    try
    {
        tokens = lex(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (tokens.empty())
    {
        std::cout << "No tokens lexed. Is input file empty?" << std::endl;
        return 0;
    }

    try
    {
        assert(!tokens.empty());
        parse_node* root = parse_tokens(tokens);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Parsing failed\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}
