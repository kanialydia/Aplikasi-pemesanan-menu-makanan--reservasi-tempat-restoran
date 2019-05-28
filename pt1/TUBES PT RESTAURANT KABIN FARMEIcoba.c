#include<stdio.h>
#include<string.h>
#include<windows.h>

typedef struct{
    int nomor;
    char deskripsi[15];
    char jenis[20];
    char status[200];
}statusMeja;// tipe data yang dapat menampung daftar meja

typedef struct{
    int nomor;
    char makanan [200];
    float harga;
    int kaliPesan;
}menu;//tipe data yang dapat menampung daftar menu

typedef struct{
    char pesanan [200];
    int kuantitas;
    float total;
}order;//tipe data yang dapat menampung pesanan pelanggan

FILE *menuApp;
FILE *menuMC;
FILE *menuDes;
FILE *menuBev;
FILE *meja;

char END;


void MEJA(statusMeja A[], int n, char status[200], char kata[20]);//prosedur untuk mengubah status meja
void tampilMenu(menu A[], int x, int y, char kata[11]);//prosedur untuk menampilkan menu ke layar
void terlaris(menu A[], int x, int y, char kata[20]);//prosedur untuk melihat menu terlaris dari daftar pilihan
void PilihanTakValid();//prosedur yang menampilkan pesan jika pilihan yang dimasukkan tidk dapat dimengerti program
void end();//prosedur menampilkan pesan untuk mengakhiri suatu program

