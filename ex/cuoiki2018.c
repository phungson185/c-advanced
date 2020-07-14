#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 9
int so_thanh_tri;
int so_duong;
int ma_tran_ke[MAX][MAX];
int case1(){
    int m,n,z,k=0;
    memset(ma_tran_ke,0,4*MAX*MAX);
    FILE* p = fopen("/home/phungson/hyouteisan/ex/dothi.txt","r");
    if(p == NULL)
    {
        printf("Loi khong doc duoc file\n");
        return -1;
    }
    fscanf(p,"%d",&so_thanh_tri);
    fscanf(p,"%d",&so_duong);
    while(fscanf(p,"%d",&m) != EOF)
    {
        fscanf(p,"%d",&n);
        fscanf(p,"%d",&z);
        ma_tran_ke[m][n] = z;
    }
    for(int j =0 ; j< MAX ;j++)
    {
        ma_tran_ke[0][j]=k;
        k++;
    }
    k=0;
    for(int i =0 ; i< MAX ;i++)
    {
        ma_tran_ke[i][0]=k;
        k++;
    }
    for(int i =0; i < MAX ;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            printf("%5d",ma_tran_ke[i][j]);
        }
        printf("\n");
    }
}
int case2(){
    for(int i=1;i< MAX -1 ;i++)
    {
        for (int j = 0; j < MAX -1 ; j++)
        {
            
        }
        
    }
}
int main(){
    int chon;
    while (1)
    {  
    printf("1. In ra ma tran ke cua do thi\n");
    printf("2. In ra danh sach ke cua moi thanh tri\n");
    printf("31. Danh sach cac thanh tri co the den no bang cach di bo\n");
    printf("32. Danh sach cac thanh tri co nhieu duong di noi truc tiep tu mot thanh tri khac den no nhat\n");
    printf("4. Tim duong di ngan nhat tu thanh tri s den thanh tri t\n");
    printf("5. Tim duong di bo ngan nhat tu thanh tri s den thanh tri t\n");
    printf("6. Thoat\n");
    printf("Chon so tuong ung: ");
    scanf("%d",&chon);
    switch (chon)
    {
    case 1: case1()    ;   break; 
    case 6: break; 
    default: printf("So ban chon khong co trong menu. Moi nhap lai\n");break;
    }
    if(chon == 6) break;
    }
}   