#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "../Executer.h"

void If::Execute(const std::vector<Token>& Tokens, int&i, Environment& env,Function& func){
    if (i + 6 < Tokens.size()){
        if (Tokens[i + 1].token == TokenList::Parentheses && Tokens[i + 5].token == TokenList::Parentheses){
            bool is_true = false;
            std::variant<int, std::string> val1;
            std::variant<int, std::string> val2;

            if (Tokens[i + 2].token == TokenList::Number){
                val1 = std::stoi(Tokens[i + 2].val);
            }
            else if (Tokens[i + 2].token == TokenList::Variable){
                if (env.StringExists(Tokens[i + 2].val) == true){
                    val1 = env.GetString(Tokens[i + 2].val);
                }
                else if (env.NumberExists(Tokens[i + 2].val) == true){
                    val1 = env.GetNumber(Tokens[i + 2].val);
                }
            }
            else if (Tokens[i + 2].token == TokenList::String){
                val1 = Tokens[i + 2].val;
            }

            if (Tokens[i + 4].token == TokenList::Number){
                val2 = std::stoi(Tokens[i + 4].val);
            }
            else if (Tokens[i + 4].token == TokenList::Variable){
                if (env.StringExists(Tokens[i + 4].val) == true){
                    val2 = env.GetString(Tokens[i + 4].val);
                }
                else if (env.NumberExists(Tokens[i + 4].val) == true){
                    val2 = env.GetNumber(Tokens[i + 4].val);
                }
            }
            else if (Tokens[i + 4].token == TokenList::String){
                val2 = Tokens[i + 4].val;
            }

            if (Tokens[i + 3].token == TokenList::Equal){
                if (val1 == val2){
                    is_true = true;
                }
            }
            else if (Tokens[i + 3].token == TokenList::NotEqual){
                if (val1 != val2){
                    is_true = true;
                }
            }
            else if (Tokens[i + 3].token == TokenList::Less){
                if (val1 < val2){
                    is_true = true;
                }
            }
            else if (Tokens[i + 3].token == TokenList::Greater){
                if (val1 > val2){
                    is_true = true;
                }
            }

            if (is_true == true){
                func.OnLBrace();
                i += 7;
            }

            else if (is_true == false){
                func.OnLBrace();
                i+=6;
                int braces = 0;
                while (i < Tokens.size()){
                    if (Tokens[i].token == TokenList::LBrace){braces++;}
                    else if (Tokens[i].token == TokenList::RBrace){braces--;}
                    i++;
                    if (braces == 0){break;}
                }
                if (i + 1 < Tokens.size() && Tokens[i].token == TokenList::KeywordElse && Tokens[i + 1].token == TokenList::LBrace){
                    i += 2;
                }
            }
        }
    }
}

void Else::Execute(const std::vector<Token>& Tokens, int&i, Environment& env){
    i++;
    int braces = 0;
    while (i < Tokens.size()){
        if (Tokens[i].token == TokenList::LBrace){braces++;}
        else if (Tokens[i].token == TokenList::RBrace){braces--;}
        i++;
        if (braces == 0){break;}
    }
}