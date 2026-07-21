#ifndef OYUN_H
#define OYUN_H

#include "Sehir.h"

struct OYUN{
    Sehir* sehir_listesi;
    int sehir_sayisi;
    char** kisilerin_isimleri;
    char** sehirlerin_adimlari;
    char** ilcelerin_adimlari;
    char** mahallelerin_adimlari;
    void (*add_sehir)(struct OYUN*, Sehir);
    void (*tur_baslat)(struct OYUN*);
    void (*sehir_nufusu_kontrol)(struct OYUN*);
    void (*yeni_sehir_olustur)(struct OYUN*, Sehir);
    void (*ozel_yeni_sehir_olustur)(struct OYUN*, Sehir);
    void (*son_ozel_yeni_sehir_olustur)(struct OYUN*, Sehir);
    void (*sehirler_gostermek)(struct OYUN*);
    void (*koordinatla_sehir_goster)(struct OYUN*, int, int); //int satir, int sutun
    void (*Delete)(struct OYUN*);
};
typedef struct OYUN* Oyun;

Oyun new_Oyun(int*, int);//int* sehir_sayilari / int diziBoyutu
void add_sehir(const Oyun, const Sehir);
void tur_baslat(const Oyun);
void sehir_nufusu_kontrol(const Oyun); //nufus >== 1000 şehirleri tespit eder ve bölme işlemini tetikler
void yeni_sehir_olustur(const Oyun, const Sehir );
void ozel_yeni_sehir_olustur(const Oyun, const Sehir); //Tek bir ilçesi olan şehrin bölünmesinden sorumlu fonksiyon İlçeleri değil, mahalleleri bölüyoruz
void son_ozel_yeni_sehir_olustur(const Oyun, const Sehir); //Bu fonksiyon, nüfusu doğrudan ikiye böler ve bir kısmını yeni şehre aktarır
void sehirler_gostermek(const Oyun); //Şehirleri görüntüleme metodu. Her satırda 5 şehir gösterilir.
void koordinatla_sehir_goster(const Oyun, int, int);//Sehir sınıfındaki detayliYazdir metodunu çağırarak şehir detaylarını yazdırıyorum. 
void delete_oyun(const Oyun);
#endif
