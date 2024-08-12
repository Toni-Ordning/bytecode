#include "lex.h"

#include <map>
#include <stdexcept>
#include <string>

#include "io.h"

#include <iostream>

const token empty_token{};

const std::map<std::string, token_t> keywords
{
    {"int", token_t::integer_keyword},
    {"float", token_t::floating_point_keyword},
    {"bool", token_t::boolean_keyword},
    {"true", token_t::true_keyword},
    {"false", token_t::false_keyword},
};

std::vector<token> lex(const char* filename)
{
    std::vector<unsigned char> bytes = read_file(filename);
    std::vector<token> tokens = lex_tokens(bytes);

    return tokens;
}

void read_word(token& t, std::vector<unsigned char>::const_iterator& iterator,
    std::vector<unsigned char>::const_iterator end)
{
    unsigned char c = *iterator;
    while (isalnum(c))
    {
        t.value.push_back(c);
        ++iterator;

        if (iterator == end)
        {
            break;
        }

        c = *iterator;
    }

    if (keywords.contains(t.value))
    {
        t.type = keywords.at(t.value);
    }
    else
    {
        t.type = token_t::variable;
    }
}

void read_number(token& t, std::vector<unsigned char>::const_iterator& iterator,
    std::vector<unsigned char>::const_iterator end)
{
    unsigned char c = *iterator;
    while (isdigit(c) || c == '.')
    {
        t.value.push_back(c);
        ++iterator;

        if (iterator == end)
        {
            break;
        }

        c = *iterator;
    }

    t.type = token_t::number;
}

void ignore_whitespace(std::vector<unsigned char>::const_iterator& iterator,
    std::vector<unsigned char>::const_iterator end)
{
    unsigned char c = *iterator;
    while (isspace(c))
    {
        ++iterator;

        if (iterator == end)
        {
            break;
        }

        c = *iterator;
    }
}

void read_token(token& t, std::vector<unsigned char>::const_iterator& iterator,
    std::vector<unsigned char>::const_iterator end)
{
    unsigned char c = *iterator;
    if (c == '=')
    {
        t.value = c;
        t.type = token_t::assign;
        
        ++iterator;
        c = *iterator;
    }
    else if (c == ';')
    {
        t.value = c;
        t.type = token_t::semicolon;
        
        ++iterator;
        c = *iterator;
    }
    else if (c == '+')
    {
        t.value = c;
        t.type = token_t::plus;
        
        ++iterator;
        c = *iterator;
    }
    else if (c == '-')
    {
        t.value = c;
        t.type = token_t::minus;
        
        ++iterator;
        c = *iterator;
    }
    else if (c == '*')
    {
        t.value = c;
        t.type = token_t::star;
        
        ++iterator;
        c = *iterator;
    }
    else if (c == '/')
    {
        t.value = c;
        t.type = token_t::slash;
        
        ++iterator;
        c = *iterator;
    }
    else
    {
        throw std::runtime_error{"Unrecognized token " + c};
    }
}

std::vector<token> lex_tokens(const std::vector<unsigned char>& bytes)
{
    std::vector<token> tokens;
    std::vector<unsigned char>::const_iterator iterator = bytes.cbegin();
    while (iterator != bytes.cend())
    {
        int c = *iterator;
        token t;
        if (isalpha(c))
        {
            read_word(t, iterator, bytes.cend());
        }
        else if (isdigit(c))
        {
            read_number(t, iterator, bytes.cend());
        }
        else if (isspace(c))
        {
            ignore_whitespace(iterator, bytes.cend());
        }
        else
        {
            read_token(t, iterator, bytes.cend()); 
        }

        if (t != empty_token)
        {
            tokens.push_back(t);
        }
    }

    return tokens;
}

std::vector<token> lex_tokens(const std::string& input)
{
    std::vector<unsigned char> bytes;
    for (unsigned char c : input)
    {
        bytes.push_back(c);
    }

    return lex_tokens(bytes);
}
