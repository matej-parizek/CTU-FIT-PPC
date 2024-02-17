#include <iostream>
#include <iomanip>
#include <vector>
#include "doprava.hpp"
#include <algorithm>

//Feel free to create your solution in multiple files
// and add the includes here. e.g.:
//#include "solution.hpp"

class Drivers
{
    public:

    string name;
    int L;
    int nC;
    int nSt;

    Drivers(string x, int l, int nc, int nst){
        name=x; L=l; nC=nc; nSt=nst;
    }
};

using namespace std;

bool compareInterval(Drivers d1, Drivers d2)
{
    /*if(d1.L == -1){
        return false;
    }*/
    if(d1.nSt > d2.nSt){
        return true;
    }
    else if(d1.nSt == d2.nSt){
        return d1.name < d2.name;

    }
    else{
        return false;
    }

}

void printTable3(vector<Drivers> drivers){

    sort(drivers.begin(),drivers.end(),compareInterval);

    cout << "+----------------------+---+----+-----+"<<endl;
    cout <<"| " << setw(21) << left <<"Driver Name"<<"| "<<"L"<<" | "<<"nC"<<" | "<<"nSt"<<" |" << endl;
    cout <<"+----------------------+---+----+-----+"<<endl;

    for(int i=0; i<(int)drivers.size();i++ ){
        
        if (drivers.at(i).L == -1){
            cout<<"| "<< setw(21)<<left<<drivers.at(i).name<<
            "| "<<"X"<<" | "<<"XX"<<" | "<<"XXX"<<" |"<<endl;
        }
        else{
            cout<<"| "<< setw(21)<<left<<drivers.at(i).name<<
            "| "<< drivers.at(i).L<<
            " | "<<setw(2)<<right<< drivers.at(i).nC<<
            " | "<<setw(3)<<drivers.at(i).nSt<<" |"<<endl;        
        }
        
    }

    cout<<"+----------------------+---+----+-----+"<<endl;
}

void printTable2(Network net){
    
    for(auto i=0; i<net.nlines(); i++){
            
        cout << "+------------------------------------------------------------------------------+" << endl;
        cout << "| " << left << "Line: " << setw(70) << i << " |" <<endl;
        cout << "+---+----+-----------------------------++---+----+-----------------------------+" << endl;
        cout << "| " << "d" << " | " << "rT" << " | " << setw(28) << left << "==>" << "|| "
        << "d" << " | " << "rT" << " | " << setw(28) << left << "<==" << "|" << endl; 
        cout << "+---+----+-----------------------------++---+----+-----------------------------+" << endl;

        auto zacetek = net.getLine(i).stops;

        
        auto timeFwd=net.getLine(i).conns_fwd.at(0);
        //auto timeBwd=net.getLine(i).conns_bwd.at(0);
        Time fwdZacatek=Time(timeFwd.at(0).ti.gets());
        Time FwdKonec=Time(timeFwd.at(zacetek.size()-1).ti.gets());
        for (auto j = 0; j < (int) zacetek.size(); j++){
            int valFwd=0,zacatekFwd=0, valBwd=0, zacatekBwd=0;
            Time aktulFwd= Time(timeFwd.at(j).ti.gets());
            Time aktulBwd= Time(timeFwd.at(zacetek.size()-j-1).ti.gets());
            if(j>0){

                Time prevFwd= Time(timeFwd.at(j-1).ti.gets());
                Time vysledekFwd= aktulFwd-prevFwd;
                valFwd=vysledekFwd.gets()/60;
                vysledekFwd=aktulFwd-fwdZacatek;
                zacatekFwd=vysledekFwd.gets()/60;
                
                Time prevFwdBack= Time(timeFwd.at(zacetek.size()-j).ti.gets());
                vysledekFwd=prevFwdBack-aktulBwd;
                valBwd=vysledekFwd.gets()/60;
                vysledekFwd=FwdKonec-aktulBwd;
                zacatekBwd=vysledekFwd.gets()/60;
            }

            cout << "| " << valFwd<< " | " <<right<< setw(2)<<setfill('0')<< zacatekFwd
            <<left<<setfill(' ') << " | " <<setw(28) << left << zacetek.at(j)
            << "|| " << valBwd << " | " << right << setw(2)<< setfill('0')<< zacatekBwd
            << left << setfill(' ') << " | " 
            << setw(28) << left << zacetek.at(zacetek.size()-1-j) << "|" << endl;
        }
        cout << "+---+----+-----------------------------++---+----+-----------------------------+"<<endl;

    }   

}

