#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#include"c-vector/cvector.h"
#define MAX 9
int so_thanh_tri;
int so_duong;
int ma_tran_ke[MAX][MAX];
long int print_range(igraph_vector_t *e, igraph_vector_t *w) {
    long int i,a; 
    long int sum = 0;
    for (i = 0; i < igraph_vector_size(e); i++) {
        a=(long int) VECTOR(*e)[i];
        sum += (long int)VECTOR(*w)[a];    
    }
    return sum;
}
void print_vector(igraph_vector_t *v) {
    long int i; 
    for (i = 0; i < igraph_vector_size(v); i++) {
        printf("%ld ",(long int) VECTOR(*v)[i]);
    }
    printf("\n");
}
int case1(){
    int m,n,z,k=0;
    memset(ma_tran_ke,0,4*MAX*MAX);
    FILE* p = fopen("/home/phungson/hyouteisan/ex/thanh_tri/dothi.txt","r");
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
        ma_tran_ke[n][m] = z;
    }
    for(int j =0 ; j< so_thanh_tri+1 ;j++)
    {
        ma_tran_ke[0][j]=k;
        k++;
    }
    k=0;
    for(int i =0 ; i< so_thanh_tri+1 ;i++)
    {
        ma_tran_ke[i][0]=k;
        k++;
    }
    for(int i =0; i < so_thanh_tri+1 ;i++)
    {
        for(int j=0;j<so_thanh_tri + 1;j++)
        {
            printf("%5d",ma_tran_ke[i][j]);
        }
        printf("\n");
    }
}
int case2(){
    int danhsach2[MAX];
    memset(danhsach2,0,4*MAX);
    for(int i=1;i< so_thanh_tri + 1 ;i++)
    {
        for (int j = 1; j < so_thanh_tri + 1 ; j++)
        {
            if(ma_tran_ke[i][j] != 0)
                danhsach2[j] = j;
        }
        printf("Castle %d: ",i);
        for(int j=1 ; j < so_thanh_tri + 1 ; j ++ )
            {
                if(danhsach2[j] != 0)
                    printf("%d ",danhsach2[j]);
            }
        printf("\n");
        memset(danhsach2,0,4*MAX);
    }
}
int case31(){
    int check = 1;
    cvector_vector_type(int) v = NULL;
    for(int i=1;i< so_thanh_tri + 1 ;i++)
    {
        for (int j = 1; j < so_thanh_tri + 1 ; j++)
        {
            if(ma_tran_ke[i][j] < 50 && ma_tran_ke[i][j] !=0)
            {
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            cvector_push_back(v,i);
        }
        check = 1;
    }
    for (int i = 0; i < cvector_size(v); ++i) {
    printf("%d ",v[i]);
  }
    printf("\n");
}
int case4(){
    int xuatphat,dich,sothanhtrimoi,soduongdimoi,a;
    printf("Nhap vao thanh tri xuat phat: ");
    scanf("%d",&xuatphat);
    printf("Nhap vao thanh tri dich: ");
    scanf("%d",&dich);
    FILE* p = fopen("/home/phungson/hyouteisan/ex/thanh_tri/dothi1.txt","r");
    fscanf(p,"%d",&sothanhtrimoi);
    fscanf(p,"%d",&soduongdimoi);
    igraph_t g;
    igraph_vector_t thanhtri;
    igraph_vector_t v;
    igraph_vector_t e;
    igraph_vector_t w;
    igraph_vector_init(&thanhtri,0);
    igraph_vector_init(&v,so_thanh_tri);
    igraph_vector_init(&e,so_thanh_tri/2);
    igraph_vector_init(&w,0);
    while(fscanf(p,"%d",&a)!= EOF)
    {
        igraph_vector_push_back(&thanhtri, a);
        fscanf(p,"%d",&a);
        igraph_vector_push_back(&thanhtri, a);
        fscanf(p,"%d",&a);
        igraph_vector_push_back(&w,a);
    }
    igraph_create(&g,&thanhtri,0,1);
    igraph_get_shortest_path_dijkstra(&g,&v,&e,xuatphat,dich,&w,IGRAPH_ALL);
    printf("%ld\n",print_range(&e,&w));
    print_vector(&v);
}
int case5(){
    int xuatphat,dich;
    printf("Nhap vao thanh tri xuat phat: ");
    scanf("%d",&xuatphat);
    printf("Nhap vao thanh tri dich: ");
    scanf("%d",&dich);
    igraph_t g;
    igraph_vector_t thanhtri;
    igraph_vector_t v;
    igraph_vector_t e;
    igraph_vector_t w;
    igraph_vector_init(&thanhtri,0);
    igraph_vector_init(&v,so_thanh_tri);
    igraph_vector_init(&e,so_thanh_tri/2);
    igraph_vector_init(&w,0);
    for(int i =1; i < so_thanh_tri+1 ;i++)
    {
        for(int j=1;j<so_thanh_tri + 1;j++)
        {
            if(ma_tran_ke[i][j] >= 50){
                igraph_vector_push_back(&thanhtri, i);
                igraph_vector_push_back(&thanhtri, j);
                igraph_vector_push_back(&w,ma_tran_ke[i][j]);
            }
        }
    }
    igraph_create(&g,&thanhtri,0,1);
    igraph_get_shortest_path_dijkstra(&g,&v,&e,xuatphat,dich,&w,IGRAPH_ALL);
    printf("%ld\n",print_range(&e,&w));
    print_vector(&v);
}
int case32(){
    int a;
    FILE* p = fopen("/home/phungson/hyouteisan/ex/thanh_tri/dothi.txt","r");
    fscanf(p,"%d",&a);
    fscanf(p,"%d",&a);
    igraph_t g;
    igraph_vector_t bbv;
    igraph_vector_t v;
    igraph_vector_t e;
    igraph_vector_t w;
    igraph_vector_init(&bbv,0);
    while(fscanf(p,"%d",&a)!= EOF)
    {
        igraph_vector_push_back(&bbv, a);
        fscanf(p,"%d",&a);
        igraph_vector_push_back(&bbv, a);
        fscanf(p,"%d",&a);
    }
    igraph_create(&g,&bbv,0,1);
    igraph_degree(&g,&bbv, igraph_vss_all(), IGRAPH_ALL, IGRAPH_NO_LOOPS);
    int max = VECTOR(bbv)[0];
    for (int i = 1; i < igraph_vector_size(&bbv); i++)
        {
            if (VECTOR(bbv)[i] > max)
            {
                max = VECTOR(bbv)[i];
            }
        }
    for (int i = 0; i < igraph_vector_size(&bbv); i++)
        {
            if (VECTOR(bbv)[i] == max)
            {
                printf("%d ",i);
            }
        }
    printf("\n");
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
    case 2 : case2(); break;
    case 31 : case31() ; break;
    case 32 : case32() ; break;
    case 4 : case4() ; break;
    case 5 : case5() ; break;
    case 6: break; 
    default: printf("So ban chon khong co trong menu. Moi nhap lai\n");break;
    }
    if(chon == 6) break;
    }
}   