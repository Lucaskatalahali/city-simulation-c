/**
*
* @author Lucas Isaac Cassoma Katalahali | lucas.katalahali@ogr.sakarya.edu.tr
* @since 05/05/2026
* <p>
* Bu sınıf, şehirlerin oluşturulduğu ve simülasyonun çalıştırıldığı ana oyun yapısını temsil eder.
* Nüfus artışı, şehir bölünmesi ve tur sistemi burada yönetilir.
* </p>
*/

#include "Oyun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Static yardimcı fonksiyonlar, oyun içindeki çeşitli işlemler için kullanılacak ve Oyun yapısının içinde tanımlanacak.

//Kullanıcı nüfus (şehir) rakamlarını girdiğinde, bu fonksiyonda rakamı doğrulayıp düzelteceğim.
static int sehir_sayisi_kontrol(int sayi){
    // Onlar basamağını alarak ilçe kısmını belirler
    int ilce_kismi = sayi/10; 
    //Birler basamağını alarak mahalle kısmını belirler.
    int mahalle_kismi = sayi%10;
    //Mahalle kısmı sıfır olamaz, bu durumda 1 artar
    if(mahalle_kismi == 0) mahalle_kismi++; 
    while(mahalle_kismi%ilce_kismi != 0) { // Mahalle kısmının ilçe kısmına tam bölünene kadar değerini ayarlar
        mahalle_kismi++;
        if(mahalle_kismi > 9)
            mahalle_kismi = 1;
    }
    // Düzenlenmiş ilçe ve mahalle kısımlarını birleştirerek yeni sayıyı döner
    sayi = ilce_kismi*10 + mahalle_kismi;
    return sayi;
}

 //Şehir nufusu mahalleye tam bölünebilirliğini kontrol eder.
static int mahalle_nufus_kontrol(int sayi){
    int mahalle_kismi = sayi%10;
    if(mahalle_kismi == 0) mahalle_kismi++;
    // Sayıyı, mahalle kısmına tam bölünene kadar yukarı yuvarlar.
    while(sayi%mahalle_kismi != 0) {
        sayi++;
    }
    return sayi;
}

//Sayının (şehir nufusu) son iki basamağını kullanarak nüfus artış oranını hesaplar.
static int nufus_artis_orani_bul(int sayi){
    // Son iki basamağın birler ve onlar değerlerini ayırır.
    int birler = (sayi%100)%10;
    int onlar = (sayi%100)/10;
    // Artış oranı bu iki basamağın toplamıdır.
    int artis_orani = birler + onlar;
    return artis_orani;
}

// Dosyayı okuyup string dizisi (char**) olarak döndüren fonksiyon
char** dosya_yukle(const char* dosya_adi, int miktar) {
    FILE* fp = fopen(dosya_adi, "r");
    if (fp == NULL) {
        printf("Dosya acilirken hata olustu:: %s\n", dosya_adi);
        return NULL;
    }

    char** list = (char**)malloc(sizeof(char*) * miktar);
    
    char buffer[256];
    int i = 0;
    
    while (fgets(buffer, sizeof(buffer), fp) && i < miktar) {
        buffer[strcspn(buffer, "\n")] = 0;
        buffer[strcspn(buffer, "\r")] = 0;

        list[i] = strdup(buffer); 
        i++;
    }

    fclose(fp);
    return list;
}

