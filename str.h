#include <NTL/ZZ.h>
#include "bigint.h"
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
using namespace NTL;

string alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";


int digits(ZZ n){
    stringstream ss;
    ss << n;
    return ss.str().size();
}

int digits(bigint n){
    return n.to_str().size();
}


bigint ZZ_to_bigint(ZZ n){
    stringstream ss;
    ss << n;
    return (bigint)ss.str();
}

ZZ bigint_to_ZZ(bigint n){
    stringstream ss;
    ss << n;
    ZZ a;
    ss >> a;
    return a;
}

int pos_letra(char n){
    for(int i = 0; i < alfabeto.size(); i++){
        if(n == alfabeto[i])return i;
    }
}

string rellenar_letra(char n){
    stringstream ss;
    ss << pos_letra(n);
    string valor = ss.str();
    ss.str(string());
    ss << alfabeto.size();
    while(valor.size() != ss.str().size()){
        valor.insert(valor.begin() , '0');
    }
    return valor;
}


string ZZ_to_str(ZZ n){
    stringstream ss;
    ss << n;
    return ss.str();
}

int ZZ_to_int(ZZ n){
    stringstream ss;
    ss << n;
    int num;
    ss >> num;
    return num;
}

string int_to_str(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}
