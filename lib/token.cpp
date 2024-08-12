#include "token.h"

bool token::operator == (const token& other)
{
    return this->type == other.type &&
        this->value == other.value;
}
