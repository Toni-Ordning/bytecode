#pragma once

#include <string>

enum class token_t
{
    assign,
    boolean_keyword,
    false_keyword,
    floating_point_keyword,
    integer_keyword,
    minus,
    number,
    plus,
    semicolon,
    slash,
    star,
    true_keyword,
    unknown,
    variable,
};

struct token
{
    token_t type = token_t::unknown;
    std::string value;

    bool operator == (const token& other);
};
