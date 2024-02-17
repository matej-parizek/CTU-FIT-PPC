#include <iostream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include "main.hpp"

Journal::Journal(std::string x, std::string y, std::string u, std::string v)
: Item(x,v){
    volume=y;issue=u;
}
//
bool Journal::find(std::string x){
    return (name.find(x)!=std::string::npos
    || volume.find(x)!=std::string::npos
    || year.find(x)!=std::string::npos
    || issue.find(x)!=std::string::npos)
    ? true : false;
}
std::string Journal::getStr() {
    return year+", "+volume+"("+issue+")";
}
Journal::~Journal(){}