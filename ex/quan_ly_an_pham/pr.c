#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#include"c-vector/cvector.h"
#define MAX 101
int so_luong_an_pham;
int so_luong_trich_dan;
JRB n2i;
JRB i2n;
igraph_t g;
igraph_vector_t code;
igraph_vector_t v;
igraph_vector_t e;
igraph_vector_t w;
typedef struct trichdan{
    int u;
    int v;
}trichdan;
cvector_vector_type(trichdan) data_trichdan = NULL;
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
int docfile(char* tenfile)
{
    trichdan tmp;
    int count1 = 0;
    int count2 = 0;
    char name[MAX];
    int id,a,b;
    FILE* p = fopen(tenfile,"r");
    if(p==NULL)
    {
        printf("loi doc\n");
        return -1;
    }
    n2i = make_jrb();
    i2n = make_jrb();
    fscanf(p,"%d",&so_luong_an_pham);
    fscanf(p,"%d",&so_luong_trich_dan);
    igraph_vector_init(&code,0);
    igraph_vector_init(&v,so_luong_trich_dan*2);
    igraph_vector_init(&e,so_luong_trich_dan);
    igraph_vector_init(&w,0);
    while(count1 != so_luong_an_pham)
    {
        count1++;
        fscanf(p,"%s",name);
        fscanf(p,"%d",&id);
        jrb_insert_str(n2i,strdup(name),(Jval){.i=id});
        jrb_insert_int(i2n,id,(Jval){.s=strdup(name)});
    }
    while(count2 != so_luong_trich_dan)
    {
        count2++;
        fscanf(p,"%d",&a);
        fscanf(p,"%d",&b);
        tmp = (trichdan){.u = a,.v = b};
        cvector_push_back(data_trichdan,tmp);
        igraph_vector_push_back(&code,a);
        igraph_vector_push_back(&code,b);
        igraph_vector_push_back(&w,1);
    }
    fclose(p);
}
int main(int argc, char *argv[])
{
    if(strcmp(argv[1],"help")==0)
        {
            printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
        }
    if(strcmp(argv[1],"about")==0)
        {
            printf("C advanced 20142 final exam\n");
        }
    if(strcmp(argv[1],"n2i")==0)
        {
            JRB ptr;
            docfile(argv[2]);
            if((ptr = jrb_find_str(n2i,strdup(argv[3])))!=NULL)
                printf("%d\n",ptr->val.i);
            else
            {
                printf("Khong tim thay.\n");
            }
        }
    if(strcmp(argv[1],"i2n")==0)
        {
            JRB ptr;
            docfile(argv[2]);
            if((ptr = jrb_find_int(i2n,atoi(argv[3])))!=NULL)
                printf("%s\n",ptr->val.s);
            else
            {
                printf("Khong tim thay.\n");
            }
        }
    if(strcmp(argv[1],"cc")==0)
        {
            int c;
            docfile(argv[2]);
            for (int i = 0; i < cvector_size(data_trichdan); ++i) {
                {
                    if(data_trichdan[i].u == atoi(argv[3]))
                        {
                            c = data_trichdan[i].v;
                            for (int j = 0; j < cvector_size(data_trichdan); j++)
                            {
                                if(data_trichdan[j].u == atoi(argv[4]) && data_trichdan[j].v == c)
                                    {
                                        printf("%s\n",jrb_find_int(i2n,c)->val.s);
                                        break;
                                    }
                            }    
                        }
                }
        }
        }
    if(strcmp(argv[1],"cr")==0)
        {
            int c;
            docfile(argv[2]);
            for (int i = 0; i < cvector_size(data_trichdan); ++i) {
                {
                    if(data_trichdan[i].v == atoi(argv[3]))
                        {
                            c = data_trichdan[i].u;
                            for (int j = i+1; j < cvector_size(data_trichdan); j++)
                            {
                                if(data_trichdan[j].v ==data_trichdan[i].v)
                                    {
                                        printf("%s\n",jrb_find_int(i2n,c)->val.s);
                                        printf("%s\n",jrb_find_int(i2n,data_trichdan[j].u)->val.s);
                                        break;
                                    }
                            }    
                        }
                }
        }
        }
    if(strcmp(argv[1],"odg")==0)
    {
        docfile(argv[2]);
        int bbr = 1,check = 1;
        cvector_vector_type(int) dinhdaduyet = NULL;
        int banbacra[MAX];
        memset(banbacra,0,4*MAX);
        for (int i = 0; i < cvector_size(data_trichdan); ++i) 
            {
                for (int h=0; h < cvector_size(dinhdaduyet); h++)
                    {
                        if(dinhdaduyet[h] == data_trichdan[i].u)
                        {
                            check = 0;
                            break;
                        }
                    }
                        if(check == 1){
                            cvector_push_back(dinhdaduyet,data_trichdan[i].u);
                            for (int j = i+1; j < cvector_size(data_trichdan); j++)
                                {
                                    if(data_trichdan[i].u == data_trichdan[j].u)
                                        bbr++;
                                }
                            banbacra[data_trichdan[i].u]=bbr;
                            }
                bbr = 1;            
                check = 1;
            }
        for(int i = 0; i<MAX ; i++)
        {
            if(banbacra[i]>atoi(argv[3]))
            {
                printf("%s\n",jrb_find_int(i2n,i)->val.s);
            }
        }
    }
    if(strcmp(argv[1],"rel")==0)
    {
        docfile(argv[2]);
        igraph_create(&g,&code,0,1);
        for(int i = 0 ; i<cvector_size(data_trichdan); i++)
        {
            igraph_get_shortest_path_dijkstra(&g,&v,&e,atoi(argv[3]),data_trichdan[i].u,&w,1);
            //print_vector(&v);
            if(igraph_vector_size(&v) == 3)
                {
                    printf("%s\n",jrb_find_int(i2n,(long int)VECTOR(v)[1])->val.s);
                    printf("%s\n",jrb_find_int(i2n,(long int)VECTOR(v)[2])->val.s);
                    break;
                }
        }
        //printf("%ld\n",print_range(&e,&w));
        //print_vector(&v);
    }
}   