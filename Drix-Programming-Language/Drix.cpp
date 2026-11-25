#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <variant>
#include <fstream>

std::map<std::string,int> NumberVariables;
std::map<std::string,std::string> StringVariables;

enum class TokenList{
    Variable,
    Number,
    String,
    LineEnder, // ;
    Plus,
    Minus,
    Parentheses, // ()
    Assign,

    KeywordDr,
    KeywordDrnum,
    KeywordOutput,
    KeywordAutoPut,
};

struct Token{
    TokenList token;
    std::string val;
};

auto Tokenizer(std::string code){
    std::vector<Token> Tokens;
    int i=0;

    std::string eq="";
    bool is_skip = false;

    while(i < code.length()){
        char current = code[i];

        if (current == '+'){
            Token tok;

            tok.token = TokenList::Plus;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '-'){
            Token tok;

            tok.token = TokenList::Minus;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '='){
            Token tok;

            tok.token = TokenList::Assign;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == ';'){
            Token tok;

            tok.token = TokenList::LineEnder;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '('){
            Token tok;

            tok.token = TokenList::Parentheses;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == ')'){
            Token tok;

            tok.token = TokenList::Parentheses;
            tok.val = current;

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
            Tokens.push_back(tok);
            eq = "";
            is_skip = true;
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
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "drnum"){
                Token tok;

                tok.token = TokenList::KeywordDrnum;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = ""; 
            }
            else if (eq == "Output"){
                Token tok;

                tok.token = TokenList::KeywordOutput;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = ""; 
            }
            else if (eq == "AutoPut"){
                Token tok;

                tok.token = TokenList::KeywordAutoPut;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else{
                Token tok;

                tok.token = TokenList::Variable;
                tok.val = eq;
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

void Executer(const std::vector<Token>& Tokens){
    int i = 0;

    while (i < Tokens.size()){
        if (Tokens[i].token == TokenList::KeywordAutoPut){
            std::cout << "auto" << std::endl;
            i+=2;
        }
        else if (Tokens[i + 3].token == TokenList::KeywordAutoPut){std::cout << "Error Variable != AutoPut" << std::endl;i+=5;}
        else if (Tokens[i].token == TokenList::Variable && Tokens[i + 1].token == TokenList::Assign){
            if (NumberVariables.count(Tokens[i].val) == 1){
                std::string varName = Tokens[i].val;
                int result;

                if (NumberVariables.count(Tokens[i + 2].val) == 1){
                    result = NumberVariables[Tokens[i + 2].val];
                }
                else{
                    result = std::stoi(Tokens[i + 2].val);
                }
                
                i+=3;
                while(i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                    if (Tokens[i].token == TokenList::Plus){
                        if (Tokens[i + 1].token == TokenList::Number){
                            result += std::stoi(Tokens[i + 1].val);
                        }
                        else if (Tokens[i + 1].token == TokenList::Variable){
                            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                                auto variable = NumberVariables[Tokens[i + 1].val];
                                result += variable;
                            }
                        }
                    }
                    if (Tokens[i].token == TokenList::Minus){
                        if (Tokens[i + 1].token == TokenList::Number){
                            result -= std::stoi(Tokens[i + 1].val);
                        }
                        else if (Tokens[i + 1].token == TokenList::Variable){
                            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                                auto variable = NumberVariables[Tokens[i + 1].val];
                                result -= variable;
                            }
                        }
                    }
                    i+=2;
                }

                NumberVariables[varName] = result;
                i++;            
            }
            else if (StringVariables.count(Tokens[i].val) == 1){
                StringVariables[Tokens[i].val] = Tokens[i + 2].val; 
                i += 4;
            }
            else{std::cout << "Error Invalid Variable" << std::endl;}
        }

        else if(Tokens[i].token == TokenList::KeywordOutput){
            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                std::cout << NumberVariables[Tokens[i + 1].val] << std::endl;
            }
            else if (StringVariables.count(Tokens[i + 1].val) == 1){
                std::cout << StringVariables[Tokens[i + 1].val] << std::endl;
            }
            else if (Tokens[i + 1].token == TokenList::String){
                std::cout << Tokens[i + 1].val << std::endl;
            }
            i += 3;
        }
        else if (Tokens[i].token == TokenList::KeywordDrnum){
            std::string varName = Tokens[i + 1].val;
            int result;
            if (NumberVariables.count(Tokens[i + 3].val) == 1){
                result = NumberVariables[Tokens[i + 3].val];
            }
            else{
                result = std::stoi(Tokens[i + 3].val);
            }
            
            i+=4;
            while(i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                if (Tokens[i].token == TokenList::Plus){
                    if (Tokens[i + 1].token == TokenList::Number){
                        result += std::stoi(Tokens[i + 1].val);
                    }
                    else if (Tokens[i + 1].token == TokenList::Variable){
                        if (NumberVariables.count(Tokens[i + 1].val) == 1){
                            auto variable = NumberVariables[Tokens[i + 1].val];
                            result += variable;
                        }
                    }
                }
                if (Tokens[i].token == TokenList::Minus){
                    if (Tokens[i + 1].token == TokenList::Number){
                        result -= std::stoi(Tokens[i + 1].val);
                    }
                    else if (Tokens[i + 1].token == TokenList::Variable){
                        if (NumberVariables.count(Tokens[i + 1].val) == 1){
                            auto variable = NumberVariables[Tokens[i + 1].val];
                            result -= variable;
                        }
                    }
                }
                i+=2;
            }

            NumberVariables[varName] = result;
            i++;
        }
        else if(Tokens[i].token == TokenList::KeywordDr){
            if (Tokens[i + 3].token == TokenList::KeywordAutoPut){std::cout << "Error Variable != AutoPut" << std::endl;i+=5;}
            else{
                StringVariables[Tokens[i + 1].val] = Tokens[i + 3].val;
                i += 5;
            }
        }

        else{i++;}
    }
}

int main(){
    std::ifstream file("Code.dr");
    std::string code;

    std::string line;
    while (std::getline(file, line)) {
        code += line + " ";
    }

    auto code_tokens = Tokenizer(code);
    Executer(code_tokens);

    return 0;
}