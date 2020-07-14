#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"c-vector/cvector.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 100
  igraph_t g,p;
  igraph_vector_t v,w,q,w1;
  int a,b,thanh, doan,i,j, choose, check, trongso;
  int mt[MAX][MAX];
  int A[MAX];
void dske(int a){
  printf("\n- Castle %d :", a);
  for(int i=0;i<igraph_vector_size(&v);i++){
    if((int)VECTOR(v)[i]==a){
      A[a]+=1;
    if(i%2==0){ 
      printf("%d\t",(int)VECTOR(v)[i+1]) ;
    }
    else
    {
    printf("%d\t",(int)VECTOR(v)[i-1]) ;
    }
    
    }
   }
}

void case3a(){
  int i=1;
 do{ i++;
    for(j=1;j<=thanh;j++) {
      if(mt[i][j]<50&& mt[i][j]>0) break;
      if(j==thanh) printf("%d ",i);
  }}
  while(i<8);
}
int max(int a[], int n)
{
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (max < a[i])
            max = a[i];
    return max;
}
void case3b(){
for(i=1;i<=thanh;i++)
  if( A[i]==max(A,thanh)) printf(" %d ",i);
}
void timduong(){
  int x,y;
  printf(" Nhap vao thanh xuat phat: ");
  scanf("%d",&x);
  printf(" Nhap vao thanh dich: ");
  scanf("%d",&y);
  igraph_vector_t d,e;
   igraph_vector_init(&d,0); //vector cac dinh di qua
   igraph_vector_init(&e,0);// vector cac canh di qua
  igraph_get_shortest_path_dijkstra(&g,&d,&e,x,y,&w,IGRAPH_ALL);
  int t=0;
  for(int i=0;i<igraph_vector_size(&e);++i){
    t+= (int)VECTOR( w)[(int)VECTOR(e)[i]];
  }
  if(t==0) {printf("Khong co duong di\n");return;}
  printf(" Do dai duong di la : %d\n",t);
  printf(" Thu tu thanh tri ma nguoi dua thu phai di qua : ");
  for(int i=0; i<igraph_vector_size(&d);++i){
    printf("%d ", (int)VECTOR(d)[i]);
  }
}
void timduongbo(){
int x,y;
  printf(" Nhap vao thanh xuat phat: ");
  scanf("%d",&x);
  printf(" Nhap vao thanh dich: ");
  scanf("%d",&y);
  igraph_vector_t d,e;
   igraph_vector_init(&d,0); //vector cac dinh di qua
   igraph_vector_init(&e,0);// vector cac canh di qua
  igraph_get_shortest_path_dijkstra(&p,&d,&e,x,y,&w1,IGRAPH_ALL);
  int t=0;
  for(int i=0;i<igraph_vector_size(&e);++i){
    t+= (int)VECTOR( w1)[(int)VECTOR(e)[i]];
  }
  if(t==0) {printf("Khong co duong di\n");return;}
  printf(" Do dai duong di la : %d\n",t);
  printf(" Thu tu thanh tri ma nguoi dua thu phai di qua : ");
  for(int i=0; i<igraph_vector_size(&d);++i){
    printf("%d ", (int)VECTOR(d)[i]);
  }
 
}
int main(int argc, char *argv[]){
  FILE* inp;
  int x,y;
  igraph_vector_init(&v,0);
  igraph_vector_init(&w,0);
   igraph_vector_init(&w1,0);
  igraph_vector_init(&q,0);
for(;;){
  printf("\n1. Doc ban do va in ra ma tran ke\n");
  printf("2. In ra danh sach ke.\n");
  printf("3. Dua ra danh sach thanh tri theo yeu cau.\n");
  printf("4. Tim duong di ngan nhat.\n");
  printf("5. Tim duong di bo ngan nhat.\n");
  printf("6. Thoat.\n");
  printf(" Nhap lua chon: ");
  scanf("%d",&choose);
  switch(choose) {
  case 1:
  inp= fopen("/home/phuongdung/C/dothi.txt","r");
 if(inp==NULL) printf("Loi mo file\n" );
 fscanf(inp,"%d",&thanh);
 fscanf(inp,"%d",&doan);
  for(i=0;i<doan;i++)
    {
    fscanf(inp,"%d %d %d",&a,&b, &trongso);
    if(trongso>=50)  {
      igraph_vector_push_back(&q,a); igraph_vector_push_back(&q,b); 
      igraph_vector_push_back(&w1,trongso);}
    igraph_vector_push_back(&v,a);
    igraph_vector_push_back(&v,b);
    igraph_vector_push_back(&w,trongso);
      
    mt[a][b]=mt[b][a]=trongso;
   }
  fclose(inp);
  check=1;
  printf("Ma tran ke cua do thi la:\n");
  for(i=1;i<=thanh;i++){
  for(j=1;j<=thanh;j++) printf("%d\t", mt[i][j]);
  printf("\n");
  }
  igraph_create(&g,&v,0,0);
  igraph_create(&p,&q,0,0);
  break; 
  case 2:
  if(check!=1){ printf("Chua doc ban do. Moi chon 1\n"); break;}
  for( int i=1; i<=thanh; i++) dske(i);
  break;
  case 3:
  printf("3a. Danh sach thanh tri chi co the den no truc tiep tu mot thanh tri khac bang cach di bo: ");
  case3a();
  printf("\n3b. Thanh tri co ban bac vao lon nhat: ");
  case3b();
  break;
  case 4:
  timduong();
  break;
  case 5:
  timduongbo();
  break;
  case 6: printf( "Ban da chon 6.Thoat \n");break;
  default: printf("So ban chon khong co trong menu. Moi chon lai: ");
  }
  if (choose==6) break;
  }


}
