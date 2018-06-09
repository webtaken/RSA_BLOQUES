#include "str.h"


ZZ pow(ZZ a , ZZ b){
  ZZ result(1);
  while(b > 0){
    if(IsOdd(b))
      result *= a;
    a *= a;
    b >>= 1;
  }
  return result;
}

ZZ binary_to_ZZ(string binary){
    ZZ num(0),j(0);
    for(int i = binary.size() - 1 ; i > -1; --i , j++)
        num += (binary[i] - '0') * pow((ZZ)2 , j);
    return num;
}

string ZZ_to_binary(ZZ n){
    string bin = "";
    while(n != 0){
        bin += '0' + n % 2;
        n >>= 1;
    }
    reverse(bin.begin() , bin.end());
    return bin;
}

ZZ pow_mod(ZZ a , ZZ b , ZZ m){//a^b mod m
  ZZ result(1);
  a = a % m;
  while(b > 0){
    if(IsOdd(b))
      result = (result * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return result;
}

ZZ BGCD(ZZ a, ZZ b){//es mucho mas rapido que el gcd clásico
  ZZ shl(0);

  while ( a != 0 && b != 0 && a != b ) {
    bool eu = !IsOdd(a);//si a es par
    bool ev = !IsOdd(b);//si b es par

    if ( eu && ev ) {
      shl += 1;
      a >>= 1;//se divide entre 2
      b >>= 1;
    }
    else if ( eu && !ev ) a >>= 1;
    else if ( !eu && ev ) b >>= 1;
    else if ( a >= b ) a = (a - b) / 2;
    else {
      ZZ tmp = a;
      a = (b - a) / 2;
      b = tmp;
    }
  }
  return IsZero(a)? b * pow((ZZ)2 , shl) : a * pow(ZZ(2) , shl);
}



ZZ generar_aleatorio(ZZ a , ZZ b){
    return a + RandomBnd(b - a + 1);//genera numeros dentro del rango <a,b>
}

ZZ inversa_modular(ZZ a , ZZ b){
  ZZ s_1(1), s_2(0) , b_c = b;
  ZZ q(0), r(0), s(0);
  while (b > 0) {
    q = a / b;

    r = a - q * b;
    a = b;
    b = r;

    s = s_1 - q * s_2;
    s_1 = s_2;
    s_2 = s;
  }
  if(s_1 < 0)
    s_1 += b_c;

  return s_1;// a*s mod b = 1
}

bool Miller_Rabin(ZZ p , int iteration = 30){
  if (p < 2)
    return false;
  if (p != 2 && !IsOdd(p))
    return false;

  ZZ s = p - 1;
  while (!IsOdd(s))
    s >>= 1;
  for (int i = 0; i < iteration; i++){
    ZZ a = generar_aleatorio(ZZ(2) , p - 2), temp = s;
    ZZ mod = pow_mod(a, temp, p);
    //if mod es diferente de n-1 y 1
    while (temp != p - 1 && mod != 1 && mod != p - 1){
      mod = (mod * mod) % p;
      temp <<= 1;
    }
    if (mod != p - 1 && !IsOdd(temp))
      return false;

  }
  return true;
}
bool Fermat(ZZ p , int iteration = 200){
    if(p == 1) return false;
    for(int i = 0; i < iteration; i++){
        ZZ a = generar_aleatorio(ZZ(2) , p - 1);
        if(pow_mod(a , p - 1 , p) != 1)
            return false;
    }
    return true;
}

bool parity(const bigint &v){//true if v is even else false
  return v.a[0] & 1? 0 : 1;
}


bigint pow(bigint a , bigint b){
  bigint result = 1;
  while(b > 0){
    if(!parity(b))
      result *= a;
    a *= a;
    b /= 2;
  }
  return result;
}

bigint pow_mod(bigint a , bigint b , bigint m){//a^b mod m
  bigint result = 1;
  a = a % m;
  while(b > 0){
    if(!parity(b))
      result = (result * a) % m;
    a = (a * a) % m;
    b /= 2;
  }
  return result;
}

bigint BGCD(bigint a, bigint b){//es mucho mas rapido que el gcd clásico
  bigint shl = 0;

  while ( a != 0 && b != 0 && a != b ) {
    bool eu = parity(a);//si a es par
    bool ev = parity(b);//si b es par

    if ( eu && ev ) {
      shl += 1;
      a /= 2;//divido entre 2, ya que la libreria no contiene corrimiento de bits
      b /= 2;
    }
    else if ( eu && !ev ) a /= 2;
    else if ( !eu && ev ) b /= 2;
    else if ( a >= b ) a = (a - b) / 2;
    else {
      bigint tmp = a;
      a = (b - a) / 2;
      b = tmp;
    }
  }
  return a == 0? b * pow(2 , shl) : a * pow(2 , shl);
}

bigint inversa_modular(bigint a , bigint b){
  bigint s_1 = 1, s_2 = 0 , b_c = b;
  bigint q = 0, r = 0, s = 0;
  while (b > 0) {
    q = a / b;

    r = a - q * b;
    a = b;
    b = r;

    s = s_1 - q * s_2;
    s_1 = s_2;
    s_2 = s;
  }
  if(s_1 < 0)
    s_1 += b_c;
  return s_1;// a*s mod b = 1
}
/**/

