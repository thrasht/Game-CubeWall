#include<stdio.h>
#include<winbgim.h>
#include <time.h>
#define NUM 15
#define TAM 15
#define XCOO 300
#define YCOO 350
#define NR 5
typedef struct
{
        int x,y;
        int color,existe;
}Tcubo;
typedef struct
{
    char nombre[30];
    int puntos;
    long tiempo;
}Records;

void waitForLeftMouseClick();
void cubo( int x, int y);
Tcubo*** reservaContenedor();
void generaCont(Tcubo*** cont);
void dibujaContenedor(Tcubo*** cont,int x, int y);
void liberaContenedor(Tcubo*** cont);
void giraDerecha(Tcubo*** cont);
void giraIzquierda(Tcubo*** cont);
void EstadoInicial(Tcubo*** cont);
void generajugador(Tcubo j[7],Tcubo*** cont);
char leetecla();
void menu(Tcubo***);
int juego(Tcubo***);
void inicializa_jugador(Tcubo*** , int *, int *);
int mueve_izquierda(Tcubo*** cont);
int mueve_derecha(Tcubo*** cont);
int mueve_adelante(Tcubo*** cont);
int mueve_atras(Tcubo*** cont);
void inicializa_pared(Tcubo*** cont, int *, int);
void actualiza_pared(Tcubo*** cont, int *p);
void ayuda();
void inicializa_records();
void muestra_records();
void agrega_records(Records);
char* captura_nombre();
int inttextxy(int x, int y, char *cad, int max);
void contornoContenedor(int x,int y,int p);
void portada();
void presentacion();
void cuadrado(Tcubo ***, int *);
void linea(Tcubo ***, int *);
void letraL(Tcubo ***, int *);
void letraT(Tcubo ***, int *);
void jugadorlinea(Tcubo*** cont, int *, int *);
void jugadorL(Tcubo*** cont, int *, int *);
void jugadorT(Tcubo*** cont, int *, int *);
int pcuad(Tcubo ***c);


