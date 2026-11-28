#include <iostream>
#include <string>
#include <vector>
#include "../Executer.h"

void Assigne::Execute(const std::vector<Token>& Tokens, int& i, Environment& env){
    if (i + 3 < Tokens.size()){
        if (Tokens[i].token == TokenList::Variable){

            if (env.StringExists(Tokens[i].val) == true){
                std::string result = "";
                std::string varname = Tokens[i].val;

                if (Tokens[i + 2].token == TokenList::Variable) {
                    result = env.GetString(Tokens[i + 2].val);
                } 
                else if (Tokens[i + 2].token == TokenList::String) {
                    result = Tokens[i + 2].val;
                }

                i += 3;
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
            else if (env.NumberExists(Tokens[i].val) == true){
                int result = 0;
                std::string varname = Tokens[i].val;

                if (Tokens[i + 2].token == TokenList::Variable) {
                    result = env.GetNumber(Tokens[i + 2].val);
                } 
                else if (Tokens[i + 2].token == TokenList::Number) {
                    result = std::stoi(Tokens[i + 2].val);
                }

                i += 3;
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
}
