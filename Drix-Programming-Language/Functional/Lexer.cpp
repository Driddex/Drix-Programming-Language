#include <string>
#include <iostream>
#include <cctype>
#include "../Lexer.h"

std::vector<Token> Lexer::Tokenize(const std::string& code){
    std::vector<Token> Tokens;
    int i=0;

    std::string eq="";
    int currentline = 1;
    bool is_skip = false;

    while(i < code.length()){
        char current = code[i];
        if (current == '\n'){currentline++;}
        else if (current == '+'){
            Token tok;

            tok.token = TokenList::Plus;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '-'){
            Token tok;

            tok.token = TokenList::Minus;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '{'){
            Token tok;

            tok.token = TokenList::LBrace;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '}'){
            Token tok;

            tok.token = TokenList::RBrace;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '>'){
            Token tok;

            tok.token = TokenList::Greater;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '<'){
            Token tok;

            tok.token = TokenList::Less;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '!'){
            if (i + 1 < code.length() && code[i + 1] == '='){
                Token tok;

                tok.token = TokenList::NotEqual;
                tok.val = current;
                tok.line = currentline;
                Tokens.push_back(tok);
                i++;
            }
        }
        else if (current == '='){
            if (i + 1 < code.length() && code[i + 1] == '='){
                Token tok;

                tok.token = TokenList::Equal;
                tok.val = current;
                tok.line = currentline;
                Tokens.push_back(tok);
                i++;
            }
            else{
                Token tok;

                tok.token = TokenList::Assign;
                tok.val = current;
                tok.line = currentline;
                Tokens.push_back(tok);
            }
        }
        else if (current == ';'){
            Token tok;

            tok.token = TokenList::LineEnder;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '('){
            Token tok;

            tok.token = TokenList::Parentheses;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == ')'){
            Token tok;

            tok.token = TokenList::Parentheses;
            tok.val = current;
            tok.line = currentline;
            Tokens.push_back(tok);
        }
        else if (current == '"'){
            i++;
            while (i < code.length() && code[i] != '"'){
                eq += code[i];
                i++;
            }
            Token tok;
            tok.token = TokenList::String;
            tok.val = eq;
            tok.line = currentline;
            Tokens.push_back(tok);
            eq = "";
        }
        else if (std::isdigit(current)){
            while (i < code.length() && std::isdigit(code[i])){
                eq += code[i];
                i++;
            }

            Token tok;
            
            tok.token = TokenList::Number;
            tok.val = eq;
            tok.line = currentline;
            Tokens.push_back(tok);
            eq = "";
            is_skip = true;
        }
        else if (current == '|' && i + 1 < code.length() && code[i + 1] == '|'){
            while (i < code.length() && code[i] != '\n'){
                 i++;
            }
        }
        else if (std::isalpha(current)){
            while (i < code.length() && std::isalpha(code[i])){
                eq += code[i];
                i++;
            }

            if (eq == "dr"){
                Token tok;

                tok.token = TokenList::KeywordDr;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "Stop"){
                Token tok;

                tok.token = TokenList::KeywordStop;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "Func"){
                Token tok;

                tok.token = TokenList::KeywordFunc;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if(eq == "if"){
                Token tok;

                tok.token = TokenList::KeywordIf;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "else"){
                Token tok;

                tok.token = TokenList::KeywordElse;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "Input"){
                Token tok;

                tok.token = TokenList::KeywordInput;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if(eq == "Ignore"){
                Token tok;

                tok.token = TokenList::KeywordIgnore;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "drnum"){
                Token tok;

                tok.token = TokenList::KeywordDrnum;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = ""; 
            }
            else if (eq == "Output"){
                Token tok;

                tok.token = TokenList::KeywordOutput;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = ""; 
            }
            else if (eq == "AutoPut"){
                Token tok;

                tok.token = TokenList::KeywordAutoPut;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }
            else{
                Token tok;

                tok.token = TokenList::Variable;
                tok.val = eq;
                tok.line = currentline;
                Tokens.push_back(tok);
                eq = "";
            }

            is_skip = true;
        }
        else{}
        if (is_skip == false){
            i++;
        }
        else{
            is_skip = false;
        }
    }
    return Tokens;
}