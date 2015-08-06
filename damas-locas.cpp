/*
 * Autor : JAvier Andres Reyes Gonzalez

*/



#include "conio.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define T 10

using namespace std ;
   
char tablero[T][T];//Crea matriz para el tablero
int i, j;// 2 enteros que nos permite mover por la matriz .
int x,y ;// 2 entero que nos permite mover las fichas o damas.
int z; // 
int turno=1;//TURNO PARA FICHAS X CUADNO CUANDO UN SUARIO MUEVE UNA FICHA EL TURNO CAMBIA A 0 Y PROSIGUE EL SIGUIENTE JUGADOR
int direccion ;//Permite mover la ficha el usuario
int error ; //Permite vaalidar cuando se come o mueve la ficha en diagonal si esta en 1 es que ocurrio un error
int fichao=15;//Cantidad de fichas CPU
int fichax=15;//Cantidad de fichas Usuario
int terminar=1;//con esto verificamos que el juego termina cuando cambia a 0
int contador_fichas_x= 7;//Contador especial 
int contador_fichas_o= 7;   //Contador especial 
 
void rellenar()
{
    for(i=0;i<T;i++)
    {
        for(j=0;j<T;j++)
        {
             if(i<=2&&((j+i)%2==0))//Agrega en el tablero las damas 0 en la parte superior (CPU)
             {
                 tablero[i][j] = 'a' ;
             } 
 
             else 
                if (i>=7&&((j+i)%2==0) )//Agrega en el tablero las damas 0 en la parte superior (CPU)
                {
                   tablero[i][j] = 'b' ;
                }//
                else  //Agrega Los espacios vacios en el tablero
                {
                 tablero[i][j] = ' ' ;
                }
        }
    }
}


