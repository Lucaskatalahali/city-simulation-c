#ifndef MAHALLE_H
#define MAHALLE_H

#include "Yerlesim.h"
#include "Kisi.h"

struct MAHALLE{
    Yerlesim super;
    Kisi* kisi_listesi;
    int kisi_sayisi;
    int (*getKisiSayisi)(struct MAHALLE*);
    void (*add_kisiler)(struct MAHALLE*, Kisi*, int);
    void (*decrease_kisi_sayisi)(struct MAHALLE*);
    void (*Delete)(struct MAHALLE*);
};
typedef struct MAHALLE* Mahalle;
Mahalle new_mahalle(char*);
void setNufus_mahalle(const Mahalle);
char* toString_mahalle(const Mahalle);
int getKisiSayisi(const Mahalle);
void add_kisiler(const Mahalle, Kisi*, int); //hangi Mahalle, yeniKisiler listesi, kaç yeni kisi var
void decrease_kisi_sayisi(const Mahalle);
void delete_mahalle(const Mahalle);

#endif