void printTable1(Network net, const string stop_in){
    for( auto i=0; i<net.nlines();i++ ){
        auto line = net.getLine(i).stops;
        auto stop=line.begin();
        for(;stop!=line.end();stop++){
            if(*stop==stop_in){
                break;
            }
        }
        if(stop==line.end())
            continue;
        string endState = line.front();
        string startState = line.back();
        
        //Vypisovani tabulky
        cout << "+------------------------------------------------------------------------------+" << "\n";
        cout << "| " << setw(69) << left << stop_in << right << "Line: " << i <<" |" <<"\n";
        cout << "+--------------------------------------++--------------------------------------+" << "\n";
        cout<<"| "<< setw(37) << left <<"To: "+startState<<"||"
        << setw(37) << " To: " +endState<< " |" <<  endl;
        cout << "+----+---------------------------------++----+---------------------------------+" << "\n";

        int len = stop-line.begin(); //pozice zastavky

        vector <PlanConn> zacatek= net.getLine(i).conns_fwd;
        vector <PlanConn> konec= net.getLine(i).conns_bwd; //vektor vsech zastavek vsech stanic
        for (int h = 0; h < 24; h++)
        {
            
            string bwd_buffer;
            string fwd_buffer;
            for(auto tmp = konec.begin(); tmp!= konec.end(); tmp++){ //prochazime ten vektor az do konce
                int hh,mm, ss =tmp->at(len).ti.gets(); // vybereme cas kdyz autobus dorazi do te zastavky 
                tmp->at(len).ti.gett(hh,mm,ss);
                
                if(hh==h){
                    string buf = to_string(mm);
                    if(mm/10<1)
                        bwd_buffer.append(" 0"+buf);
                    else
                        bwd_buffer.append(" "+buf);
                }
            }
            for (auto tmp = zacatek.begin() ;tmp!=zacatek.end(); tmp++){
                int hh,mm, ss =tmp->at(len).ti.gets(); // vybereme cas kdyz autobus dorazi do te zastavky 
                tmp->at(len).ti.gett(hh,mm,ss);
                
                if(hh==h){
                    string buf = to_string(mm);
                    if(mm/10<1)
                        fwd_buffer.append(" 0"+buf);
                    else
                        fwd_buffer.append(" "+buf);
                }
            }

            cout<<"| " <<right<< setw(2) << setfill('0')<< h<< setfill(' ')<<" |"
            <<setw(33) << left<< fwd_buffer
            << right<<"|| " << setw(2) << setfill('0')<< h<< setfill(' ')<<" |"
            << setw(33)<<left<<bwd_buffer << "|"
            <<endl;
        }

        cout << "+----+---------------------------------++----+---------------------------------+" << endl;
    
    }

}

int main(int argc, char** argv) {

    // Load files:
    DriverList dl;
    dl.loadFromFile("driver_list.txt");

    Network net;
    net.loadFromFile("network.txt");

    // variables for argument decoding
    string flag_in;
    list<string> stop_in;

    if (argc > 1)
        flag_in = string(argv[1]);
    else
    {
        cerr << "Missing argument. Terminating." << endl;
        return 1;
    }

    if ((!flag_in.compare("--schedule")))
    {
        // input check - do not edit
        if (argc > 2)
        {
            for (int i = 2; i < argc; i++)
            {
                string temp = argv[i];
                replace(temp.begin(), temp.end(), '_', ' ');
                stop_in.push_back(temp);
            }
        }
        else
        {
            cerr << "Missing stop name. Terminating." << endl;
            return 2;
        }
        // end of input check

        /* here should start the code for printing timetables*/
        /* stop_in contains names of stops, for which the timetable is to be printed. */
        
        /*Veci k networku*/
        for(string l : stop_in){ //odkud to jede
            printTable1(net,l);
        }

        // This is an example, how it can be done using lambda-function
        //for_each(stop_in.begin(), stop_in.end(), [&] (string stop_name) {print_timetable(net,stop_name);} );
        // This is an example, how it can be done using for-loop 
        // for( auto iter = stop_in.begin(); iter != stop_in.end(); iter++) print_timetable(net,*iter);

        /* here should end the code for printing timetables*/
    }
    else if ((!flag_in.compare("--line-routing")))
    {

        /* here should start the code for printing line routes without stats*/

        printTable2(net);

        /* here should end the code for printing line routes without stats*/
    }
    else if ((!flag_in.compare("--driver-stops")))
    {
        /* here should start the code for stops statistics for drivers */
        
        vector<Drivers> drivers;
        int count =0;
        int c=0;
        int num=-1;
        for( auto tmp = dl.begin(); tmp != dl.end(); tmp++){
            for(int i=0; i<net.nlines(); i++){   
                for(int j=0 ; j< (int)net.getLine(i).conns_bwd.size(); j++){
                //cout << net.getLine(i).conns_bwd.at(j).drv.name << "    "<<i<<endl;
                    if(net.getLine(i).conns_bwd.at(j).drv.name == tmp->name){//ridici 
                    c+=1;
                    count+=net.getLine(i).conns_bwd.at(j).size();
                    num=i;
                    }       
                }
                for(int j=0 ; j< (int)net.getLine(i).conns_fwd.size(); j++){
                //cout << net.getLine(i).conns_bwd.at(j).drv.name << "    "<<i<<endl;
                    if(net.getLine(i).conns_fwd.at(j).drv.name == tmp->name){//ridici 
                        c+=1;
                    count+=net.getLine(i).conns_fwd.at(j).size();
                    num=i;
                    }       
                }
            }
            drivers.push_back(Drivers(tmp->name,num,c,count));
            c=0;
            num=-1;
            count=0;
        }
        printTable3(drivers);

        /* here should end the code for stops statistics for drivers */
    }
    else
    {
        cout << "Flag not recognized, terminating." << endl;
    }
    
    return 0;
}