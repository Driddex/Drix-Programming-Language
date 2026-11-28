#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Dr::Execute(const std::vector<Token>& Tokens, int& i, Environment& env){
    if (i + 2 < Tokens.size()){

        if (Tokens[i + 2].token == TokenList::LineEnder){
            env.CreateString(Tokens[i + 1].val, "Null");
            i += 3;
        }
        else if (i + 4 < Tokens.size()){
            std::string result = "";
            std::string varname = Tokens[i + 1].val;

            if (Tokens[i + 3].token == TokenList::Variable) {
                result = env.GetString(Tokens[i + 3].val);
            } else {
                result = Tokens[i + 3].val;
            }

            i += 4;
            while (i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                if (Tokens[i].token == TokenList::Plus){
                    if (Tokens[i + 1].token == TokenList::String){
                        result += Tokens[i + 1].val;
                    }
                    
                    else if (env.StringExists(Tokens[i + 1].val) == true){
                        result += env.GetString(Tokens[i + 1].val);
                    }
                }

                if (Tokens[i].token == TokenList::Minus){
                    std::cout << "U Can't Do Minus Opererations with text!" << std::endl;
                }

                i += 2;
            }  
            env.CreateString(varname, result);
            i++; 
        }
    }
}

void Drnum::Execute(const std::vector<Token>& Tokens, int& i, Environment& env){
    if (i + 2 < Tokens.size()){
        if (Tokens[i + 2].token == TokenList::LineEnder){
            env.CreateNumber(Tokens[i + 1].val, 0);
            i += 3;
        }
        else if (i + 4 < Tokens.size()){
            int result = 0;
            std::string varname = Tokens[i + 1].val;

            if (Tokens[i + 3].token == TokenList::Variable) {
                result = env.GetNumber(Tokens[i + 3].val);
            } else {
                result = std::stoi(Tokens[i + 3].val);
            }

            i += 4;
            while (i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                if (Tokens[i].token == TokenList::Plus){
                    if (Tokens[i + 1].token == TokenList::Number){
                        result += std::stoi(Tokens[i + 1].val);
                    }
                    else if (env.NumberExists(Tokens[i + 1].val) == true){
                        result += env.GetNumber(Tokens[i + 1].val);
                    }
                }
                if (Tokens[i].token == TokenList::Minus){
                    if (Tokens[i + 1].token == TokenList::Number){
                        result -= std::stoi(Tokens[i + 1].val);
                    }
                    else if (env.NumberExists(Tokens[i + 1].val) == true){
                        result -= env.GetNumber(Tokens[i + 1].val);
                    }
                }

                i += 2;
            }  
            env.CreateNumber(varname, result);
            i++; 
        }
    }
}
