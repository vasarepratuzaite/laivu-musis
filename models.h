#ifndef MY_HEADER_H
#define MY_HEADER_H

typedef struct Koordinate_user
{
    char *a;
    int *b;
} Koordinate_user;

typedef struct Koordinate_User_Skaiciais
{
    int a;
    int b;
} Koordinate_User_Skaiciais;

typedef struct Koordinate_laivu
{
    char ix;
    int iy;
} Koordinate_laivu;

typedef struct Data
{
    int x;
    int y;
    int laivai;
    struct Koordinate_user koord ; //userio ivedimai
    struct Koordinate_laivu ix, iy; //laivu koordinates

} Data;

#endif
