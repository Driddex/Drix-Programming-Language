#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Function::Execute(const std::vector<Token>& Tokens, int&i, Environment& env){
    if (i + 5 < Tokens.size()){
        func[Tokens[i + 1].val] = i + 5;
        i+=5;
        int braces = 1;
            while (i < Tokens.size() && braces > 0){
                if (Tokens[i].token == TokenList::LBrace){
                    braces++;
                }
                else if (Tokens[i].token == TokenList::RBrace){
                    braces--;
                }
                i++;
            }
    }
}

void Function::CallFunction(const std::vector<Token>& Tokens, int&i, Environment& env){
    if (func.count(Tokens[i].val) == 1){
        stack.push_back(i + 4);
        i = func[Tokens[i].val];
        braceDepth = 0;
    }
}

void Function::OnLBrace() {
    if (!stack.empty()) {
        braceDepth++;
    }
}

bool Function::OnRBrace(int& i) {
    if (!stack.empty()) {
        if (braceDepth > 0) {
            braceDepth--;
            return false;
        }
        i = stack.back();
        stack.pop_back();
        return true;
    }
    return false;
}