void main(){
    int pilUtama=0,a,b,c,d,i=0;
    char ascii;
    int x,y;
    menu varMenu[1000];

    //Membaca menu dari file dan dimasukkan ke variabel varMenu
    menuApp=fopen("MENU_APPETIZER.txt","r");
    while(!feof(menuApp)){
        i++;
        varMenu[i].nomor=i;
        fscanf(menuApp,"\t%s",&varMenu[i].makanan);
        fscanf(menuApp,"\t%f",&varMenu[i].harga);
        fscanf(menuApp,"\t%d\n",&varMenu[i].kaliPesan);
    }
    fclose(menuApp);a=i;
    menuMC=fopen("MENU_MAIN_COURSE.txt","r");
    while(!feof(menuMC)){
        i++;
        varMenu[i].nomor=i;
        fscanf(menuMC,"\t%s",&varMenu[i].makanan);
        fscanf(menuMC,"\t%f\n",&varMenu[i].harga);
        fscanf(menuMC,"\t%d\n",&varMenu[i].kaliPesan);
    }
    fclose(menuMC);b=i;
    menuDes=fopen("MENU_DESSERT.txt","r");
    while(!feof(menuDes)){
        i++;
        varMenu[i].nomor=i;
        fscanf(menuDes,"\t%s",&varMenu[i].makanan);
        fscanf(menuDes,"\t%f\n",&varMenu[i].harga);
        fscanf(menuDes,"\t%d\n",&varMenu[i].kaliPesan);
    }
    fclose(menuDes);c=i;
    menuBev=fopen("MENU_BEVERAGE.txt","r");
    while(!feof(menuBev)){
        i++;
        varMenu[i].nomor=i;
        fscanf(menuBev,"\t%s",&varMenu[i].makanan);
        fscanf(menuBev,"\t%f\n",&varMenu[i].harga);
        fscanf(menuBev,"\t%d\n",&varMenu[i].kaliPesan);
    }
    fclose(menuApp);d=i;

    while (pilUtama!=4){//Selama tidak menekan tombol keluar
        system("cls");
        system("color 07");
        printf("\nMenu utama program restoran''KaBin FarMei''\nKetik angka menurut pilihan yang akan dipilih!");
        printf("\n1.Ambil Meja\n2.Ambil Pesanan\n3.Lihat menu terlaris\n4.Tutup Restoran\n\nPilihan: ");
        scanf("%d",&pilUtama);
        system("cls");
        while((pilUtama<1)||(pilUtama>4)){//pencegahan inputan diluar pilihan yang ada
            PilihanTakValid();
            printf("\n1.Ambil Meja\n2.Ambil Pesanan\n3.Lihat menu terlaris\n4.Keluar\n\nPilihan: ");
            scanf("%d",&pilUtama);
            system("cls");
        }

        if (pilUtama==1){//Beralih ke opsi meja
            statusMeja staMej[300];
            int e=0,pilM;
            meja=fopen("STATUS_MEJA.txt","r");
            while(!feof(meja)){
                e++;
                fscanf(meja,"%d",&staMej[e].nomor);
                fscanf(meja,"\t%s",&staMej[e].deskripsi);
                fscanf(meja,"\t\t%s",&staMej[e].jenis);
                fscanf(meja,"\t\t%s\n",&staMej[e].status);
            }
            fclose(meja);
            printf("Apa yang ingin dilakukan?\n1. Ambil Meja\n2. Kosongkan Meja\n3. Reservasi\n4. Tampilkan status\nPILIHAN: ");
            scanf("%d",&pilM);
            while((pilM<0)||(pilM>4)){//pencegahan inputan diluar pilihan yang ada
                system("cls");
                PilihanTakValid();
                printf("Apa yang ingin dilakukan?\n1. Ambil Meja\n2. Kosongkan Meja\n3. Reservasi\n4. Tampilkan status\NPILIHAN: ");
                scanf("%d",&pilM);
            }
            if(pilM==1){
                 MEJA(&staMej,e,"Taken","ambil");
            }else if(pilM==2){
                MEJA(&staMej,e,"Vacant","kosongkan");
            }else if(pilM==3){
                MEJA(&staMej,e,"Reserved","reservasi");
            }else if(pilM==4){
                printf("\nNO\tMeja\t\tJenis\t\tStatus\n");
                for(i=1;i<=e;i++){
                    printf("%d\t%s\t%s\t\t%s\n",staMej[i].nomor,staMej[i].deskripsi,staMej[i].jenis,staMej[i].status);
                }
            }

            //meng-update file daftar meja
            meja=fopen("STATUS_MEJA.txt","w");
            for(i=1;i<=40;i++){
                fprintf(meja,"%d",staMej[i].nomor);
                fprintf(meja,"\t%s",staMej[i].deskripsi);
                fprintf(meja,"\t\t%s",staMej[i].jenis);
                fprintf(meja,"\t\t%s\n",staMej[i].status);
            }
            fclose(meja);
            end();

        }else if(pilUtama==2){//Hendak memesan makanan
            system("cls");
            order pes[100];
            int pil,j=0,LAGI=1,x=0,z;
            float TOTAL=0.0;

            //Menampilkan menu di layar
            while(LAGI==1){//Selama pelanggan masih ingin memesan lagi
                system("cls");
                printf("Silahkan memilih makanan yang ingin di pesan dengan menginputkan nomor makanan\nCONTOH: Input angka 5 untuk memesan %s. Input angak 10 untuk memesan %s\n",varMenu[5].makanan,varMenu[10].makanan);
                tampilMenu(varMenu,0,a,"APPETIZER");
                tampilMenu(varMenu,a,b,"MAIN COURSE");
                tampilMenu(varMenu,b,c,"DESSERT");
                tampilMenu(varMenu,c,d,"BEVERAGE");
                if(j!=0){//Menampilkan daftar menu yang sudah dipesan dan berapa banyak
                    printf("\n\nAnda sudah memesan:\n");
                    for(i=1;i<=j;i++){
                        printf("%s\tx%d\n",pes[i].pesanan,pes[i].kuantitas);
                        printf("TOTAL = %.1fK\n",TOTAL);
                    }
                }
                printf("\nPilihan: ");
                scanf("%d",&pil);

                //menanyakan berapa banyak item yang dipilih akan dipesan
                if(varMenu[pil].nomor==pil){
                    j++;
                    printf("\nAnda memesan %s dengan harga %.1fK. Anda hendak memesan item ini untuk berapa orang?\nJAWABAN: ",varMenu[pil].makanan,varMenu[pil].harga);
                    scanf("%d",&pes[j].kuantitas);
                    if(pes[j].kuantitas<1){
                        printf("\nAnda memesan %s untuk %d orang. Maka kami menganggap anda batal memesan item ini",varMenu[pil].makanan,pes[j].kuantitas);
                        pes[j].kuantitas=0;
                        j--;
                    }else{
                        strcpy(pes[j].pesanan,varMenu[pil].makanan);
                        pes[j].total=varMenu[pil].harga*pes[j].kuantitas;
                          TOTAL=TOTAL+pes[j].total;
                        varMenu[pil].kaliPesan=varMenu[pil].kaliPesan+pes[j].kuantitas;
                    }
                }else{
                    printf("\nInputan yang anda masukkan tidak cocok dengan menu yang ada. anda dianggap tidak memesan apapun");
                }

                //Menanyakan apakah pelanggan hendak memesan atau tidak
                printf("\n\nApakah anda hendak memesan lagi?\n(Tekan 1 untuk iya, 0 untuk CETAK STRUK)\nPILIHAN:  ");
                scanf("%d",&LAGI);
                while((LAGI!=1)&&(LAGI!=0)){//pencegahan inputan diluar pilihan yang ada
                    PilihanTakValid();
                    printf("\n\nApakah anda hendak memesan lagi?\n(Tekan 1 untuk IYA, 0 untuk CETAK STRUK)\nPILIHAN:  ");
                    scanf("%d",&LAGI);
                }
            }

            //Menampilkan biaya total
            system("cls");
            system("color F9");
            printf("Berikut struk daftar pesanan anda:\n\n");
            printf("%c",(char)218);
            for (x=1;x<40;x++){printf("%c",(char)196);}
            printf("%c\n",(char)191);
            printf("%c\t\t\t\t\t%c\n",(char)179,(char)179);
            printf("%c\t       KABIN FARMEY \t\t%c\n",(char)179,(char)179);
            printf("%c\t   Makan Enak Tiap Hari \t%c\n",(char)179,(char)179);
            printf("%c      Anda Kenyang Kamipun Senang\t%c\n",(char)179,(char)179);
            printf("%c\t\t\t\t\t%c",(char)179,(char)179);
            printf("\n%c=======================================%c\n",(char)179,(char)179);
            printf("%c\t\t\t\t\t%c\n",(char)179,(char)179);
            printf("%cMENU\t\t\tQty\tTotal\t%c\n%c",(char)179,(char)179,(char)195);
            for (x=1;x<40;x++){printf("%c",(char)196);}
            printf("%c",(char)180);
            printf("\n%c",(char)179);
            for(i=1;i<=j;i++){
                printf("%s\t\t%d\t%.1fK\t%c\n",pes[i].pesanan,pes[i].kuantitas,pes[i].total,(char)179);
                printf("%c",(char)179);
            }
            printf("\t\t\t\t\t%c\n%c",(char)179,(char)195);
            for (x=1;x<40;x++){
            printf("%c",(char)196);}
            printf("%c\n%cTOTAL\t\t\t\t%.1fK \t%c\n",(char)180,(char)179,TOTAL,(char)179);
            printf("%c\t\t\t\t\t%c",(char)179,(char)179);
            printf("\n%c=======================================%c\n",(char)179,(char)179);
            printf("%c\t\t\t\t\t%c\n",(char)179,(char)179);
            printf("%c    TERIMA KASIH ATAS KUNJUNGAN ANDA\t%c\n",(char)179,(char)179);
            printf("%c\t      DATANG KEMBALI\t\t%c\n",(char)179,(char)179);
            printf("%c\t\t\t\t\t%c\n",(char)179,(char)179);
            printf("%c",(char)192);
            for (x=1;x<40;x++){
            printf("%c",(char)196);}
            printf("%c",(char)217);

            //Menyimpan data menu yang sudah di update ke file
            menuApp=fopen("MENU_APPETIZER.txt","w");
            for(i=1;i<=a;i++){
                fprintf(menuApp,"%s",varMenu[i].makanan);
                fprintf(menuApp,"\t%.1f",varMenu[i].harga);
                fprintf(menuApp,"\t%d\n",varMenu[i].kaliPesan);
            }
            fclose(menuApp);
            menuMC=fopen("MENU_MAIN_COURSE.txt","w");
            for(i=a+1;i<=b;i++){
                fprintf(menuMC,"%s",varMenu[i].makanan);
                fprintf(menuMC,"\t%.1f",varMenu[i].harga);
                fprintf(menuMC,"\t%d\n",varMenu[i].kaliPesan);
            }
            fclose(menuMC);
            menuDes=fopen("MENU_DESSERT.txt","w");
            for(i=b+1;i<=c;i++){
                fprintf(menuDes,"%s",varMenu[i].makanan);
                fprintf(menuDes,"\t%.1f",varMenu[i].harga);
                fprintf(menuDes,"\t%d\n",varMenu[i].kaliPesan);
            }
            fclose(menuDes);
            menuBev=fopen("MENU_BEVERAGE.txt","w");
            for(i=c+1;i<=d;i++){
                fprintf(menuBev,"%s",varMenu[i].makanan);
                fprintf(menuBev,"\t%.1f",varMenu[i].harga);
                fprintf(menuBev,"\t%d\n",varMenu[i].kaliPesan);
            }
            fclose(menuBev);
            end();

        }else if(pilUtama==3){//Hendak menunjukkan menu terlaris
            int piLar;
            printf("Pilih manakah daftar yang ingin anda lihat:\n1. Appetizer\n2. Main Course\n3. Dessert\n4. Food\n5. Beverage(Drink)\n6. All\nPILIHAN:");
            scanf("%d",&piLar);
            while((piLar<1)||(piLar>6)){//pencegahan inputan diluar pilihan yang ada
                PilihanTakValid();
                printf("Pilih manakah daftar yang ingin anda lihat:\n1. Appetizer\n2. Main Course\n3. Dessert\n4. Food\n5. Beverage(Drink)\n6. All\nPILIHAN:");
                scanf("%d",&piLar);
            }
            if(piLar==1){
                terlaris(varMenu,0,a,"menu appetizer");
            }else if(piLar==2){
                terlaris(varMenu,a,b,"menu main course");
            }else if(piLar==3){
                terlaris(varMenu,b,c,"menu desert");
            }else if(piLar==4){
                terlaris(varMenu,0,c,"menu makanan");
            }else if(piLar==5){
                terlaris(varMenu,c,d,"menu minuman");
            }else if(piLar==6){
                terlaris(varMenu,0,d,"semua menu");
            }

        }else{//menutup restoran
            printf("RESTORAN DI TUTUP");
        }
    }
}

