/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 08/05/2026
*
* Bu sinif, bir mahalleyi temsil eder.
* Mahalle, icinde bulunan kisilerden olusan bir yapidir.
* Kisi sayisi mahalle nufusunu belirler ve dinamik olarak guncellenir.
* Kisilerin eklenmesi, azaltilmasi ve bellek yonetimi burada yapilir.
*
*/

#include "Mahalle.h"
#include <stdio.h>
#include <stdlib.h>

Mahalle new_mahalle(char* adi){
    Mahalle this;
    this = (Mahalle)malloc(sizeof(struct MAHALLE));
    this->super = new_yerlesim(adi);
    this->kisi_listesi = NULL;
    this->kisi_sayisi = 0;
    this->super->toString = &toString_mahalle;
    this->add_kisiler = &add_kisiler;
    this->getKisiSayisi = &getKisiSayisi;
    this->super->setNufus = &setNufus_mahalle;
    this->decrease_kisi_sayisi = &decrease_kisi_sayisi;
    this->Delete = &delete_mahalle;

    return this;
}

void setNufus_mahalle(const Mahalle this){
    this->super->nufus = this->kisi_sayisi;
}

char* toString_mahalle(const Mahalle this){
    int size = snprintf(NULL, 0,
        "Mahalle: %s - Nufus: %d",
        this->super->adi, this->super->nufus); // Mahalle içinde olduğumuz için getAdi metodunu çağırmaya gerek yoktur
    char* str = (char*)malloc(size + 1); 
    sprintf(str, "Mahalle: %s - Nufus: %d", this->super->adi, this->super->nufus);
    
    return str;        
}

void add_kisiler(const Mahalle this, Kisi* yeni_kisiler, int miktar){
    if(miktar <= 0) return;

    // İşaretçi dizisini yeni toplam boyuta göre yeniden boyutlandırır
    // (Mevcut boyut + yeni eklenen kişi sayısı)
    this->kisi_listesi = (Kisi*)realloc(this->kisi_listesi, (this->kisi_sayisi + miktar) * sizeof(Kisi));

    // Yeni kişilerin pointer'larını dizinin sonuna kopyalar
    for(int i = 0; i < miktar; i++){
        this->kisi_listesi[this->kisi_sayisi + i] = yeni_kisiler[i];
    }
    this->kisi_sayisi += miktar; // Dahili sayaç değerini günceller
}

int getKisiSayisi(const Mahalle this){
    return this->kisi_sayisi;
}

void decrease_kisi_sayisi(const Mahalle this){
    this->kisi_sayisi -= 1;
}

void delete_mahalle(const Mahalle this){

    for(int i = 0; i < this->kisi_sayisi; i++){
        this->kisi_listesi[i]->Delete(this->kisi_listesi[i]);
    }

    free(this->kisi_listesi);

    this->super->Delete(this->super);

    free(this);
}