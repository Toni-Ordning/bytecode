#pragma once

#include "parse_node.h"

#include <vector>

parse_node* parse_tokens(const std::vector<token>& tokens);
