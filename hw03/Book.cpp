#include <iostream>
#include <sstream>
#include <algorithm>
#include "main.hpp"

//constructor Book
Book::Book(std::string x, std::string y, std::string z) : Item(x,z)
{author=y;}

//Hledani slova
bool Book::find(std::string x) {
    return (name.find(x)!=std::string::npos
    || author.find(x)!=std::string::npos
    || year.find(x)!=std::string::npos)
    ? true : false;
}
std::string Book::getStr() {return year+", "+author;}
Book::~Book() {}
