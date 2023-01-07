#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

#include "models.h"

int **sukurtiSkaiciuLentele(Data *data) {
    int **skaiciuLentele = (int **)malloc(sizeof(int *)*data->y);
    
    for(int i = 0; i < data->y; ++i){
        *(skaiciuLentele+i) = (int *)malloc(sizeof(int)*data->x);
    }

    //uzpildom skaiciu lentele
    for(int iy = 0; iy < data->y; ++iy){ 
        for(int ix=0; ix<data->x; ++ix){ 
            *(*(skaiciuLentele+iy)+ix)=0; 
        }
    }

    return skaiciuLentele;
}

char **sukurtiSimboliuLentele(Data *data) {
    char **simboliuLentele = (char **)malloc(sizeof(char *)*data->y);

    for(int i = 0;i < data->y;i++){
        *(simboliuLentele+i) = (char *)malloc(sizeof(char)*data->x);
    }
    
    //uzpildom zenklu lentele
    for(int iy=0; iy<data->y; ++iy){ 
        for(int ix=0;ix<data->x;++ix){ 
            *(*(simboliuLentele+iy)+ix)='+';
        }
    }

    return simboliuLentele;
}
