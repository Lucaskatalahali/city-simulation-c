#ifndef SEHIR_H
#define SEHIR_H

#include "Yerlesim.h"
#include "Ilce.h"

struct SEHIR{
    Yerlesim super;
    Ilce* ilce_listesi;
    int ilce_sayisi;
    void (*detayli_yazdir)(struct SEHIR*);
    void (*decrease_ilce_sayisi)(struct SEHIR*);
    void (*add_ilceler)(struct SEHIR*, Ilce*, int);
    int (*getIlceSayisi)(struct SEHIR*);
    void (*Delete)(struct SEHIR*);
};
typedef struct SEHIR* Sehir;

Sehir new_sehir(char*);
void detayli_yazdir(const Sehir);
void setNufus_sehir(const Sehir);
void decrease_ilce_sayisi(const Sehir);
void add_ilceler(const Sehir, Ilce*, int);
char* toString_sehir(const Sehir);
int getIlceSayisi(const Sehir);
void delete_sehir(const Sehir);

#endif