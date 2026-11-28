#pragma once
#include <vector>
#include <map>
#include <string>
#include "Environment.h"
#include "Tokens.h"

class StopHandler{
    public:
        void Execute(std::vector<Token>& Tokens,int&i);
};

class Ignore{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i);
};

class Output{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Input{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Dr{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Drnum{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Assigne{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Function{
    private:
        std::map<std::string, int> func;
        std::vector<int> stack;
        int braceDepth = 0;
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
        void CallFunction(const std::vector<Token>& Tokens,int&i, Environment& env);
        void OnLBrace();
        bool OnRBrace(int& i);
};

class If{
    public:
        void Execute(const std::vector<Token>& Tokens, int& i, Environment& env, Function& func);
};

class Else{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Length{
    public:
        void Execute(const std::vector<Token>& Tokens,int&i, Environment& env);
};

class Use{
    private:
        std::vector<std::string> exist = {"system"};
        std::vector<std::string> uses;
    public:
        void Activate(const std::vector<Token>& Tokens,int&i);
        bool IsActivated(const std::string& libname);
};

class System{
    private:
        void RunCmd(const std::vector<Token>& Tokens, int& i, Environment& env);
    public:
        void Execute(const std::vector<Token>& Tokens, int& i, Environment& env, Use& use);
};

class Executer{
    public:
        void Execute(std::vector<Token>& Tokens,Environment& env);
};