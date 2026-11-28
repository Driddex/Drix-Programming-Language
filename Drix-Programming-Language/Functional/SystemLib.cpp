#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"
#include <cstdlib>

void System::Execute(const std::vector<Token>& Tokens, int& i, Environment& env, Use& use) {
    if (!use.IsActivated("system")){
        std::cout << "Library Is Not Activated!" << std::endl;
        while (i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
            i++;
        }
        i++;
        return;
    }
    if (i + 2 < Tokens.size() && Tokens[i + 1].token == TokenList::Dot) {
        if (Tokens[i + 2].val == "command") {
            RunCmd(Tokens, i, env);
            return;
        }
    }
    i++;
}


void System::RunCmd(const std::vector<Token>& Tokens, int& i, Environment& env) {
    if (i + 6 < Tokens.size() &&
        Tokens[i + 3].token == TokenList::Parentheses &&
        Tokens[i + 5].token == TokenList::Parentheses &&
        Tokens[i + 6].token == TokenList::LineEnder) {

        if (Tokens[i + 4].token == TokenList::String) {
            std::string command = Tokens[i + 4].val;
            std::system(command.c_str());
        }
        else if (Tokens[i + 4].token == TokenList::Variable && env.StringExists(Tokens[i + 4].val)) {
            std::string command = env.GetString(Tokens[i + 4].val);
            std::system(command.c_str());
        }
        i += 7;
    }
    else {
        std::cout << "Syntax error in system.command!" << std::endl;
        i++;
    }
}
