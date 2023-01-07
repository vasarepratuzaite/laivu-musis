#include <stdio.h>
#include <stdbool.h>
#include "models.h"

void logData (char *filename, char *log);
Data *readData (char *filename);
bool writeData (char *filename, Data *data);
