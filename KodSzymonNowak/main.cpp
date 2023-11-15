#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "classes.h"
#include "functions.cpp"
using namespace std;

vector<string> readTXT(const string& filename);

const string filename = "daty.txt";
vector<string> days = readTXT(filename);

string getDays(int id){
    if (id >= 0 && id < days.size()) {
        return days[id];
    } else {
        cerr << "Blad: Nieprawidlowe ID." << endl << days[0];
        return "";
    }
}

int main() {
    Kalendarz k1;
    while(true){
        int id;
        cout<<"Podaj ID sprzetu, (0 aby wyjsc z programu): ";
        cin>>id;

        if(id == 0)
            break;

        Sprzet s1(id, k1);
        string day = getDays(s1.id);
        Wydarzenie w1(day, s1.id);
        
        char c;
        if(s1.id != 0){
            cout<<"Czy potwierdzasz ustawienie przypomnien w dniu "<<day<< " (T): ";
            cin>>c;
            if(c == 'T')
                k1.push_event(w1);
        }else if (s1.id == 0)
            break;
        else
            continue;
        }
    return 0;
}


vector<string> readTXT(const string &filename) {
    vector<string> result;
    fstream hander;
    hander.open(filename);

    if (!hander.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku!" << endl;
        return result;
    }
    string line;
    getline(hander,line);
    while (line != "end") {
        //cout<<line;
        result.push_back(line);
        getline(hander,line);
    }
    hander.close();
    return result;
}

