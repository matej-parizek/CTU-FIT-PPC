#include <vector>
#include <string>

#ifndef __MAIN_HPP__
#define __MAIN_HPP__

//struct sort_name;

class Item{
    protected:
		int ID;
		std::string name, year;
	public:
		Item (std::string a, std::string b);
		virtual ~Item ();
        bool virtual find(std::string argument);
        std::string getName();
        virtual std::string getStr();
        void id(int n);
        int getID();
        int getYear();
		//friend sort_name;
};

// Book related to the Database
class Book: public Item{
    protected:
        std::string author;
    public:
        Book(std::string x,std::string y, std::string z);
        bool find(std::string argument);
        std::string getStr();
        ~Book();
};

// Journal related to the Database
class Journal: public Item{
    protected:
        std::string volume, issue;
    public:
        Journal(std::string x, std::string y, std::string u, std::string name);
        bool find(std::string argument);
        std::string getStr();
        ~Journal();
};

// declaration of the sort function according to name
/*struct sort_name {
	inline bool operator() (const Item *a, const Item * b);
};*/

class Database {
	private:
        int ID;
		std::vector<Item *> db;
	public:
        Database ();
		~Database();
		void add(Item * a);
        void list();
        void find(std::string argument);
        void remove(int argument);
        void erasing(std::string argument);
        void sorting(std::string arg);
};

#endif // __MAIN_HPP__