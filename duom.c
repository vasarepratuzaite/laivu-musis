#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

#include "models.h"

void logData (char *filename, char *log)
{
    FILE *fp = fopen(filename, "a+");

    char buff[20];
    struct tm *sTm;
    time_t now = time (0);
    sTm = localtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(fp, "%s %s", buff, log);
    printf("%s", log);

    fclose(fp);
}

Data *readData (char *filename)
{
    int totalInt = 1; //create int
    int *total = &totalInt; //asign int to int pointer

    FILE *file;
    file =fopen (filename, "rb");
    if (file == NULL)
    {
        return NULL;
    }
    //read the total number of data  struct 
    if (fread(total, sizeof(int), 1, file)!=1)
    {
        return NULL;
    }
    Data *data = malloc (sizeof(Data) * *total);//**paima dydi baitais kiek uzima baitu in struct
    if (fread (data, sizeof(Data), *total, file)!= *total)
    {
        free(data);
        return NULL;
    }
    if(fclose(file) == EOF)//close the file
    {
        free(data);
        return NULL;
    }
    return data; 
}

bool writeData (char *filename, Data *data)
{
    int total = 1;

    FILE *file;
    file = fopen (filename, "wb");
    
    if (file == NULL) //return false if there was an error opering the file
    {
        return false;
    }
    if (fwrite (&total, sizeof(int), 1, file) != 1)//write the total number of structs in the array to the file
    {
        return false;// return false if the function fails to write the data successfully
    }
    if (fwrite(data, sizeof(Data), total, file) != total)//write the structs in the array to the file
    {
        return false;
    }
    if (fclose(file) == EOF) //close access to the file, return false if this fails
    {
        return false;
    }
    return true;
}