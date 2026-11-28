#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Use::Activate(const std::vector<Token>& Tokens, int&i){
    if (i + 4 < Tokens.size()){
        if (Tokens[i + 4].token == TokenList::LineEnder && Tokens[i + 1].token == TokenList::Less && Tokens[i + 3].token == TokenList::Greater){
            if (Tokens[i + 2].token == TokenList::String){
                bool found = false;
                for (int b = 0; b < exist.size();b++){
                    if (exist[b] == Tokens[i + 2].val){
                        found = true;
                        uses.push_back(exist[b]);
                        break;
                    }
                }
                if (found == false){
                    std::cout << "This Library not exists" << std::endl;
                }
            }
        }

        i+=5;
    }
    else{i++;}
}

bool Use::IsActivated(const std::string& libname){
    for (int i=0;i < uses.size();i++){
        if (uses[i] == libname){
            return true;
        }
    }
    return false;
}