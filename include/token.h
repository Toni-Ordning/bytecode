#pragma once

#include <string>

enum class token_t
{
    assign,
    boolean_keyword,
    closed_curly_bracket,
    closed_paranthesis,
    elif_keyword,
    else_keyword,
    false_keyword,
    floating_point_keyword,
    if_keyword,
    integer_keyword,
    minus,
    number,
    open_curly_bracket,
    open_paranthesis,
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
