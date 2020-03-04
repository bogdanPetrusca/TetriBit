//PETRUSCA BOGDAN-MIHAI
//SERIA: 313CB
#include <stdio.h>
#include <math.h>
unsigned long long is_set(unsigned long long number,int i)
{
    unsigned long long mask=1;
    mask<<=i;
    return  (number&mask)!=0;
}
void print_bits (unsigned long long number)
{
    int i;
    for(i=63;i>=0;i--)
    {
        if(is_set(number,i))
            printf("#");
        else
            printf(".");
        if(i%8==0)
            printf("\n");
    }
}
int miscStanga(unsigned long long piesa, unsigned long long n,int mutare)
{
    mutare=-mutare;
    int bitStanga,nr=0,verif=0;
    int val=0;
    while(1)
    {
        for(bitStanga=7; bitStanga<=63; bitStanga=bitStanga+8)
        {
            if(is_set(piesa, bitStanga)==1 || ((piesa & n) != 0) )
            {
                verif=1;
                if((piesa&n) != 0)
                    val--;
                break;
            }
        }

            if(verif==0)
                nr++;
            else
                break;

        piesa<<=1;
    }
    if(mutare<(nr+val))
        return mutare;
    else
        return nr+val;
}

int miscDreapta(unsigned long long piesa, unsigned long long n,int mutare)
{
    int bitDreapta,nr=0,verif=0;
        int val=0;
    while(1)
    {
        for(bitDreapta=0;bitDreapta<=56;bitDreapta=bitDreapta+8)
        {
            if(is_set(piesa,bitDreapta)==1 || ((piesa&n) != 0) )
            {
                verif=1;
                if((piesa&n) != 0)
                    val=-1;
                break;
            }
        }
            if(verif==0)
                nr++;
            else
                break;
        piesa>>=1;
    }
    if(mutare<(nr+val))
        return mutare;
    else
        return nr+val;
}

