#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "main.hpp"
#include "parse.hpp"
#include <cmath>

int main(){
    std::vector<config_t> configure; /* udelal jsem ja pole struktur*/
    configure.push_back(getConfig("config.min=-99"));
    configure.push_back(getConfig("config.max=100"));
    configure.push_back(getConfig("config.width=3"));
    configure.push_back(getConfig("config.align=left"));
    int min=-99,max=100,width=3,header = 1, stretch = 0;
    bool state = false; std::string align= "left";
    
    // variable for decoded config
    config_t config;
    std::string line;
    do{
        std::getline(std::cin, line);
        config = getConfig(line);

        if(config.valid){
           // todo
           int number;

           /*vytvorit z value cislo pokud to nebude left or right s pouzitim try and catch exception stejne jak je to v sum
            * nize napsane */
           try{
               number=std::stoi(config.value);
                if(config.type=="min")
                    min=number;
                if(config.type=="max")
                    max=number;
                if(config.type== "width")
                    width=number;
                if(config.type=="header")
                    header=number;
                if(config.type=="stretch")
                {
                    stretch=number;
                    state = true;
                }    
           }
           catch(const std::exception& e){
               if(config.value!="left" && config.value!="right" ) {
                   std::cerr << "Invalid input" << std::endl;
                   return 101;
                }
                else if(config.type=="align" )
                    align=config.value;

           }
           //std::cout<< width<< "    " << min<<"     "<<max<<std::endl;
           /*kontorla vstupu Invalid configuration*/
            if(min>max || width<1 || header < 0 || header > 1 || stretch < 0 || stretch > 1){
                std::cerr << "Invalid configuration" << std::endl;
                return 102;
            }

           /* Zde jsem vytvoril zda je jiz obsazen v poli*/
           for (auto i=configure.begin(); i!=configure.end();++i)
                if((*i).type==config.type)
                    (*i).value=config.value;
            if (config.type=="stretch")
                configure.push_back(config);
            if (config.type=="header")
                configure.push_back(config);
                
                

        }
    }while(config.valid);

    std::vector<std::vector<int>> values;

    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;
        

        while (std::getline(ss,cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);

                if(number<min || number>max){   /*Kontrola Out of range*/
                    std::cerr << "Out of range" << std::endl;
                    return 100;
                }
                if(number >= pow(10, width+1)){   /*Kontrola Cell is too short*/
                    if(state == false)
                    {
                        std::cerr << "Cell is too short" << std::endl;
                        return 103;
                    }
                    
                }
				row.push_back(number);
            }
            catch(const std::exception& e){ // if there is a text (SUM?)

                sum_t sumary=getSum(cell,row); /* pridal jsem bude pocitat sumu uprava v parse proto funguje !sumary.valid*/
                if(!sumary.valid) {
                    std::cerr << "Invalid input" << std::endl;
                    return 101;
                }
                int sum = sumary.value; //zde jsem dal sumary.value
                if(sumary.value >= pow(10, width+1)){   /*Kontrola Cell is too short*/
                    if(state == false)
                    {
                        std::cerr << "Cell is too short" << std::endl;
                        return 103;
                    }
                }
                row.push_back(sum);
            }     
        }
        values.push_back(row);
        
    }
    if( stretch == 1)
    {
        for (int i = 0; i < (int)values.size(); i++)
        {
            for (int j = 0; j < (int)values[i].size(); j++)
            {
                for(;values[i][j] > pow(10, width);)
                {
                    width += 1;
                }
                
            }
        }
    }

    
    // print out the config - TODO
    for (auto i= configure.begin(); i!=configure.end(); ++i)
    {
        if((*i).type=="width" && stretch == 1 && state ==true)
            (*i).value= std::to_string(width);
        std::cout<<"config."<<(*i).type<<"="<<(*i).value<<std::endl;
    }
    std::cout<<std::endl;

    //TODO - upravit print table
    
    // print table
    int max_val = 0;
    for (auto i = 0; i < (int)values.size(); i++)
    {
        if(max_val < (int)values[i].size()){
            max_val = values[i].size();
        }
    }
   
   //Horni ABCD...
   if (header != 0)
   {
        for (auto i = 0; i < max_val + 1; i++)
        {
            std::cout << "+";
            for (int k = 0; k <= width+1; k++)
            {
                std::cout << "-";
            }
            
        }
        std::cout << "+" << std::endl;
        if ((align =="left")){
            char x = 64;
            for (auto i = 0; i < max_val; i++)
            {
                if (i == 0)
                {
                    std::cout << std::left << "| " << std::setw(width) << " " << " ";
                }
                
                ++x;
                std::cout << std::left << "| " << std::setw(width) << x << " ";
            }
            std::cout << "|" << std::endl;
        }
        else{
            char x =64;
            for (auto i = 0; i < max_val; i++)
            {
                if (i == 0)
                {
                    std::cout << std::right << "| " << std::setw(width) << " " << " ";
                }
                
                ++x;
                std::cout << std::right << "| " << std::setw(width) << x << " ";
            }
            std::cout << "|" << std::endl;
        }
    }
   
    //Table
    for (auto i = 0; i < (int)values.size(); i++){
        
        if (align == "left")
        {
            if (header != 0)
            {
                for (auto j = 0; j < max_val + 1; j++)
                {
                    std::cout << "+";
                    for (int k = 0; k <= width + 1; k++)
                    {
                        std::cout << "-";
                    }
                    
                }
                std::cout << "+" << std::endl;
            }
            else
            {
                for (auto j = 0; j < max_val; j++)
                {
                    std::cout << "+";
                    for (int k = 0; k <= width + 1; k++)
                    {
                        std::cout << "-";
                    }
                    
                }
                std::cout << "+" << std::endl;
            }

            for (auto j = 0; j < max_val; j++){
                
                if (j == 0 && header != 0)
                {
                    std::cout << std::left << "| " << std::setw(width) << i + 1 << " ";
                }
                
                if (j < (int)values[i].size()){
                    if(stretch==0 && state==true && values[i][j]>=pow(10,width)){
                        std::cout << std::left << "| ";
                        for(int l=0 ; l<width; l++)
                            std::cout<<"#";
                        std::cout<<(char)32;
                    }
                    else
                        std::cout << std::left << "| " << std::setw(width) << values[i][j] << " ";

                }
                else{
                    std::cout << std::left << "| " << std::setw(width) << " " << " ";
                }
            
                
                                          
            }
            std::cout << "|" << std::endl;
        }   
        else{
            if (header != 0)
            {
                for (auto j = 0; j < max_val + 1; j++)
                {
                    std::cout << "+";
                    for (int k = 0; k <= width + 1; k++)
                    {
                        std::cout << "-";
                    }
                    
                }
                std::cout << "+" << std::endl;
            }
            else
            {
                for (auto j = 0; j < max_val; j++)
                {
                    std::cout << "+";
                    for (int k = 0; k <= width + 1; k++)
                    {
                        std::cout << "-";
                    }
                    
                }
                std::cout << "+" << std::endl;
            }

            for (auto j = 0; j < max_val; j++){
                
                if (j == 0 && header != 0)
                {
                    std::cout << std::right << "| " << std::setw(width) << i + 1 << " ";
                }
                
                if (j < (int)values[i].size()){
                    if(stretch==0 && state==true && values[i][j]>=pow(10,width)){
                        std::cout << std::right << "| ";
                        for(int l=0 ; l<width; l++)
                            std::cout<<"#";
                        std::cout<<(char)32;
                    }
                    else
                        std::cout << std::right << "| " << std::setw(width) << values[i][j] << " ";

                }
                else{
                    std::cout << std::right << "| " << std::setw(width) << " " << " ";
                }                                          
            }
            std::cout << "|" << std::endl;
        }
    }
    if (header != 0)
    {
        for (auto i = 0; i < max_val + 1; i++)
        {
            std::cout << "+";
            for (int k = 0; k <= width+1; k++)
            {
                std::cout << "-";
            }
            
        }
        std::cout << "+" << std::endl;
    }
    else
    {
        for (auto i = 0; i < max_val; i++)
        {
            std::cout << "+";
            for (int k = 0; k <= width+1; k++)
            {
                std::cout << "-";
            }
            
        }
        std::cout << "+" << std::endl;
    }
    
    return 0;
}