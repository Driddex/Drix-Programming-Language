#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <variant>
#include <fstream>

std::map<std::string,int> NumberVariables;
std::map<std::string,std::string> StringVariables;

enum class TokenList{
    Variable,
    Number,
    String,
    LineEnder, // ;
    Plus,
    Minus,
    Parentheses, // ()
    Assign,
    LBrace,
    RBrace,
    Greater,
    Less,
    Equal,
    NotEqual,

    KeywordDr,
    KeywordDrnum,
    KeywordOutput,
    KeywordAutoPut,
    KeywordIgnore,
    KeywordIf,
    KeywordElse,
    KeywordInput,
    KeywordStop,
    KeywordFunc,
};

struct Token{
    TokenList token;
    std::string val;
};

class StopHandler{
    public:
        void execute(const std::vector<Token>& Tokens,int&i){
            i = Tokens.size();
        }
};

class FunctionManager{
    private:
        std::map<std::string, int> functions;
        std::vector<int> callStack; 
        std::vector<int> braceDepth;
    public:
        void define(const std::vector<Token>& Tokens, int& i){
            if (i + 5 < Tokens.size()){
                functions[Tokens[i + 1].val] = i + 5;
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
        bool call(const std::vector<Token>& Tokens, int& i){
            if (functions.count(Tokens[i].val) == 1){
                callStack.push_back(i+4);
                braceDepth.push_back(1);
                i = functions[Tokens[i].val];
                return true;
            }
            return false;
        }

        bool onRBrace(int& i){
            if (!callStack.empty()){
                braceDepth.back()--;
                if (braceDepth.back() == 0){
                    braceDepth.pop_back();
                    i = callStack.back();
                    callStack.pop_back();
                    return true;
                }
            }
            return false;
        }
        void onLBrace(){
            if (!braceDepth.empty()){
                braceDepth.back()++;
            }
        }
};

class InputHandler{
    public:
        void execute(const std::vector<Token>& Tokens, int& i){
            if (i + 2 < Tokens.size()){
                std::string varName = Tokens[i + 1].val;
                if (NumberVariables.count(varName) == 1){
                    std::cin >> NumberVariables[varName];
                }
                else if (StringVariables.count(varName) == 1){
                    std::cin >> StringVariables[varName];
                }
                else{std::cout << "Variable not found" << std::endl;}
                i+=3;
            }
            else{
                i = Tokens.size();
            }
        }
};

auto Tokenizer(std::string code){
    std::vector<Token> Tokens;
    int i=0;

    std::string eq="";
    bool is_skip = false;

    while(i < code.length()){
        char current = code[i];

        if (current == '+'){
            Token tok;

            tok.token = TokenList::Plus;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '-'){
            Token tok;

            tok.token = TokenList::Minus;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '{'){
            Token tok;

            tok.token = TokenList::LBrace;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '}'){
            Token tok;

            tok.token = TokenList::RBrace;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '>'){
            Token tok;

            tok.token = TokenList::Greater;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '<'){
            Token tok;

            tok.token = TokenList::Less;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '!'){
            if (i + 1 < code.length() && code[i + 1] == '='){
                Token tok;

                tok.token = TokenList::NotEqual;
                tok.val = current;

                Tokens.push_back(tok);
                i++;
            }
        }
        else if (current == '='){
            if (i + 1 < code.length() && code[i + 1] == '='){
                Token tok;

                tok.token = TokenList::Equal;
                tok.val = current;

                Tokens.push_back(tok);
                i++;
            }
            else{
                Token tok;

                tok.token = TokenList::Assign;
                tok.val = current;

                Tokens.push_back(tok);
            }
        }
        else if (current == ';'){
            Token tok;

            tok.token = TokenList::LineEnder;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '('){
            Token tok;

            tok.token = TokenList::Parentheses;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == ')'){
            Token tok;

            tok.token = TokenList::Parentheses;
            tok.val = current;

            Tokens.push_back(tok);
        }
        else if (current == '"'){
            i++;
            while (i < code.length() && code[i] != '"'){
                eq += code[i];
                i++;
            }
            Token tok;
            tok.token = TokenList::String;
            tok.val = eq;
            Tokens.push_back(tok);
            eq = "";
        }
        else if (std::isdigit(current)){
            while (i < code.length() && std::isdigit(code[i])){
                eq += code[i];
                i++;
            }

            Token tok;
            
            tok.token = TokenList::Number;
            tok.val = eq;
            Tokens.push_back(tok);
            eq = "";
            is_skip = true;
        }
        else if (current == '|' && i + 1 < code.length() && code[i + 1] == '|'){
            while (i < code.length() && code[i] != '\n'){
                 i++;
            }
        }
        else if (std::isalpha(current)){
            while (i < code.length() && std::isalpha(code[i])){
                eq += code[i];
                i++;
            }

            if (eq == "dr"){
                Token tok;

                tok.token = TokenList::KeywordDr;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "Stop"){
                Token tok;

                tok.token = TokenList::KeywordStop;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "Func"){
                Token tok;

                tok.token = TokenList::KeywordFunc;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if(eq == "if"){
                Token tok;

                tok.token = TokenList::KeywordIf;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "else"){
                Token tok;

                tok.token = TokenList::KeywordElse;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "Input"){
                Token tok;

                tok.token = TokenList::KeywordInput;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if(eq == "Ignore"){
                Token tok;

                tok.token = TokenList::KeywordIgnore;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else if (eq == "drnum"){
                Token tok;

                tok.token = TokenList::KeywordDrnum;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = ""; 
            }
            else if (eq == "Output"){
                Token tok;

                tok.token = TokenList::KeywordOutput;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = ""; 
            }
            else if (eq == "AutoPut"){
                Token tok;

                tok.token = TokenList::KeywordAutoPut;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }
            else{
                Token tok;

                tok.token = TokenList::Variable;
                tok.val = eq;
                Tokens.push_back(tok);
                eq = "";
            }

            is_skip = true;
        }
        else{}
        if (is_skip == false){
            i++;
        }
        else{
            is_skip = false;
        }
    }
    return Tokens;
}

void Executer(const std::vector<Token>& Tokens){
    FunctionManager FuncManager;
    int i = 0;

    while (i < Tokens.size()){
        if (Tokens[i].token == TokenList::KeywordAutoPut){
            std::cout << "auto" << std::endl;
            i+=2;
        }
        else if (Tokens[i].token == TokenList::KeywordInput){
            InputHandler().execute(Tokens,i);
        }
        else if (Tokens[i].token == TokenList::KeywordStop){
            StopHandler().execute(Tokens,i);
        }
        else if (Tokens[i].token == TokenList::KeywordFunc){
            FuncManager.define(Tokens, i);
        }
        else if (i + 1 < Tokens.size() && Tokens[i].token == TokenList::KeywordElse && Tokens[i + 1].token == TokenList::LBrace) { 
            i += 2; 
            FuncManager.onLBrace();
        }
        else if (i + 1 < Tokens.size() && Tokens[i].token == TokenList::Variable && Tokens[i + 1].token == TokenList::Parentheses){
            if (FuncManager.call(Tokens,i) == true){}
            else{i+=4;}
        }
        else if (Tokens[i].token == TokenList::KeywordIf){
            if (Tokens[i + 1].token == TokenList::Parentheses){
                std::variant<int, std::string> val1;
                std::variant<int, std::string> val2;
                bool IsTrue = false;
                if (Tokens[i + 2].token == TokenList::Number){
                    val1 = std::stoi(Tokens[i + 2].val);
                }
                else if (Tokens[i + 2].token == TokenList::Variable){
                    if (NumberVariables.count(Tokens[i + 2].val) == 1){
                        val1 = NumberVariables[Tokens[i + 2].val];
                    }
                    else if (Tokens[i + 2].token == TokenList::Variable && StringVariables.count(Tokens[i + 2].val) == 1){
                        val1 = StringVariables[Tokens[i + 2].val];
                    }
                }
                else if (Tokens[i + 2].token == TokenList::String){
                    val1 = Tokens[i + 2].val;
                }

                if (Tokens[i + 4].token == TokenList::Number){
                    val2 = std::stoi(Tokens[i + 4].val);
                }
                else if (Tokens[i + 4].token == TokenList::Variable){
                    if (NumberVariables.count(Tokens[i + 4].val) == 1){
                        val2 = NumberVariables[Tokens[i + 4].val];
                    }
                    else if (Tokens[i + 4].token == TokenList::Variable && StringVariables.count(Tokens[i + 4].val) == 1){
                        val2 = StringVariables[Tokens[i + 4].val];
                    }
                }
                else if (Tokens[i + 4].token == TokenList::String){
                    val2 = Tokens[i + 4].val;
                }

                if (Tokens[i + 3].token == TokenList::Equal){
                    if (val1 == val2){
                        IsTrue = true;
                    }
                }
                else if (Tokens[i + 3].token == TokenList::NotEqual){
                    if (val1 != val2){
                        IsTrue = true;
                    }
                }
                else if (Tokens[i + 3].token == TokenList::Less){
                    if (val1 < val2){
                        IsTrue = true;
                    }
                }
                else if (Tokens[i + 3].token == TokenList::Greater){
                    if (val1 > val2){
                        IsTrue = true;
                    }
                }
                i+=7;
                if (IsTrue == true){
                    FuncManager.onLBrace();
                }
                else{
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
        }
        else if (Tokens[i].token == TokenList::KeywordIgnore){
            while (i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                i++;
            }
            i++;
        }
        else if (Tokens[i].token == TokenList::RBrace) {
            if (FuncManager.onRBrace(i) == true){

            }
            else{
                i++;
                if (i + 1 < Tokens.size() && Tokens[i].token == TokenList::KeywordElse && Tokens[i + 1].token == TokenList::LBrace){
                i+=2;
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
        }
        else if (i + 3 < Tokens.size() && (Tokens[i].token == TokenList::KeywordDr || Tokens[i].token == TokenList::KeywordDrnum) && Tokens[i + 3].token == TokenList::KeywordAutoPut){std::cout << "Error Variable != AutoPut" << std::endl;i+=5;}
        else if (Tokens[i].token == TokenList::Variable && Tokens[i + 1].token == TokenList::Assign){
            if (NumberVariables.count(Tokens[i].val) == 1){
                std::string varName = Tokens[i].val;
                int result;

                if (NumberVariables.count(Tokens[i + 2].val) == 1){
                    result = NumberVariables[Tokens[i + 2].val];
                }
                else{
                    result = std::stoi(Tokens[i + 2].val);
                }
                
                i+=3;
                while(i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                    if (Tokens[i].token == TokenList::Plus){
                        if (Tokens[i + 1].token == TokenList::Number){
                            result += std::stoi(Tokens[i + 1].val);
                        }
                        else if (Tokens[i + 1].token == TokenList::Variable){
                            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                                auto variable = NumberVariables[Tokens[i + 1].val];
                                result += variable;
                            }
                        }
                    }
                    if (Tokens[i].token == TokenList::Minus){
                        if (Tokens[i + 1].token == TokenList::Number){
                            result -= std::stoi(Tokens[i + 1].val);
                        }
                        else if (Tokens[i + 1].token == TokenList::Variable){
                            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                                auto variable = NumberVariables[Tokens[i + 1].val];
                                result -= variable;
                            }
                        }
                    }
                    i+=2;
                }

                NumberVariables[varName] = result;
                i++;            
            }
            else if (StringVariables.count(Tokens[i].val) == 1){
                StringVariables[Tokens[i].val] = Tokens[i + 2].val; 
                i += 4;
            }
            else{std::cout << "Error Invalid Variable" << std::endl;i++;}
        }

        else if(Tokens[i].token == TokenList::KeywordOutput){
            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                std::cout << NumberVariables[Tokens[i + 1].val] << std::endl;
            }
            else if (StringVariables.count(Tokens[i + 1].val) == 1){
                std::cout << StringVariables[Tokens[i + 1].val] << std::endl;
            }
            else if (Tokens[i + 1].token == TokenList::String){
                std::cout << Tokens[i + 1].val << std::endl;
            }
            else if (Tokens[i + 1].token == TokenList::Variable){
                std::cout << "Failed To Output Variable" << std::endl;
            }
            i += 3;
        }
        else if (Tokens[i].token == TokenList::KeywordDrnum){
            if (i + 2 < Tokens.size() && Tokens[i + 2].token == TokenList::LineEnder){
                NumberVariables[Tokens[i + 1].val] == 0;
                i+=3;
            }
            else{
                std::string varName = Tokens[i + 1].val;
                int result;
                if (NumberVariables.count(Tokens[i + 3].val) == 1){
                    result = NumberVariables[Tokens[i + 3].val];
                }
                else{
                    result = std::stoi(Tokens[i + 3].val);
                }
                
                i+=4;
                while(i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                    if (Tokens[i].token == TokenList::Plus){
                        if (Tokens[i + 1].token == TokenList::Number){
                            result += std::stoi(Tokens[i + 1].val);
                        }
                        else if (Tokens[i + 1].token == TokenList::Variable){
                            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                                auto variable = NumberVariables[Tokens[i + 1].val];
                                result += variable;
                            }
                        }
                    }
                    if (Tokens[i].token == TokenList::Minus){
                        if (Tokens[i + 1].token == TokenList::Number){
                            result -= std::stoi(Tokens[i + 1].val);
                        }
                        else if (Tokens[i + 1].token == TokenList::Variable){
                            if (NumberVariables.count(Tokens[i + 1].val) == 1){
                                auto variable = NumberVariables[Tokens[i + 1].val];
                                result -= variable;
                            }
                        }
                    }
                    i+=2;
                }

                NumberVariables[varName] = result;
                i++;
            }
        }
        else if(Tokens[i].token == TokenList::KeywordDr){
            if (i + 2 < Tokens.size() && Tokens[i + 2].token == TokenList::LineEnder){StringVariables[Tokens[i + 1].val] = "Null";i += 3;}
            else{
                if (Tokens[i + 3].token == TokenList::KeywordAutoPut){std::cout << "Error Variable != AutoPut" << std::endl;i+=5;}
                else{
                    std::string varName = Tokens[i + 1].val;
                    std::string result = Tokens[i + 3].val;
                    
                    if (Tokens[i + 3].token == TokenList::Variable){
                        result = StringVariables[Tokens[i + 3].val];
                    }
                    i+=4;

                    while (i < Tokens.size() && Tokens[i].token != TokenList::LineEnder){
                        if (Tokens[i].token == TokenList::Plus){
                            if(StringVariables.count(Tokens[i + 1].val) == 1){
                                result += StringVariables[Tokens[i + 1].val];
                            }
                            else if(Tokens[i + 1].token == TokenList::String){
                                result += Tokens[i + 1].val;
                            }
                        }
                        else if(Tokens[i].token == TokenList::Minus){
                            std::cout << "Failed To Decrease `String`" << std::endl;
                        }
                        i+=2;
                    }
                    StringVariables[varName] = result;
                    i++;
                }
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

    auto code_tokens = Tokenizer(code);
    Executer(code_tokens);

    return 0;
}