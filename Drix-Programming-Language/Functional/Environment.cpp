#include <map>
#include <string>
#include <vector>
#include "../Environment.h"

void Environment::CreateString(const std::string& name, const std::string& value){
    StringVariables[name] = value;
}
void Environment::CreateNumber(const std::string& name, const int& value){
    NumberVariables[name] = value;
}
std::string Environment::GetString(const std::string& name){
    if (StringVariables.count(name) == 1){
        return StringVariables[name];
    }
    return "";
}
int Environment::GetNumber(const std::string& name){
    if (NumberVariables.count(name) == 1){
        return NumberVariables[name];
    }
    return 0;
}

bool Environment::StringExists(const std::string& name){
    if (StringVariables.count(name) == 1){
        return true;
    }
    return false;
}

bool Environment::NumberExists(const std::string& name){
    if (NumberVariables.count(name) == 1){
        return true;
    }
    return false;
}
