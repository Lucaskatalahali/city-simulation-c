/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 08/05/2026
*
* Bu sinif, bir ilceyi temsil eder.
* Ilce, mahallelerden olusur ve toplam nufus icindeki mahallelerin nufusuna gore hesaplanir.
* Mahallelerin eklenmesi, silinmesi ve ilce nufusunun guncellenmesi burada yapilir.
*
*/

#include "Ilce.h"
#include <stdio.h>
#include <stdlib.h>

Ilce new_ilce(char* adi){
    Ilce this;
    this = (Ilce)malloc(sizeof(struct ILCE));
    this->super = new_yerlesim(adi);
    this->mahalle_listesi = NULL;
    this->mahalle_sayisi = 0;
    this->add_mahalleler = &add_mahalleler;
    this->super->toString = &toString_ilce;
    this->super->setNufus = &setNufus_ilce;
    this->getMahalleSayisi = &getMahalleSayisi;
    this->decrease_mahalle_sayisi = &decrease_mahalle_sayisi;
    this->Delete = &delete_ilce;

    return this;
}
void setNufus_ilce(const Ilce this){
    //İlçenin toplam nüfusunu, mahalle sayısı ve ilk mahallenin nüfusu üzerinden hesaplayarak günceller
    //Bu yöntem, tüm mahallelerin aynı nüfusa sahip olduğu için geçerlidir
    this->super->nufus = this->mahalle_sayisi * this->mahalle_listesi[0]->super->nufus;
}

char* toString_ilce(const Ilce this){
    int size = snprintf(NULL, 0,
        "Ilce: %s - Nufus: %d",
        this->super->adi, this->super->nufus);
        
    char* str = (char*)malloc(size + 1);
    sprintf(str, "Ilce: %s - Nufus: %d", this->super->adi, this->super->nufus); // İlçe içinde olduğumuz için getAdi metodunu çağırmaya gerek yoktur
    
    return str;        
}
void add_mahalleler(const Ilce this, Mahalle* yeni_mahalleler, int miktar){
    if(miktar <= 0) return;

    // İşaretçi dizisini yeni toplam boyuta göre yeniden boyutlandırır
    // (Mevcut boyut + yeni mahalle sayısı)
    this->mahalle_listesi = (Mahalle*)realloc(this->mahalle_listesi, (this->mahalle_sayisi + miktar) * sizeof(Mahalle));

    // Yeni MAHALLE pointer'larını dizinin sonuna kopyalar
    for(int i = 0; i < miktar; i++){
        this->mahalle_listesi[this->mahalle_sayisi + i] = yeni_mahalleler[i];
    }
    this->mahalle_sayisi += miktar;
}

int getMahalleSayisi(const Ilce this){
    return this->mahalle_sayisi;
}

void decrease_mahalle_sayisi(const Ilce this){
    this->mahalle_sayisi -= 1;
}

void delete_ilce(const Ilce this){

    for(int i = 0; i < this->mahalle_sayisi; i++){
        this->mahalle_listesi[i]->Delete(this->mahalle_listesi[i]);
    }

    free(this->mahalle_listesi);

    this->super->Delete(this->super);

    free(this);
}