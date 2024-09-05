#include "parse_test.h"

class parse_assignment_test : public parse_test {};

TEST_F(parse_assignment_test, parsing_no_tokens_does_not_return_root_token)
{
    root = parse_tokens({});
}

TEST_F(parse_assignment_test, parses_integer_assignment_expression)
{
    std::vector<token> tokens = lex_tokens("int i = 5;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->left_child;
    ASSERT_EQ(node->type, token_t::variable);

    node = node->left_child;
    ASSERT_EQ(node->type, token_t::integer_keyword);

    node = root->right_child;
    ASSERT_EQ(node->type, token_t::number);
    EXPECT_EQ(node->value, "5");
}

TEST_F(parse_assignment_test, parses_floating_point_assignment_expression)
{
    std::vector<token> tokens = lex_tokens("float f = 5.0;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->left_child;
    ASSERT_EQ(node->type, token_t::variable);

    node = node->left_child;
    ASSERT_EQ(node->type, token_t::floating_point_keyword);

    node = root->right_child;
    ASSERT_EQ(node->type, token_t::number);
    EXPECT_EQ(node->value, "5.0");
}

TEST_F(parse_assignment_test, parses_boolean_assignment_expression)
{
    std::vector<token> tokens = lex_tokens("bool b = true;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->left_child;
    ASSERT_EQ(node->type, token_t::variable);

    node = node->left_child;
    ASSERT_EQ(node->type, token_t::boolean_keyword);

    node = root->right_child;
    ASSERT_EQ(node->type, token_t::true_keyword);
    EXPECT_EQ(node->value, "true");
}

TEST_F(parse_assignment_test, parsing_multiple_assignment_expressions_produces_correct_amount_of_tokens)
{
    std::stringstream input;
    input << "int i = 5;";
    input << "int j = 7;";
    input << "int k = 12;";
    std::vector<token> tokens = lex_tokens(input.str());
    root = parse_tokens(tokens);

    EXPECT_EQ(get_node_count(root, token_t::assign), 3);
    EXPECT_EQ(get_node_count(root, token_t::integer_keyword), 3);
    EXPECT_EQ(get_node_count(root, token_t::variable), 3);
    EXPECT_EQ(get_node_count(root, token_t::number), 3);
}

TEST_F(parse_assignment_test, parsing_multiple_assignments_produces_tree_in_correct_order)
{
    std::stringstream input;
    input << "int i = 5;";
    input << "int j = 7;";
    input << "int k = 12;";
    std::vector<token> tokens = lex_tokens(input.str());
    root = parse_tokens(tokens);

    ASSERT_TRUE(root->right_child != nullptr);
    EXPECT_EQ(root->right_child->type, token_t::assign);
    
    ASSERT_TRUE(root->left_child != nullptr);
    parse_node* node = root->left_child;

    ASSERT_TRUE(node->right_child != nullptr);
    EXPECT_EQ(node->right_child->type, token_t::assign);

    ASSERT_TRUE(node->left_child != nullptr);
    EXPECT_EQ(node->left_child->type, token_t::assign);
}

TEST_F(parse_assignment_test, parses_complex_integer_assignment_expression_1)
{
    std::vector<token> tokens = lex_tokens("int i = 5 + 7 * 9;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->right_child;
    ASSERT_EQ(node->type, token_t::plus);
    
    parse_node* left = node->left_child;
    ASSERT_EQ(left->type, token_t::number);
    ASSERT_EQ(left->value, "5");
    
    parse_node* right = node->right_child;
    ASSERT_EQ(right->type, token_t::star);

    node = right;

    left = node->left_child;
    ASSERT_EQ(left->type, token_t::number);
    ASSERT_EQ(left->value, "7");

    right = node->right_child;
    ASSERT_EQ(right->type, token_t::number);
    ASSERT_EQ(right->value, "9");
}

TEST_F(parse_assignment_test, parses_complex_integer_assignment_expression_2)
{
    std::vector<token> tokens = lex_tokens("int i = 5 * 7 + 9;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->right_child;
    ASSERT_EQ(node->type, token_t::plus);
    
    parse_node* right = node->right_child;
    ASSERT_EQ(right->type, token_t::number);
    ASSERT_EQ(right->value, "9");

    parse_node* left = node->left_child;
    ASSERT_EQ(left->type, token_t::star);
    
    node = left;

    left = node->left_child;
    ASSERT_EQ(left->type, token_t::number);
    ASSERT_EQ(left->value, "5");

    right = node->right_child;
    ASSERT_EQ(right->type, token_t::number);
    ASSERT_EQ(right->value, "7");
}

TEST_F(parse_assignment_test, parses_complex_integer_assignment_expression_3)
{
    std::vector<token> tokens = lex_tokens("int i = 3 * 5 + 7 * 9;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->right_child;
    ASSERT_EQ(node->type, token_t::plus);
    
    parse_node* left = node->left_child;
    ASSERT_EQ(left->type, token_t::star);

    node = left;

    left = node->left_child;
    ASSERT_EQ(left->type, token_t::number);
    EXPECT_EQ(left->value, "3");

    parse_node* right = node->right_child;
    ASSERT_EQ(right->type, token_t::number);
    EXPECT_EQ(right->value, "5");

    node = root->right_child;
    ASSERT_TRUE(node->right_child != nullptr);
    
    node = node->right_child;
    ASSERT_EQ(node->type, token_t::star);
    
    left = node->left_child;
    ASSERT_EQ(left->type, token_t::number);
    EXPECT_EQ(left->value, "7");

    right = node->right_child;
    ASSERT_EQ(right->type, token_t::number);
    EXPECT_EQ(right->value, "9");
}

TEST_F(parse_assignment_test, parses_complex_integer_assignment_expression_4)
{
    std::vector<token> tokens = lex_tokens("int i = 3 + 5 * 7 + 9;");
    root = parse_tokens(tokens);
    
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root->type, token_t::assign);

    parse_node* node = root->right_child;
    ASSERT_EQ(node->type, token_t::plus);
    
    parse_node* left = node->left_child;
    ASSERT_EQ(left->type, token_t::number);
    EXPECT_EQ(left->value, "3");

    node = node->right_child;
    ASSERT_EQ(node->type, token_t::plus);

    node = node->left_child;
    ASSERT_EQ(node->type, token_t::star);

    left = node->left_child;
    parse_node* right = node->right_child;

    ASSERT_EQ(left->type, token_t::number);
    EXPECT_EQ(left->value, "5");
    
    ASSERT_EQ(right->type, token_t::number);
    EXPECT_EQ(right->value, "7");

    node = root->right_child->right_child;
    ASSERT_EQ(node->type, token_t::plus);

    left = node->right_child;

    ASSERT_EQ(left->type, token_t::number);
    EXPECT_EQ(left->value, "9");
}
