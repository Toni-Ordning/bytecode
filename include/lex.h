#pragma once

#include <vector>

#include "token.h"

/* Convenience wrapper for lex_tokens.
 * Reads filename contents into a vector, and then calls lex_tokens().
 *
 * Throws: If file could not be read.
 * Throws: Anything that lex_tokens throws.
*/
std::vector<token> lex(const char* filename);

/* Returns a vector of tokens from given bytes.
 * Tokens are in the same order as the bytes were read.
 * If no tokens were generated, returns an empty vector.
 *
 * Throws: If input could not be lexed, i.e. there was an unexpected token.
*/
std::vector<token> lex_tokens(const std::vector<unsigned char>& bytes);
std::vector<token> lex_tokens(const std::string& input);
