#pragma once
#include <string>
#include <vector>
#include "Tokens.h"

class Lexer {
    public:
        std::vector<Token> Tokenize(const std::string& code);
};