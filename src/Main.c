/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 08/05/2026
* <p>
* Bu dosya, programın giriş noktasıdır.
* Oyun başlatılır, kullanıcı girdileri alınır ve simülasyon döngüsü çalıştırılır.
* </p>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "Oyun.h"

//Ekranı platformlar arası temizlemek için fonksiyon
void clean_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, ""); // Konsolda Türkçe karakterlerin doğru görüntülenmesi için yerel ayarları yapar

    int turSayisi;
    char userInput[256]; // Kullanıcıdan alınan şehir numaralarını geçici olarak saklamak için giriş tamponu

    //Kullanıcıdan tur sayısının alınması
    printf("Tur sayisini girin: ");
    scanf("%d", &turSayisi);
    getchar(); //buffer'deki '\n' karakterini temizler

    // Şehir numaralarının alınması
    printf("Sehir numaralarini boslukla ayirarak girin (Ornek: 18 25 79 37 62 86 17 50): ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0;

    // String'i tam sayı dizisine dönüştürme
    int numbers[100]; // Array temporário
    int count = 0;
    char* token = strtok(userInput, " ");
    while (token != NULL) {
        numbers[count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    Oyun oyun = new_Oyun(numbers, count);

    for(int i = 0; i < turSayisi; i++) {
        clean_screen(); // Yeni turu göstermeden önce ekranı temizler
        printf("\n\t==== %d. Tur ====\n\n", i + 1);
        
        oyun->tur_baslat(oyun);
        oyun->sehirler_gostermek(oyun);
    }

    clean_screen();
    printf("\n\t ==== Oyun Bitti - Son Durum ====\n\n");
    oyun->sehirler_gostermek(oyun);

    // Koordinatlara göre detayları görüntüleme
    int satir, sutun;
    printf("\nBir sehir hakkindaki bilgileri gormek icin:");
    printf("\nSatir girin (0'dan baslayarak): ");
    scanf("%d", &satir);
    printf("Sutun girin (0'dan baslayarak): ");
    scanf("%d", &sutun);

    clean_screen();
    oyun->koordinatla_sehir_goster(oyun, satir, sutun);
    printf("\nOyunu kapatmak icin Enter tusuna basin...");
    
    getchar(); 
    getchar(); // Kullanıcının son Enter tuşuna basmasını bekler

    oyun->Delete(oyun);// Tüm belleği serbest bırakır

    return 0;
}