Oyun new_Oyun(int* sehir_sayilar, int dizi_boyutu){
    Oyun this;
    this = (Oyun)malloc(sizeof(struct OYUN));
    this->sehir_listesi = NULL;
    this->sehir_sayisi = 0;

    // Veri tabanlarını yükler
    this->sehirlerin_adimlari = dosya_yukle("sehirler.txt", 10000);
    this->ilcelerin_adimlari = dosya_yukle("ilceler.txt", 10000);
    this->mahallelerin_adimlari = dosya_yukle("mahalleler.txt", 10000);
    this->kisilerin_isimleri = dosya_yukle("kisiler.txt", 10000);

    this->add_sehir = &add_sehir;
    this->tur_baslat = &tur_baslat;
    this->sehir_nufusu_kontrol = &sehir_nufusu_kontrol;
    this->yeni_sehir_olustur = &yeni_sehir_olustur;
    this->ozel_yeni_sehir_olustur = &ozel_yeni_sehir_olustur;
    this->son_ozel_yeni_sehir_olustur = &son_ozel_yeni_sehir_olustur;
    this->sehirler_gostermek = &sehirler_gostermek;
    this->koordinatla_sehir_goster = &koordinatla_sehir_goster;
    this->Delete = &delete_oyun;

    for(int i = 0; i < dizi_boyutu; i++){
       
        //Nüfus rakamını kurallara göre düzeltir ve hiyerarşiyi (ilçe/mahalle) hesaplar
        int sehirin_sayisi = sehir_sayisi_kontrol(sehir_sayilar[i]);
        int ilce_sayisi = sehirin_sayisi/10;


        //Her ilçenin sahip olacağı mahalle sayısı
        int mahalle_sayisi = (sehirin_sayisi%10)/(sehirin_sayisi/10);
        //Nüfusu eşit olarak bölmek için kullanılacak mahalle payını tutar
        int mahalle_kismi = sehirin_sayisi%10;

        sehirin_sayisi = mahalle_nufus_kontrol(sehirin_sayisi);
		//Her mahalledeki nüfus miktarı
		int mahalle_nufus = sehirin_sayisi/mahalle_kismi;

        Sehir sehir = new_sehir(this->sehirlerin_adimlari[rand() % 10000]);
        Ilce* ilceler = (Ilce*)malloc(sizeof(Ilce) * ilce_sayisi); // Şehir başına ilçe sayısı kadar yer açılır

        // Hiyerarşik oluşturma döngüleri.
        for(int i = 0; i < ilce_sayisi; i++) {
            Ilce ilce = new_ilce(this->ilcelerin_adimlari[rand() % 10000]);
            Mahalle* mahalleler = (Mahalle*)malloc(sizeof(Mahalle) * mahalle_sayisi); // İlçe başına mahalle sayısı kadar yer açılır
            
            for(int j = 0; j < mahalle_sayisi; j++) {
                Mahalle mahalle = new_mahalle(this->mahallelerin_adimlari[rand() % 10000]);
                Kisi* kisiler = (Kisi*)malloc(sizeof(Kisi) * mahalle_nufus); //Mahalle nüfusu kadar kişi için yer açılır
                for(int k = 0; k < mahalle_nufus; k++) {
                    kisiler[k] = new_kisi(this->kisilerin_isimleri[rand() % 10000], rand() % 51); //Rastgele isim ve yaş ataması
                }
                mahalle->add_kisiler(mahalle, kisiler, mahalle_nufus); //Mahalleye kişi ekleme fonksiyonu çağrılır
                free(kisiler);
                // Mahalle nüfusu eklendikten sonra, nüfus bilgisini güncelle ve mahalle ilçeye ekle
                mahalle->super->setNufus(mahalle);
                mahalleler[j] = mahalle; //Mahalle, mahalleler listesine eklenir);
            }
            ilce->add_mahalleler(ilce, mahalleler, mahalle_sayisi); //İlçeye mahalleleri ekleme fonksiyonu çağrılır
            free(mahalleler);
            //Ilçeye mahalleleri eklendikten sonra, ilçe nüfusunu güncelle ve ilçe şehre ekle
            ilce->super->setNufus(ilce);
            ilceler[i] = ilce; //İlçe, ilçeler listesine eklenir
        }
        sehir->add_ilceler(sehir, ilceler, ilce_sayisi); //Şehre ilçeleri ekleme fonksiyonu çağrılır
        free(ilceler);
        sehir->super->setNufus(sehir); //Şehre ilçeler eklendikten sonra, şehir nüfusunu güncelle
        this->sehir_listesi = (Sehir*)realloc(this->sehir_listesi, sizeof(Sehir) * (this->sehir_sayisi + 1)); //Oyun içindeki şehir listesine yeni şehri eklemek için yer açılır
        this->sehir_listesi[this->sehir_sayisi] = sehir; //Yeni şehir, oyun içindeki şehir listesine eklenir
        this->sehir_sayisi++; //Oyun içindeki şehir sayısı güncellenir
    }
    return this;
}

