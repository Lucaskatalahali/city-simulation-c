/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 08/05/2026
* <p>
* Bu sınıf, sistemdeki kişileri temsil eder.
* Her kişi için ID, isim ve yaş bilgisi tutulur.
* </p>
*/

#include "Kisi.h"
#include <stdio.h>
#include <stdlib.h>

//Benzersiz ID ataması için kullanılan statik sayaç. ID 1'den başlıyor
static int id_counter = 1; 

Kisi new_kisi(char* isim, int yas){
    Kisi this;
    this = (Kisi)malloc(sizeof(struct KISI));
    this->isim = isim;
    this->yas = yas;
    this->id = id_counter++; //ID ataması yapıldıktan sonra sayaç bir artırılır
    this->yaslan = &yaslan;
    this->toString = &toString;
    this->Delete = &delete_kisi;

    return this;
}

void yaslan(const Kisi this){
    this->yas += 1;
}
char* toString(const Kisi this){
     int size = snprintf(NULL, 0,
        "%d - %s - %d",
        this->id, this->isim, this->yas);

    char* str = (char*)malloc(size + 1);

    sprintf(str, "%d - %s - %d",
            this->id, this->isim, this->yas);
    return str;
}

void delete_kisi(const Kisi this){
    free(this);
};