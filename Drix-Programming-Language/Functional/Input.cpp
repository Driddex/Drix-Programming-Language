#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Input::Execute(const std::vector<Token>& Tokens, int&i, Environment& env){
    if (i < Tokens.size()){
        if (Tokens[i + 1].token == TokenList::Variable){
            if (env.StringExists(Tokens[i + 1].val) == true){
                std::string val;
                std::cin >> val;

                env.CreateString(Tokens[i + 1].val, val);
            }
            else if (env.NumberExists(Tokens[i + 1].val) == true){
                int val;
                std::cin >> val;

                env.CreateNumber(Tokens[i + 1].val, val);
            }
        }
    }
    i+=3;
}