int main()
{
    initwindow(800,600);
    Tcubo*** contenedor;
    portada();
    cleardevice();
    contenedor=reservaContenedor();
    generaCont(contenedor);
    //EstadoInicial(contenedor);
    //inicializa_jugador(contenedor);
    menu(contenedor);
    liberaContenedor(contenedor);
    closegraph();
}
void cubo( int x, int y)
{
     //tapa frontal//

     int *punto;
     punto=(int*)malloc(sizeof(int)*8);
     
     *(punto+0)=x;
     *(punto+1)=y;
     *(punto+2)=x+TAM;
     *(punto+3)=y;
     *(punto+4)=x+TAM;
     *(punto+5)=y+TAM;
     *(punto+6)=x;
     *(punto+7)=y+TAM;
     fillpoly(4,punto);

     //tapa superior//

     *(punto+0)=x;
     *(punto+1)=y;
     *(punto+2)=x+TAM/2;
     *(punto+3)=y-TAM/2;
     *(punto+4)=x+TAM+TAM/2;
     *(punto+5)=y-TAM/2;
     *(punto+6)=x+TAM;
     *(punto+7)=y;
     fillpoly(4,punto);

     //tapa de lateral//

     *(punto+0)=x+TAM;
     *(punto+1)=y;
     *(punto+2)=x+TAM+TAM/2;
     *(punto+3)=y-TAM/2;
     *(punto+4)=x+TAM+TAM/2;
     *(punto+5)=y+TAM/2;
     *(punto+6)=x+TAM;
     *(punto+7)=y+TAM;
     fillpoly(4,punto);

}
Tcubo*** reservaContenedor()
{
     int i,j,k;
     Tcubo*** aux;
     aux=(Tcubo***)malloc(sizeof(Tcubo**)*NUM);
     for(i=0;i<NUM;i++)
     {
         *(aux+i)=(Tcubo**)malloc(sizeof(Tcubo*)*NUM);
         for(j=0;j<NUM;j++)
         {
             *(*(aux+i)+j)=(Tcubo*)malloc(sizeof(Tcubo)*NUM);
         }
     }
     return(aux);
}
void generaCont(Tcubo*** cont)
{
    int i,j,k;
    for(k=0;k<NUM;k++)
    {
        for(j=0;j<NUM;j++)
        {
            for(i=0;i<NUM;i++)
            {
                (*(*(*(cont+k)+j)+i)).x=(i*TAM-k*TAM/2);
                (*(*(*(cont+k)+j)+i)).y=(-j*TAM+k*TAM/2);
                (*(*(*(cont+k)+j)+i)).color=2;
                (*(*(*(cont+k)+j)+i)).existe=0;
            }
        }
    }
}
void dibujaContenedor(Tcubo*** cont,int x, int y)
{
     int i,j,k;
     setcolor(BLACK);
     line(x+TAM/2,-15+y+TAM/2,x+TAM/2,y-(NUM*TAM)+TAM/2);
     for(k=0;k<NUM;k++)
         {
         for(j=0;j<NUM;j++)
             {
             for(i=0;i<NUM;i++)
                 {
                     if((*(*(*(cont+k)+j)+i)).existe!=0&&(*(*(*(cont+k)+j)+i)).existe!=5)
                     {
                     setfillstyle(1,(*(*(*(cont+k)+j)+i)).color);
                     cubo(x+((*(*(*(cont+k)+j)+i))).x,y+((*(*(*(cont+k)+j)+i))).y);
                     }
                 }
             }
         }
                 
     contornoContenedor(x,y,NUM);
}
void contornoContenedor(int x,int y,int p)
{
    setcolor(WHITE); 
    line(x-(p*TAM/2)+TAM/2,y-(p*TAM/2)+TAM/2,x+(p*TAM/2)+TAM/2,y-(p*TAM/2)+TAM/2);
    line(x-(p*TAM/2)+TAM/2,y+(p*TAM/2)+TAM/2,x-(p*TAM/2)+TAM/2,y-(p*TAM/2)+TAM/2);
    line(x+(p*TAM/2)+TAM/2,y+(p*TAM/2)+TAM/2,x+(p*TAM/2)+TAM/2,y-(p*TAM/2)+TAM/2);
    line(x+(p*TAM)+TAM/2,y+TAM/2,x+(p*TAM)+TAM/2,y-(p*TAM)+TAM/2);
    line(x+TAM/2,y-(p*TAM)+TAM/2,x+(p*TAM)+TAM/2,y-(p*TAM)+TAM/2);
    line(x+TAM/2,y-(p*TAM)+TAM/2,x-(p*TAM/2)+TAM/2,y-(p*TAM/2)+TAM/2);  
    line(x+(p*TAM)+TAM/2,y-(p*TAM)+TAM/2,x+(p*TAM/2)+TAM/2,y-(p*TAM/2)+TAM/2);
}
void liberaContenedor(Tcubo*** cont)
{
     int i,j;
     for(i=0;i<NUM;i++)
     {
         for(j=0;j<NUM;j++)
             free(*(*(cont+i)+j));
                 free(*(cont+i));
    }
        free(cont);
}
void libera_jugador(Tcubo*** cont)//jugador.existe=2
{
     (*(*(*(cont+7)+1)+7)).existe=0;
     (*(*(*(cont+7)+1)+7)).existe=0;
     (*(*(*(cont+8)+1)+7)).existe=0;
     (*(*(*(cont+8)+1)+7)).existe=0;
     (*(*(*(cont+7)+1)+8)).existe=0;
     (*(*(*(cont+7)+1)+8)).existe=0;
     (*(*(*(cont+8)+1)+8)).existe=0;
     (*(*(*(cont+8)+1)+8)).existe=0;
     
}
void giraDerecha(Tcubo*** cont)
{
     Tcubo***c;//auxiliar
     int i,j,k;
     
     c=reservaContenedor();
     //respaldo de contenedor
     for(k=0;k<NUM;k++)
      for(j=0;j<NUM;j++)
       for(i=0;i<NUM;i++)
       {
          (*(*(*(c+k)+j)+i)).existe=(*(*(*(cont+k)+j)+i)).existe;
          (*(*(*(c+k)+j)+i)).color=(*(*(*(cont+k)+j)+i)).color;
       }

     for(k=0;k<NUM;k++)
      for(j=0;j<NUM;j++)
       for(i=0;i<NUM;i++)
       {
          (*(*(*(cont+NUM-i-1)+j)+k)).existe=(*(*(*(c+k)+j)+i)).existe;//pared renglon columna
          (*(*(*(cont+NUM-i-1)+j)+k)).color=(*(*(*(c+k)+j)+i)).color;
       }   
       liberaContenedor(c); 
             
}

