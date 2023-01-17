#include <stdio.h>
#include <stdlib.h> //atof
#include <time.h>
#include <string.h> //strchr

/* ***************** 4D **************************
Vytvorte program, ktor˝ pre ËÌsla od 1 do 20 vypÌöe ich n-tÈ mocniny.
Umoûnite n zadaù pouûÌvateæovi a na v˝poËet mocniny pouûite funkciu.
******************** 4D ************************** */

double mocnina (int a, int n, int c_men);
double newton_method(int a, int c_men);
int nsd (int num1, int num2);

int main(void)
{
    double i_dbl=1,j_dbl=20;

    /* cislo n-tej mocniny */
    char cislo_n[10], n_zobraz[10], *pos;
    int k, l, dlzka_str = 0, cislo_nINT = 0, cislo_men = 1, nsd_val;
    double cislo_nDBL = 0;
    /* cislo n-tej mocniny */

    printf("Zadaj cislo n-tej mocniny (cele alebo desatinne cislo, moze byt aj zaporne):");
    scanf("%s", &cislo_n);

    for(l = 0; l <= strlen(cislo_n); l++) //Replace - Ak uzivatel zada , namiesto .
    {
        if(cislo_n[l] == ',')
        {
            cislo_n[l] = '.';
        }
    }

    while(cislo_n[k++] != '\0')
    {
        if(cislo_n[k] == '.')    // Ak je bodka
        {
            pos = strchr(cislo_n,'.') ;
            dlzka_str = strlen(pos); //vypocita desatinne miesta ale aj s bodkou
            break;
        }
    }

    printf("N-te mocniny cisiel 1 az 20 su: \n");

    if (dlzka_str > 0)
    {
        //cislo_n je desatinne cislo
        cislo_nDBL = atof(cislo_n);

        int pomocne;

        switch(dlzka_str-1)
        {
        case 1 :
            cislo_nDBL = cislo_nDBL * 100;
            cislo_men = cislo_men * 100;
            memcpy(n_zobraz, cislo_n, 4);  //Zobrazenie v printf n-ta mocnina
            break;
        case 2 :
            cislo_nDBL = cislo_nDBL * 100;
            cislo_men = cislo_men * 100;
            memcpy(n_zobraz, cislo_n, 4);  //Zobrazenie v printf n-ta mocnina
            break;
        case 3 :
            cislo_nDBL = cislo_nDBL * 1000;
            cislo_men = cislo_men * 1000;

            if(nsd (cislo_nDBL, cislo_men)==1)
            {
                cislo_nDBL /=  10;
                cislo_men /= 10;

                memcpy(n_zobraz, cislo_n, 5);  //Zobrazenie v printf n-ta mocnina
            }
            else
            {
                nsd_val = nsd (cislo_nDBL, cislo_men);

                cislo_nDBL = cislo_nDBL / nsd_val;
                cislo_men = cislo_men / nsd_val;

                memcpy(n_zobraz, cislo_n, 5);  //Zobrazenie v printf n-ta mocnina
            }

            break;
        default :
            cislo_nDBL = cislo_nDBL * 100;
            cislo_men = cislo_men * 100;
            memcpy(n_zobraz, cislo_n, 4);  //Zobrazenie v printf n-ta mocnina
        }


        cislo_nINT = cislo_nDBL;

        for(i_dbl; i_dbl<=j_dbl; i_dbl++)
        {
            printf("%.0lf ^ %s = %lf \n", i_dbl, n_zobraz, mocnina(i_dbl,cislo_nINT,cislo_men));//mocnina(2;335;100)
        }
    }
    else
    {
        //cislo_n nie je desatinne cislo
        cislo_nDBL = atof(cislo_n);
        cislo_nINT = cislo_nDBL;

        for(i_dbl; i_dbl<=j_dbl; i_dbl++)
        {
            printf("%.0lf ^ %s = %.25lf \n", i_dbl, cislo_n, mocnina(i_dbl,cislo_nINT,0));
        }
    }

    return 0;
}


/* ******* Funkcia n-te mocniny ******* */
double mocnina (int a, int n, int c_men)//mocnina(2;335;100)
{
    double i=1;
    double vypocet, vypocet_xval;

    vypocet=a;

    if (n>0) //mocnina je kladna
    {
        if (c_men > 0) //mocnina je desatinne cislo
        {
            vypocet_xval = newton_method(a, c_men);
            vypocet=vypocet_xval;
        }

        for(i=1; i<n; i++)
        {
            if (c_men > 0)
            {
                vypocet=vypocet*vypocet_xval;
            }
            else
            {
                vypocet=vypocet*a;
            }
        }

    }
    else if (n<0) //mocnina je zaporna
    {
        if (c_men > 0) //mocnina je desatinne cislo
        {
            vypocet_xval = newton_method(a, c_men);
            vypocet=vypocet_xval;

            n=n*(-1);

            for(i=1; i<n; i++)
            {
                vypocet=vypocet*vypocet_xval;
            }
            vypocet = 1/vypocet;

        }
        else  //mocnina nie je desatinne cislo
        {
            n = n * (-1);
            for(i=1; i<n; i++)
            {
                vypocet=vypocet*a;
            }

            vypocet = 1/vypocet;
        }

    }
    else if (n==0) //mocnina je 0
    {
        vypocet = 1;
    }


    return vypocet;
}

/* ************* Newtonís Method ************************** */
double newton_method(int a, int c_men)
{
    /* ************* Newtonís Method ************************** */
    int rnd,odmocnitel, i=0, iteracie=0;
    long double odmocnenec, x_val, x_val2=0, x_rozdiel, citatel, menovatel;
    /* ************* Newtonís Method ************************** */

    srand(time(NULL));
    rnd = rand() % 10+1;

    x_val = citatel = menovatel = rnd;

    odmocnitel=c_men;
    odmocnenec=a;

    do
    {
        /* ************* Newtonís Method ************************** */
        /* ************* xn+1 = xn - (f(xn)/f'(xn)) *************** */
        /* ************* Priklad: 7 domocnina z 1000 ************** */
        /* ************* x7 = 1000 ******************************** */
        /* ************* f(x) = x7 - 1000  ************************ */
        /* ************* f' = 7x6 ********************************* */
        /* * https://calcworkshop.com/derivatives/newtons-method/ * */

        x_val2 = x_val;

        for(i=1; i<odmocnitel; i++)
        {
            citatel = citatel * x_val;
        }

        for(i=1; i<odmocnitel-1; i++)
        {
            menovatel = menovatel * x_val;
        }

        x_val = x_val -((citatel-odmocnenec)/(odmocnitel*menovatel));

        citatel = x_val;
        menovatel = x_val;

        x_rozdiel = abs(x_val - x_val2);

        iteracie += 1;
    }
    while(x_val != x_val2);

    return x_val;
}

/* ******* Funkcia Najvacsi spolocny delitel ******* */
int nsd (int num1, int num2)
{
    int i, nsd;

    for(i=1; i <= num1 && i <= num2; ++i)
    {
        if(num1%i==0 && num2%i==0)
            nsd = i;
    }

    return nsd;
}