void MoverUsuario()
{
     do
     {
      do
      {
       do
       {
        do
        {
         cout<<"Tu turno" <<endl ;
        
         if(turno==1 )
         {  
              cout<<"ingrese coordenada horizaontal "<<endl ;   //ingresamos primera cordenada eje vertical
              cin>> x ;
   
              cout<<"ingrese coordenada vertical "<<endl ;   //ingresamos primera cordenada eje horizaontal
              cin>> y;
         }
        
         if  (tablero[x][y]!='b'&&tablero[x][y]!='B')  //Revisamos si esta ocupada 
         {
           cout<<"No se encuentra Ficha, vuelva intentar"<<x<<"-"<<y<<endl ;}
         }while (tablero[x][y]!='b'&&tablero[x][y]!='B');//VALIDACION PARA EL TIRO DE MOVIMIENTO
        
         do
         {
          if (tablero[x][y] == 'b') //Verifica si encuentra la ficha X
          {
           {
           cout<<"Seleccione poscicion [1]IZQUIERDA-ARRIBA [2] DERECHA-ARRIBA" ; //Selecciona posicion en que te puedes mover
           cin>>direccion ;
           error=0;
  
           if(direccion>2||direccion<1) //Verifica si puso el 1 o 2
              cout<<"No se puede, escoja nuevamente."<<endl;
           }

         if((y==7&&direccion==2)||(y==0&&direccion==1)) //verifica si no se a salido del tablero
           cout<<"No se puede, escoja nuevamente."<<endl ;
         }
 
         if (tablero[x][y]=='B') //Verifica si es Dama
         {
          
              cout<<"Seleccione [1]IZQUIERDA-ARRIBA [2]DERECHA-ARRIBA [3]IZQUIERDA-ABAJO [4] DERECHA-ABAJO " <<endl ; //Selecciona posicion en que te puedes mover
              cin>>direccion ;
              error=0;
            
              if(direccion>4||direccion<1) //Verifica si puso el 1, 2, 3, 4
                 cout<<"No se puede, escoja nuevamente. "<<endl; 
       
             if((y==7&&direccion==2)||(y==0&&direccion==1)||(y==7&&direccion==4)||(y==0&&direccion==3)||(x==0&&direccion==1)||(x==0&&direccion==2)||(x==7&&direccion==3)||(x==7&&direccion==4))//verifica si no se a salido del tablero
                cout<<"No se puede, escoja nuevamente. "<<endl ;
         }
             
     }while (direccion>4||direccion<1);//Valdicacion para saber si se realizo efectivamente los movimientos
}while((y==7&&direccion==2)||(y==0&&direccion==1)||(y==7&&direccion==4)||(y==0&&direccion==3)||(x==0&&direccion==1)||(x==0&&direccion==2)||(x==7&&direccion==3)||(x==7&&direccion==4));//Vlidacion para no salirte del tablero

if (direccion == 1 && ( tablero[x-1][y-1]== 'b'||tablero[x-1][y-1]== 'B')  ) //Verifica si la casilla se encuentra ocupada por una ficha o dama propia
   cout<<"Posicion ocupada "<<endl ;

else if (direccion == 2 && (tablero[x-1][y+1]== 'b'||tablero[x-1][y+1]== 'B') )///Verifica si la casilla se encuentra ocupada por una ficha o dama propia
   cout<<"Posicion ocupada "<<endl ;
  
else if (direccion == 3 && (tablero[x+1][y-1]== 'b'||tablero[x+1][y-1]== 'B') )//Verifica si la casilla se encuentra ocupada por una ficha o dama propia
   cout<<"Posicion ocupada "<<endl ;
  
else if (direccion == 4 && (tablero[x+1][y+1]== 'b'||tablero[x+1][y+1]== 'B') )//Verifica si la casilla se encuentra ocupada por una ficha o dama propia
   cout<<"Posicion ocupada "<<endl ;
  
}while((direccion==1&&(tablero[x-1][y-1]== 'b'||tablero[x-1][y-1]== 'B'))||(direccion==2&&(tablero[x-1][y+1]== 'b'||tablero[x-1][y+1]== 'B') )||(direccion == 3 && (tablero[x+1][y-1]== 'b'||tablero[x-1][y+1]== 'B') )||(direccion == 4 && (tablero[x+1][y+1]== 'b'||tablero[x+1][y+1]== 'B') ));//Valdicacion para saber si esta ocupada por una ficha propia  
 

if (direccion==1 && (tablero[x-1][y-1] == 'a'||tablero[x-1][y-1] == 'A') )  
{
  if(y==1)
  {
          cout<<"No se puede "<<endl ;
          error=1;
  }
  if(x==1)
  {
          cout<<"No se puede  "<<endl ;
          error=1;
  }
  if(tablero[x-2][y-2] == 'b') //Verificacion de posicion de ficha para comer 
  {        
          cout<<"No se puede, casilla ocupada "<<x-2<<"-"<<y-2<<endl; 
          error=1;
  }
  if(tablero[x-2][y-2] == 'a' )//Verificacion de posicion de ficha para comer 
  {
          cout<<"No se puede, casilla ocupada "<<x-2<<"-"<<y-2<<endl;
          error=1;
  }
  if(tablero[x-2][y-2] == 'B' )//Verificacion de posicion de ficha para comer 
  {
          cout<<"No se puede, casilla ocupada  "<<x-2<<"-"<<y-2<<endl;
          error=1;
  }
  
  if(tablero[x-2][y-2] == 'A' )//Verificacion de posicion de ficha para comer 
  {
          cout<<"No se puede, casilla ocupada  "<<x-2<<"-"<<y-2<<endl;
          error=1;}
  }
  
  else if (direccion==2 && (tablero[x-1][y+1] == 'a'||tablero[x-1][y+1] == 'A'))//Verificacion de posicion para nosalir del tablero 
  {
   if(y==6)
   {
           cout<<"No se puede"<<endl ;
           error=1;
   }
   
   if(x==1)
   {
           cout<<"No se puede "<<endl ;
           error=1;
   }      
  
   if(tablero[x-2][y+2] == 'b')//Verificacion de posicion de ficha propia para comer 
   {
           cout<<"No se puede, casilla ocupada "<<endl;
           error=1;
   }
  
   if (tablero[x-2][y+2] == 'a')//Verificacion de posicion de ficha  cpu para comer
   {
           cout<<"No se puede, casilla ocupada  "<<endl;
           error=1;
   }
   
   if (tablero[x-2][y+2] == 'B')
   {
           cout<<"No se puede, casilla ocupada  "<<endl;//Verificacion de posicion de dama propia para comer 
           error=1;
   }
   
   if (tablero[x-2][y+2] == 'A')
   {
           cout<<"No se puede, casilla ocupada  "<<endl;//Verificacion de posicion de dama  cpu para comer
           error=1;}
   }
  
   else if (direccion==3 && (tablero[x+1][y-1] == 'a'||tablero[x+1][y-1] == 'A')) //Verificaicon de que no se salga dle tablero al comer
   {
    if(y==1)
    {
            cout<<"No se puede "<<endl ;
            if(y==1)
            {  
               cout<<"No se puede "<<endl ;
               error=1;
            }
            error=1;
    }
  
    if(x==6)
    {
            cout<<"No se puede "<<endl ;
            error=1;
    }
    if(tablero[x+2][y-2] == 'b') //Verificaicon de que no este ocupada la casilla para comer
    {
            cout<<"No se puede, casilla ocupada "<<endl;
            error=1;
    }
  
    if (tablero[x+2][y-2] == 'a')//Verificaicon de que no este ocupada la casilla para comer
    {
            cout<<"No se puede, casilla ocupada "<<endl;
            error=1;
    }
    
    if (tablero[x-2][y+2] == 'A')//Verificaicon de que no este ocupada la casilla para comer
    {
            cout<<"No se puede, casilla ocupada "<<endl;
            error=1;
    }
    if (tablero[x-2][y+2] == 'B')//Verificaicon de que no este ocupada la casilla para comer
    {
            cout<<"No se puede, casilla ocupada"<<endl;
            error=1;
    }
  }
    
  else if (direccion==4 && (tablero[x+1][y+1] == 'a'||tablero[x+1][y+1] == 'A'))//Verificaicon de que no se salga del tablero
  {
   if(y==6)
   {
           cout<<"No se puede "<<endl ;
           error=1;
   }
   
   if(x==6)
   {       
           cout<<"No se puede "<<endl ;
           error=1;
   }
  
   if(tablero[x+2][y+2] == 'b')
   {
           cout<<"No se puede, casilla ocupada"<<endl;
           error=1;
   }
  if (tablero[x+2][y+2] == 'a')
  {
          cout<<"No se puede, casilla ocupada"<<endl;
          error=1;
  }
  if (tablero[x+2][y+2] == 'B')
  {
          cout<<"No se puede, casilla ocupada"<<endl;
          error=1;
  }
  if (tablero[x+2][y+2] == 'A')
  {
          cout<<"No se puede, casilla ocupada"<<endl;
          error=1;}
  }
}while(error==1); //Verificacion de casillas que estan ocupadas cuando realizan movimientos para comer

if(tablero[x][y]== 'B' && direccion==1 && tablero[x-1][y-1]== ' '  ) //Revisa que casilla esta libre y hace movimiento
{
   tablero[x][y]= ' ';
   tablero[x-1][y-1]= 'B';
}
 
else 
   if (tablero[x][y]=='B'&& direccion == 2 && tablero[x-1][y+1]== ' ' )//Revisa que casilla esta libre y hace movimiento
   {
      tablero[x][y]=' ' ;
      tablero[x-1][y+1] = 'B' ;
   }
   else 
      if (tablero[x][y]=='B'&& direccion == 3 && tablero[x+1][y-1]== ' ' )//Revisa que casilla esta libre y hace movimiento
      {
            tablero[x][y]=' ' ;
            tablero[x+1][y-1] = 'B' ;
      }
      else 
      if (tablero[x][y]=='B'&& direccion == 4 && tablero[x+1][y+1]== ' ' )//Revisa que casilla esta libre y hace movimiento
      {
            tablero[x][y]=' ' ;
            tablero[x+1][y+1] = 'B' ;
      }
      else 
         if(tablero[x][y]=='B'&& direccion== 1 &&( tablero [x-1][y-1] == 'a' || tablero [x-1][y-1] == 'A'))//Revisa que casilla ocupada con ficha o dama  CPU y hace movimiento para comer con dama
         {
             tablero[x][y]=' ' ;
             tablero[x-1][y-1]=' ' ;
             tablero[x-2][y-2]= 'B' ;
             
             cout<<"\a";
             cout<<"Lograste comer una ficha "<<x-1<<"-"<<y-1 ;
             fichao=fichao-1;
             contador_fichas_x= contador_fichas_x+3;
             getche ();
         }
         else 
              if(tablero[x][y]=='B'&& direccion==2 && (tablero [x-1][y+1] == 'a'||tablero [x-1][y+1] == 'A'))//Revisa que casilla ocupada con ficha o dama  CPU y hace movimiento para comer con dama
              {
                 tablero[x][y]=' ' ;
                 tablero[x-1][y+1]=' ' ;
                 tablero[x-2][y+2]= 'B' ;
                 
                 cout<<"\a";
                 cout<<"Lograste comer una ficha   "<<x-1<<"-"<<y+1 ;
                 fichao=fichao-1;
                 contador_fichas_x= contador_fichas_x+3;
                 getche ();
              }
              else 
              if(tablero[x][y]=='B'&& direccion== 3 && (tablero [x+1][y-1] == 'a'||tablero [x+1][y-1] == 'A'))//Revisa que casilla ocupada con ficha o dama  CPU y hace movimiento para comer con dama
              {
                  tablero[x][y]=' ' ;
                  tablero[x+1][y-1]=' ' ;
                  tablero[x+2][y-2]= 'B' ;
                  
                  cout<<"\a";
                  cout<<"Lograste comer una ficha "<<x+1<<"-"<<y-1 ;
                  fichao=fichao-1;
                  contador_fichas_x= contador_fichas_x+3;
                  getche ();
              }
              else 
                   if(tablero[x][y]=='B'&& direccion== 4 && (tablero [x+1][y+1] == 'a'||tablero [x+1][y-1] == 'A'))//Revisa que casilla ocupada con ficha o dama  CPU y hace movimiento para comer con dama
                   {
                         tablero[x][y]=' ' ;
                         tablero[x+1][y+1]=' ' ;
                         tablero[x+2][y+2]= 'B' ;
                         
                         cout<<"\a";
                         cout<<"Lograste comer una ficha "<<x+1<<"-"<<y+1 ;
                         fichao=fichao-1;
                         contador_fichas_x= contador_fichas_x+3;
                         getche ();}
              else 
                   if(tablero[x][y]== 'b' && direccion== 1 && tablero [x-1][y-1] == ' ')//Revisa que casilla desocupada y hace movimiento con ficha
                   {
                         tablero[x][y]=' ' ;
                         tablero [x-1][y-1]= 'b' ;  
                   }
              else 
              if(tablero[x][y]=='b'&& direccion== 1 && (tablero [x-1][y-1] == 'a'||tablero [x-1][y-1] == 'A'))////Revisa que casilla desocupada y hace movimiento con ficha
              {
                     tablero[x][y]=' ' ;
                     tablero[x-1][y-1]=' ' ;
                     tablero[x-2][y-2]= 'b' ;
  
                     cout<<"\a";
                     cout<<"Lograste comer una ficha "<<x-1<<"-"<<y-1 ;
                     fichao=fichao-1;
                     contador_fichas_x= contador_fichas_x+3;
                     getche ();
             }
             else 
             if(tablero[x][y]== 'b' && direccion== 2 && tablero [x-1][y+1] == ' ')//Revisa que casilla ocupada con ficha o dama  CPU y hace movimiento para comer con ficha
             {
                     tablero[x][y]=' ' ;
                     tablero [x-1][y+1]= 'b' ;  
             }
   
             else 
             if(tablero[x][y]== 'b' && direccion== 2 && (tablero [x-1][y+1] == 'A'||tablero [x-1][y+1] == 'a'))//Revisa que casilla ocupada con ficha o dama  CPU y hace movimiento para comer con ficha
             {
                    tablero[x][y]=' ' ;
                    tablero [x-1][y+1]= ' ' ;
                    tablero[x-2][y+2]= 'b' ;
                    
                    cout<<"\a";
                    cout<<"Lograste comer una ficha "<<x-1<<"-"<<y+1 ;
                    fichao=fichao-1;
                    contador_fichas_x= contador_fichas_x+3;
                    getche();
             }
             
             turno = 0 ;  
}  


