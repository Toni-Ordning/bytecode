#include "parse_strategies.h"

#include "parse_stack.h"

#include <functional>
#include <map>

static void close_block(std::vector<token>::const_iterator&);
static void open_block(std::vector<token>::const_iterator&);
static void parse_initialization(std::vector<token>::const_iterator&);
static void parse_assignment(std::vector<token>::const_iterator&);
static void parse_if_statement(std::vector<token>::const_iterator&);
static void parse_boolean_expression(std::vector<token>::const_iterator& iterator);
static uint8_t get_priority(token_t type);

std::map<parse_strategy, std::function<void(std::vector<token>::const_iterator&)>> strategies
{
    {parse_strategy::close_block, close_block},
    {parse_strategy::initialize, parse_initialization},
    {parse_strategy::if_statement, parse_if_statement},
    {parse_strategy::open_block, open_block},
};

parse_strategy get_parse_strategy(const token& t)
{
    switch (t.type)
    {
        case token_t::integer_keyword:
        case token_t::floating_point_keyword:
        case token_t::boolean_keyword:
            return parse_strategy::initialize;
        case token_t::if_keyword:
            return parse_strategy::if_statement;
        case token_t::open_curly_bracket:
            return parse_strategy::open_block;
        case token_t::closed_curly_bracket:
            return parse_strategy::close_block;
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

static void parse_if_statement(std::vector<token>::const_iterator& iterator)
{
    parse_node* if_node = new parse_node(*iterator);
    ++iterator;
    
    if (!parse_stack::is_empty())
    {
        if_node->parent = parse_stack::top();
        parse_stack::top()->set_child(if_node);
    }
    
    parse_stack::push(if_node);

    parse_boolean_expression(iterator);
}

static void parse_boolean_expression(std::vector<token>::const_iterator& iterator)
{
    parse_node* node = new parse_node(*iterator);
    ++iterator;

    if (iterator->type == token_t::open_curly_bracket)
    {
        parse_stack::top()->set_child(node);
        node->parent = parse_stack::top();
    }
    else
    {
        throw "Not implemented";
    }
}

static void open_block(std::vector<token>::const_iterator& iterator)
{
    ++iterator;
}

static void close_block(std::vector<token>::const_iterator& iterator)
{
    ++iterator;
}
