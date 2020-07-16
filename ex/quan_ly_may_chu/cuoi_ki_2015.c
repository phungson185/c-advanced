#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#include"c-vector/cvector.h"
#define MAX 10001
JRB id_to_dns;
JRB dns_to_id;
int so_luong_may_chu;
int so_luong_lien_ket;
int matrix[MAX][MAX];
int dung[MAX][MAX];
igraph_t g;
igraph_vector_t duongdi;
igraph_vector_t v;
igraph_vector_t e;
igraph_vector_t w;
cvector_vector_type(int)son = NULL;
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
        printf("%ld\n",(long int) VECTOR(*v)[i]);
    }
    printf("\n");
}
int docfile(char *filename)
{
    memset(matrix,0,4*MAX*MAX);
    memset(dung,0,4*MAX*MAX);
    igraph_vector_init(&duongdi,0);
    igraph_vector_init(&w,0);
    int count1 = 0, count2 = 0;
    id_to_dns = make_jrb();
    dns_to_id = make_jrb();
    char b[MAX];
    int a,c,d;
    FILE* p = fopen(filename,"r");
    fscanf(p,"%d",&so_luong_may_chu);
    while(count1 != so_luong_may_chu)
    {
        count1++;
        fscanf(p,"%d",&a);
        fscanf(p,"%s",b);
        jrb_insert_int(id_to_dns,a,(Jval){.s = strdup(b)});
        jrb_insert_str(dns_to_id,strdup(b),(Jval){.i = a});
    }
    fscanf(p,"%d",&so_luong_lien_ket);
    while(fscanf(p,"%d",&a)!= EOF)
    {
        fscanf(p,"%d",&c);
        fscanf(p,"%d",&d);
        //printf("%d\n",d);
        igraph_vector_push_back(&duongdi,a);
        igraph_vector_push_back(&duongdi,c);
        igraph_vector_push_back(&w,d);
        matrix[a][c] = d;
        matrix[c][a] = d;
        dung[a][c] = d;
    }
    //printf("%d\n",matrix[2][9]);
    fclose(p);
}
int main(int argc, char *argv[])
{
    if(strcmp(argv[1],"-h")==0)
    {
        printf("C 20152\n");
    }
    if(strcmp(argv[1],"-v")==0)
    {
        docfile(argv[2]);
        for(JRB ptr = jrb_first(id_to_dns);ptr != jrb_nil(id_to_dns);ptr = jrb_next(ptr))
        {
            printf("%d %s\n",ptr->key.i,ptr->val.s);
        }
    }
    if(strcmp(argv[1],"-w")==0)
    {
        int check = 0;
        docfile(argv[2]);
        if(matrix[atoi(argv[3])][atoi(argv[4])]!=0)
        {
            printf("%d\n",matrix[atoi(argv[3])][atoi(argv[4])]);
        }
        else
        {
            printf("-1\n");
        }
    }
    if(strcmp(argv[1],"-p")==0)
    {
        docfile(argv[2]);
        long int a;
        igraph_vector_init(&v,so_luong_may_chu);
        igraph_vector_init(&e,so_luong_lien_ket);
        igraph_create(&g,&duongdi,0,1);
        igraph_get_shortest_path_dijkstra(&g,&v,&e,atoi(argv[3]),atoi(argv[4]),&w,IGRAPH_ALL);
        printf("%ld\n",print_range(&e,&w));
        for (int i = 0; i < igraph_vector_size(&v); i++) 
            {
                a = (long int) VECTOR(v)[i];
                printf("%s\n",jrb_find_int(id_to_dns,a)->val.s);
            } 
    }
    if(strcmp(argv[1],"-n")==0)
    {
        int sum = 0;  
        docfile(argv[2]);
        for(int i= 0; i<= MAX ; i++)
        {
            if(matrix[atoi(argv[3])][i]>0)
                {
                    sum++;
                    cvector_push_back(son,i);
                }
        }
        printf("%d\n",sum);
        for(int i =0 ; i<cvector_size(son);i++)
        {
            printf("%d %s %d\n",son[i],jrb_find_int(id_to_dns,son[i])->val.s,matrix[atoi(argv[3])][son[i]]);
        }
        cvector_free(son);   
    }
    if(strcmp(argv[1],"-s") == 0)
    {
        int sum = 0;
        int sum1= 0;
        docfile(argv[2]);
        for(int i = 3; i< argc ;i++)
        {
            if(jrb_find_int(id_to_dns,atoi(argv[i]))!= NULL)
            {
                sum++;
                cvector_push_back(son,atoi(argv[i]));
            }
        }
        printf("%d\n",sum);
        for(int i =0 ; i<cvector_size(son);i++)
        {
            printf("%d %s\n",son[i],jrb_find_int(id_to_dns,son[i])->val.s);
        }
        for(int i =0 ; i<cvector_size(son);i++)
        {
            for(int j =i+1 ; j<cvector_size(son);j++)
            {
                if(dung[son[i]][son[j]]!=0)
                    sum1++;
            }
        }
        printf("%d\n",sum1);
        for(int i =0 ; i<cvector_size(son);i++)
        {
            for(int j =0 ; j<cvector_size(son);j++)
            {
                if(dung[son[i]][son[j]]!=0)
                    
                    {
                        printf("%d %d %d\n",son[i],son[j],dung[son[i]][son[j]]);
                    }
            }
        }
    }
}