unsigned long long rmvLine(int *l_elim, unsigned long long n)
{
    int liniePlina=0, val,i,j;
    unsigned long long rez=n;
    for(i=0; i<=7; i++)
    {
        val=1;
        liniePlina=0;
        //for-ul de mai jos gaseste ce linie este plina de 1
        for(j=8*i; j<8*(i+1); j++)
        {
            if(is_set(n,j))
                 continue;
            else
                val=0;//val e 0 cand linie are cel putin un .
        }
        if(val == 1)
        {
            //pe variabila liniePlina o maresc cu unu iar in if-ul de mai jos
            //o scad cu unu pentru a intra in respectivul if daca linia ce
            //trebuie eliminata este prima adica daca i=0
            liniePlina=i+1;
            *l_elim = (*l_elim) + 1;
             i--;
        }
            //printf("%s", "ma printez");
        if(liniePlina!=0)
        {
            int k;
            //am explicat mai sus de ce scad cu unu
            liniePlina--;
            ;
            unsigned long long u=255,v=0, v2=0;
            //in variabila v umplu cu 1 liniile de sub linia
            //ce trebue eliminata
            for(k=0; k<liniePlina; k++)
                v = v | (u<<(k*8));
            //in variabila v2 umplu cu 1 liniile de deasupra
            //liniei ce trebuie eliminate
            for(k=liniePlina+1; k<=7; k++)
                v2= v2 | (u<<(k*8));
            //creez variabila t astfel incat sa se salveze harta
            //de sub linia ce trebuie eliminata, iar deasupra liniei
            //sa fie 0
            unsigned long long t=(n&v);
            //creez variabila t2 astfel incat sa se salvezeze harta
            //de deasupra liniei ce trebuie eliminate, iar sub linie sa fie 0
            //shiftez cu 8 t2 pentru a se elimnata linia pe care
            //o vrem eliminata
            unsigned long long t2=(n&v2);
            t2=t2>>8;
            //combin ambele variabile si returnez harta fara linia respectiva
            n=t|t2;
            rez = n;
        }
    }
    return rez;
}
float score(unsigned long long n,int linii_eliminate)
{
    float score=0;
    int i,x=0;
    //in variabila x se numara cate 0-uri sunt
    for(i=63;i>=0;i--)
        if(is_set(n,i)==0)
            x++;
    score=sqrt(x)+pow(1.25,linii_eliminate);
    return score;
}
int main()
{
    unsigned long long n,piesa,limit=128;
    limit<<=56;
    int i,nrPiesa=0,linii_eliminate=0;
    scanf("%llu",&n);
    scanf("%d",&nrPiesa);
    int verif=0;
    for(i=1;i<=nrPiesa;i++)
    {
        //acest verif ia valoarea 1 daca se citesc piese
        verif=1;
        int cnt=0;
        unsigned long long aux;
        int j,ok=0;
        scanf("%llu",&piesa);
        //instructiunea de mai jos verifica daca piesa mai are loc pe harta.
        if(((piesa<<56)&n)!=0)
            {
                print_bits(n);
                printf("\n");
                printf("GAME OVER!\n");
                printf("Score:%.2f\n", score(n,linii_eliminate));
                return 0;
            }
        //instructiunea de mai jos afiseaza harta prima data, inainte de 
        //inserarea pieselor in ea
        if(i==1)
        {
            print_bits(n);
            printf("\n");
        }
        //instructiunea de mai jos face prima mutare pentru o piesa de 2 linii
        if(piesa>255)
        {
            aux=piesa;
            int mutare;
            scanf("%d", &mutare);
            cnt++;
            printf("\n");
            if(mutare<0)
            {
                print_bits(n|((piesa<<56)<<miscStanga((piesa<<56),n,mutare)));
                piesa<<=miscStanga((piesa<<56),n,mutare);
            }
            else
            {
                print_bits(n|((piesa<<56)>>miscDreapta((piesa<<56),n,mutare)));
                piesa>>=miscDreapta((piesa<<56),n,mutare);
            }

            printf("\n");
            piesa<<=48;
        }
        else
        {
            aux=piesa;
            piesa<<=56;
        }
        for(j=0;j<=7;j++)
        {
            int mutare;
            scanf("%d",&mutare);
            cnt++;
            //instructiunile de mai jos fac mutarile pe orizontala
            if((piesa&n)==0)
            {
                if(mutare<0)
                {
                    print_bits(n|(piesa<<miscStanga(piesa,n,mutare)));
                    piesa<<=miscStanga(piesa,n,mutare);
                }
                else
                {
                    print_bits(n|(piesa>>miscDreapta(piesa,n,mutare)));
                    piesa>>=miscDreapta(piesa,n,mutare);
                }
                printf("\n");
                //instructiunea de mai jos opreste piesa de 2 linii 
                //pe ultima linie hartii
                if((aux>255)&&(j==6))
                    break;
                //instructiunea de mai jos verifica in avans daca
                //intre piesa si harta nu este colizune atunci cand
                //ea este coborata mai jos. daca nu exista coliziune,
                //atunci ea este coborata
                if(!(j==7))
                {
                    if(((piesa>>8)&n)==0)
                        piesa>>=8;

                    else
                    {
                        //while-ul de mai jos citeste in gol mutarile care
                        //nu s-au efectuat datorita opririi piesei
                        while(cnt<=7)
                        {
                            scanf("%d",&mutare);
                            cnt++;

                        }
                        break;
                    }
                }
            }
            else
            {
                //se insereaza piesa in harta
                n=n|piesa;
                ok=1;
                break;
            }
        }
        if(!(ok==1))
            n|=piesa;
        int verif = linii_eliminate;
        //salveza in n valoarea returnata de rmvLine
        n = rmvLine(&linii_eliminate, n);
        if(verif!=linii_eliminate) 
            print_bits(n);
    }
    //daca nu se citesc piese verif ramane 0 si se afiseaza harta
    if(verif==0)
        print_bits(n);
    printf("\n");
    printf("GAME OVER!\n");
    printf("Score:%.2f\n", score(n,linii_eliminate));
    return 0;
}