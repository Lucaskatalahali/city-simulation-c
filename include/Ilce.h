#ifndef ILCE_H
#define ILCE_H

#include "Yerlesim.h"
#include "Mahalle.h"

struct ILCE{
    Yerlesim super;
    Mahalle* mahalle_listesi;
    int mahalle_sayisi;
    void (*add_mahalleler)(struct ILCE*, Mahalle*, int);
    int (*getMahalleSayisi)(struct ILCE*);
    void (*decrease_mahalle_sayisi)(struct ILCE*);
    void (*Delete)(struct ILCE*);
};
typedef struct ILCE* Ilce;
Ilce new_ilce(char*);
void setNufus_ilce(const Ilce);
char* toString_ilce(const Ilce);
void add_mahalleler(const Ilce, Mahalle*, int);
int getMahalleSayisi(const Ilce);
void decrease_mahalle_sayisi(const Ilce);
void delete_ilce(const Ilce);

#endif