#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//#include <sstream>
using namespace std;

class rezerwacja;
class kalendarz;

class kalendarz
{
    string plik = "kalendarz.csv";
public:
    vector<vector<string>> otwartyKalendarz;
    void OtworzKalendarz();
    void wypiszKalendarz(rezerwacja rez);
    void zapiszKalendarz();
};

class rezerwacja
{

public:
    int typ;
    string data, godzina;

    rezerwacja(): typ(0){}

    void WybierzTypWizyty();
    void wybierzTermin(kalendarz &k);
};


int main() {
    kalendarz kalendarz1;
    rezerwacja rezerwacja1;

    rezerwacja1.WybierzTypWizyty();
    kalendarz1.OtworzKalendarz();

    kalendarz1.wypiszKalendarz(rezerwacja1);
    rezerwacja1.wybierzTermin(kalendarz1);
    kalendarz1.zapiszKalendarz();

    return 0;
}


void rezerwacja::WybierzTypWizyty()
{
    while(typ!=1 && typ!=2 && typ!=3)
    {
        cout << "1 - Wizyta kontrolna (15min)\n";
        cout << "2 - Leczenie 1 zeba (30min)\n";
        cout << "3 - Leczenie kanalowe zeba (60min)\n";
        cout << "Wybierz typ wizyty: ";
        cin >> typ; //nic skomplikowanego po prostu wybieram typ wizyty
    }
    if (typ==3)
    {
        typ++;
    }
}

void kalendarz::OtworzKalendarz()
{
    ifstream fin;
    fin.open(plik, ios::in);//otwieram plik do odczytu

    string line;
    string word;

    while(getline(fin,line)) //odczytuje po kolei linie pliku
    {
        vector<string> row;
        stringstream a(line);

        while(getline(a,word,',')) //a tutaj rozbijam linie na poszczegolne elementy
        {
            row.push_back(word);
        }
        otwartyKalendarz.push_back(row); //zapisuje wszystko w tablicy AxA string aby moc pozniej dokonac zmian
    }

    fin.close();
}

void kalendarz::wypiszKalendarz(rezerwacja rez)
{
    for(auto &lin : otwartyKalendarz) //dla kazdej linii vectora lines AxA
    {
        for(auto &l : lin) //dla kazdego elementu w linii
        {
            if(l.size()<1)
            {
                continue;
            }
            else if(l.size()==10) //tu sprawdzam czy element ma size==10 czyli jest data
            {
                cout << l << "\t";
            }
            else //a jezeli nie jest data to jest przedzialem godzinowym
            {
                stringstream o(l);
                string godziny1,minuty1,godziny2,minuty2;
                getline(o,godziny1,':');
                getline(o,minuty1,'-');
                getline(o,godziny2,':');
                getline(o,minuty2); //wyciagam poszczegolne godziny i minuty

                if(stoi(godziny2)*60+stoi(minuty2)-stoi(godziny1)*60-stoi(minuty1) ==rez.typ*15)
                { //sprawdzam czy dlugosc wizyty spelnia warunek typu wizyty
                    cout << l << '\t';
                } //wypisuje tylko godziny spelniajace dlugosc wizyty
            }


        }
        cout << endl;


    }


}

void rezerwacja::wybierzTermin(kalendarz &k)
{
    string s,dat,godz;
    while(!isdigit(dat[0]))
    {
        cout<< "Wybierz date rezerwacji: "; //wybieram date wizyty
        cin >> dat;
    }
    stringstream d(dat);


    getline(d,dat,'.'); //teraz szukam odpowiedniego indeksu linii
    int i = stoi(dat); //i przechowuje indeks linii

    int licznik = 1;
    vector<string> temp;
    for(auto &a : k.otwartyKalendarz[i-1]) //odczytuje godziny z odpowiedniej linii
    {
        if(a.size()<1)
        {
            continue;
        }
        else if(a.size()==10)
        {
            cout << "\nWolne godziny " << a << '\n';
        }
        else {
            stringstream o(a);
            string godziny1, minuty1, godziny2, minuty2;
            getline(o, godziny1, ':');
            getline(o, minuty1, '-');
            getline(o, godziny2, ':');
            getline(o, minuty2);

            if (stoi(godziny2) * 60 + stoi(minuty2) - stoi(godziny1) * 60 - stoi(minuty1) == typ * 15)
            {
                cout << licznik <<"-->" << a << '\n';
                licznik++;
                temp.push_back(a);
            } //jezeli godzina spelnia typ wizyty to ja wypisuje z odpowiednim indexem
        }// i wrzucam do tablicy aby latwiej pozniej bylo wybrac rezerwacje
    }

    cout << "\nWybierz godzine rezerwacji: ";
    cin >> godz; //teraz wybieram godzine rezerwacji

    data = k.otwartyKalendarz[i-1][0];
    godzina = temp[stoi(godz)-1];
    cout << "Twoja rezerwacja to: " << data << " godzina " << godzina;

    for(auto &x : k.otwartyKalendarz[i-1]) //w tablicy AxA zmieniam a nawet usuwam zarezerwowana godzine
    {
        if(x==godzina)
        {
            x="";
            break;
        }
    }
}

void kalendarz::zapiszKalendarz()
{
    ofstream fileOut(plik); //otwieram plik csv do zapisu

    for(auto &a : otwartyKalendarz)
    {
        stringstream updatedLine;
        for (size_t i = 0; i < a.size(); i++) { //tworze linie kalendarza
            updatedLine << a[i];
            if (i < a.size() - 1) {
                updatedLine << ",";
            }
        }
        fileOut << updatedLine.str() << endl; //nadpisuje linie w pliku z kalendarzem
    }


}

/*
 * wybrać typ wizyty
 * otworz kalendarz
 * wyswietl wizyty ktore mieszcza sie w limicie
 * wybierz godzine wizyty
 * wyswietl dane rezerwacji
 * potwierdz rezerwacje
 * zmien dane w kalendarzu
 * zapisz kalendarz
 */