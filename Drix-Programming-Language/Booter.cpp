#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Executer.h"
#include "Lexer.h"
#include "fstream"

void Executer::Execute(std::vector<Token>& Tokens,Environment& env){
    int i = 0;

    Dr DrHandler;
    Drnum DrnumHandler;
    Function FuncHandler;
    Output OutputHandler;
    Input InputHandler;
    Assigne AssigneHandler;
    StopHandler StopHandle;
    Ignore IgnoreHandler;
    If IfHandler;
    Else ElseHandler;
    Length LengthHandler;
    Use UseHandler;
    System SystemHandler;

    while (i < Tokens.size()){
        if (Tokens[i].token == TokenList::KeywordDr){
            DrHandler.Execute(Tokens, i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordDrnum){
            DrnumHandler.Execute(Tokens, i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordFunc){
            FuncHandler.Execute(Tokens,i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordInput){
            InputHandler.Execute(Tokens,i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordIf){
            IfHandler.Execute(Tokens,i,env,FuncHandler);
        }
        else if (Tokens[i].token == TokenList::KeywordElse){
            ElseHandler.Execute(Tokens,i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordIgnore){
            IgnoreHandler.Execute(Tokens,i);
        }
        else if (Tokens[i].token == TokenList::KeywordOutput){
            OutputHandler.Execute(Tokens,i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordLength){
            LengthHandler.Execute(Tokens,i,env);
        }
        else if (Tokens[i].token == TokenList::KeywordUse){
            UseHandler.Activate(Tokens,i);
        }
        else if (Tokens[i].token == TokenList::Variable && i + 1 < Tokens.size()){
            if (Tokens[i + 1].token == TokenList::Assign){
                AssigneHandler.Execute(Tokens, i, env);
            }
            else if (Tokens[i + 1].token == TokenList::Parentheses){
                FuncHandler.CallFunction(Tokens, i, env);
            }
            else if (Tokens[i + 1].token == TokenList::Dot){
                if (Tokens[i].val == "system"){
                    SystemHandler.Execute(Tokens, i, env, UseHandler);
                }
                else { i++; }
            }
            else { i++; }
        }
        else if (Tokens[i].token == TokenList::KeywordStop){
            StopHandle.Execute(Tokens,i);
        }
        else if (Tokens[i].token == TokenList::LBrace) {
            FuncHandler.OnLBrace();
            i++;
        }
        else if (Tokens[i].token == TokenList::RBrace) {
            if (!FuncHandler.OnRBrace(i)) {
                i++;
            }
        }
        else{i++;}
    }
}

int main(int argc, char* argv[]){
    if (argc < 2){
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) { 
        return 1; 
    }

    std::string code;
    std::string line;

    while (std::getline(file, line)) {
        code += line + "\n"; 
    }

    Lexer code_tokens;
    Executer executer;
    Environment env;

    std::vector<Token> tokens = code_tokens.Tokenize(code);
    executer.Execute(tokens, env);

    return 0;
}