//add sehirler metodu
void add_sehir(const Oyun this, Sehir yeni_sehir){
    // Pointer dizisi yeni toplam boyuta göre yeniden boyutlandırılır
    // (Mevcut boyut + yeni şehir sayısı)
    this->sehir_listesi = (Sehir*)realloc(this->sehir_listesi, (this->sehir_sayisi + 1) * sizeof(Sehir));

    // Yeni şehir pointer'ları dizinin sonuna kopyalanır
    this->sehir_listesi[this->sehir_sayisi] = yeni_sehir;
    this->sehir_sayisi += 1; //Atualiza o contador interno
} 

//Her turda nüfusu yaşlandırır ve artış oranına göre yeni kişiler ekler.
void tur_baslat(const Oyun this){
    // Her şehirdeki ilçeler ve mahalleler üzerinden geçerek nüfusu yaşlandırır ve yeni kişiler ekler
    for(int i = 0; i < this->sehir_sayisi; i++){
        int artis_orani = nufus_artis_orani_bul(this->sehir_listesi[i]->super->getNufus(this->sehir_listesi[i]->super));

        for(int j = 0; j < this->sehir_listesi[i]->getIlceSayisi(this->sehir_listesi[i]); j++){
            for(int k = 0; k < this->sehir_listesi[i]->ilce_listesi[j]->getMahalleSayisi(this->sehir_listesi[i]->ilce_listesi[j]); k++){
                //Yeni kişiler eklenmeden önce, mevcut kişiler 1 yaş yaşlandırılmalıdır
                for(int m = 0; m < this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->getKisiSayisi(this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]); m++){
                    this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->kisi_listesi[m]->yaslan(
                        this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->kisi_listesi[m]);
                }
                //Nüfus artış formülü uygulaması
                int mevcut_nufus = this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->super->getNufus(this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->super);
                //Eğer artış oranı sıfır ise, her mahalleye sadece bir kişi eklenir. Sıfır değilse, formül uygulanır
                int eklenecek_kisi_sayisi = (artis_orani == 0) ? 1 : mevcut_nufus * (artis_orani - 1);
                Kisi* yeni_kisiler = (Kisi*)malloc(sizeof(Kisi) * eklenecek_kisi_sayisi); //Eklenecek kişi sayısı kadar yer açılır
                for(int sayici = 0; sayici < eklenecek_kisi_sayisi; sayici++){
                    yeni_kisiler[sayici] = new_kisi(this->kisilerin_isimleri[rand() % 10000], rand() % 51); //Rastgele isim ve yaş ataması
                }
                // Yeni kişiler mahalleye eklenir
                this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->add_kisiler(
                    this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k], yeni_kisiler, eklenecek_kisi_sayisi
                );
                free(yeni_kisiler);
                //Yeni kişiler eklendikten sonra nüfus bilgisini güncelliyoruz.
			    this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]->super->setNufus(
                    this->sehir_listesi[i]->ilce_listesi[j]->mahalle_listesi[k]
                );
            }
            this->sehir_listesi[i]->ilce_listesi[j]->super->setNufus(this->sehir_listesi[i]->ilce_listesi[j]);
        }
        this->sehir_listesi[i]->super->setNufus(this->sehir_listesi[i]);
    } 
    //Bir sonraki tura geçmeden önce, 4 haneli nüfusa ulaşan ve ikiye bölünmesi gereken şehirleri kontrol etmek için 
	//sehirNufusuKontrol metodunu çağırıyoruz.
    sehir_nufusu_kontrol(this);
}

//Eşik değeri (1000) aşan şehirleri tespit eder ve bölme işlemini tetikler
void sehir_nufusu_kontrol(const Oyun this){
    int Orijinal_sinir = this->sehir_sayisi;
    for(int i = 0; i < Orijinal_sinir; i++){
        if(this->sehir_listesi[i]->super->getNufus(this->sehir_listesi[i]->super) >= 1000){
            this->yeni_sehir_olustur(this, this->sehir_listesi[i]);
        }
    }
} 

