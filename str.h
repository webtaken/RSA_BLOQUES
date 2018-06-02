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
string alfabeto_values[] = {"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62"};


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

int pos_valor_letra(string n){
    for(int i = 0; i < alfabeto.size(); i++){
        if(n == alfabeto_values[i])return i;
    }
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
