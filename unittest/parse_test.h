#pragma once

#include <gtest/gtest.h>

#include "lex.h"
#include "parse.h"
#include "parse_stack.h"

class parse_test : public testing::Test
{
    protected:
        parse_node* root = nullptr;

        uint64_t get_node_count(parse_node* node, token_t type)
        {
            uint64_t count = 0;
            if (node->left_child != nullptr)
            {
                count += get_node_count(node->left_child, type);
            }
            if (node->right_child != nullptr)
            {
                count += get_node_count(node->right_child, type);
            }
            
            if (node->type == type)
            {
                ++count;
            }

            return count;
        }

        void TearDown() override
        {
            parse_stack::free();
        }
};
