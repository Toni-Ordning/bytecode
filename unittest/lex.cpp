#include "lex.h"

#include "gtest/gtest.h"

class lex_test : public testing::Test
{
    protected:
        std::vector<unsigned char> bytes;
        std::vector<token> tokens;

        void test(const std::string& input)
        {
            bytes.clear();
            tokens.clear();

            for (const unsigned char c : input)
            {
                bytes.push_back(c);
            }

            tokens = lex_tokens(bytes);
        }
};

TEST_F(lex_test, parsing_no_characters_produces_no_tokens)
{
    test("");

    EXPECT_TRUE(tokens.empty());
}

TEST_F(lex_test, parsing_whitespace_produces_no_tokens)
{
    test(" \t\n");

    EXPECT_TRUE(tokens.empty());
}

TEST_F(lex_test, parses_assignment_token)
{
    test("=");

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens.at(0).type, token_t::assign);
    EXPECT_EQ(tokens.at(0).value, "=");
}

TEST_F(lex_test, parses_semicolon_token)
{
    test(";");

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens.at(0).type, token_t::semicolon);
    EXPECT_EQ(tokens.at(0).value, ";");
}

TEST_F(lex_test, parses_integer_token)
{
    test("int");

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens.at(0).type, token_t::integer_keyword);
    EXPECT_EQ(tokens.at(0).value, "int");
}

TEST_F(lex_test, parses_float_token)
{
    test("float");

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens.at(0).type, token_t::floating_point_keyword);
    EXPECT_EQ(tokens.at(0).value, "float");
}

TEST_F(lex_test, parses_boolean_tokens)
{
    test("bool true false");
    
    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens.at(0).type, token_t::boolean_keyword);
    EXPECT_EQ(tokens.at(0).value, "bool");

    EXPECT_EQ(tokens.at(1).type, token_t::true_keyword);
    EXPECT_EQ(tokens.at(1).value, "true");

    EXPECT_EQ(tokens.at(2).type, token_t::false_keyword);
    EXPECT_EQ(tokens.at(2).value, "false");
}

TEST_F(lex_test, parses_arithmetic_operation_tokens)
{
    test("+ - * /");
    
    ASSERT_EQ(tokens.size(), 4);

    EXPECT_EQ(tokens.at(0).type, token_t::plus);
    EXPECT_EQ(tokens.at(0).value, "+");

    EXPECT_EQ(tokens.at(1).type, token_t::minus);
    EXPECT_EQ(tokens.at(1).value, "-");

    EXPECT_EQ(tokens.at(2).type, token_t::star);
    EXPECT_EQ(tokens.at(2).value, "*");

    EXPECT_EQ(tokens.at(3).type, token_t::slash);
    EXPECT_EQ(tokens.at(3).value, "/");
}

TEST_F(lex_test, lexes_character_only_variable)
{
    test("variable");

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens.at(0).type, token_t::variable);
    EXPECT_EQ(tokens.at(0).value, "variable");
}

TEST_F(lex_test, lexes_variable_with_characters_and_numbers)
{
    test("var123 V4r14bl3");

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens.at(0).type, token_t::variable);
    EXPECT_EQ(tokens.at(0).value, "var123");
    
    EXPECT_EQ(tokens.at(1).type, token_t::variable);
    EXPECT_EQ(tokens.at(1).value, "V4r14bl3");
}

TEST_F(lex_test, lexes_integer_numbers)
{
    test("5 42 167854");

    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(0).type, token_t::number);
    EXPECT_EQ(tokens.at(0).value, "5");
    
    EXPECT_EQ(tokens.at(1).type, token_t::number);
    EXPECT_EQ(tokens.at(1).value, "42");
    
    EXPECT_EQ(tokens.at(2).type, token_t::number);
    EXPECT_EQ(tokens.at(2).value, "167854");
}

TEST_F(lex_test, lexes_floating_point_numbers)
{
    test("1.0 0.5 1.234");

    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(0).type, token_t::number);
    EXPECT_EQ(tokens.at(0).value, "1.0");
    
    EXPECT_EQ(tokens.at(1).type, token_t::number);
    EXPECT_EQ(tokens.at(1).value, "0.5");
    
    EXPECT_EQ(tokens.at(2).type, token_t::number);
    EXPECT_EQ(tokens.at(2).value, "1.234");
}
