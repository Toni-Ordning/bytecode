#pragma once

#include "parse_node.h"

namespace parse_stack
{
    parse_node* pop();
    parse_node* top();
    void push(parse_node* node);
    bool is_empty();
    uint64_t get_size();
    void reduce();
    void free();
}
