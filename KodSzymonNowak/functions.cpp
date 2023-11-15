#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "classes.h"
using namespace std;

bool is_id_ok(int id, Kalendarz k);

Sprzet::Sprzet(int i, Kalendarz k){
        if(!is_id_ok(i, k))
            while(true){
                int new_id;
                cout<<"podaj nowe ID (0 aby wyjsc): ";
                cin>>new_id;
                if(new_id == 0){
                    i = new_id;
                    break;
                }
                else if(is_id_ok(new_id, k)){
                    cout<<"dobre id"<<endl;
                    i = new_id;
                    break;
                }
            }
        id = i;
        //cout<<id<<endl;   
    } 

Sprzet::Sprzet(){id = 0;}

bool Kalendarz::includes(int id){
        for(int i = 0; i < wydarzenia.size(); i++){
            if(wydarzenia[i].id == id)
                return true;
        }
        return false;
    }

void Kalendarz::push_event(Wydarzenie w){
    wydarzenia.push_back(w);
    cout<<"pomyslnie dodano wydarzenie w dniu: "<<w.data<<"  dla sprzetu o id: "<<w.id<<endl;
}


Wydarzenie::Wydarzenie(string d, int i){
        data = d;
        id = i;
    }

void Kalendarz::show(){
    for(int i = 0; i < wydarzenia.size(); i++)
        cout<<"Kalendarz:\ndata: "<<wydarzenia[i].data<<"\tid: "<<wydarzenia[i].id<<endl;
}

bool is_id_ok(int id, Kalendarz k){
    //k.show();
    if(k.includes(id)){
        cout<<"Sprzet zostal juz wprowadzony do systemu"<<endl;
        return false;
    }else{
        return true;
    }
}