void imprimir()
{
     for(z=0;z<T;z++)
     {
      
      cout<<z<<"    ";}
      cout<<endl;
      
      for(i=0;i<T;i++)
      {
            cout<<"\t\t       ";
            cout<<i;
            
            for(j=0;j<T;j++)
            {
                if((tablero[i][j]=='b'||tablero[i][j]=='a'||tablero[i][j]=='A'||tablero[i][j]=='B')&&((j+i)%2==0))
                   cout<<" "<<" "<<tablero[i][j]<<" "<<" "; 
                   
                else 
                     if (tablero[i][j]==' ' && (j+i)%2!=0)
                         cout<<" "<<" "<<" "<<" "<<" ";
                     
                     else 
                         if (tablero[i][j]==' ' &&(j+i)%2==0)
                         cout<<" "<<" "<<" "<<" "<<" "; ;
            }
            cout<<endl; 
      }
 }


void cpu ()
{
     cout<<"Turno cpu." <<endl ;    
     do
     {
       do
       {
        do
        {
         do
         {
                  srand(time(NULL));
                  x=rand() % 7+0 ;
                  y=rand() % 7+0 ;
         }while (tablero[x][y]!='a'&&tablero[x][y]!='A');//verifica que tipo de movimiento puede hacer si con dama o ficha

         do
         {
              if (tablero[x][y]=='A')
              {
                  direccion=rand()% 4+1 ;
                  error=0;
                  
                  if (tablero[x][y] == 'a')
                  {
                     direccion=rand() % 2+1 ;
                     error=0;
                  }
              }
         }while (direccion>4||direccion<1);
        }while ((y==7&&direccion==2)||(y==0&&direccion==1)||(y==7&&direccion==4)||(y==0&&direccion==3)||(x==0&&direccion==4)||(x==0&&direccion==3)||(x==7&&direccion==1)||(x==7&&direccion==2));
      }while((direccion == 1 &&( tablero[x+1][y-1]== 'a'||tablero[x+1][y-1]== 'A') )||(direccion == 2 && (tablero[x+1][y+1]== 'a' || tablero[x+1][y+1]== 'A') )|| (direccion == 3 && (tablero[x-1][y-1]== 'a' || tablero[x-1][y-1]== 'A') )||(direccion == 4 && (tablero[x-1][y+1]== 'a' || tablero[x-1][y+1]== 'A') ));//VALIDACION PARA CASILLA OCUPADA POR UNA AMIGA
   
   if (direccion==1 &&( tablero[x+1][y-1] == 'b' || tablero[x+1][y-1] == 'B') )
   {
      if(y==1)
      {
              error=1;
      }
  
      if(x==6)
      {
              error=1;
      }
      
      if(tablero[x+2][y-2] == 'b')
      {
             error=1;
      }
             
      if(tablero[x+2][y-2] == 'a')
      {
             error=1;
      }
      
      if(tablero[x+2][y-2] == 'A')
      {
             error=1;
      }
      if(tablero[x+2][y-2] == 'B')
      {
             error=1;}
      }
 
      if (direccion==2 && (tablero[x+1][y+1] == 'b'||tablero[x+1][y+1] == 'B'))
      {
         if(y==6)
         {
                 error=1;
         }
         if(x==6)
         { 
                 error=1;
         }
         if(tablero[x+2][y+2] == 'b')
         {
                 error=1;
         }
                 
         if( tablero[x+2][y+2] == 'a')
         {
                 error=1;
         }
         
         if( tablero[x+2][y+2] == 'A')
         {
                error=1;
         }
         
         if( tablero[x+2][y+2] == 'B')
         {
               error=1;}
         }
 
         if (direccion==3 && (tablero[x-1][y-1] == 'b'||tablero[x-1][y-1] == 'B'))
         {
            if(y==1)
            { 
                    error=1;
            }
            if(x==1)
            { 
                    error=1;
            }
            if(tablero[x-2][y-2] == 'b')
            {
                    error=1;
            }
            if( tablero[x-2][y-2] == 'a')
            {
                    error=1;
            }
            if( tablero[x-2][y-2] == 'A')
            {
                    error=1;
            }
            if( tablero[x-2][y-2] == 'B')
            {
                    error=1;}
            }
            
            if (direccion==4 && (tablero[x-1][y+1] == 'b'||tablero[x-1][y+1] == 'B'))
            {
                  if(y==6)
                  {
                          error=1;
                  }
                  if(x==1)
                  {
                          error=1;
                  }
                  if(tablero[x-2][y+2] == 'b')//verifica que no este ocupado la posicion
                  {
                          error=1;}
                  
                  if( tablero[x-2][y+2] == 'a')//verifica que no este ocupado la posicion
                  {
                          error=1;
                  }
                  if( tablero[x-2][y+2] == 'B')//verifica que no este ocupado la posicion
                  {
                          error=1;
                  }
                          
                  if( tablero[x-2][y+2] == 'A')//verifica que no este ocupado la posicion
                  {
                         error=1;}
                  }
         }while(error==1);


if (tablero[x][y]=='A' && direccion == 1 && tablero[x+1][y-1]== ' ' ) //Revisa que casilla si esta vacia hace movimiento con dama
{
   tablero[x][y]=' ' ;
   tablero[x+1][y-1] = 'A' ;
   cout<<"Cpu Movio dama "<<x+1<<"-"<<y-1 ;
   getche ();
}
else 
   if (tablero[x][y]=='A' && direccion == 2 && tablero[x+1][y+1]== ' '  )//Revisa que casilla si esta vacia hace movimiento con dama
   {
      tablero[x][y]=' ' ;
      tablero[x+1][y+1] = 'A' ;
      cout<<"Cpu Movio dama "<<x+1<<"-"<<y+1 ;
      getche ();
   }
   else 
        if (tablero[x][y]=='A' && direccion == 3 && tablero[x-1][y-1]== ' '  )//Revisa que casilla si esta vacia hace movimiento con dama
        {
            tablero[x][y]=' ' ;
            tablero[x-1][y-1] = 'A' ;
            cout<<"Cpu Movio dama  "<<x-1<<"-"<<y-1 ;
            getche ();
        }
        else 
            if (tablero[x][y]=='A' && direccion == 4 && tablero[x-1][y+1]== ' '  )//Revisa que casilla si esta vacia hace movimiento con dama
            {
               tablero[x][y]=' ' ;
               tablero[x-1][y+1] = 'A' ;
               cout<<"Cpu Movio dama  "<<x-1<<"-"<<y+1 ;
               getche ();
            }
            else 
                 if(tablero[x][y]=='A' && direccion== 1 && (tablero [x+1][y-1] == 'b'||tablero [x+1][y-1] == 'B'))//Revisa que casilla esta ocupada con ficha o dama de usuario para atacar
                 {
                     tablero[x][y]=' ' ;
                     tablero[x+1][y-1]=' ' ;
                     tablero[x+2][y-2]= 'A' ;
                     
                     cout<<"\a";
                     cout<<"Cpu comio con dama "<<x+1<<"-"<<y-1 ;
                     fichax=fichax-1;
                     contador_fichas_o= contador_fichas_o+3;
                     getche ();
                 }
                 else 
                      if(tablero[x][y]=='A' && direccion== 2 && (tablero [x+1][y+1] == 'b'||tablero [x+1][y+1] == 'B'))//Revisa que casilla esta ocupada con ficha o dama de usuario para atacar
                      {
                           tablero[x][y]=' ' ;
                           tablero[x+1][y+1]=' ' ;
                           tablero[x+2][y+2]= 'A' ;
    
                           cout<<"\a";
                           cout<<"Cpu comio con dama   "<<x+1<<"-"<<y+1 ;
   
                           fichax=fichax-1;
                           contador_fichas_o= contador_fichas_o+3;
                           getche ();
                      }
                      else 
                           if(tablero[x][y]=='A' && direccion== 3 && (tablero [x-1][y-1] == 'b'||tablero [x-1][y-1] == 'B'))//Revisa que casilla esta ocupada con ficha o dama de usuario para atacar
                           {
                                 tablero[x][y]=' ' ;
                                 tablero[x-1][y-1]=' ' ;
                                 tablero[x-2][y-2]= 'A' ;
                                 
                                 cout<<"\a";
                                 cout<<"Cpu comio con dama  "<<x-1<<"-"<<y-1 ;
                                 fichax=fichax-1;
                                 contador_fichas_o= contador_fichas_o+3;
                                 getche ();
                           }
                           else 
                                if(tablero[x][y]=='A' && direccion== 4 && (tablero [x-1][y+1] == 'b'||tablero [x-1][y+1] == 'B'))//Revisa que casilla esta ocupada con ficha o dama de usuario para atacar
                                {
                                     tablero[x][y]=' ' ;
                                     tablero[x-1][y+1]=' ' ;
                                     tablero[x-2][y+2]= 'A' ;
    
                                     cout<<"\a";
                                     cout<<"Cpu comio con dama   "<<x-1<<"-"<<y+1 ;
                                     fichax=fichax-1;
                                     contador_fichas_o= contador_fichas_o+3;
                                     getche ();
                                 }
                                else 
                                     if (tablero[x][y]=='a' && direccion == 1 && tablero[x+1][y-1]== ' ' )//Ficha se mueve hacia la derecha de la cpu
                                     {
                                        tablero[x][y]=' ' ;
                                        tablero[x+1][y-1] = 'a' ;
                                        cout<<"Cpu Movio dama "<<x+1<<"-"<<y-1 ;
                                        getche ();
                                        }
                                        
                                     if (tablero[x][y]=='a' && direccion == 2 && tablero[x+1][y+1]== ' ' ) //Ficha se mueve hacia la izquierda de la cpu
                                        {
                                           tablero[x][y]=' ' ;
                                           tablero[x+1][y+1] = 'a' ;
                                           cout<<"Cpu Movio dama "<<x+1<<"-"<<y+1 ;
                                           getche ();
                                        }
                                     else 
                                          if(tablero[x][y]=='a'&& direccion== 1 && (tablero [x+1][y-1] == 'b'||tablero [x+1][y-1] == 'B'))//Revisa que casilla esta ocupada con ficha o dama de usuario para atacar
                                          {
                                                     tablero[x][y]=' ' ;
                                                     tablero [x+1][y-1]= ' ' ;
                                                     tablero[x+2][y-2]= 'a' ;
    
                                                     cout<<"\a";
                                                     cout<<"Cpu comio con dama  "<<x+1<<"-"<<y-1 ;
  
                                                     fichax=fichax-1;
                                                     contador_fichas_o= contador_fichas_o+3;
                                                     getche ();
                                          }
                                          
                        else 
                            if(tablero[x][y]=='a'&& direccion== 2 && ( tablero [x+1][y+1] == 'B'|| tablero [x+1][y+1] == 'b'))//Revisa que casilla esta ocupada con ficha o dama de usuario para atacar
                            {
                                  tablero[x][y]=' ' ;
                                  tablero[x+1][y+1]=' ' ;
                                  tablero[x+2][y+2]= 'a' ;
    
                                  cout<<"\a";
                                  cout<<"Cpu comio con dama  "<<x+1<<"-"<<y+1 ;
                 
                                  fichax=fichax-1;
                                  contador_fichas_o= contador_fichas_o+3;
                                  getche ();
                            }
   turno = 1 ;  
}


