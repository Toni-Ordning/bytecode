#include "parse.h"

#include "parse_stack.h"
#include "parse_strategies.h"

#include <cassert>
#include <map>
#include <stack>

parse_node* parse_tokens(const std::vector<token>& tokens)
{
    if (tokens.size() < 2)
    {
        return nullptr;
    }

    std::vector<token>::const_iterator iterator = tokens.cbegin();
    while (iterator != tokens.cend())
    {
        token current = *iterator;
        parse_strategy strategy = get_parse_strategy(current);
        execute_strategy(strategy, iterator);
    }
    
    assert(iterator == tokens.cend());

    parse_node* top = parse_stack::top();
    parse_node* root = find_root(top);
    return root;
}
