#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 20
typedef struct infor
{
    int id1[MAX];
    int id2[MAX];
    int kc[MAX];
}infor;
infor tt;
int kiemtra_ip = 0,kiemtra_lk = 0,i=0;
char dia_chi_ip[MAX];
int id,kc;
int so_luong_may_chu,so_luong_lien_ket;
long int print_range(igraph_vector_t *e, igraph_vector_t *w) {
    long int i,a; 
    long int sum = 0;
    for (i = 0; i < igraph_vector_size(e); i++) {
        a=(long int) VECTOR(*e)[i];
        sum += (long int)VECTOR(*w)[a];    
    }
    return sum;
}
void print_vector(igraph_vector_t *v,JRB ip) {
    long int i,a; 
    for (i = 0; i < igraph_vector_size(v); i++) {
        a=(long int) VECTOR(*v)[i];
        printf("%s\n",jrb_find_int(ip,a)->val.s);
    }
}
int main(int argc, char *argv[])
{
    
    if(strcmp(argv[1],"-h")==0)
    {
        printf("C-Advanced,HK20152\n");
        return 0;
    }
    else
    {
    JRB ip = make_jrb();
    FILE *f = fopen(argv[2], "r");
    if(f==NULL)
    {
        printf("Loi khong doc duoc file\n");
        return -1;
    }
    fscanf(f,"%d",&so_luong_may_chu);
    while(fscanf(f,"%d",&id))
    {
        kiemtra_ip++;
        fscanf(f,"%s",dia_chi_ip);
        jrb_insert_int(ip,id,(Jval){.s=strdup(dia_chi_ip)});
        if(kiemtra_ip == 3) break;
    }
    fscanf(f,"%d",&so_luong_lien_ket);
    while(fscanf(f,"%d",&tt.id1[i]))
    {
        kiemtra_lk++;
        fscanf(f,"%d",&tt.id2[i]);
        fscanf(f,"%d",&tt.kc[i]);
        i++;
        if(kiemtra_lk == 3) break;
    }
    fclose(f);
    if (strcmp(argv[1],"-v")==0)
    {
        for(JRB ptr = jrb_first(ip);ptr != jrb_nil(ip);ptr = jrb_next(ptr))
        {
            printf("%d %s\n",ptr->key.i,ptr->val.s);
        }
    }
    else if (strcmp(argv[1],"-w")==0)
    {
        int check = 0;
        for(int i=0;i<so_luong_lien_ket;i++)
        {
            if(atoi(argv[3]) == tt.id1[i] && atoi(argv[4]) == tt.id2[i])
                {
                    printf("%d\n",tt.kc[i]);
                    check = 1;
                }
        }
        if(check == 0) printf("-1\n");
    }
    else if (strcmp(argv[1],"-p")==0)
    {
        igraph_t g;
        igraph_vector_t id_may;
        igraph_vector_t v;
        igraph_vector_t e;
        igraph_vector_t w;
        igraph_vector_init(&id_may,0);
        igraph_vector_init(&v,so_luong_may_chu);
        igraph_vector_init(&e,so_luong_may_chu/2);
        igraph_vector_init(&w,0);
        int from = atoi(argv[3]);
        int to = atoi(argv[4]);
        for(int i =0; i < so_luong_may_chu ;i++)
        {
            igraph_vector_push_back(&id_may, tt.id1[i]);
            igraph_vector_push_back(&id_may, tt.id2[i]);
            igraph_vector_push_back(&w, tt.kc[i]);
        }
        igraph_create(&g,&id_may,0,1);
        igraph_get_shortest_path_dijkstra(&g,&v,&e,from,to,&w,IGRAPH_ALL);
        printf("%ld\n",print_range(&e,&w));
        print_vector(&v,ip);
    }
    else if (strcmp(argv[1],"-n")==0)
    {
        int sum = 0;
        for(int i = 0;i<so_luong_may_chu ;i++)
        {
            if(atoi(argv[3]) == tt.id1[i])
                sum++;
            if(atoi(argv[3]) == tt.id2[i])
                sum++;
        }
        printf("%d\n",sum);
        for(int i = 0;i<so_luong_may_chu ;i++)
        {
            if(atoi(argv[3]) == tt.id1[i])
                printf("%d %s\n",tt.id2[i],jrb_find_int(ip,tt.id2[i])->val.s);
            if(atoi(argv[3]) == tt.id2[i])
                printf("%d %s\n",tt.id1[i],jrb_find_int(ip,tt.id1[i])->val.s);
        }
    }
    else if (strcmp(argv[1],"-s")==0)
    {
        int sum_dinh = 0;
        if(jrb_find_int(ip,atoi(argv[3])))
            {
                sum_dinh ++;
            }
        if(jrb_find_int(ip,atoi(argv[4])))
            {
                sum_dinh ++;
            }
        printf("%d\n",sum_dinh);
        printf("%d %s\n",atoi(argv[3]),jrb_find_int(ip,atoi(argv[3]))->val.s);
        printf("%d %s\n",atoi(argv[4]),jrb_find_int(ip,atoi(argv[4]))->val.s);
        printf("%d\n",sum_dinh/2);
        for(int i = 0 ;i <so_luong_may_chu;i++)
        {
            if(atoi(argv[3]) == tt.id1[i] && atoi(argv[4]) == tt.id2[i])
                printf("%d %d %d\n",tt.id1[i],tt.id2[i],tt.kc[i]);
        }
    }
    }
}
