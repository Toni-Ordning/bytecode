#include "parse_node.h"

#include <stdexcept>

parse_node::parse_node(const token& t)
{
    type = t.type;
    value = t.value;
}

void parse_node::set_child(parse_node* child)
{
    if (!left_child)
    {
        left_child = child;
    }
    else if (!right_child)
    {
        right_child = child;
    }
    else
    {
        throw std::logic_error{"Cannot set child node: Left and right child exist"};
    }
}

parse_node* find_root(parse_node* node)
{
    parse_node* root = node;
    while (root->parent != nullptr)
    {
        root = root->parent;
    }

    return root;
}
