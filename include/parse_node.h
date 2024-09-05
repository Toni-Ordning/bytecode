#pragma once

#include "token.h"

#include <string>

struct parse_node
{
    parse_node() = default;
    parse_node(const token& t);

    void set_child(parse_node* child);

    token_t type = token_t::unknown;
    parse_node* left_child = nullptr;
    parse_node* right_child = nullptr;
    parse_node* parent = nullptr;
    std::string value;
};

parse_node* find_root(parse_node* node);
