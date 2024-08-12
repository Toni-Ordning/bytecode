#include "parse_stack.h"

#include <map>
#include <stack>

std::stack<parse_node*> stack;
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
namespace parse_stack
{
    static void free_node(parse_node* node);
    
    parse_node* pop()
    {
        parse_node* top = stack.top();
        stack.pop();
        return top;
    }
    
    parse_node* top()
    {
        return stack.top();
    }

    void push(parse_node* node)
    {
        stack.push(node);
    }
    
    bool is_empty()
    {
        return stack.empty();
    }
    
    uint64_t get_size()
    {
        return stack.size();
    }
    
    void reduce()
    {
        parse_node* first = parse_stack::pop();
        parse_node* second = parse_stack::pop();
        if (parse_stack::is_empty())
        {
            if (first->left_child != nullptr && first->right_child != nullptr &&
                second->left_child != nullptr && second->right_child != nullptr)
            {
                parse_node* node = new parse_node;
                node->left_child = second;
                second->parent = node;
                node->right_child = first;
                first->parent = node;
                parse_stack::push(node);
                return;
            }

            second->right_child = first;
            first->parent = second;
            parse_stack::push(second);
            
            return;
        }
        
        second->right_child = first;
        first->parent = second;
        parse_stack::push(second);
    }

    void free()
    {
        if (stack.empty())
        {
            return;
        }
        
        parse_node* top = stack.top();
        free_node(top);
        stack.pop();
    }

    void free_node(parse_node* node)
    {
        if (node->left_child != nullptr)
        {
            free_node(node->left_child);
        }
        if (node->right_child != nullptr)
        {
            free_node(node->right_child);
        }

        delete node;
    }
}
