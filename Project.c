#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
@brief Matrisi olusturma islemi burada dinamik sekilde yapiliyor.
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
@return matrisi dondurur
*/
int **matrisOlustur(int N, int M) {
	int i;
    int **matris = (int **)malloc(N * sizeof(int *));
    if (matris == NULL) {
        printf("Hata: Bellek tahsisi basarisiz oldu!\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < N; i++) {
        matris[i] = (int *)malloc(M * sizeof(int));
        if (matris[i] == NULL) {
            printf("Hata: Bellek tahsisi basarisiz oldu!\n");
            exit(EXIT_FAILURE);
        }
    }
    return matris;
}

/* 
@brief Kuyruklarin kapasitesini tutan dizi burada olusturuluyor ve sirasiyla kapasiteler aliniyor.
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
@return boyut dizisini dondurur
*/
int *kapasiteOku(int N, int M) {
	int i;
    int *boyut = (int *)malloc(N * sizeof(int));
    if (boyut == NULL) {
        printf("Hata: Bellek tahsisi basarisiz oldu!\n");
        exit(EXIT_FAILURE);
    }
    printf("Her bir oncelikli kuyrugun kapasitesini girin (En fazla M degeri kadar girebilirsiniz):\n");
    for (i = 0; i < N; i++) {
        do {
            scanf("%d", &boyut[i]);
            if (boyut[i] > M) {
                printf("Hata: Kapasite M degerinden buyuk olamaz. Lutfen tekrar girin: ");      // Eger bir satirin uzunlugundan buyuk bir kapasite degeri girilirse tekrardan isteniyor.
            }
        } while (boyut[i] > M);
    }
    return boyut;
}

/* 
brief Matrisin icini rastgele sayilarla doldurma islemi burada yapiliyor.
@param matris 
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
@param boyut dizisi
@return boyut dizisini dondurur
*/
void matrisiDoldur(int ***matris, int N, int M, int **boyut) {
	int i,k,temp,rastgele_indis,count;
    int *farkli_sayilar = (int *)malloc(N * M * sizeof(int));
    if (farkli_sayilar == NULL) {
        printf("Hata: Bellek tahsisi basarisiz oldu!\n");
        exit(EXIT_FAILURE);
    }
    // farkli_sayilar dizisini 1'den N*M'e kadar olan sayýlarla doldur
    for (i = 0; i < N * M; i++) {
        farkli_sayilar[i] = i + 1;
    }
    // farkli_sayilar dizisini karýþtýr
    srand(time(NULL));
    for (i = 0; i < N * M; i++) {
        temp = farkli_sayilar[i];
        rastgele_indis = rand() % (N * M);
        farkli_sayilar[i] = farkli_sayilar[rastgele_indis];
        farkli_sayilar[rastgele_indis] = temp;
    }
    // Matrisi farkli_sayilar dizisi ile doldur
    count = 0;
    for (i = 0; i < N; i++) {
        k = 0;
        while (k < (*boyut)[i] && count < N * M) {
            (*matris)[i][k++] = farkli_sayilar[count++];
        }
        // Eðer satýrýn kapasitesi boyut[i]'den küçükse, geri kalan hücreleri -1 ile doldur
        while (k < M) {
            (*matris)[i][k++] = -1;
        }
    }
    free(farkli_sayilar);          // Bu dizi ile isimiz bittiginde dizi serbest birakiliyor.
}

/*
brief Diziyi maxheapify eder ve en buyuk elemani ilk indise alir.@param matris 
@param arr heapify edilecek kuyruk
@param n o kuyrugun uzunlugu
@param i ebeveynler
*/
void maxHeapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < n && arr[l] > arr[largest])
        largest = l;
    if(r < n && arr[r] > arr[largest])
        largest = r;
    if(largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        maxHeapify(arr, n, largest);
    }
}

