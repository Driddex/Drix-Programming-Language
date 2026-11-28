#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Ignore::Execute(const std::vector<Token>& Tokens, int&i){
    while(i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
        i++;
    }
    i++;
}