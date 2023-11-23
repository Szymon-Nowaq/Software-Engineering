#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class Pacjent {
public:
    string imie;
    string nazwisko;

    Pacjent(const string& imie, const string& nazwisko) : imie(imie), nazwisko(nazwisko) {}
};


class Wizyta {
public:
    string data;
    Pacjent pacjent;

    Wizyta(const string& data, const Pacjent& pacjent) : data(data), pacjent(pacjent) {}
};


void wczytajPacjentow(vector<Pacjent>& pacjenci, const string& plik) {
    ifstream plikPacjenci(plik);
    if (plikPacjenci.is_open()) {
        string imie, nazwisko;
        while (plikPacjenci >> imie >> nazwisko) {
            pacjenci.push_back(Pacjent(imie, nazwisko));
        }
        plikPacjenci.close();
    }
}


void wczytajWizyty(vector<Wizyta>& wizyty, const string& plik) {
    ifstream plikWizyty(plik);
    if (plikWizyty.is_open()) {
        string data, imie, nazwisko;
        while (plikWizyty >> data >> imie >> nazwisko) {
            wizyty.push_back(Wizyta(data, Pacjent(imie, nazwisko)));
        }
        plikWizyty.close();
    }
}


void zapiszPacjentow(const vector<Pacjent>& pacjenci, const string& plik) {
    ofstream plikPacjenci(plik);
    if (plikPacjenci.is_open()) {
        for (const auto& pacjent : pacjenci) {
            plikPacjenci << pacjent.imie << " " << pacjent.nazwisko << "\n";
        }
        plikPacjenci.close();
    }
}


void zapiszWizyty(const vector<Wizyta>& wizyty, const string& plik) {
    ofstream plikWizyty(plik);
    if (plikWizyty.is_open()) {
        for (const auto& wizyta : wizyty) {
            plikWizyty << wizyta.data << " " << wizyta.pacjent.imie << " " << wizyta.pacjent.nazwisko << "\n";
        }
        plikWizyty.close();
    }
}


void wyswietlKalendarz(const vector<Wizyta>& wizyty) {
    cout << "Aktualne Wizyty:\n";
    for (const auto& wizyta : wizyty) {
        cout << "Data: " << wizyta.data << ", Pacjent: " << wizyta.pacjent.imie << " " << wizyta.pacjent.nazwisko << "\n";
    }
}


bool czyNowyPacjent(const vector<Pacjent>& pacjenci, const string& imie, const string& nazwisko) {
    return find_if(pacjenci.begin(), pacjenci.end(),
        [imie, nazwisko](const Pacjent& pacjent) { return pacjent.imie == imie && pacjent.nazwisko == nazwisko; }) == pacjenci.end();
}


bool czyDataDostepna(const vector<Wizyta>& wizyty, const string& data) {
    return find_if(wizyty.begin(), wizyty.end(),
        [data](const Wizyta& wizyta) { return wizyta.data == data; }) == wizyty.end();
}


void umowWizyte(vector<Wizyta>& wizyty, const vector<Pacjent>& pacjenci, const string& imie, const string& nazwisko) {
    string data;
    cout << "Podaj date wizyty wedlug wzoru (RRRR.MM.DD): ";
    cin >> data;

    while (!czyDataDostepna(wizyty, data)) {
        cout << "Data zajeta. Podaj inna date wizyty wedlug wzoru (RRRR-MM-DD): ";
        cin >> data;
    }

    auto pacjent = find_if(pacjenci.begin(), pacjenci.end(),
        [imie, nazwisko](const Pacjent& p) { return p.imie == imie && p.nazwisko == nazwisko; });

    if (pacjent != pacjenci.end()) {
        wizyty.push_back({ data, *pacjent });
        cout << endl << "Umowiono wizyte dla " << imie << " " << nazwisko << " na " << data << "\n";
    }
}


void przelozWizyte(vector<Wizyta>& wizyty) {
    string staraData, nowaData;
    cout << "Podaj aktualna date wizyty (RRRR-MM-DD): ";
    cin >> staraData;

    auto it = find_if(wizyty.begin(), wizyty.end(),
        [staraData](const Wizyta& wizyta) { return wizyta.data == staraData; });
    while (it == wizyty.end()) {
        cout << "Nie znaleziono wizyty na " << staraData << ". Podaj poprawna date: ";
        cin >> staraData;
        it = find_if(wizyty.begin(), wizyty.end(),
            [staraData](const Wizyta& wizyta) { return wizyta.data == staraData; });
    }
    do {
        cout << "Podaj nowa date wizyty (RRRR-MM-DD): ";
        cin >> nowaData;

        if (!czyDataDostepna(wizyty, nowaData)) {
            cout << "Termin zajety. Nie mozna przelozyc wizyty.\n";
        }
    } while (!czyDataDostepna(wizyty, nowaData));
    it->data = nowaData;
    cout << "Wizyta przelozona z " << staraData << " na " << nowaData << "\n";
}


void obsluzJuzZarejestrowanegoPacjenta(vector<Wizyta>& wizyty, const vector<Pacjent>& pacjenci, const string& imie, const string& nazwisko) {
    
    cout << "Twoje aktualne wizyty:\n";
    for (const auto& wizyta : wizyty) {
        if (wizyta.pacjent.imie == imie && wizyta.pacjent.nazwisko == nazwisko) {
            cout << "Data: " << wizyta.data << "\n";
        }
    }

    cout << endl << "Wybierz opcje:\n";
    cout << "1. Przeloz wizyte\n";
    cout << "2. Dodaj nowa rezerwacje\n";

    int opcja;
    do {
    cin >> opcja;

    switch (opcja) {
    case 1:
        przelozWizyte(wizyty);
        break;
    case 2:
        umowWizyte(wizyty, pacjenci, imie, nazwisko);
        break;
    default:
        cout << "Nieprawidlowa opcja, Wybierz jeszcze raz\n";
    }
    } while (opcja != 1 && opcja != 2);
}

int main() {
    vector<Pacjent> pacjenci;
    vector<Wizyta> wizyty;

    
    wczytajPacjentow(pacjenci, "pacjenci.txt");
    wczytajWizyty(wizyty, "wizyty.txt");

    
    wyswietlKalendarz(wizyty);

    
    string imie, nazwisko;
    cout << "\nPodaj swoje imie: ";
    cin >> imie;
    cout << "Podaj swoje nazwisko: ";
    cin >> nazwisko;

    if (czyNowyPacjent(pacjenci, imie, nazwisko)) {
        cout << endl << "Jestes nowym pacjentem. Automatyczna rejestracja...\n";
        pacjenci.push_back({ imie, nazwisko });
        umowWizyte(wizyty, pacjenci, imie, nazwisko);
    }
    else {
        cout << endl << "Jestes juz zarejestrowanym pacjentem.\n";
        obsluzJuzZarejestrowanegoPacjenta(wizyty, pacjenci, imie, nazwisko);
    }


    
    zapiszPacjentow(pacjenci, "pacjenci.txt");
    zapiszWizyty(wizyty, "wizyty.txt");

    return 0;
}

