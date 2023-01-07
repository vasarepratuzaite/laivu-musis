#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "duom.h"
#include "vartotojas.h"

char *test_data_filename = "test_data.bin";
char *test_log_filename = "test_log.log";

bool PatikrintiArIrasoIFailaTeisingai() {
    Data data = {.x = 1, .y = 2, .laivai = 3};

    // irasom i faila duomenis
    writeData(test_data_filename, &data);

    // nuskaitom duomenu faila i kuri katik iraseme duomenis
    Data *dataFromFile = readData(test_data_filename);

    // grazinam bool reiksme ar nuskaityti duomenys sutampa su irasytais duomenimis
    return data.x == dataFromFile->x && 
            data.y == dataFromFile->y && 
            data.laivai == dataFromFile->laivai;
}

bool PatikrintiArLogFailasPildosi() {
    logData(test_log_filename, "log1\n");
    logData(test_log_filename, "log2\n");
    logData(test_log_filename, "log3\n");
    logData(test_log_filename, "log4\n");
    logData(test_log_filename, "log5\n");

    int count = 0;
    FILE *fp = fopen(test_log_filename, "r");

    if (fp == NULL) {
        return false;
    }

    // suskaiciuojam kiek faile eiluciu
    while(!feof(fp))
        if(fgetc(fp) == '\n')
            count++;
 
    fclose(fp);

    return count == 5;
}

Koordinate_User_Skaiciais PatikrintiIvestis(char *k) {
    Koordinate_User_Skaiciais rez = ivedimas(k);

    return rez;
}

int main(int argc, char **argv) {
    printf("Leidziam testus ...\n");

    assert(PatikrintiArIrasoIFailaTeisingai() == true);
    
    assert(PatikrintiArLogFailasPildosi() == true);

    Koordinate_User_Skaiciais rez = PatikrintiIvestis("stop");
    assert(rez.a == -1 && rez.b == -1);
    rez = PatikrintiIvestis("a1");
    assert(rez.a == 0 && rez.b == 1);
    rez = PatikrintiIvestis("d4");
    assert(rez.a == 3 && rez.b == 4);

    printf("Testai baigti.\n");

    return 0;
}