void yeni_sehir_olustur(const Oyun this, const Sehir sehir){
    // 'count' değişkeni, yeni şehrin sahip olacağı ilçe sayısını temsil eder. 
    //Bölme işlemi tam sayı değilse, yeni şehir otomatik olarak daha az parçaya (ilçeye) sahip olacaktır.
    int count = sehir->getIlceSayisi(sehir)/2;

    
    // Eğer 'count' sıfır ise, şehir sadece bir ilçeye sahiptir; 
    //bu durumda bu tür şehir bölünmesinden sorumlu olan özel metodu çağırmamız gerekir.
    if(count == 0) ozel_yeni_sehir_olustur(this, sehir);
    else{
        Ilce* tasinanlar =  (Ilce*)malloc(sizeof(Ilce) * count);
        for(int i = 0; i < count; i++){
            tasinanlar[i] = sehir->ilce_listesi[sehir->getIlceSayisi(sehir)-1];
            sehir->decrease_ilce_sayisi(sehir);
        }
        sehir->super->setNufus(sehir);
        Sehir yeni_sehir = new_sehir(this->sehirlerin_adimlari[rand() % 10000]);
        yeni_sehir->add_ilceler(yeni_sehir, tasinanlar, count);
        free(tasinanlar);
        yeni_sehir->super->setNufus(yeni_sehir);
        this->add_sehir(this, yeni_sehir);
    }
}
//Tek bir ilçesi olan şehrin bölünmesinden sorumlu fonksiyon İlçeleri değil, mahalleleri bölüyoruz
void ozel_yeni_sehir_olustur(const Oyun this, const Sehir sehir){
    //'count' değişkeni, (yeni şehre eklenecek olan) yeni ilçenin sahip olacağı mahalle sayısını temsil eder.
    int count = sehir->ilce_listesi[0]->getMahalleSayisi(sehir->ilce_listesi[0])/2;
    // Eğer 'count' sıfır ise, ilçe sadece bir mahalle sahiptir; 
    //bu durumda bu tür şehir bölünmesinden sorumlu olan özel metodu çağırmamız gerekir.
    if(count == 0) son_ozel_yeni_sehir_olustur(this, sehir);
    else{
        // Taşınacak mahallelerin geçici listesini oluşturuyoruz
        Mahalle* tasinanlar = (Mahalle*)malloc(sizeof(Mahalle)*count);
        for(int i = 0; i < count; i++){
            tasinanlar[i] = sehir->ilce_listesi[0]->mahalle_listesi[sehir->ilce_listesi[0]->getMahalleSayisi(sehir->ilce_listesi[0]) - 1];
            sehir->ilce_listesi[0]->decrease_mahalle_sayisi(sehir->ilce_listesi[0]);
        }
        sehir->ilce_listesi[0]->super->setNufus(sehir->ilce_listesi[0]);
        sehir->super->setNufus(sehir);

        Ilce yeni_ilce = new_ilce(this->ilcelerin_adimlari[rand() % 10000]);
        yeni_ilce->add_mahalleler(yeni_ilce, tasinanlar, count);
        free(tasinanlar);
        yeni_ilce->super->setNufus(yeni_ilce);

        Sehir yeni_sehir = new_sehir(this->sehirlerin_adimlari[rand() % 10000]);
        Ilce* liste = (Ilce*)malloc(sizeof(Ilce));
        liste[0] = yeni_ilce;
        yeni_sehir->add_ilceler(yeni_sehir, liste, 1);
        free(liste);
        yeni_sehir->super->setNufus(yeni_sehir);

        this->add_sehir(this, yeni_sehir);
    }
} 

 //Bu fonksiyon, nüfusu doğrudan ikiye böler ve bir kısmını yeni şehre aktarır
