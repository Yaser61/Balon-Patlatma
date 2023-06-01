#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct dugum{
	int veri;
	char * renk;
	struct dugum *sonraki;
};

typedef struct dugum balonlar;
balonlar *ilk = NULL;
balonlar *us  = NULL;

int a;
void bastan_patlat(balonlar*);
void sondan_patlat(balonlar*);
void aradan_patlat(balonlar*,int);
void patlatilanlar();
void listele(balonlar*);
void toplu_dugum_olustur(int,char[][8]);

int main(){
	srand(time(NULL));
	int b,x;
    char renkler[][8] = {"Yesil","Mavi","Kirmizi","Beyaz","Sari","Siyah","Mor","Gri"};
    printf("Olusturulacak balon adedini giriniz : ");
    scanf("%d",&a);
    for(x = 1 ; x <= a ; x++){
		toplu_dugum_olustur(x,renkler);
	}
	listele(ilk);
	while(1) {
		printf("Patlatmak istediginiz balonun numarasini giriniz. Programi sonlandirmak icin 0 giriniz: ");
		scanf("%d",&b);
		if (b == ilk-> veri)
			bastan_patlat(ilk);
		else if (b == a)
			sondan_patlat(ilk);
		else if (b > a)
			printf("Girdiginiz numarada balon yok\n");
		else if (b == 0)
			break;
		else
			aradan_patlat(ilk,b);
		}
		patlatilanlar();
		printf("Kalan balonlar\n");
		listele(ilk);
	return 0;	
}	
void toplu_dugum_olustur(int veri,char renkler[][8] ){
	if(ilk == NULL){ 
		ilk = (balonlar*)malloc(sizeof(balonlar));
		ilk -> veri = veri;
		ilk -> renk = renkler[rand()%8];
    	ilk -> sonraki = ilk;
	}
	else{
		balonlar *temp1 = ilk;
		balonlar*temp2 = (balonlar*)malloc(sizeof(balonlar));
		while(temp1 -> sonraki != ilk)
			temp1 = temp1 -> sonraki;
		temp2 -> veri = veri;
		temp2 -> renk = renkler[rand()%8];
		temp1 -> sonraki = temp2;
		temp2 -> sonraki = ilk;
	}
}

void listele(balonlar *ilk){
	int Yesil = 0, Mavi = 0, Kirmizi = 0, Beyaz = 0, Sari= 0, Siyah = 0, Mor = 0, Gri = 0;
	balonlar *temp = ilk;
	if(ilk == NULL){
		printf("Listede eleman yok\n");
		return;
	}
	do{
		if (strcmp( temp -> renk, "Yesil") == 0)
			Yesil++;
		else if (strcmp( temp -> renk, "Mavi") == 0)
			Mavi++;
		else if (strcmp( temp -> renk, "Kirmizi") == 0)
			Kirmizi++;
		else if (strcmp( temp -> renk, "Beyaz") == 0)
			Beyaz++;
		else if (strcmp( temp -> renk, "Sari") == 0)
			Sari++;
		else if (strcmp( temp -> renk, "Siyah") == 0)
			Siyah++;
		else if (strcmp( temp -> renk, "Mor") == 0)
			Mor++;
		else if (strcmp( temp -> renk, "Gri") == 0)
			Gri++;
		if( temp-> veri > a ){
			printf("Kalan balon yok\n");
			break;
		}
		printf("%d. balon ", temp -> veri);
		printf("%s renk\n", temp -> renk);
		temp = temp -> sonraki;
	}while(temp != ilk);
	printf("\n");
	printf("%d Yesil balon\n",Yesil);
	printf("%d Mavi balon\n",Mavi);
	printf("%d Kirmizi balon\n",Kirmizi);
	printf("%d Beyaz balon\n",Beyaz);
	printf("%d Sari balon\n",Sari);
	printf("%d Siyah balon\n",Siyah);
	printf("%d Mor balon\n",Mor);
	printf("%d Gri balon\n\n",Gri);
}	

void bastan_patlat(balonlar *bas) {
	balonlar *temp = bas;
	if(temp == NULL) {
		printf("Patlatilacak balon bulunamadi\n");
		return;
	}
	while(temp -> sonraki != bas)
		temp = temp -> sonraki;
	temp -> sonraki = ilk -> sonraki;
	ilk = bas -> sonraki;
    balonlar *yeni = (balonlar*)malloc(sizeof(balonlar));
	yeni -> veri = bas -> veri;
	yeni -> renk = bas -> renk;
	if(us == NULL)
		yeni -> sonraki = NULL;
	else
		yeni -> sonraki = us;
	us = yeni;
	free(bas);
}
	
void sondan_patlat(balonlar *bas) {
	balonlar *temp = bas;
	if(temp == NULL){
		printf("Patlatilacak balon bulunamadi\n");
		return;
	}
	while(temp -> sonraki -> sonraki != bas)
		temp = temp -> sonraki;
	balonlar *yeni = (balonlar*)malloc(sizeof(balonlar));
	yeni -> veri = temp -> sonraki -> veri;
	yeni -> renk = temp -> sonraki -> renk;
	if(us == NULL)
		yeni -> sonraki = NULL;
	else
		yeni -> sonraki = us;
	us = yeni;
	free(temp -> sonraki);
	temp -> sonraki = ilk;
}

void aradan_patlat(balonlar *bas,int key) {
	balonlar *temp = bas;
	if(temp == NULL){
		printf("Patlatilacak balon bulunamadi\n");
		return;
	}
	while(temp -> sonraki != bas){
		if (temp -> sonraki -> veri == key) {
			balonlar *temp2 = temp;
			balonlar *temp3 = temp -> sonraki -> sonraki;
			balonlar *yeni = (balonlar*)malloc(sizeof(balonlar));
			yeni -> veri = temp -> sonraki -> veri;
			yeni -> renk = temp -> sonraki -> renk;
			if(us == NULL)
				yeni -> sonraki = NULL;
			else
				yeni -> sonraki = us;
			us = yeni;
			free(temp -> sonraki);
			temp2 -> sonraki = temp3;
			break;
		}
		temp = temp-> sonraki;
	}
}

void patlatilanlar(){
	printf("Patlatilan balonlar\n\n");
	balonlar *temp = us;
	while(temp != NULL){
		printf("%d. balon patlatildi rengi %s \n", temp -> veri, temp->renk);
		temp = temp -> sonraki;
	}
	printf("\n");
}
