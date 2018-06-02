#include "rsa.h"

int main()
{
//    ofstream dir("directorio_publico.txt" , ofstream::out);
//    ofstream cif("cifrado.txt" , ofstream::out);
//    ifstream des("cifrado.txt" , ifstream::in);
//    string user = "pluto" , correo = "pluto@gmail.com";
//    RSA yo(ZZ(3) , ZZ(1003));
//    dir << yo.get_N() << " " << yo.get_e() << " " << user << " " << correo << endl;
//    string cifrado = yo.cifrar("comehere");
//    cif << cifrado << endl;
//    string cifer;
//    des >> cifer;
//    string descifrado = yo.descifrar(cifer);
//    cout << descifrado << endl;
//    cif.close();
//    dir.close();
//    des.close();
    RSA mi((ZZ)1024);
    string g =  mi.generar_semilla();
    cout << mi.generar_numero_aleatorio(g , (ZZ)8 , (ZZ)2) << endl;
    return 0;

}