void Obligacion()
{
     for(i=0;i<T;i++)
     {
     for(j=0;j<T;j++)
     {
           if (tablero[i][j]=='B' && tablero[i+2][j+2]==' ' && (tablero[i+1][j+1]=='a'||tablero[i+1][j+1]=='A') && j!= 6)//verifica que puede comer con dama usuario a dama o ficha de CPU hacia la derecha arriba
           {
                  cout<<"Obligacion de comer ficha dejada por CPU "<<i+1<<"-"<<j+1<<endl;
                  tablero[i][j]=' ';
                  tablero[i+1][j+1]= ' ';
                  tablero[i+2][j+2]='B' ;
                  getche();
                  fichao=fichao-1;
                  turno=0;
           }
           
           else if (tablero[i][j]=='B' && tablero[i+2][j-2]==' ' && (tablero[i+1][j-1]=='a'||tablero[i+1][j-1]=='A') && j!= 1)//verifica que puede comer con dama usuario a dama o ficha de CPU hacia la derecha abajo
           {
                  cout<<"Obligacion de comer ficha dejada por CPU "<<i+1<<"-"<<j-1<<endl;
                  tablero[i][j]=' ';
                  tablero[i+1][j-1]= ' ';
                  tablero[i+2][j-2]='B' ;
                  getche();
                  fichao=fichao-1;
                  turno=0;
           }      
           
           else if (tablero[i][j]=='B' && tablero[i-2][j+2]==' ' && (tablero[i-1][j+1]=='a'||tablero[i-1][j+1]=='A')  && j!= 6)//verifica que puede comer con dama usuario a dama o ficha de CPU hacia la derecha
           {
                  cout<<"Obligacion de comer ficha dejada por CPU "<<i-1<<"-"<<j+1<<endl;
                  tablero[i][j]=' ';
                  tablero[i-1][j+1]= ' ';
                  tablero[i-2][j+2]='B' ;
                  getche();
                  fichao=fichao-1;
                  turno=0;
           }      
           
           else if(tablero[i][j]=='B'&& tablero[i-2][j-2]==' ' && (tablero[i-1][j-1]=='a'||tablero[i-1][j-1]=='A') && j!= 1 )//verifica que puede comer con dama usuario a dama o ficha de CPU hacia la izquierda
           {
                  cout<<"Obligacion de comer ficha dejada por CPU"<<i-1<<"-"<<j-1<<endl;
                  tablero[i][j]=' ';
                  tablero[i-1][j-1]= ' ';
                  tablero[i-2][j-2]='B' ;
                  getche();
                  fichao=fichao-1;
                  turno=0;
           }        
           
           else if(tablero[i][j]=='b'&& tablero[i-2][j-2]==' ' && (tablero[i-1][j-1]=='a'||tablero[i-1][j-1]=='A') && j!= 1  )//verifica que puede comer con ficha usuario a dama o ficha de CPU hacia la izquierda
                      {
                         cout<<"Obligacion de comer ficha dejada por CPU "<<i-1<<"-"<<j-1<<endl;
                         tablero[i][j]=' ';
                         tablero[i-1][j-1]= ' ';
                         tablero[i-2][j-2]='b' ;
                         getche();
                         fichao=fichao-1;
                         turno=0;
                      }
                      else if (tablero[i][j]=='b' && tablero[i-2][j+2]==' ' && (tablero[i-1][j+1]=='A'||tablero[i-1][j+1]=='a') && j!= 6 )//verifica que puede comer con ficha usuario a dama o ficha de CPU hacia la derecha
                      {
                         cout<<"Obligacion de comer ficha dejada por CPU "<<i-1<<"-"<<j+1<<endl;
                         tablero[i][j]=' ';
                         tablero[i-1][j+1]= ' ';
                         tablero[i-2][j+2]='b' ;
                         getche();
                         fichao=fichao-1;
                         turno=0;
                      }
                                       
                    }
           }        
}

