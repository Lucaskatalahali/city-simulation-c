#ifndef YERLESIM_H
#define YERLESIM_H

struct YERLESIM{
    char* adi;
    int nufus;
    char*(*toString)(); //// Her alt yapı (türetilmiş yapı) bu pointer'ı kendi şekilde implemente edecektir
    char* (*getAdi)(struct YERLESIM*);
    int (*getNufus)(struct YERLESIM*);
    void (*setNufus)(); //// Her alt yapı (türetilmiş yapı) bu pointer'ı kendi şekilde implemente edecektir
    void (*Delete)(struct YERLESIM*);
};
typedef struct YERLESIM* Yerlesim;

Yerlesim new_yerlesim(char*);
char* getAdi(const Yerlesim);
int getNufus(const Yerlesim);
void delete_yerlesim(const Yerlesim);

#endif