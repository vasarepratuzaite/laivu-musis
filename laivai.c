#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

#include "models.h"

int isrikiuotiLaivus(Data *data, int **skaiciuLentele) {
    int isrikiuotiLaivai=0;
    srand(time(0));
    while(data->laivai > isrikiuotiLaivai)
    {
        int iy = rand()%data->y;
        int ix = rand()%data->x;
        int skaicius = rand()%2;
        if((skaicius == 1) && (*(*(skaiciuLentele+iy)+ix) == 0) && (data->laivai > isrikiuotiLaivai)) {
            *(*(skaiciuLentele+iy)+ix)=1; 
            isrikiuotiLaivai++;
        }
    }

    return isrikiuotiLaivai;
}