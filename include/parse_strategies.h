#pragma once

#include "token.h"

#include <vector>

enum class parse_strategy
{
    close_block,
    if_statement,
    initialize,
    open_block,
};

parse_strategy get_parse_strategy(const token& t);
void execute_strategy(parse_strategy strategy, std::vector<token>::const_iterator& iterator);
