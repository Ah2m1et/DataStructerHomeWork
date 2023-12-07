#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct {
    int count;
    NODE *pos;
    NODE *head;
    NODE *rear;
}LIST;

typedef struct ogrenci{
    int ogrenciNo;
    char isim[20];
    char soyad[20];
    char bolum[30];
    int sinif;
}ogrenci;

LIST *createList();
void destroyList(LIST *list);
void addNode(LIST *list);
void deleteNode(LIST *list, int sorgu);
void searchNode(LIST *list,int okulNo);
void treverseList(LIST *list);
void ogrenciOlustur(NODE *node);

int main(){
    int secim,sorgu;
    printf("**********merhabalar ogrenci menusune hosgeldiniz!**********\n");
    printf("liste eklemek icin -> 1\nliste silmek icin -> 2\nlisteye ogrenci eklemek icin -> 3\n");
    printf("listeden ogrenci silmek icin -> 4\nogrenci sorgulam icin -> 5\nlisteyi komple yazdirmak icin -> 6\ncikis icin -> 9");

    while(true){
        printf("\nislem seciniz:");
        scanf("%d",&secim);
        LIST *list;// captain we have a problem!!
        switch (secim) {
            case 1:
                list = createList();
                printf("==>>liste olusturuldu!");
                break;
            case 2:
                destroyList(list);
                printf("==>>liste silindi!");
                break;
            case 3:
                addNode(list);
                break;
            case 4:
                printf("listeden silmek istediginiz ogrencinin numarasini girin :");
                scanf("%d",&sorgu);
                deleteNode(list,sorgu);
                break;
            case 5:
                printf("sorgulamak istediginiz ogrencinin okul no girin: ");
                scanf("%d",&sorgu);
                searchNode(list,sorgu);
                break;
            case 6:
                treverseList(list);
                break;
            case 9:
                return 0;
            default:
                printf("==>gecersiz islem");
                break;
        }
    }
    return 0;
}

LIST *createList(){
    LIST *newList=(LIST *) malloc(sizeof (LIST));
    newList->count=0;
    newList->head=NULL;
    newList->pos=NULL;
    newList->rear=NULL;
    return newList;
}
void destroyList(LIST *list){
    if(list->head==NULL)
        free(list);
    else{
        while (list->head!=NULL){
            if(list->head==list->rear){
                free(list->head);
                free(list);
                return;
            }
            list->pos=list->rear;
            list->rear=list->rear->prev;
            free(list->pos);
        }
        free(list);
    }
}
void searchNode(LIST *list,int okulNo){
    if(list->head==NULL||list==NULL)
        printf("**henuz tanimli ogrenci bulunmuyor!!!\n");
    else{
        list->pos=list->head;
        while(list->pos!=NULL){
            if(((struct ogrenci *)list->pos->data)->ogrenciNo==okulNo){
                printf("\n----ogrenci----\n");
                printf("%s %s %s %d.sinif %d\n",((struct ogrenci *)list->pos->data)->isim,
                       ((struct ogrenci *)list->pos->data)->soyad,((struct ogrenci *)list->pos->data)->bolum,
                       ((struct ogrenci *)list->pos->data)->sinif,((struct ogrenci *)list->pos->data)->ogrenciNo);
                return;
            }
            list->pos=list->pos->next;
        }
        printf("**ogrenci bulunamadi!!\n");
    }
}
void deleteNode(LIST *list, int sorgu){
    if(list->head==NULL)
        printf("**henuz tanimli ogrenci bulunmuyor!");
    else{
        list->pos=list->head;
        while(list->pos!=NULL){
            if(((struct ogrenci *)list->pos->data)->ogrenciNo==sorgu){//node silme islemleri
                if(list->pos==list->head){
                    list->head=list->pos->next;
                    list->pos->next->prev=(struct node*)list;
                    free(list->pos);
                }
                else if (list->pos==list->rear){
                    list->rear=list->rear->prev;
                    free(list->rear->next);
                    list->rear->next=NULL;
                } else{
                    list->pos->prev->next=list->pos->next;
                    list->pos->next->prev=list->pos->prev;
                    free(list->pos);
                }
                printf("\n==>>silme islemi basarili!");
                return;
            }
            list->pos=list->pos->next;
        }
        printf("**silinecek ogrenci bulunamadi!");
    }
}
void addNode(LIST *list){
    if(list==NULL){
        printf("**liste olusturulmadan ogrenci eklenemez!");
        return;
    } else{
        if(list->head==NULL){
            list->head=(NODE *) malloc(sizeof (NODE));
            ogrenciOlustur(list->head);
            list->head->prev = (struct node *) list;
            list->head->next = NULL;
            list->rear=list->head;
            list->pos=list->head;
        } else{
            list->rear->next=(NODE *) malloc(sizeof (NODE));
            list->rear->next->prev=list->rear;
            list->rear=list->rear->next;
            ogrenciOlustur(list->rear);
            list->rear->next=NULL;
        }
    }
}
void treverseList(LIST *list){
    if(list->head==NULL){
        printf("==>liste bos!");
    } else{
        list->pos=list->head;
        printf("<----------*ogrenciler*---------->\n");
        while(list->pos!=NULL){
            printf("--%s %s %s %d.sinif %d\n",((struct ogrenci *)list->pos->data)->isim,
                   ((struct ogrenci *)list->pos->data)->soyad,((struct ogrenci *)list->pos->data)->bolum,
                   ((struct ogrenci*)list->pos->data)->sinif,((struct ogrenci *)list->pos->data)->ogrenciNo);
            list->pos=list->pos->next;
        }
    }
}
void ogrenciOlustur(NODE *node){
    ogrenci ogrenci;
    printf("ogrenci numarasi girin: ");
    scanf("%d",&(ogrenci.ogrenciNo));
    printf("ogrenci ismi girin: ");
    scanf("%s",(ogrenci.isim));
    printf("ogrenci soyadi girin: ");
    scanf("%s",ogrenci.soyad);
    printf("ogrenci bolum girin: ");
    scanf("%s",ogrenci.bolum);
    printf("ogrenci sinifi girin: ");
    scanf("%d",&ogrenci.sinif);
    printf("\n==>>islem basarili!");
    node->data=(struct ogrenci *) malloc(sizeof (struct ogrenci));
    *(struct ogrenci *)node->data=ogrenci;
}
