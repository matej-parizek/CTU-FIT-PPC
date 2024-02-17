#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "main.hpp"

// definition of the sort function according to name
/*bool sort_name::operator()(const Item *a, const Item * b){
    return false;
}*/



// constructor of the Item class
Item::Item(std::string a, std::string b){
    name=a; year=b;
}
void Item::id(int n) {ID=n;}
Item::~Item() {}

//@Override
bool Item::find(std::string argumment) { return false;}
std::string Item::getName(){return name;}
std::string Item::getStr() {return year;}
int Item::getID() {return ID;}
int Item::getYear(){return stoi(year);}

int main() {
	Database db;
	db.add(new Journal("IEEE Transaction on Computers", "C-35", "10", "1986"));
	db.add(new Journal("IEEE Transaction on Computers", "C-35", "11", "1986"));
	db.add(new Journal("IEEE Transactions on Communications", "28", "8", "1980"));
	db.add(new Book("Dva roky prazdnin", "Jules Verne", "1888"));
	db.add(new Book("Tajuplny ostrov", "Jules Verne", "1874"));
	db.add(new Book("Ocelove mesto", "Jules Verne", "1879"));
	std::string a;
	while (std::getline(std::cin, a)) {
		size_t position;
		if ((position = a.find(":")) == std::string::npos) {
			if (a == "list")
				db.list();
			if(a=="remove"){
				std::cout<<"+----------------------------------------------------------+"<<std::endl;
				std::cout<<"| "<<std::setw(56)<<std::left<<"Command \"remove\" expects some argument"<<" |"<<std::endl;
				std::cout<<"+----------------------------------------------------------+"<<std::endl;
			}
			if(a=="delete"){
				std::cout<<"+----------------------------------------------------------+"<<std::endl;
				std::cout<<"| "<<std::setw(56)<<std::left<<"Unknown command \"delete\""<<" |"<<std::endl;
				std::cout<<"+----------------------------------------------------------+"<<std::endl;
			}
			
		}
		else {
			std::string command = a.substr(0, position);
			std::string argument = a.substr(position+1);
			if (command == "find")
                db.find (argument);
            if (command == "remove") {
                int number=stoi(argument);
                db.remove(number);
            }
			if (command== "sort"){
				db.sorting(argument);
			}
			if (command=="erase"){
				db.erasing(argument);
			}
		}
    }
	return 0;
}