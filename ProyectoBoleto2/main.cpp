#include <iostream>
#include <string>
#include <vector>
#include <ostream>
using namespace std;
#include "Boleto.h"
vector<string> MItem;
vector<string> Evento;
Fecha *FECHA;

void mostrar_vector(Bol *);
void agregar(Bol *, int, Boleto *);
void resumen(Bol *, int);
int mostrar_menu();
void procesar_comandos(Bol *B);
void generar_Boleto(Bol *P);
void presentar_Resumen(Bol *P);
void agregar_evento(Bol *B);
int main(){
  MItem.push_back("Generar Boleto");
  MItem.push_back("Presentar Resumen");
  MItem.push_back("Agregar evento");
  MItem.push_back("Salir");
  FECHA=new Fecha(10,10,2015);
  string evento1="Guerra de Robots";
  string evento2="Eleccion de Representantes al CTCE UPIITA";
  Evento.push_back(evento1);
  Evento.push_back(evento2);
  Bol *B;
  B=new Bol[30];
  B->set_evento(evento1);
  (B+1)->set_evento(evento2);
  procesar_comandos(B);

  return 0;
}//end main()

int mostrar_menu(){
  int cho;
  do{
  cout << endl;
  cout << "Teclee un numero que corresponda a un elemento del siguiente menu:" << endl;
  for(int i=0; i<MItem.size(); ++i)
    cout << i << " " << MItem[i] << endl;
  cout << "Teclee el numero de la opcion elegida: ";
  cin >> cho;
  }while((cho<0)||(cho>=MItem.size()));
  return cho;
}
void procesar_comandos(Bol *B){
  int elec;
  do{
    elec=mostrar_menu();
    switch(elec){
      case 0:{generar_Boleto(B);break;}
      case 1:{presentar_Resumen(B);break;}
      case 2:{agregar_evento(B);break;}    //Para evitar SEGFAULT hay que llamar a presentar_Resumen()
                                          //solo si para todos los eventos hay al menos un Boleto generado
                                          // o mas bien en presentar_Resumen() antes de imprimir
                                          //la info del cada evento asegurarse de que hay al menos un boleto
                                          //generado por el evento.
      default:{break;}
    };
  }while(elec!=MItem.size()-1);
}
void presentar_Resumen(Bol *P){
  resumen(P, Evento.size());
}

int Boleto::consecutivo=0;
Boleto::Boleto(Fecha *fec):Producto(fec){
//  set_fecha(fec);
  consecutivo++;
}
void Bol::set_evento(string evt){
  evento=evt;
}

void mostrar_vector(Bol *P){
  for(int i=0; i<P->V.size(); ++i)
    cout << P->V[i]->numdbol << " " << P->evento << " "
         << (*(P->V[i])).NombreDEmpresa << " "
         << *((*(P->V[i])).f) << endl;
  cout <<  endl;
}
//void mostrar_Boleto(Boleto *);

/**
 @param index: indice que corresponde al evento para el cual
 se va a agregar un Boleto en el vector<Boleto*> V del
 index-esimo objeto de clase Bol.
 */
void agregar(Bol *P, int index, Boleto *b){
  b->numdbol=(P+index)->V.size()+1;
  (P+index)->V.push_back(b);
}
void generar_Boleto(Bol *P){
  int M;
  Boleto *b;
  cout << "Elija el evento:" << endl;
  for(int i=0; i<Evento.size(); ++i)
    cout << i << " " << Evento[i] << endl;
  cout << "Evento elegido: ";
  cin >> M;
  b=new Boleto(FECHA);
  agregar(P, M, b);
}

ostream& operator<<(ostream& out, Fecha& f){
    out << f.dia << "/" << f.mes << "/" << f.anio;
    return out;
}

/**
  @param n: el numero de eventos para los cuales hay series de boletos.
 */
void resumen(Bol *P, int n){
  cout << Empresa<string>::str_empresa << endl;
  for(int k=0; k<n; ++k){
    cout << "Boletos emitidos para el evento (" << *((*((P+k)->V[0])).f) << ") \""
         << (P+k)->evento << "\": " << (P+k)->V.size() << endl;
  }
  cout << "Total de Boletos emitidos: " << Boleto::get_consecutivo() << endl;
}
void agregar_evento(Bol *B){
     string a;
     int b;
     cout<<"¿Cuantos eventos ya existen? ";
     cin>>b;
     cout<<"¿Que evento deseas agregar? "<<endl;
     cin.ignore(500,'\n');
     getline(cin,a);
     Evento.push_back(a);
     (B+b)->set_evento(a);
     }