void ComeCPU()
{
    for(i=0;i<T;i++)
    {
         for(j=0;j<T;j++)
         {
              if(tablero[i][j]=='A'&& tablero[i+2][j+2]==' ' && (tablero[i+1 ][j+1]=='b'||tablero[i+1 ][j+1]=='B') && j!=1)// Verifica que dama Cpu puede comer a Dama o ficha usuario hacia arriba y izquierda de la CPU
              {
                   cout<<"Cpu comio tu ficha"<<i+1<<"-"<<j+1<<endl;
                   tablero[i][j]=' ';
                   tablero[i+1][j+1]= ' ';
                   tablero[i+2][j+2]='A' ;
                   getche();
                   fichax=fichax-1;
                   turno=1;
              }
              if (tablero[i][j]=='A' && tablero[i-2 ][j-2]==' ' && ( tablero[i-1][j-1]=='b'||tablero[i-1][j-1]=='B') && j!=1) // Verifica que dama Cpu puede comer a Dama o ficha usuario hacia abajo y derecha de la CPU
              {
                    cout<<"Cpu comio tu ficha"<<i-1<<"-"<<j-1<<endl;
                    tablero[i][j]=' ';
                    tablero[i-1][j-1]= ' ';
                    tablero[i-2][j-2]='A' ;
                    getche();
                    fichax=fichax-1;
                    turno=1;
              }
                    
              else if (tablero[i][j]=='A' && tablero[i-2][j+2]==' ' && (tablero[i-1][j+1]=='b'||tablero[i-1][j+1]=='B') && j!=6  )// Verifica que dama Cpu puede comer a Dama o ficha usuario hacia arriba y izquierda de la CPU
              {
                    cout<<"Cpu comio tu ficha "<<i-1<<"-"<<j+1<<endl;
                    tablero[i][j]=' ';
                    tablero[i-1][j+1]= ' ';
                    tablero[i-2][j+2]='A' ;
                    getche();
                    fichax=fichax-1;
                    turno=1;
              }
              else if (tablero[i][j]=='A' && tablero[i+2][j-2]==' ' && (tablero[i+1][j-1]=='b'||tablero[i+1][j-1]=='B') && j!=6)// Verifica que dama Cpu puede comer a Dama o ficha usuario hacia arriba y derecha de la CPU
              {
                    cout<<"Cpu comio tu ficha "<<i+1<<"-"<<j-1<<endl;
                    tablero[i][j]=' ';
                    tablero[i+1][j-1]= ' ';
                    tablero[i+2][j-2]='A' ;
                    getche();
                    fichax=fichax-1;
                    turno=1;
              }
              else if(tablero[i][j]=='a'&& tablero[i+2][j+2]==' ' &&( tablero[i+1][j+1]=='b'||tablero[i+1][j+1]=='B') && j!=6)// Verifica que ficha Cpu puede comer a Dama o ficha usuario hacia der de CPU
              {
                    cout<<"Cpu comio tu ficha"<<i+1<<"-"<<j+1<<endl;
                    tablero[i][j]=' ';
                    tablero[i+1][j+1]= ' ';
                    tablero[i+2][j+2]='a' ;
                    getche();
                    fichax=fichax-1;
                    turno=1;
              }
              else if (tablero[i][j]=='a' && tablero[i+2 ][j-2 ]==' ' && (tablero[i+1][j-1]=='b' ||tablero[i+1][j-1]=='B' ) && j!=1)// Verifica que ficha Cpu puede comer a Dama o ficha usuario hacia izq CPU
              {            
                    cout<<"Cpu comio tu ficha "<<i+1<<"-"<<j-1<<endl;
                    tablero[i][j]=' ';
                    tablero[i+1][j-1]= ' ';
                    tablero[i+2][j-2]='a' ;
                    getche();
                    fichax=fichax-1;
                    turno=1;
              }
         }
    }
}

