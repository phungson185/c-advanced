#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 1000
JRB name_to_id;
JRB id_to_name;
JRB kho_to_id;
JRB id_to_kho;
int so_loai_san_pham;
int so_luong_kho_hang;
int so_duong_di;
int so_san_pham[MAX][MAX];
int duong_di[MAX][MAX];
igraph_t g;
igraph_vector_t kho;
igraph_vector_t v;
igraph_vector_t e;
igraph_vector_t w;
long int print_range(igraph_vector_t *e, igraph_vector_t *w) {
    long int i,a; 
    long int sum = 0;
    for (i = 0; i < igraph_vector_size(e); i++) {
        a=(long int) VECTOR(*e)[i];
        sum += (long int)VECTOR(*w)[a];    
    }
    return sum;
}
int docfilesanpham(char *filename)
{
    name_to_id = make_jrb();
    id_to_name = make_jrb();
    char a[MAX];
    int b;
    FILE* p = fopen(filename,"r");
    fscanf(p,"%d",&so_loai_san_pham);
    while(fscanf(p,"%s",a) != EOF)
    {
        fscanf(p,"%d",&b);
        jrb_insert_str(name_to_id,strdup(a),(Jval){.i = b});
        jrb_insert_int(id_to_name,b,(Jval){.s = strdup(a)});
    }
    fclose(p);
}
int docfilekhohang(char* filename)
{
    igraph_vector_init(&kho,0);
    igraph_vector_init(&w,0);   
    int count = 0;
    int count1 = 0;
    FILE* p = fopen(filename,"r");
    fscanf(p,"%d",&so_luong_kho_hang);
    kho_to_id = make_jrb();
    id_to_kho = make_jrb();
    
    char a[MAX];
    int b,d,c;
    while(count != so_luong_kho_hang)
    {
        count ++;
        fscanf(p,"%s",a);
        fscanf(p,"%d",&b);
        jrb_insert_str(kho_to_id,strdup(a),(Jval){.i = b});
        jrb_insert_int(id_to_kho,b,(Jval){.s = strdup(a)});
        while(count1 != so_loai_san_pham)
        {
            
            count1++;
            fscanf(p,"%d",&c);
            fscanf(p,"%d",&d);
            so_san_pham[b][c] = d;
        }
        count1 = 0;
    }
    fscanf(p,"%d",&so_duong_di);
   // printf("%d\n",so_duong_di);
    while(fscanf(p,"%d",&b)!= EOF)
    {
       // printf("-1\n");
        fscanf(p,"%d",&c);
        fscanf(p,"%d",&d);
        duong_di[b][c]=d;
        duong_di[c][b]=d;
        igraph_vector_push_back(&kho, b);
        igraph_vector_push_back(&kho, c);
        igraph_vector_push_back(&w, d);
    }
    fclose(p);
}
int main(int argc, char *argv[])
{
    if(strcmp(argv[1],"-t")==0)
    {
        printf("C-Advanced,HK20182\n");
        return 0;
    }
    if(strcmp(argv[1],"-s")==0)
    {
        docfilesanpham(argv[2]);
        for(JRB ptr = jrb_first(id_to_name);ptr != jrb_nil(id_to_name);ptr = jrb_next(ptr))
        {
            printf("%s %d\n",ptr->val.s,ptr->key.i);
        }
    }
    if(strcmp(argv[1],"-w")==0)
    {
        int check = 0;
        docfilesanpham(argv[3]);
        docfilekhohang(argv[2]);
        if(jrb_find_int(id_to_kho,atoi(argv[4])) == NULL ||jrb_find_int(id_to_kho,atoi(argv[5])) == NULL )
        {
            printf("-1\n");
            return -1;
        }
        for(int i = 1 ; i <= so_loai_san_pham ;i++ )
        {
            for(int j = 1 ; j<= so_loai_san_pham ; j++)
                {
                    if(i ==  atoi(argv[4]) && j == atoi(argv[5]) )
                    {
                        printf("%dkm\n", duong_di[i][j]);
                        check = 1;
                        break;
                    }
                }
            if(check == 1)
                break;
        }
        if(check == 0)
            printf("Khong ton tai duong di giua %d va %d\n",atoi(argv[4]),atoi(argv[5]));
    }
    if(strcmp(argv[1],"-a")==0)
    {
        
        docfilesanpham(argv[3]);
        docfilekhohang(argv[2]);
        for(int i = 1; i <= so_luong_kho_hang ; i++)
        {
            printf("%s\n",jrb_find_int(id_to_kho,i)->val.s);
            for(int j = 1; j<= so_loai_san_pham ; j++)
            {
                printf("%s ",jrb_find_int(id_to_name,j)->val.s);
                printf("%d\n",so_san_pham[i][j]);
            }
            printf("----\n");
        }
    }
    if(strcmp(argv[1],"-b")==0)
    {
        memset(duong_di,0,MAX);
        docfilesanpham(argv[3]);
        docfilekhohang(argv[2]);
        printf("%s\n",jrb_find_int(id_to_kho,atoi(argv[5]))->val.s);
        printf("%s %d\n",jrb_find_int(id_to_name,atoi(argv[4]))->val.s,so_san_pham[atoi(argv[5])][atoi(argv[4])]);
        printf("----Cac kho ke la:\n");
        for(int i = 1;i<=so_luong_kho_hang ;i++)
            {
                if(duong_di[atoi(argv[5])][i] != 0)
                    {
                        printf("%s\n",jrb_find_int(id_to_kho,i)->val.s);
                        printf("%s %d\n",jrb_find_int(id_to_name,atoi(argv[4]))->val.s,so_san_pham[i][atoi(argv[4])]);
                    }
            }
    }
    if(strcmp(argv[1],"-g")==0)
    {
        docfilesanpham(argv[3]);
        docfilekhohang(argv[2]);
        igraph_create(&g,&kho,0,1);
        igraph_vector_init(&v,so_luong_kho_hang);
        igraph_vector_init(&e,so_luong_kho_hang);
        int a;
        if(so_san_pham[atoi(argv[6])][atoi(argv[4])]>= atoi(argv[5]))
        {
            printf("Dat hang thanh cong.\n Thoi gian giao hang la 30p");
        }
        else
        {
            if(so_san_pham[atoi(argv[6])][atoi(argv[4])]+so_san_pham[atoi(argv[7])][atoi(argv[4])] >= atoi(argv[5]) )
                {
                    igraph_get_shortest_path_dijkstra(&g,&v,&e,atoi(argv[6]),atoi(argv[7]),&w,IGRAPH_ALL);
                    a = print_range(&e,&w)/0.5 + 30;
                    printf("Dat hang thanh cong. Thoi gian giao hang la %d phut\n",a);
                }
            else
            {
                printf("Dat hang khong thanh cong\n");
            }
            
        }
        
    }
}