void PilihanTakValid(){
    printf("\nPilihan yang dimasukkan tidak dapat dijalankan. Masukkan ulang inputan anda");
}

void tampilMenu(menu A[], int x, int y, char kata[11]){
    int i;
    printf("\n\n%s\nNO\tMENU\t\tHARGA",kata);
    for(i=x+1;i<=y;i++){
        printf("\n%d\t%s\t%.1fK",A[i].nomor,A[i].makanan,A[i].harga);
    }
}

void terlaris(menu A[], int x, int y, char kata[20]){
    menu Z[100],temp; int i,j=0,k,mark=0;
    for(i=x+1;i<=y;i++){
        j++;
        strcpy(Z[j].makanan,A[i].makanan);
        Z[j].harga=A[i].harga;
        Z[j].kaliPesan=A[i].kaliPesan;
    }

    //Mengurutkan menu sesuai dengan berapa kali item dipesan
    for(i=j;i>=2;i--){
        for(k=2;k<=i;k++){
            if(Z[k-1].kaliPesan<Z[k].kaliPesan){
                strcpy(temp.makanan,Z[k-1].makanan);
                temp.harga=Z[k-1].harga;
                temp.kaliPesan=Z[k-1].kaliPesan;
                strcpy(Z[k-1].makanan,Z[k].makanan);
                Z[k-1].harga=Z[k].harga;
                Z[k-1].kaliPesan=Z[k].kaliPesan;
                strcpy(Z[k].makanan,temp.makanan);
                Z[k].harga=temp.harga;
                Z[k].kaliPesan=temp.kaliPesan;
            }
        }
    }

    //Menampilkan urutan menu sesuai berapa kali pernah dipesan ke layar
    system("cls");
    printf("Pada %s, menu yang paling sering dibeli adalah %s",kata,Z[1].makanan);
    for(i=2;i<=j;i++){
        if(Z[1].kaliPesan==Z[i].kaliPesan){
            mark++;
        }
    }

    //disini program mengecek apakah ada item lain yang jumlah berapa kali di pesan nya sama dengan item terlaris. Agar dia juga tercetak
    for(i=1;i<=mark;i++){
        if(i==mark){
            printf(" &");
        }else{
            printf(",");
        }
        printf(" %s",Z[i+1].makanan);
    }
    printf("\n\nMenu\t\tHarga\tBerapa kali dipesan\n");
    for(i=1;i<=j;i++){
        printf("%s\t%.1f\t%d x\n",Z[i].makanan,Z[i].harga,Z[i].kaliPesan);
    }
    end();
}

