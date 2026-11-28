#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Length::Execute(const std::vector<Token>& Tokens, int&i, Environment& env){
    if (i + 4 < Tokens.size()){
        int length;
        if (Tokens[i + 2].token == TokenList::String){
            length = Tokens[i + 2].val.length();
            std::cout << length << std::endl;
        }
        else if (Tokens[i + 2].token == TokenList::Variable && env.StringExists(Tokens[i + 2].val) == true){
            length = env.GetString(Tokens[i + 2].val).length();
            std::cout << length << std::endl;
        }
        else if (Tokens[i + 2].token == TokenList::Variable && env.NumberExists(Tokens[i + 2].val) == true){
            length = std::to_string(env.GetNumber(Tokens[i + 2].val)).length();
            std::cout << length << std::endl;
        }
        else if (Tokens[i + 2].token == TokenList::Number){
            length = Tokens[i + 2].val.length();
            std::cout << length << std::endl;
        }
        i+=5;
    }
}