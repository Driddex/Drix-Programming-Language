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
};

struct Token{
    TokenList token;
    std::string val;
    int line = 1;
};