void giraIzquierda(Tcubo*** cont)
{
     Tcubo***c;//auxiliar
     int i,j,k;
     
     c=reservaContenedor();
     //respaldo de contenedor
     for(k=0;k<NUM;k++)
      for(j=0;j<NUM;j++)
       for(i=0;i<NUM;i++)
       {
          (*(*(*(c+k)+j)+i)).existe=(*(*(*(cont+k)+j)+i)).existe;
          (*(*(*(c+k)+j)+i)).color=(*(*(*(cont+k)+j)+i)).color;
       }

     for(k=0;k<NUM;k++)
      for(j=0;j<NUM;j++)
       for(i=0;i<NUM;i++)
       {
          (*(*(*(cont+i)+j)+NUM-k-1)).existe=(*(*(*(c+k)+j)+i)).existe;//pared renglon columna
          (*(*(*(cont+i)+j)+NUM-k-1)).color=(*(*(*(c+k)+j)+i)).color;
       }   
     liberaContenedor(c);    
}
void EstadoInicial(Tcubo*** cont)
{
     int i, j,k;
     for(j=0;j<NUM;j++)
     {
         for(i=0;i<NUM;i++)
         {for(k=0;k<NUM;k++)
         if(k==0)
             (*(*(*(cont+j)+k)+i)).existe=1;
             else
             (*(*(*(cont+j)+k)+i)).existe=0;
         }
     }
}
char leetecla()
{
     char tecla;
     tecla=getch();
     if(getch==0)
     {
         tecla=getch();
     }
     return(tecla);
}
void menu(Tcubo ***cont)
{
 int op=0;
 int x,y,a;
 presentacion();
 while(!op)
	{
       x=mousex();
       y=mousey();
     if("waitForLeftMouseClick()")
     {
           if(x>300 && x<600 && y>150 && y<200) //boton jugar
		    {
				 cleardevice();
				// inicializa_jugador(cont);
				 a=juego(cont);
                 presentacion();                     
		    }
		  if(x>300 && x<600 && y>250 && y<300) //boton puntuaciones 
		    {
                   cleardevice();
                   ayuda();
                   presentacion();

           }
          if(x>300 && x<600 && y>350 && y<400) //boton creditos 
		    {
                   cleardevice();
		           muestra_records();
		           presentacion();
            }
	      if(x>300 && x<600 && y>450 && y<500) //boton ayuda 
		    {
                  op=1;
		    }
        }
	}
}
void presentacion()                     
{
cleardevice();
setfillstyle(1,BLACK);
rectangle(300,100,900,650);      
floodfill(301,101,6);
setcolor(BLUE);
settextstyle(3,0,4);
outtextxy(150,40,"P A R E D   A P L A S T A   C U B O S !");
settextstyle(3,0,3);
setcolor(BLUE);
setcolor(WHITE);
setfillstyle(1,0);
rectangle(300,150,600,200); //jugar     
floodfill(301,151,0);
rectangle(300,250,600,300); //ayuda
floodfill(301,251,0);
rectangle(300,350,600,400); //puntuaciones
floodfill(301,351,0);
rectangle(300,450,600,500); //salir
floodfill(301,451,0);
setcolor(BLUE);
outtextxy(370,160,"J U G A R");
outtextxy(370,260,"A Y U D A");
outtextxy(370,360,"R E C O R D S");
outtextxy(370,460,"S A L I R");
waitForLeftMouseClick();
}
void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; 
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}
/*void menu(Tcubo*** cont)
{ 
    int pos=0, a;
    char op;
    while(op!=27)//ESC
    {
        switch(op)
        {
        case 80:
             cleardevice();
             if(pos<3)
             {
                 pos++;
             }
             break;
        case 72:
             cleardevice();
             if(pos>0)
             {
                 pos--;
             }
             break;
        case 13://ENTER
             switch(pos)
             {
                 case 0:cleardevice();
                        a=juego(cont);
                        break;
                 case 1:cleardevice();
                        ayuda();
                        break;
                 case 2:cleardevice();
                        muestra_records();
                        break;
                 case 3:exit(1);
                        break;
             }
             break;
        }
    settextstyle(3,0,6);
    setcolor(WHITE);
    outtextxy(130,50,"PARED APLASTACUBOS!");
    settextstyle(4,0,2);
    if(pos==0)
    {
        setcolor(BLUE);
    }  
    else
    {
        setcolor(GREEN);
    }
    outtextxy(350,250,"JUGAR");
    if(pos==1)
    {
        setcolor(BLUE);
    }
    else
    {
        setcolor(GREEN);
    }
    outtextxy(350,280,"AYUDA");
    if(pos==2)
    {
        setcolor(BLUE);
    }
    else
    {
        setcolor(GREEN);
    }
    outtextxy(330,310,"RECORDS");
    if(pos==3)
    {
        setcolor(BLUE);
    }
    else
    {
        setcolor(GREEN);
    }
    outtextxy(360,340,"SALIR");
    op=leetecla();
    }
}*/
int juego(Tcubo*** contenedor)
{
    char tecla, cad[10]="\0", *nom;
    int punt=0, pagina=0, i=0,j=0,c,l=0,a,izq=7,der=7,v=0;
    long d;
    Records R;
    time_t ha, hi;
    EstadoInicial(contenedor);
    //inicializa_jugador(contenedor,&izq,&der);
    nom=captura_nombre();
    setactivepage(pagina);
    dibujaContenedor(contenedor,XCOO,YCOO);
    time(&hi);
    while(tecla!=27)
    {
        setvisualpage(pagina);
        if(pagina==1)
        {
            pagina=0;
        }
        else
        {
            pagina=1;
        }
        setactivepage(pagina);
	    time(&ha);
	    d=(long)difftime(ha, hi);
	    sprintf(cad, "Tiempo: %02d:%02d:%02d", d/3600, d%3600/60, d%3600%60);
	    outtextxy(50,50,cad);
	    outtextxy(480,50,"Nombre:");
        outtextxy(600,50,nom);
	    sprintf(cad, "Puntos: %d",punt);
	    outtextxy(570,250,cad);
        if(j%120==0)
        {
        EstadoInicial(contenedor);
        if(izq>TAM||izq<0)
        izq=2;
        if(der>TAM||der<0)
        der=2;
        switch(v)
        {
                 case 0:
                      inicializa_jugador(contenedor,&izq,&der);
                      inicializa_pared(contenedor,&c,v);
                      v++;
                      break;
                 case 1:
                      jugadorlinea(contenedor,&izq,&der);
                      inicializa_pared(contenedor,&c,v);
                      v++;
                      break;
                 case 2:
                      jugadorL(contenedor,&izq,&der);
                      inicializa_pared(contenedor,&c,v);
                      v++;
                      break;
                 case 3:
                      jugadorT(contenedor,&izq,&der);
                      inicializa_pared(contenedor,&c,v);
                      v=0;
                      break;
        }      
            
        //inicializa_pared(contenedor,&c,v);
        if(punt%100==0)
         l++;}
        j++;
        if(j>120)
        j=1;
               if(i%(10-l)==0)
           actualiza_pared(contenedor, &punt);
           i++;
           if(i>(10-l))
           i=1;
        if(kbhit())
        {
            tecla=leetecla();
            switch(tecla)
            {
                case 77:
                     a=mueve_derecha(contenedor);
                     der++;
                break;
                case 75:
                     a=mueve_izquierda(contenedor);
                     der--;
                break;
                case 72:
                     a=mueve_adelante(contenedor);
                     izq--;
                break;
                case 80:
                     a=mueve_atras(contenedor);
                     izq++;
                break;
                case 'a':giraIzquierda(contenedor);
                break;
                case 'd':giraDerecha(contenedor);
                break;
                case 27:
                     setvisualpage(pagina);
                     cleardevice();
                     liberaContenedor(contenedor);
                     return(1);
                break;
            }
            setfillstyle(1,BLACK);
            bar(XCOO-150,YCOO-250,XCOO+240,YCOO+130);
            dibujaContenedor(contenedor,XCOO,YCOO);
            delay(30);
        }
        else
        {
            setfillstyle(1,BLACK);
            bar(XCOO-150,YCOO-250,XCOO+240,YCOO+130);
            dibujaContenedor(contenedor,XCOO,YCOO);
            delay(30);
        }
        if((*(*(*(contenedor+NUM-1)+2)+0)).existe==4)
        { punt+=10;
     if(pcuad(contenedor))
        {
            R.puntos=punt;
            R.tiempo=d;
            strcpy(R.nombre,nom);
            setvisualpage(pagina);
            cleardevice();
            outtextxy(150,200,"FIN DEL JUEGO");
            getch();
            inicializa_records();
            agrega_records(R);
            cleardevice();
            muestra_records();
            getch();
            setvisualpage(1);
            setactivepage(1);
            cleardevice();
            setvisualpage(0);
            setactivepage(0);
            cleardevice();
            return(1);
        }}
    }
}
void agrega_records(Records r)
{
     Records registros[NR];
     int i;
     FILE *f;
     
     for(i=0;i<NR;i++)
     {  strcpy(registros[i].nombre," ");
        registros[i].puntos=0;
     }
     
     f=fopen("Records.dat","rb+");
     if(f==NULL)
     {  printf("No se encontro el archivo");
        registros[0]=r;
        f=fopen("Records.dat","wb");
        fwrite(registros,sizeof(Records),NR,f);
        fclose(f);
     }
     else
     {
         fread(registros,sizeof(Records),NR,f);
        
         for(i=NR-1;i>=0;i--)
         {  if(registros[i].puntos<=r.puntos && i+1<NR)
               registros[i+1]=registros[i];
            else 
               if(registros[i].puntos>=r.puntos && i+1<NR)
               {  registros[i+1]=r;
                  i=-1;
               }
         }
         if(registros[0].puntos<=r.puntos)
            registros[0]=r;
         rewind(f);
         fwrite(registros,sizeof(Records),NR,f);
         fclose(f);
     }
}