/*
@brief Bir kuyrugu son ebeveynden baslayarak maxHeapify eder.
@param arr heapify edilecek kuyruk
@param n o kuyrugun uzunlugu
*/
void buildMaxHeap(int *arr, int n) {
	int i;
    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

/*
@brief Matristeki tum kuyruklari ilk olusturmadan sonra maxHeapify eder.
@param matris 
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
@param boyut dizisi
*/
void maxHeapTree(int **matris,int N,int M,int *boyut){
	int i,j;
	for (i = 0; i < N; i++) {
        buildMaxHeap(matris[i], boyut[i]);
    }
}

/* 
@brief Kuyrugun ilk elemanlari burada okunuyor ve max olan ekrana yaziliyor. Bulundugu satirin indisi ise sonraki islemlerden dolayý donduruluyor.
@param matris 
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
@param boyut dizisi
@return k ilk elemani max olan kuyrugun indisini dondurur.
*/
int maxElemanBulma(int **matris, int *boyut, int N, int M) {
    int max = -1,k = -1,j;
    printf("Kuyruklardan degeri okunan elemanlar=");
    for (j = 0; j < N; j++) {
        if (boyut[j] != 0) {          // Eger bulundugu satir yani kuyruk bitmemisse max eleman taramasi yapiyor.
        	if(max == -1 || matris[j][0] > max){
        		max = matris[j][0];
            	k = j;	
			}
			printf("%d ",matris[j][0]);
        }
    }
    if (k != -1) {
        printf("\nSecilen eleman = %d\n", max);
    }
    return k;             //Max elemanin bulundugu satirin indisini yani hangi kuyruk oldugunu donduruyoruz.
}

/*
@brief Max eleman bulunduktan sonra silme islemi yapiliyor ve kuyruk sonuna bosluk anlamýna gelen -1 ekleniyor. Boyut dizisini ise 1 azaltiyoruz.
@param matris 
@param k ilk elemani max olan kuyrugun indisi
@param M matrisin sütun sayisi
@param boyut dizisi
*/
void maxElemanSilme(int ***matris, int **boyut, int k, int M) {
	int i;
    if ((*boyut)[k] != 0) {               // Aslinda yapilan islem tum dizinin 1 birim sola otelenmesi ve sona -1 gelmesidir.
        for (i = 0; i < M - 1; i++) {
            (*matris)[k][i] = (*matris)[k][i + 1];
        }
        (*matris)[k][M - 1] = -1;
        (*boyut)[k]--;
    }
}

/*
@brief Matrisi yazdirir.
@param matris
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
*/
void matrisiYazdir(int **matris, int N, int M) {
	int i,j;
	printf("\n");
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
@brief Tum kuyruklar bitmisse 0 bitmemisse 1 dondurur.
@param boyut dizisi,
@param N matrisin satir sayisi
@return 1 ise tum kuyruklar bos, 0 ise degil
*/
int bitmeKontrol(int *boyut,int N){
	int i;
	for(i=0;i<N;i++){
		if(boyut[i]!=0){
			return 0;
		}
	}
	return 1;
}

/*
@brief Max eleman bulunduktan sonra silme yapiliyor. Sonrasinda kuyruk bitmisse bitme sirasinin oldugu diziye ekliyor. Bitmediyse o kuyrugu heapify ediyor.
@param matris 
@param N matrisin satir sayisi
@param M matrisin sütun sayisi
@param boyut dizisi
@param bitis biten kuyruklari sirasiyla tutuyor.
*/
void oncelikSirala(int ***matris,int N, int M, int **boyut,int **bitis){
	int i,j,k,m=0;
	while(bitmeKontrol(*boyut,N)==0){          // Tum kuyruklar bitene kadar islem yapiliyor.
		k=maxElemanBulma(*matris,*boyut,N,M);    // Max eleman bulunup ekrana yazildiktan sonra bulundugu kuyruk k'ye ataniyor.
		maxElemanSilme(matris,boyut,k,M);        // Eleman siliniyor.
		if((*boyut)[k]==0){                    // Kuyruk bitmisse bitis dizisine hangi sirada bittigini tutabilmek icin yaziyoruz.
			(*bitis)[m]=k;                      
			m++;
		}else{
			buildMaxHeap((*matris)[k], (*boyut)[k]);        // Bitmemisse o kuyrugu sonraki islem icin maxHeapify ediyoruz.
		}
		matrisiYazdir((*matris), N, M);	           // Her adimi gorebilmek icin matrisi yazdiriyoruz.
	}
}

/* 
@brief Olusturdugumuz dizileri serbest birakiyoruz.
@param matris 
@param N matrisin satir sayisi
@param bitis dizisi
@param boyut dizisi
*/
void serbestBirak(int **matris, int *boyut, int *bitis, int N) {
	int i;
    // Matrisi serbest býrak
    for (i = 0; i < N; i++) {
        free(matris[i]);
    }
    free(matris);
    // Boyut dizisini serbest býrak
    free(boyut);
    // Bitiþ dizisini serbest býrak
    free(bitis);
}

int main(){
	int N,M,*boyut,*bitis,**matris,i;
	printf("Matris satir sayisini giriniz.\n");
	scanf("%d",&N);
	printf("Matris sutun sayisini giriniz.\n");
	scanf("%d",&M);
    matris = matrisOlustur(N, M);
    boyut = kapasiteOku(N, M);
    bitis = (int *)malloc(N * sizeof(int));
    matrisiDoldur(&matris,N,M,&boyut);
	matrisiYazdir(matris, N, M);
	maxHeapTree(matris,N,M,boyut);
	printf("Tum kuyruklar heapify edildikten sonraki hali=\n");
	matrisiYazdir(matris, N, M);
	oncelikSirala(&matris,N,M,&boyut,&bitis);
    printf("Kuyruklarin bitis sirasi=\n");
	for(i=0;i<N;i++){                                 // Tum kuyruklar bosaldiktan sonra bitis siramizi ekrana yazdiriyoruz.
		printf("%d ",bitis[i]+1);                     // 1 ile toplamamin sebebi bitis dizisi indis tutuyor. Ilk kuyruk 0 diye tutuluyor. Sirasini 1 göstermek için 1 ile topladim.
	}    
	serbestBirak(matris, boyut, bitis, N);
	return 0;
}
