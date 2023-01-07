#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "models.h"

Koordinate_User_Skaiciais ivedimas(char *koordinates)
{
    if (strcmp(koordinates, "stop") == 0) {
        Koordinate_User_Skaiciais ivestis = {.a = -1, .b = -1};

        return ivestis;
    }

    int b = 0;
    int a = koordinates[0]-97;

    for(int i = 1; i < strlen(koordinates); ++i)
        b += koordinates[i] - 0x30;

    Koordinate_User_Skaiciais ivestis = {.a = a, .b = b};

    return ivestis;
}

void duomenuIvedimas(Data *data) {
    printf("================================================\n");
    printf("================================================\n");
    printf("= Lenteles ilgis:   ");
    scanf("%3d", &data->x);
    printf("= Lenteles aukstis: ");
    scanf("%3d", &data->y);
    printf("= Laivu skaicius:   ");
    scanf("%3d", &data->laivai);
    printf("================================================\n");
}