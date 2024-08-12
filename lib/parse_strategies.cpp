#include "parse_strategies.h"

#include "parse_stack.h"

#include <functional>
#include <map>

static void parse_initialization(std::vector<token>::const_iterator&);
static void parse_assignment(std::vector<token>::const_iterator&);
static uint8_t get_priority(token_t type);

std::map<parse_strategy, std::function<void(std::vector<token>::const_iterator&)>> strategies
{
    {parse_strategy::initialize, parse_initialization},
};

parse_strategy get_parse_strategy(const token& t)
{
    switch (t.type)
    {
        case token_t::integer_keyword:
        case token_t::floating_point_keyword:
        case token_t::boolean_keyword:
            return parse_strategy::initialize;
        default:
            throw "Unimplemented parsing strategy";
    }
}

void execute_strategy(parse_strategy strategy, std::vector<token>::const_iterator& iterator)
{
    std::function<void(std::vector<token>::const_iterator&)> method = strategies.at(strategy);
    method(iterator);
}

void parse_initialization(std::vector<token>::const_iterator& iterator)
{
    while (true)
    {
        const token& current = *iterator;
        ++iterator;

        parse_stack::push(new parse_node(current));

        if (current.type == token_t::assign)
        {
            break;
        }
    }

    parse_node* assign = parse_stack::pop();
    parse_node* id = parse_stack::pop();
    parse_node* type = parse_stack::pop();

    id->left_child = type;
    assign->left_child = id;

    parse_stack::push(assign);

    parse_assignment(iterator);
}

static void parse_assignment(std::vector<token>::const_iterator& iterator)
{
    while (true)
    {
        const token& current = *iterator;
        ++iterator;
        const token& peek = *iterator;
        token_t top = parse_stack::top()->type;

        if (peek.type == token_t::semicolon)
        {
            parse_node* top = parse_stack::top();
            parse_node* child = new parse_node(current);
            
            top->right_child = child;
            child->parent = top;

            ++iterator;
            break;
        }

        if (get_priority(top) <= get_priority(peek.type))
        {
            parse_node* parent = new parse_node(peek);
            parse_node* child = new parse_node(current);
            
            parent->left_child = child;
            child->parent = parent;
            
            parse_stack::push(parent);
        }
        else
        {
            parse_node* top = parse_stack::pop();
            parse_node* child = new parse_node(current);

            top->right_child = child;
            child->parent = top;

            parse_node* parent = new parse_node(peek);
            parent->left_child = top;
            top->parent = parent;

            parse_stack::push(parent);
        }

        ++iterator;
    }

    while (parse_stack::get_size() > 1)
    {
        parse_stack::reduce();
    }
}

static uint8_t get_priority(token_t type)
{
    std::map<token_t, uint8_t> priorities
    {
        {token_t::plus, 1},
        {token_t::minus, 1},
        {token_t::star, 2},
        {token_t::slash, 2},
    };

    if (priorities.contains(type))
    {
        return priorities.at(type);
    }

    return 0;
}
