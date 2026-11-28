#pragma once
#include <map>
#include <string>
#include <vector>
#include "Tokens.h"

class Environment{
    private:
        std::map<std::string,int> NumberVariables;
        std::map<std::string,std::string> StringVariables;
    public:
        void CreateString(const std::string& name, const std::string& value);
        void CreateNumber(const std::string& name, const int& value);
        std::string GetString(const std::string& name);
        int GetNumber(const std::string& name);

        bool StringExists(const std::string& name);

        bool NumberExists(const std::string& name);
};