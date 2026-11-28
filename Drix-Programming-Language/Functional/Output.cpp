#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Output::Execute(const std::vector<Token>& Tokens, int&i, Environment& env){
    if (i < Tokens.size()){
        if (Tokens[i + 1].token == TokenList::String){
            std::cout << Tokens[i + 1].val << std::endl;
        }
        else if (Tokens[i + 1].token == TokenList::Variable){
            if (env.StringExists(Tokens[i + 1].val) == true){
                std::cout << env.GetString(Tokens[i + 1].val) << std::endl;
            }
            else if (env.NumberExists(Tokens[i + 1].val) == true){
                std::cout << env.GetNumber(Tokens[i + 1].val) << std::endl;
            }
            else{std::cout << Tokens[i + 1].val << std::endl;}
        }
        else if (Tokens[i + 1].token == TokenList::Number){
            std::cout << Tokens[i + 1].val << std::endl;
        }
        i+=3;
    }
}