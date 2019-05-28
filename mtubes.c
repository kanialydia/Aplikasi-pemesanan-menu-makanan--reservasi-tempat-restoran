#include <stdio.h>
#include "tubes.c"

//cek baris 14-29,91-138
void main(){
    lMeja ListMe; createListMeja(&ListMe);
    lMakanan ListMa; createListMakanan(&ListMa);
    QTunggu QueueT; createQueueTunggu(&QueueT);
    int i,banyakMeja=5;
    for(i=1;i<=banyakMeja;i++){
        isiListMeja(&ListMe,i,0);
    }

    FILE *menu;
    int noMenu=0;
    char namaMenu[200];
    int hargaMenu;
    int freqMenu;
    adrMa p;
    menu=fopen("Menu.txt","r");
    while(!feof(menu)){
        noMenu=noMenu+1;
        p=alokasiMakanan(0,"LLL",0,0);
        p->noMakanan=noMenu;
        fscanf(menu,"\t%s",(p->namaMakanan));
        fscanf(menu,"\t%d",&(p->harga));
        fscanf(menu,"\t%d\n",&(p->freq));
        isiMenuMakanan(&ListMa,p);
    }

    char pilihanMenuUtama;
    boolean tutup=false;
    int noPelMasuk=0;
    while(!tutup){
        system("cls");
        system("color F");
        printf("\nSELAMA DATANG DI RESTORAN TUBES STRUKDAT\n=====================================\n");
        printf("Silahkan ketik nomor pilihan\n");
        printf("1 Pengisian Meja\n2 Pengosongan Meja\n3 Membatalkan Tunggu\n4 Cek Menu Terlaris\n5 Tutup restoran\n");
        printf("PILIHAN: ");
        pilihanMenuUtama=getche();
        if(pilihanMenuUtama=='1'){
            system("cls");
            noPelMasuk++;
            printf("\nNo. Antrian: %d",noPelMasuk);

            adrMe mejaKosong=ListMe.firstMe;
            boolean adaKosong=false;
            while((mejaKosong!=NULL)&&(!adaKosong)){
                if(mejaKosong->noPelanggan==0){
                    adaKosong=true;
                }else{
                    mejaKosong=mejaKosong->next;
                }
            }
            if(mejaKosong==NULL){
                printf("\nMeja penuh. Ingin dimasukkan ke Waiting List?\n");
                boolean inginTunggu;
                yaTidak(&inginTunggu);
                if(inginTunggu){
                    system("cls");
                    masukQueueTunggu(&QueueT,noPelMasuk);
                    printf("No. Antrian %d sudah dimasukkan ke Waiting Queue",(QueueT.tailT)->noPelanggan);
                    tekanSembarang();
                }else{
                    printf("Terima kasih\n");
                }
            }else if(adaKosong==true){
                mejaKosong->noPelanggan=noPelMasuk;
                pesanMakanan(&mejaKosong,ListMa);
            }
        }else if(pilihanMenuUtama=='2'){
            boolean pindahkan=false;
            adrMe mejaKosong;
            pengosonganMeja(&ListMe,&QueueT,&mejaKosong);
            if(QueueT.headT!=NULL){
                printf("\nPelanggan dengan nomor %d berada di awal antrian tunggu. Masukkan ke dalam meja %d?\n",QueueT.headT->noPelanggan,mejaKosong->noMeja);
                yaTidak(&pindahkan);
                if(pindahkan){
                    int pelangganMasuk;
                    keluarQueueTunggu(&QueueT,&pelangganMasuk);
                    mejaKosong->noPelanggan=pelangganMasuk;
                    pesanMakanan(&mejaKosong,ListMa);
                }
            }else{
                tekanSembarang();
            }
        }else if(pilihanMenuUtama=='3'){
            batalTunggu(&QueueT);
        }else if(pilihanMenuUtama=='4'){
            system("cls");
            lMakanan ListMaT;
            createListMakanan(&ListMaT);
            p=ListMa.firstMa;
            while(p!=NULL){
                adrMa q=alokasiMakanan(p->noMakanan,p->namaMakanan,p->harga,p->freq);
                isiMenuMakananTerurut(&ListMaT,q);
                p=p->next;
            }

            printf("Berikut menu yang diurutkan berdasarkan berapa kali dibeli\n\n");
            printf("No\tItem\t\tHarga\tFrek.\n========================================\n");
            adrMa cetakMenu=ListMaT.firstMa;
            while(cetakMenu!=NULL){
                printf("%d\t%s\t%d\t%d\n",cetakMenu->noMakanan,cetakMenu->namaMakanan,cetakMenu->harga,cetakMenu->freq);
                cetakMenu=cetakMenu->next;
            }
            tekanSembarang();
        }else if(pilihanMenuUtama=='5'){
            system("cls");
            boolean statusMejaKosong=true;
            boolean antrianKosong=false;
            adrMe cekMeja=ListMe.firstMe;
            while((cekMeja!=NULL)&&(statusMejaKosong)){
                if(cekMeja->noPelanggan!=0){
                    statusMejaKosong=false;
                }else{
                    cekMeja=cekMeja->next;
                }
            }
            if(QueueT.tailT==NULL){
                    antrianKosong=true;
            }

            if((statusMejaKosong)&&(antrianKosong)){
                printf("\nRESTORAN SUDAH DITUTUP");
                adrMa tulis=ListMa.firstMa;
                menu=fopen("Menu.txt","w");
                while(tulis!=NULL){
                    fprintf(menu,"%s",tulis->namaMakanan);
                    fprintf(menu,"\t%d",tulis->harga);
                    fprintf(menu,"\t%d\n",tulis->freq);
                    tulis=tulis->next;
                }
                fclose(menu);
                delAllMakanan(&ListMa);
                delAllMeja(&ListMe);
                tutup=true;
            }else{
                printf("Restoran masih belum bisa ditutup. Masih terdapat orang di antrian tunggu dan/atau Meja\n");
                cekMeja=ListMe.firstMe;
                printf("MEJA\nNo. Meja\tNo. Antrian\n======================\n");
                while(cekMeja!=NULL){
                    printf("%d\t\t%d\n",cekMeja->noMeja,cekMeja->noPelanggan);
                    cekMeja=cekMeja->next;
                }
                adrT cekAntrian=QueueT.headT;
                printf("ANTRIAN TUNGGU:\n|");
                while(cekAntrian!=NULL){
                    printf(" %d |",cekAntrian->noPelanggan);
                    cekAntrian=cekAntrian->next;
                }
                tekanSembarang();
                system("cls");
            }
        }
    }
}