void son_ozel_yeni_sehir_olustur(Oyun this, Sehir sehir){
    int count = sehir->ilce_listesi[0]->mahalle_listesi[0]->getKisiSayisi(sehir->ilce_listesi[0]->mahalle_listesi[0])/2;

    // if(count > 0){} gereksiz cunku her mahalledeki nufus bir tur sonra her zaman > 1 oluyor
    Kisi* tasinanlar = (Kisi*)malloc(sizeof(Kisi) * count);
    for(int i = 0; i < count; i++){
    tasinanlar[i] = sehir->ilce_listesi[0]->mahalle_listesi[0]->kisi_listesi[
        sehir->ilce_listesi[0]->mahalle_listesi[0]->getKisiSayisi(sehir->ilce_listesi[0]->mahalle_listesi[0]) - 1];
    sehir->ilce_listesi[0]->mahalle_listesi[0]->decrease_kisi_sayisi(sehir->ilce_listesi[0]->mahalle_listesi[0]);
    }
    // Eski şehrin tüm hiyerarşisi güncellenir
    sehir->ilce_listesi[0]->mahalle_listesi[0]->super->setNufus(sehir->ilce_listesi[0]->mahalle_listesi[0]);
    sehir->ilce_listesi[0]->super->setNufus(sehir->ilce_listesi[0]);
    sehir->super->setNufus(sehir);

    // Yeni şehir aşağıdan yukarıya doğru oluşturulur
    Mahalle yeni_mahalle = new_mahalle(this->mahallelerin_adimlari[rand() % 10000]);
    yeni_mahalle->add_kisiler(yeni_mahalle, tasinanlar, count);
    free(tasinanlar);
    yeni_mahalle->super->setNufus(yeni_mahalle);

    Ilce yeni_ilce = new_ilce(this->ilcelerin_adimlari[rand() % 10000]);
    Mahalle* mahalle_liste = (Mahalle*)malloc(sizeof(Mahalle));
    mahalle_liste[0] = yeni_mahalle;
    
    yeni_ilce->add_mahalleler(yeni_ilce, mahalle_liste, 1);
    free(mahalle_liste);
    yeni_ilce->super->setNufus(yeni_ilce);

    Sehir yeni_sehir = new_sehir(this->sehirlerin_adimlari[rand() % 10000]);
    Ilce* ilce_liste = (Ilce*)malloc(sizeof(Ilce));
    ilce_liste[0] = yeni_ilce;

    yeni_sehir->add_ilceler(yeni_sehir, ilce_liste, 1);
    free(ilce_liste);
    yeni_sehir->super->setNufus(yeni_sehir);

    this->add_sehir(this, yeni_sehir);
}

//Şehirleri görüntüleme metodu. Her satırda 5 şehir gösterilir.
void sehirler_gostermek(const Oyun this) {
    int blok = 0;

    for (int i = 0; i < this->sehir_sayisi; i++) {
        printf("[%d]", this->sehir_listesi[i]->super->getNufus(this->sehir_listesi[i]->super));
        blok++;

        int listedekiSon = (i == this->sehir_sayisi - 1);
        int satirBiti = (blok == 5);

       // Toplam listenin sonu değilse VE 5'lik satırın sonu değilse tire yazdırır
        if (!listedekiSon && !satirBiti) {
            printf("-");
        }

        if (satirBiti) {
            printf("\n"); // Her 5 elemanda bir satır sonu ekler
            blok = 0;
        }
    }

    // Liste 5'in katında bitmediyse, en sonda yeni satır ekler
    if (blok != 0) {
        printf("\n");
    }
}

//Sehir sınıfındaki detayliYazdir metodunu çağırarak şehir detaylarını yazdırıyorum. 
void koordinatla_sehir_goster(const Oyun this, int satir, int sutun) {
    // Cálculo do índice baseado na visualização de 5 colunas
    int indexOfSehir = (satir * 5) + sutun;

    // Sınır kontrolü
    if (indexOfSehir >= 0 && indexOfSehir < this->sehir_sayisi) {
        Sehir secilen = this->sehir_listesi[indexOfSehir];
        secilen->detayli_yazdir(secilen);
    } else {
        printf("Hata: Gecersiz koordinat!");
    }
}

void delete_oyun(const Oyun this){

    for(int i = 0; i < this->sehir_sayisi; i++){
        this->sehir_listesi[i]->Delete(this->sehir_listesi[i]);
    }

    free(this->sehir_listesi);

    for (int i = 0; i < 10000; i++) {
        free(this->kisilerin_isimleri[i]);
        free(this->sehirlerin_adimlari[i]);
        free(this->ilcelerin_adimlari[i]);
        free(this->mahallelerin_adimlari[i]);
    }

    free(this->kisilerin_isimleri);
    free(this->sehirlerin_adimlari);
    free(this->ilcelerin_adimlari);
    free(this->mahallelerin_adimlari);

    free(this);
}