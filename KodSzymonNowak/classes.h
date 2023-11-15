#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Wydarzenie;

class Kalendarz{
private:
public:
    vector<Wydarzenie> wydarzenia;

    void push_event(Wydarzenie w);
    void show();
    bool includes(int id);
};

class Sprzet{
private:
public:
    int id;

    Sprzet(int i, Kalendarz k);
    Sprzet();
};

class Wydarzenie : public Sprzet{
private:
public:
    string data;

    Wydarzenie(string d, int i);
};