void IdentificarDamaUsuario() //Procedimiento Convertir ficha en Dama en el usuario
{
    for (x=0;x<T;x++)
    {
        if(tablero[0][x]== 'b' )
        {
             tablero[0][x]='B';
             cout<<"Ficcha de Usuario se corono, ocupa letra B "<<endl ;
             getche();
        }
    }
}

void IdentificarDamaCPU() //Procedimiento Convertir ficha en Dama ede la CPU
{
     for (x=0;x<T;x++)
         {
             if(tablero[7][x]== 'a' )
             {
             tablero[7][x]='A';
             cout<<"Ficha de CPU se corono, ocupa letra A"<<endl ;
             getche();
             }
         }
}


void Limpiar()
{   
    system("CLS");
    cout<<"\t\t         ";
    imprimir() ;
}

//---------------------------------------------------------------------------------------------------------------------------


int main( )
{
  cout<<"\t\t         ";
  //system("color 0A") ;
  
  rellenar();  // Llena las casillas
  imprimir() ; //Lo muestra en pantalla
  
  do
  { 
    Obligacion();   //Prodceimiento que te obliga a comer ficha o dama de la CPU

    if(turno==1)
        MoverUsuario();    //Movimiento del Usuario;
         
    IdentificarDamaUsuario(); //Identifica ficha para transformar a dama
    Limpiar();   //limpia la pantalla y ejecuta nuevamente llenado
    
    if (fichao==0) //Revisa si ganaste partida
    {
       cout<<"GANASTE " <<endl;
       terminar=2;
    break;
    }

    ComeCPU();   //procedimiento en que CPU puede comer tu ficha
         
    if(turno==0)   //Movimiento de la CPU
      cpu();
         
    IdentificarDamaCPU; //Identifica ficha para transformarla en Dama CPU
    Limpiar();    //limpia la pantalla y ejecuta nuevamente llenado     
        
    if(fichax==0) //Revisa si persite la partida
    {
       cout<<"YOU LOST... LOSEER! "<<endl;
       terminar=2;
       break;
    }
    
}while(terminar==1); //bucle para que peuda seguir el juego
    
system("pause");
}




