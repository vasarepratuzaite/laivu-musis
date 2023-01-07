#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

#include "duom.h"
#include "laivai.h"
#include "lentele.h"
#include "vartotojas.h"
#include "models.h"

#define ZINUTE_PATAIKEI "Pataikete!\n"
#define ZINUTE_NEPATAIKEI "Nepataikete!\n"
#define ZINUTE_JAUSOVEI "Jau sovete!\n"
#define ZINUTE_BLOGAKOORDINATE "Blogai ivestos koordinates. Turi buti raide skaicius!\n"

clock_t begin, end;

void atlaisvinimas(int **m1, char **m2, int a)
{
    for(int i=0; i<a; ++i)
    {
        free(*(m1+i));
    }

    free(m1);

    for(int i=0; i<a; ++i)
    {
        free(*(m2+i));
    }

    free(m2);
}

void pataikei(int **skaiciuLentele, char **simboliuLentele, Koordinate_User_Skaiciais *koordinate)
{
    printf(ZINUTE_PATAIKEI);
    *(*(skaiciuLentele+koordinate->b)+koordinate->a)=2;
    *(*(simboliuLentele+koordinate->b)+koordinate->a)='#';
}

void nepataikei(int **skaiciuLentele, char **simboliuLentele, Koordinate_User_Skaiciais *koordinate)
{
    printf(ZINUTE_NEPATAIKEI); 
    *(*(skaiciuLentele+koordinate->b)+koordinate->a) = 2;
    *(*(simboliuLentele+koordinate->b)+koordinate->a) = '~';
}

void programosPabaiga() {
    end = time(NULL);

    char str[128];
    snprintf(str, sizeof str, "Zaidimas truko %lu s.\n", (end - begin));

    logData("laivu_musis.log", str);
}

int main()
{    
    begin = time(NULL);
    atexit(programosPabaiga);

    char *logFile = "laivu_musis.log";
    char *dataFile = "data.bin";

    int **skaiciuLentele;
    char **simboliuLentele;

    Data *data = readData(dataFile);
    if (data == NULL) {
        logData(logFile, "duomenu baze tuscia. Zaidimas prasides is naujo.\n");

        struct Data temp = { .x = 0, .y = 0, .laivai = 0};  
        data = &temp;
    } else {
       logData(logFile, "duomenu baze nera tuscia. Zaidimas tesis nuo paskutinio veiksmo.\n");
    }

    //patikrinam tik viena kintamaji ar 0 nes jei bent vienas yra 0 tai ir kiti bus 0
    if (data->x == 0) { 
        duomenuIvedimas(data);
    }

    int pataikyta = 0, bandymai = 0;

    if( (data->laivai <= data->x * data->y) && (data->laivai > 0) && (data->x > 1) && (data->y > 1) )
    {
        skaiciuLentele = sukurtiSkaiciuLentele(data);
        simboliuLentele = sukurtiSimboliuLentele(data);
        int isrikiuotiLaivai = isrikiuotiLaivus(data, skaiciuLentele);        

        while(pataikyta < isrikiuotiLaivai)
        {
            printf("================================================\n");
            printf("=   Supaprastintas Laivu musis ver 1.0         =\n");
            printf("================================================\n");
            printf("= Lenteles dydis: %3dx%3d  Laivu skaicius: %3d =\n",data->x,data->y,data->laivai);
            printf("================================================\n");

            printf("\n   ");
            int sk=0;
            for(int i=0;i<data->x;i++){
                int raide=97+i; 
                printf("%c ",raide);
            } 
            
            printf("\n");
            for(int iy=0; iy<data->y; ++iy)
            {
                for(int ix=0; ix<data->x; ++ix)
                {
                    if (ix==0) { 
                        printf("%2d ",sk); sk=sk+1;
                    }

                    printf("%c ",*(*(simboliuLentele+iy)+ix));
                }
                printf("\n");
            }
            printf(" \n (#) - Pataikyta\n (+) - Nesauta\n (~) - Sauta bet nepataikyta\n\n");
            printf("================================================\n");
            printf("= Bandymu: %4d Liko laivu:%3d                   \n",bandymai,data->laivai-pataikyta);
            printf("================================================\n");

            char k[10];
            printf("Iveskite koordinate(raide_skaicius):\n");
            scanf("%s",k);

            Koordinate_User_Skaiciais koordinates = ivedimas(k);

            if (koordinates.a == -1 && koordinates.b == -1) {
                logData(logFile, "Duomenys issaugoti. Kita kart paleidus zaidimas tesis.\n");
                writeData(dataFile, data);
                return 0;
            }

            if((koordinates.a < data->x) && (koordinates.b < data->y))
            {
                bandymai++; 

                if(*(*(skaiciuLentele + koordinates.b) + koordinates.a) == 2) {
                    printf(ZINUTE_JAUSOVEI);
                }
                if(*(*(skaiciuLentele + koordinates.b) + koordinates.a) == 1)  {
                    pataikei(skaiciuLentele, simboliuLentele, &koordinates);
                    pataikyta++;
                }
                if(*(*(skaiciuLentele + koordinates.b) + koordinates.a) == 0){
                    nepataikei(skaiciuLentele, simboliuLentele, &koordinates);
                }
            }
            else
            {
                printf(ZINUTE_BLOGAKOORDINATE);
            }
        }
    }
    else
    {
        if((data->laivai>data->x*data->y)|| (data->laivai==0))
            logData(logFile, "Atsiprasome bet ivestas laivu skaicius didesnis nei yra langeliu !\n");
        if(data->x * data->y > 15*15)
            logData(logFile, "Aukstis arba plotis didesni nei leidziama!\n");
    }

    if((pataikyta==data->laivai) && (data->laivai > 0)) {
        char str[128];
        snprintf(str, sizeof str, "Laimejote. Viso atlikote bandymu: %d ir numusete laivu: %d\n", bandymai,data->laivai);

        logData(logFile, str);
        atlaisvinimas(skaiciuLentele,simboliuLentele,data->y);
    }
    
    return 0;
}