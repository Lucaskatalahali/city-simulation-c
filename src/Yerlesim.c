/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 08/05/2026
*
* Bu sinif, tum yerlesim birimleri icin temel siniftir.
* Yerlesim adi, nufus bilgisi ve ortak metodlari icerir.
*
*/

#include "Yerlesim.h"
#include <stdio.h>
#include <stdlib.h>

Yerlesim new_yerlesim(char* adi){
    Yerlesim this;
    this = (Yerlesim)malloc(sizeof(struct YERLESIM));
    this->adi = adi;
    this->nufus = 0;
    this->getAdi = &getAdi;
    this->getNufus = &getNufus;
    this->Delete = &delete_yerlesim;

    return this;
}

char* getAdi(const Yerlesim this){
    return this->adi;
}

int getNufus(const Yerlesim this){
    return this->nufus;
}

void delete_yerlesim(const Yerlesim this){
    free(this);
}