void inicializa_jugador(Tcubo*** cont, int *i, int *d)//jugador.existe=2
{
     (*(*(*(cont+*i)+1)+*d)).existe=2;
     (*(*(*(cont+*i)+1)+*d)).color=7;
     (*(*(*(cont+*i)+1)+*d+1)).existe=2;
     (*(*(*(cont+*i)+1)+*d+1)).color=7;
     (*(*(*(cont+*i+1)+1)+*d+1)).existe=2;
     (*(*(*(cont+*i+1)+1)+*d+1)).color=7;
     (*(*(*(cont+*i+1)+1)+*d)).existe=2;
     (*(*(*(cont+*i+1)+1)+*d)).color=7;
}
int mueve_izquierda(Tcubo*** cont)
{
     int i, j, k;
     for(k=0;k<NUM;k++)
     {
         for(j=0;j<NUM;j++)
         {
             for(i=0;i<NUM;i++)
             {
                     if((*(*(*(cont+k)+j)+i)).existe==2)
                     {
                         if(i-1>=0)
                         {
                         (*(*(*(cont+k)+j)+i-1)).existe=2;
                         (*(*(*(cont+k)+j)+i)).existe=0;
                         (*(*(*(cont+k)+j)+i-1)).color=(*(*(*(cont+k)+j)+i)).color;
                         }
                         else
                         {
                         return(1);
                         }
                     }
             }
         }
     }
}
int mueve_derecha(Tcubo*** cont)
{
     int i, j, k;
     for(k=0;k<NUM;k++)
     {
         for(j=0;j<NUM;j++)
         {
             for(i=NUM;i>=0;i--)
             {
                 if((*(*(*(cont+k)+j)+i)).existe==2)
                 {
                     if(i+1<NUM)
                     {
                     (*(*(*(cont+k)+j)+i+1)).existe=2;
                     (*(*(*(cont+k)+j)+i)).existe=0;
                     (*(*(*(cont+k)+j)+i+1)).color=(*(*(*(cont+k)+j)+i)).color;
                     }
                     else
                     {
                         return(1);
                     }
                 }
             }
         }
     }
}
int mueve_adelante(Tcubo*** cont)
{
     int i, j, k;
     for(k=0;k<NUM;k++)
     {
         for(j=0;j<NUM;j++)
         {
             for(i=0;i<NUM;i++)
             {
                 if((*(*(*(cont+k)+j)+i)).existe==2)
                 {
                     if(k-1>=0)
                     {
                     (*(*(*(cont+k-1)+j)+i)).existe=2;
                     (*(*(*(cont+k)+j)+i)).existe=0;
                     (*(*(*(cont+k-1)+j)+i)).color=(*(*(*(cont+k)+j)+i)).color;
                     }
                     else
                     {
                         return(1);
                     }
                 }
             }
         }
     }
}
int mueve_atras(Tcubo*** cont)
{
     int i, j, k;
     for(k=NUM-1;k>=0;k--)
     {
         for(j=0;j<NUM;j++)
         {
             for(i=0;i<NUM;i++)
             {
                 if((*(*(*(cont+k)+j)+i)).existe==2)
                 {
                     if(k+1<NUM)
                     {
                     (*(*(*(cont+k+1)+j)+i)).existe=2;
                     (*(*(*(cont+k)+j)+i)).existe=0;
                     (*(*(*(cont+k+1)+j)+i)).color=(*(*(*(cont+k)+j)+i)).color;
                     }
                     else
                     {
                         return(1);
                     }
                 }
             }
         }
     }
}
void inicializa_pared(Tcubo*** cont, int *c, int v)
{
     int p,i,j;
    /* srand(time(NULL));
     *c=rand()%(NUM-3);*/
     for(i=0;i<NUM;i++)
       for(j=0;j<NUM;j++)
     {
     (*(*(*(cont+i)+NUM-1)+j)).existe=4;
     (*(*(*(cont+i)+NUM-1)+j)).color=4;
     (*(*(*(cont+i)+0)+j)).existe=1;
     (*(*(*(cont+i)+0)+j)).color=2;
     }
     switch(v)
        {
                 case 0:
                      cuadrado(cont,c);
                      break;
                 case 1:
                     linea(cont,c);
                      break;
                 case 2:
                      letraL(cont,c);
                      break;
                 case 3:
                      letraT(cont,c);
                      break;
        } 
}
void actualiza_pared(Tcubo*** cont, int *p)
{
    int i, j, k;
    
    for(k=0;k<NUM;k++)
    {
        for(j=0;j<NUM;j++)
        {
            for(i=0;i<NUM;i++)
            {
                if((*(*(*(cont+k)+j)+i)).existe==4)
                {
                    if(j>2)
                    {
                        (*(*(*(cont+k)+j)+i)).existe=0;
                        (*(*(*(cont+k)+j-1)+i)).color=(*(*(*(cont+k)+j)+i)).color;
                        (*(*(*(cont+k)+j-1)+i)).existe=4;
                    }
                    else
                    {
                        (*(*(*(cont+k)+j)+i)).existe=0;
                        (*(*(*(cont+k)+0)+i)).color=2;
                    }
                }
            }
        }
    }
    
}
void ayuda()
{
    char C[80];
	FILE *fp;
	int y=25;
	fp=fopen("ayuda.txt","r");
	settextstyle(3,0,1);
	if(fp==NULL)
	{
        outtextxy(20,20,"No se puede abrir el archivo");
    }
    else
    {
        while(!feof(fp))
        {
            fgets(C,79,fp);
            outtextxy(20,y,C);
            y+=25;
        }
    }
    getch();
    cleardevice();
}
void inicializa_records()
{
    int i;
    Records R={"Anonimo",100,0};
    FILE *fp;
    fp=fopen("records.dat","rb");
    if(fp!=NULL)
    {
        fclose(fp);
        //outtextxy(150,50,"Error al abrir el archivo de los records");
        getch();
        cleardevice();
        return;
    }
    fp=fopen("records.dat","wb");
    if(fp==NULL)
    {
        outtextxy(150,50,"Error al crear el archivo");
        getch();
        cleardevice();
        return;
    }
    for(i=0;i<5;i++)
    {
        fwrite(&R,sizeof(Records),1,fp);
    }
    fclose(fp);
}
void muestra_records()
{
     char cad[40];
     int i=100;
     Records R;
     FILE *fp;
     settextstyle(3,0,3);
     setcolor(WHITE);
     fp=fopen("records.dat","rb");
     if(fp==NULL)
     {
         inicializa_records();
         muestra_records();
     }
     else
     {
         fread(&R,sizeof(Records),1,fp);
         outtextxy(300,60,"RECORDS");
         while(!feof(fp))
         {
             sprintf(cad,"Nombre: %s Puntos: %d Tiempo: %02d:%02d:%02d", R.nombre, R.puntos, R.tiempo/3600, R.tiempo%3600/60, R.tiempo%3600%60);
             outtextxy(50,i,cad);
             fread(&R,sizeof(Records),1,fp);
	         i+=30;
         }
         getch();
         cleardevice();
     }
     fclose(fp);
}
char* captura_nombre()
{
	char *cadena;
	int out;
	setcolor(BLUE);
	settextstyle(1,0,2);
	cadena=(char *)malloc(sizeof(char)*20);
	out=inttextxy(100,50,cadena,20);
	cleardevice();
	return(cadena);
}
int inttextxy(int x, int y, char *cad, int max)
{
    char car;
    int pos=0;
    (*(cad+0))='\0';
    do
    {
        outtextxy(x-20,y,"Nombre:");
        car=leetecla();
        switch(car)
        {
            case 13:return(1);
                 break;
            case 27:(*(cad+0))='\0';
                 return(0);
                 break;
            case 8:
                 if(pos>=0)
                 {
                 pos--;
                 (*(cad+pos))='\0';
                 }
                 break;
            default:
                 if(pos<max-1)
                 {
                 (*(cad+pos))=car;
                 pos++;
                 (*(cad+pos))='\0';
                 }
                 break;
        }
        cleardevice();
        outtextxy(x+110,y,cad);
    }while(pos<max);
    return(1);
}
void portada()
{
cleardevice();
setcolor(RED);
settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
outtextxy(100,50,"UNIVERSIDAD AUTONOMA DE SAN LUIS POTOSI.");
setcolor(2);
outtextxy(100,100,"FACULTAD DE INGENIERIA.");
setcolor(6);
outtextxy(100,150,"AREA DE COMPUTACION E INFORMATICA.");
setcolor(1);
outtextxy(100,200,"ESTRUCTURAS DE DATOS Y ALGORITMOS A.");
setcolor(11);
outtextxy(100,250,"PROYECTO DE CUBOS.");
setcolor(10);
outtextxy(100,300,"AUTOR:");
setcolor(8);
outtextxy(100,350,"EDUARDO MONTES HERNANDEZ");
outtextxy(100,450,"ENTER PARA CONTINUAR.");
getch();
}
void cuadrado(Tcubo ***cont, int *c)
{
     srand(time(NULL));
     *c=(rand()%(NUM-5))+2;
     (*(*(*(cont+*c)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c)+0)+*c)).existe=5;
     (*(*(*(cont+*c+1)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c+1)+0)+*c)).existe=5;
     (*(*(*(cont+*c)+NUM-1)+*c+1)).existe=5;
     (*(*(*(cont+*c)+0)+*c+1)).existe=5;
     (*(*(*(cont+*c+1)+NUM-1)+*c+1)).existe=5;
     (*(*(*(cont+*c+1)+0)+*c+1)).existe=5;  
}
void linea(Tcubo ***cont, int *c)
{
     srand(time(NULL));
     *c=(rand()%(NUM-5))+2;
     (*(*(*(cont+*c)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c)+0)+*c)).existe=5;
     (*(*(*(cont+*c+1)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c+1)+0)+*c)).existe=5;
     (*(*(*(cont+*c+2)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c+2)+0)+*c)).existe=5;
     (*(*(*(cont+*c+3)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c+3)+0)+*c)).existe=5;  
}     
void letraL(Tcubo ***cont, int *c)
{
     srand(time(NULL));
     *c=(rand()%(NUM-5))+2;
     (*(*(*(cont+*c)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c)+0)+*c)).existe=5;
     (*(*(*(cont+*c)+NUM-1)+*c+1)).existe=5;
     (*(*(*(cont+*c)+0)+*c+1)).existe=5;
     (*(*(*(cont+*c)+NUM-1)+*c+2)).existe=5;
     (*(*(*(cont+*c)+0)+*c+2)).existe=5;
     (*(*(*(cont+*c+1)+NUM-1)+*c+2)).existe=5;
     (*(*(*(cont+*c+1)+0)+*c+2)).existe=5;  
}
void letraT(Tcubo ***cont, int *c)
{
     srand(time(NULL));
     *c=(rand()%(NUM-5))+2;
     (*(*(*(cont+*c)+NUM-1)+*c)).existe=5;
     (*(*(*(cont+*c)+0)+*c)).existe=5;
     (*(*(*(cont+*c)+NUM-1)+*c+1)).existe=5;
     (*(*(*(cont+*c)+0)+*c+1)).existe=5;
     (*(*(*(cont+*c)+NUM-1)+*c+2)).existe=5;
     (*(*(*(cont+*c)+0)+*c+2)).existe=5;
     (*(*(*(cont+*c-1)+NUM-1)+*c+1)).existe=5;
     (*(*(*(cont+*c-1)+0)+*c+1)).existe=5;  
}
int pcuad(Tcubo ***contenedor)
{
    int j,k,res=0;
     for(j=0;j<TAM&&(*(*(*(contenedor+j)+1)+k)).existe!=2;j++)
       for(k=0;(*(*(*(contenedor+j)+1)+k)).existe!=2&&k<TAM;k++);
       if((*(*(*(contenedor+j-1)+0)+k)).existe!=4&&(*(*(*(contenedor+j-1)+0)+k-1)).existe==1)
     return(res);
     return(res+1);
}
void jugadorlinea(Tcubo*** cont,int *i,int *d)//jugador.existe=2
{
     (*(*(*(cont+*i)+1)+*d)).existe=2;
     (*(*(*(cont+*i)+1)+*d)).color=7;
     (*(*(*(cont+*i+1)+1)+*d)).existe=2;
     (*(*(*(cont+*i+1)+1)+*d)).color=7;
     (*(*(*(cont+*i+2)+1)+*d)).existe=2;
     (*(*(*(cont+*i+2)+1)+*d)).color=7;
     (*(*(*(cont+*i+3)+1)+*d)).existe=2;
     (*(*(*(cont+*i+3)+1)+*d)).color=7;
}
void jugadorL(Tcubo*** cont, int *i, int *d)//jugador.existe=2
{
     (*(*(*(cont+*i)+1)+*d)).existe=2;
     (*(*(*(cont+*i)+1)+*d)).color=7;
     (*(*(*(cont+*i)+1)+*d+1)).existe=2;
     (*(*(*(cont+*i)+1)+*d+1)).color=7;
     (*(*(*(cont+*i)+1)+*d+2)).existe=2;
     (*(*(*(cont+*i)+1)+*d+2)).color=7;
     (*(*(*(cont+*i+1)+1)+*d+2)).existe=2;
     (*(*(*(cont+*i+1)+1)+*d+2)).color=7;
}
void jugadorT(Tcubo*** cont, int *i, int *d)//jugador.existe=2
{
     (*(*(*(cont+*i)+1)+*d)).existe=2;
     (*(*(*(cont+*i)+1)+*d)).color=7;
     (*(*(*(cont+*i)+1)+*d+1)).existe=2;
     (*(*(*(cont+*i)+1)+*d+1)).color=7;
     (*(*(*(cont+*i)+1)+*d+2)).existe=2;
     (*(*(*(cont+*i)+1)+*d+2)).color=7;
     (*(*(*(cont+*i-1)+1)+*d+1)).existe=2;
     (*(*(*(cont+*i-1)+1)+*d+1)).color=7;
}
