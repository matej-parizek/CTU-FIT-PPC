#include <iostream>
#include <sstream>
#include <algorithm>
#include "main.hpp"
#include <vector>
#include <iomanip>

void print(Item * tmp){
    // tmp->getName() vrati name
    // tmp->getStr() vrati str = year autor apod.
    // tmp->getID() vrati ID

    std::cout<<"|"<<std::setw(3)<<std::right<< tmp->getID()<<" | "
    <<std::setw(51)<< std::left<<tmp->getName()<<" |"<<std::endl;
    std::cout<<"| "<<std::setw(2)<<""<<" | "<<std::setw(51)<<std::left<<tmp->getStr()<<" |"<<std::endl;
    std::cout<<"+----+-----------------------------------------------------+"<<std::endl;
    
}


Database::Database(){
    ID=1;
}

// add item to the database
void Database::add(Item * a) {
    a->id(ID);
    ID++;
    db.push_back(a);
}

Database::~Database(){
    for (auto i = db.begin(); i != db.end(); i++)
        delete *i;
    db.clear();
}



void Database::find( std::string argument) {

    std::cout<<"+----------------------------------------------------------+"<<std::endl;
    int count=0;
    for (auto i = db.begin(); i != db.end(); i++) {
        if((*i)->find(argument)) {
            if(count==0){
                std::cout<<"| Search for \""<<std::left<<std::setw(45)<<argument+"\" "<<"|"<<std::endl;
                std::cout<<"+----+-----------------------------------------------------+"<<std::endl;
            }
            print(*i);
            count++;
        }
    }
    std::cout<<"| Total: "<<std::setw(50)<<std::left<<std::to_string(count)<<"|"<<std::endl;
    std::cout<<"+----------------------------------------------------------+"<<std::endl;
}
void Database::list() {
    std::cout<<"+----------------------------------------------------------+"<<std::endl;
    std::cout<<"| List of all records "<<std::setw(37)<<" "<<"|"<<std::endl;
    std::cout<<"+----+-----------------------------------------------------+"<<std::endl;
    int count=0;
    for (auto i = db.begin(); i != db.end(); i++) {
        print(*i);
        count++;
    }
    //61 znaku to je
    std::cout<<"| Total: "<<std::setw(50)<<std::left<<std::to_string(count)<<"|"<<std::endl;
    std::cout<<"+----------------------------------------------------------+"<<std::endl;
}
void  Database::remove(int argument) { 
    auto tmp=db.end()-1;
    if((*tmp)->getID()==argument){
        db.erase(tmp);
        delete *tmp;
        return;
    }
    for (auto i = db.begin(); i != db.end(); i++) {
        if((*i)->getID()==argument) {
            delete *i;
            db.erase(i);
            return;
        }
    }
    std::cout<<"+----------------------------------------------------------+"<<std::endl;
	std::cout<<"| "<<std::setw(56)<<std::left<<"ID = "+ std::to_string(argument) +" is not in the database"<<" |"<<std::endl;
	std::cout<<"+----------------------------------------------------------+"<<std::endl;
}

void Database::erasing(std::string argument){
    auto tmp=db.end()-1;
    if((*tmp)->find(argument)){
        db.erase(tmp);
        delete *tmp;
    }
    for (auto i = db.begin(); i != db.end(); i++) {
        if((*i)->find(argument)) {
            delete *i;
            db.erase(i);
        }
        
    }
    tmp=db.end()-1;
    if((*tmp)->find(argument)){
        db.erase(tmp);
        delete *tmp;
    }
}

bool cmp6(Item*a, Item*b){
	return a->getID() > b->getID();
}
bool cmp5(Item*a, Item*b){

	return a->getID() < b->getID();
}

bool cmp2(Item*a, Item*b){
	if(a->getName() <b->getName())
        return true;
    else if( a->getName() == b->getName())
        return cmp6(a,b);
	else
        return false;
}
bool cmp1(Item*a, Item*b){
	if(a->getName() >b->getName())
        return true;
    else if( a->getName() == b->getName())
        return cmp5(a,b);
	else
        return false;
}
bool cmp4(Item*a, Item*b){
    if(a->getYear() <b->getYear())
        return true;
    else if( a->getYear() == b->getYear())
        return cmp5(a,b);
	else
        return false;
}
bool cmp3(Item*a, Item*b){
	if(a->getYear() >b->getYear())
        return true;
    else if( a->getYear() == b->getYear())
        return cmp6(a,b);
	else
        return false;
}

//Pouziti sort(tmp.begin(),tmp.end(),cmp)
void Database::sorting(std::string arg){
    if(arg == "name:desc"){
        std::sort(db.begin(),db.end(),cmp1);
        return;
    }
    if(arg == "name:asc" || arg == "name"){
        sort(db.begin(),db.end(),cmp2);
        return;
    }
    if(arg == "year:desc"){
        sort(db.begin(),db.end(),cmp3);
        return;
    }
    if(arg == "year:asc" || arg == "year"){
        sort(db.begin(),db.end(),cmp4);
        return;
    }
    if(arg == "id:desc"){
        sort(db.begin(),db.end(),cmp5);
        return;
    }
    if(arg == "id:asc" || arg=="id" ){
        sort(db.begin(),db.end(),cmp6);
        return;
    }
    std::cout<<"+----------------------------------------------------------+"<<std::endl;
    std::cout<<"| "<<std::setw(57)<<std::left<<"Unknown sorting order"<<" |"<<std::endl;
    std::cout<<"+----------------------------------------------------------+"<<std::endl;
    

}