void MEJA(statusMeja A[], int n, char status[200], char kata[20]){
    FILE *LOL;
    int i,z;
    char B[200], namaRes[200];
    system("cls");

    //menampilkan daftar meja agar pelayan dapat melihat status meja dan memilih meja yang akan di update
    printf("Ketik nomor meja yang ingin di %s!\nNO\tMeja\t\t\tJenis\t\tStatus\n",kata);
    for(i=1;i<=n;i++){
        printf("%d\t%s\t\t%s\t\t%s\n",A[i].nomor,A[i].deskripsi,A[i].jenis,A[i].status);
    }
    printf("\nPILIHAN: ");
    scanf("%d",&z);
    if(status=="Reserved"){
        //menanyakan nama yang ingin membooking meja (jika pelanggan ingin membooking meja)
         printf("Meja %d akan di reservasi atas nama (Gunakan (_) pengganti ( ) : ",z);
         scanf("%s",&namaRes);
         printf("%s",namaRes);
         LOL=fopen("SYALALA.txt","w");
         fprintf(LOL,"Reserved_by_");
         fclose(LOL);
         LOL=fopen("SYALALA.txt","a");
         fprintf(LOL,"%s",namaRes);
         fclose(LOL);
         printf("LOL");
         LOL=fopen("SYALALA.txt","r");
         fscanf(LOL,"%s",&namaRes);
         fclose(LOL);
         printf("LOL");
         printf("%s",namaRes);
         printf("LOL");
         strcpy(A[z].status,namaRes);
    }else{
        strcpy(A[z].status,status);
    }

    //menampilkan daftar meja setelah di update
    system("cls");
    printf("Berikut daftar meja setelah di update!\nNO\tMeja\t\tJenis\t\tStatus\n");
    for(i=1;i<=n;i++){
        if(i==z){
            printf("%d\t%s\t%s\t\t%s     <== UPDATED\n",A[i].nomor,A[i].deskripsi,A[i].jenis,A[i].status);//menunjukkan nomor meja yang di barusan di update
        }else{
            printf("%d\t%s\t%s\t\t%s\n",A[i].nomor,A[i].deskripsi,A[i].jenis,A[i].status);
        }
    }
}

void end(){
    printf("\nTekan sembarang untuk melanjutkan\n");
    END=getche();
}
