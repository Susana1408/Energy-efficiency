#include <iostream>
#include <stdlib.h>
using namespace std;


class AcidoGraso
{
    private:
        int c;
    public:
        AcidoGraso(int carbonos=0) {c=carbonos;};
        int Carbonos() {return c;};
};

class bOxidacion:public AcidoGraso
{
    private:
        float NADH = 2.5;
        float FADH2 = 1.5;
    public:
        bOxidacion(int carbonos):AcidoGraso(carbonos) {};
        float rendimientoOxi();
        void esquemabOxidacion();
        float Nadh() {return NADH;};
        float Fadh2() {return FADH2;};
};

float bOxidacion::rendimientoOxi()
{
    float ATP1;
    float numero=(Carbonos()/2)-1;
    ATP1=(NADH*numero)+(FADH2*numero);
    return ATP1;
}

void bOxidacion::esquemabOxidacion()
{
    cout<<endl<<"B-OXIDACION"<<endl;
    cout<<"Acido Graso ("<<Carbonos()<<")"<<"c"<<" -> Acetil-CoA -> AcilCarnitina -> Acil-CoA";
    cout<<" -> Enoil-CoA -> B-HidroxiAcil-CoA -> B-CetoAcil-CoA -> Acil-CoA ("<<Carbonos()<<"-2)c & Acetil-CoA ...";
}

class cicloKrebs:public bOxidacion
{
    private:
        float GTP = 1;
    public:
        cicloKrebs(int carbonos):bOxidacion(carbonos) {};
        float rendimientoKrebs();
        void esquemaKrebs();
};

float cicloKrebs::rendimientoKrebs()
{
    float ATP2;
    float numero=(Carbonos()/2);
    ATP2=(GTP*numero)+(Nadh()*numero*3)+(Fadh2()*numero);
    return ATP2;
}

void cicloKrebs::esquemaKrebs()
{
    cout<<endl<<"CICLO DE KREBS"<<endl;
    cout<<"Acetil-CoA -> Citrato -> Cis-Aconitato -> Isocitrato -> a-Cetoglutarato ->";
    cout<<" Succinil-CoA -> Succinato -> Fumarato -> Malato -> Oxalacetato ...";
}

class rutaCompleta: public cicloKrebs
{
    private:
      float actAG=2;
    public:
      rutaCompleta(int carbonos):cicloKrebs(carbonos) {};
      float rendimientoTotal();
      void infoFinal();
      void esquemas();
};

float rutaCompleta::rendimientoTotal()
{
    float ATPT;
    ATPT=rendimientoKrebs()+rendimientoOxi()-actAG;
    return ATPT;
}

void rutaCompleta::esquemas()
{
    cout<<endl<<"------ESQUEMA RUTAS METABOLICAS DE UN ACIDO GRASO (AG)----------"<<endl;
    esquemabOxidacion();
    cout<<endl;
    esquemaKrebs();
}

void rutaCompleta::infoFinal()
{
   cout<<endl<<"------RENDIMIENTO ENERGETICO DE UN ACIDO GRASO (AG)----------"<<endl;

   cout<<"RENDIMIENTO B-OXIDACION (ATP): ";
   cout<<rendimientoOxi()<<endl;

   cout<<"RENDIMIENTO CICLO KREBS (ATP): ";
   cout<<rendimientoKrebs()<<endl;

   cout<<"ATP PERDIDO EN LA ACTIVACION DEL AG: ";
   cout<<actAG<<endl;

   cout<<"RENDIMIENTO TOTAL (ATP): ";
   cout<<rendimientoTotal()<<endl;
}


int main()
{
   int carbonos,op;
   cout<<"CARBONOS DEL ACIDO GRASO SATURADOS (AG): ";
   cin>>carbonos;
   if((carbonos>0)&&(carbonos%2==0))
   {
       rutaCompleta AG(carbonos);
          do
           {
               cout<<endl<<"--------MENU--------"<<endl;
               cout<<"0) Salir"<<endl;
               cout<<"1) Rendimiento Energetico B-Oxidacion"<<endl;
               cout<<"2) Esquema de B-Oxidacion"<<endl;
               cout<<"3) Rendimiento Energetico Ciclo Krebs"<<endl;
               cout<<"4) Esquema de Ciclo Krebs"<<endl;
               cout<<"5) Rendimiento Energetico Total"<<endl;
               cout<<"6) Esquema ruta metabolica completa (B-Oxidacion & Ciclo Krebs)"<<endl;
               cin>>op;
               system("cls");

               switch(op)
               {
                   case 0:
                    return 0;
                    break;

                   case 1:
                    cout<<"RENDIMIENTO ENERGETICO B-OXIDACION: "<<AG.rendimientoOxi()<<endl;
                    AG.esquemabOxidacion();
                    break;

                   case 2:
                    AG.esquemabOxidacion();
                    break;

                   case 3:
                    cout<<"RENDIMIENTO ENERGETICO CICLO KREBS: "<<AG.rendimientoKrebs()<<endl;
                    AG.esquemaKrebs();
                    break;

                   case 4:
                    AG.esquemaKrebs();
                    break;

                   case 5:
                    AG.infoFinal();
                    break;

                   case 6:
                    AG.esquemas();
                    break;
               }
           }
           while(op!=0);
   }
   else
   {
       cout<<"El numero de carbonos tiene que ser mayor de cero y un numero par"<<endl;
   }
   return 0;
}

