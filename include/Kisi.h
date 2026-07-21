#ifndef KISI_H
#define KISI_H

struct KISI{
    char* isim;
    int id;
    int yas;
    void (*yaslan)(struct KISI*);
    char* (*toString)(struct KISI*);
    void (*Delete)(struct KISI*);
};
typedef struct KISI* Kisi;

Kisi new_kisi(char*, int);

void yaslan(const Kisi);
char* toString(const Kisi);
void delete_kisi(const Kisi);

#endif
