#include<btree.h>
#include<stdlib.h>
#include<string.h>
#define MAX 255
typedef struct {
    char *mo_ta;
    int tong;
} KhoanThanhToan;
KhoanThanhToan *deserialize(char *key){
    int name_len, total_len,b;
    KhoanThanhToan *a=(KhoanThanhToan*)malloc(sizeof(KhoanThanhToan));
    name_len = key[0];
    total_len = key[name_len+1];
    char *total = (char*)malloc(total_len+1);
    for(int i = name_len+2,j=0 ;i<name_len+total_len+2;i++,j++)
        total[j] = (unsigned char)key[i];
    total[total_len+1]='\0';
    b = atoi(total);
    a->tong = b;
    return a;
}
int main(){
    btinit();
    int size;
    int sum =0; 
    BTA* ktt = btopn("/home/phungson/hyouteisan/ex/test.bt",0,0);
    if(ktt == NULL){
        printf("Loi khong the mo file.\n");
        return -1;
    }
    char khoa[MAX];
    char giatri[MAX];
    btpos(ktt,ZSTART);
    while((btseln(ktt,khoa,giatri,MAX,&size) == 0))
    {
        sum+= deserialize(giatri)->tong;
    }
    btcls(ktt);
    printf("%d\n",sum);
}