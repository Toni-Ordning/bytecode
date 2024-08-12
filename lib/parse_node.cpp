#include "parse_node.h"

parse_node::parse_node(const token& t)
{
    type = t.type;
    value = t.value;
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
