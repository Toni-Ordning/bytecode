#include "parse_test.h"

class parse_if_statement_test : public parse_test {};

TEST_F(parse_if_statement_test, parses_simple_if_statement)
{
    std::vector<token> tokens = lex_tokens("if true { }");
    root = parse_tokens(tokens);

    ASSERT_TRUE(root != nullptr);
    EXPECT_EQ(root->type, token_t::if_keyword);

    parse_node* child = root->left_child;
    ASSERT_TRUE(child != nullptr);
    EXPECT_EQ(child->type, token_t::true_keyword);
}

TEST_F(parse_if_statement_test, parses_simple_if_statement2)
{
    std::vector<token> tokens = lex_tokens("if false { }");
    root = parse_tokens(tokens);

    ASSERT_TRUE(root != nullptr);
    EXPECT_EQ(root->type, token_t::if_keyword);

    parse_node* child = root->left_child;
    ASSERT_TRUE(child != nullptr);
    EXPECT_EQ(child->type, token_t::false_keyword);
}
