#pragma once
#include <string>

enum class TokenList{
    Variable,
    Number,
    String,
    LineEnder, // ;
    Plus,
    Minus,
    Parentheses, // ()
    Assign,
    LBrace,
    RBrace,
    Greater,
    Less,
    Equal,
    NotEqual,
    Dot,

    KeywordDr,
    KeywordDrnum,
    KeywordOutput,
    KeywordAutoPut,
    KeywordIgnore,
    KeywordIf,
    KeywordElse,
    KeywordInput,
    KeywordStop,
    KeywordFunc,
    KeywordLength,
    KeywordUse,
};

struct Token{
    TokenList token;
    std::string val;
    int line = 1;
};