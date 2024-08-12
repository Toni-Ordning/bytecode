#include <gtest/gtest.h>

#include "parse_strategies.h"
#include "token.h"

TEST(parse_strategies_test, integer_keyword_returns_initialization_strategy)
{
    token t{token_t::integer_keyword, "int"};
    parse_strategy strategy = get_parse_strategy(t);

    EXPECT_EQ(strategy, parse_strategy::initialize);
}

TEST(parse_strategies_test, floating_point_keyword_returns_initialization_strategy)
{
    token t{token_t::integer_keyword, "float"};
    parse_strategy strategy = get_parse_strategy(t);

    EXPECT_EQ(strategy, parse_strategy::initialize);
}

TEST(parse_strategies_test, boolean_keyword_returns_initialization_strategy)
{
    token t{token_t::integer_keyword, "bool"};
    parse_strategy strategy = get_parse_strategy(t);

    EXPECT_EQ(strategy, parse_strategy::initialize);
}
