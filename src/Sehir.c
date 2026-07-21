/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 08/05/2026
*
* Bu sinif, bir sehri temsil eder. Sehir, ilcelerden olusan bir yapidir ve toplam nufus
* ilcelerin nufusuna gore hesaplanir. Ilce ve mahalle yapilarini yonetir ve hiyerarsik yapinin
* en ust seviyesini temsil eder.
*
*/

#include "Sehir.h"
#include <stdio.h>
#include <stdlib.h>

Sehir new_sehir(char* adi){
    Sehir this;
    this = (Sehir)malloc(sizeof(struct SEHIR));
    this->super = new_yerlesim(adi);
    this->ilce_listesi = NULL;
    this->ilce_sayisi = 0;
    this->detayli_yazdir = &detayli_yazdir;
    this->add_ilceler = &add_ilceler;
    this->super->toString = &toString_sehir;
    this->super->setNufus = &setNufus_sehir;
    this->decrease_ilce_sayisi = &decrease_ilce_sayisi;
    this->getIlceSayisi = &getIlceSayisi;
    this->Delete = &delete_sehir;

    return this;
}

void detayli_yazdir(const Sehir this){
    printf("Sehir: %s - Nufus: %d\n", this->super->adi, this->super->nufus); // Sehir içinde olduğumuz için getAdi metodunu çağırmaya gerek yoktur

    for(int i = 0; i < this->ilce_sayisi; i++){
        Ilce ilce = this->ilce_listesi[i];
        // Burada ve aşağıda metodları çağırmamız gerekir çünkü İlçe ve Mahalle dışında bulunuyoruz
        printf("Ilce: %s - Nufus: %d\n", ilce->super->getAdi(ilce->super), ilce->super->getNufus(ilce->super));

        for(int j = 0; j < ilce->mahalle_sayisi; j++){
            Mahalle mahalle = ilce->mahalle_listesi[j];
            printf("Mahalle: %s - Nufus: %d\n", mahalle->super->getAdi(mahalle->super), mahalle->super->getNufus(mahalle->super));
            printf("Kisiler:\n");

            for(int k = 0; k < mahalle->kisi_sayisi; k++){
                Kisi kisi = mahalle->kisi_listesi[k];
                char* KisiStr = kisi->toString(kisi);
                printf("\t%s\n", KisiStr);
                free(KisiStr); // toString tarafından allocate edilen stringi serbest bırakır
            }
        }
    }
}
void setNufus_sehir(const Sehir this){
    this->super->nufus = this->ilce_sayisi * this->ilce_listesi[0]->super->nufus;
}

void add_ilceler(const Sehir this, Ilce* yeni_ilceler, int miktar){
    if(miktar <= 0) return;

    // İşaretçi dizisini yeni toplam boyuta göre yeniden boyutlandırır
    // (Mevcut boyut + yeni ilçe sayısı)
    this->ilce_listesi = (Ilce*)realloc(this->ilce_listesi, (this->ilce_sayisi + miktar) * sizeof(Ilce));

    // Yeni İLÇE pointer'larını dizinin sonuna kopyalar
    for(int i = 0; i < miktar; i++){
        this->ilce_listesi[this->ilce_sayisi + i] = yeni_ilceler[i];
    }
    this->ilce_sayisi += miktar;
}

char* toString_sehir(const Sehir this){
    int size = snprintf(NULL, 0,
        "Sehir: %s - Nufus: %d",
        this->super->adi, this->super->nufus); // Bu sınıfın içindeyiz (Şehir). Bu yüzden metotlari çağırmaya gerek yok.

    char* str = (char*)malloc(size + 1);
    sprintf(str, "Sehir: %s - Nufus: %d", this->super->adi, this->super->nufus);
    
    return str;
}

int getIlceSayisi(const Sehir this){
    return this->ilce_sayisi;
}

void decrease_ilce_sayisi(const Sehir this){
    this->ilce_sayisi -= 1;
}

void delete_sehir(const Sehir this){

    for(int i = 0; i < this->ilce_sayisi; i++){
        this->ilce_listesi[i]->Delete(this->ilce_listesi[i]);
    }

    free(this->ilce_listesi);

    this->super->Delete(this->super);

    free(this);
}