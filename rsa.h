#include "math.h"

class RSA
{
 private:
  ZZ bits;
  ZZ d;//clave privada
  ZZ e;//clave publica
  ZZ N;//la multiplicacion de 2 numeros primos
  ZZ p;//primer primo
  ZZ q;//segundo primo
 public:
     ZZ get_N(){
        return N;
     }
     ZZ get_e(){
        return e;
     }
  RSA(ZZ c_bits){//generacion de claves
    bits = c_bits;
    p = generar_aleatorio(pow(ZZ(2) , bits - 1) , pow(ZZ(2) , bits) - 1);
    while(!Miller_Rabin(p))
        p = generar_aleatorio(pow(ZZ(2) , bits - 1) , pow(ZZ(2) , bits) - 1);
    q = generar_aleatorio(pow(ZZ(2) , bits - 1) , pow(ZZ(2) , bits) - 1);
    while(q != p &&!Miller_Rabin(q))
        q = generar_aleatorio(pow(ZZ(2) , bits - 1) , pow(ZZ(2) , bits) - 1);
    N = p * q;
    ZZ phi_n = (p - 1) * (q - 1);
    do{
        do{
            e = generar_aleatorio(ZZ(3) , phi_n - 1);
        }while(!IsOdd(e));
    }while(BGCD(e , phi_n) != 1);
    d = inversa_modular(e , phi_n);
  }

  RSA(ZZ e_c , ZZ N_c){//public key from other user
    N = N_c;
    e = e_c;
  }
  RSA(bigint c_p , bigint c_q , bigint c_bits){
    bits = bigint_to_ZZ(c_bits);
    p = bigint_to_ZZ(c_p) , q = bigint_to_ZZ(c_q);
    N = p * q;
    ZZ phi_n = (p - 1) * (q - 1);
    do{
        do{
            e = generar_aleatorio(ZZ(3) , phi_n - 1);
        }while(!IsOdd(e));
    }while(BGCD(e , phi_n) != 1);
    d = inversa_modular(e , phi_n);
  }
  RSA(ZZ c_p, ZZ c_q , ZZ c_bits){//p and qq both are primes
    bits = c_bits;
    p = c_p , q = c_q;
    N = p * q;
    ZZ phi_n = (p - 1) * (q - 1);
    do{
        do{
            e = generar_aleatorio(ZZ(3) , phi_n - 1);
        }while(!IsOdd(e));
    }while(BGCD(e , phi_n) != 1);
    d = inversa_modular(e , phi_n);
  }

  //ZZ resto_chino(ZZ a);

  string cifrar(string M){//26 es espacio
    vector <bigint> C;
    string m_c = "";

    for(int i = 0; i < M.size(); i++)
        m_c += rellenar_letra(M[i]);

    while(m_c.size() % (digits(N) - 1) != 0)
        m_c += '2';


    for(int i = 0; i < m_c.size(); i += digits(N) - 1){
        C.push_back( pow_mod((bigint)m_c.substr(i , digits(N) - 1) , ZZ_to_bigint(e) , ZZ_to_bigint(N) ) );
    }

    string cc = "";
    for(int i = 0; i < C.size(); i++){
        string aux = C[i].to_str();//the bignumber to string
        while((bigint)aux.size() % digits(N) != 0){
            aux.insert(aux.begin() , 1 , '0');
        }
        cc += aux;
    }
    return cc;
  }

  string descifrar(string C){
    vector <bigint> M;
    for(int i = 0; i < C.size(); i += digits(N - 1)){
        M.push_back((bigint)C.substr(i , digits(N - 1)));
    }
    string mm = "";
    for(int i = 0; i < M.size(); i++){
        string aux = ZZ_to_str( pow_mod(bigint_to_ZZ(M[i]) , d , N) );
        while(aux.size() % (digits(N) - 1))
            aux.insert(aux.begin() , 1 , '0');
        mm += aux;
    }
    string res = "";
    for(int i = 0; i < mm.size(); i += 2){
        res += alfabeto[ pos_valor_letra(mm.substr(i , 2)) ];
    }
    return res;
  }

  string generar_semilla(){
      ZZ n = bits / 10;//10% de la cantidad total de bits
      if(n == 0)n++;
      int *p = new int;
      string granito_de_mostaza_1 = "" , granito_de_mostaza_2 = "";
      granito_de_mostaza_1 = int_to_str((int)p);
      delete p;
      while(granito_de_mostaza_1.size() < ZZ_to_int(n)){
          p = new int;
          granito_de_mostaza_1 += int_to_str((int)p);
          delete p;
      }
      p = new int;
      granito_de_mostaza_2 = int_to_str((int)p);
      delete p;
      while(granito_de_mostaza_2.size() < ZZ_to_int(n)){
          p = new int;
          granito_de_mostaza_2 += int_to_str((int)p);
          delete p;
      }
      int tam = ZZ_to_int(n);
      string s_1(tam , ' ') , s_2(tam , ' ');
      reverse(granito_de_mostaza_2.begin() , granito_de_mostaza_2.end());
      for(int i = 0; i < tam; ++i){
          s_1[i] = '0' + (int)granito_de_mostaza_1[i % tam] % 2;
          s_2[i] = '0' + (int)granito_de_mostaza_2[i % tam] % 2;
      }
      for(int i = 0; i < tam; i++){
          s_1[i] = '0' + ((bool)(s_1[i] - '0') ^ (bool)(s_2[i] - '0'));//s1 = s1 xor s2
      }
      return s_1;
    }
    ZZ generar_numero_aleatorio(string semilla , ZZ particiones , ZZ vueltas){
        ZZ pos_aleatoria;
        pos_aleatoria = generar_aleatorio((ZZ)0 , bits / particiones);
        string cadena_bits(semilla.begin() , semilla.end());
        cadena_bits.resize(ZZ_to_int(bits));
        for(int i = semilla.size() , j = 0; i < bits; i++ , j++){
            cadena_bits[i] = (bool)(cadena_bits[j] - '0') ^ (bool)(cadena_bits[j + 1] - '0') + '0';
        }
        if(!(cadena_bits[ZZ_to_int(bits) - 1] - '0'))
            cadena_bits[ZZ_to_int(bits) - 1] = '1';
//        cout << cadena_bits << endl;
//        vector <ZZ> cadena_aleatoria;
//        for(int j = 0; j < bits; j+= ZZ_to_int(bits/particiones)){
//            cadena_aleatoria.push_back( binary_to_ZZ(cadena_bits.substr(j , ZZ_to_int(bits / particiones))) );
//        }
//        for(int i = 0; i < vueltas; i++){
//            for(int j = 0; j < cadena_aleatoria.size(); j += 2)
//                cout << cadena_aleatoria[j] << " " << cadena_aleatoria[j + 1] << endl;
//        }
        return binary_to_ZZ(cadena_bits);
    }
/**/
};
