#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#include"c-vector/cvector.h"
#define MAX 1000
igraph_t g;
igraph_vector_t code;
igraph_vector_t v;
igraph_vector_t e;
igraph_vector_t w;
JRB dns_to_id;
JRB id_to_dns;
int so_web;
int so_canh = 0;
long int print_range(igraph_vector_t *e, igraph_vector_t *w) {
    long int i,a; 
    long int sum = 0;
    for (i = 0; i < igraph_vector_size(e); i++) {
        a=(long int) VECTOR(*e)[i];
        sum += (long int)VECTOR(*w)[a];    
    }
    return sum;
}
void docfile()
{
    char a[MAX];
    int id;
    dns_to_id = make_jrb();
    id_to_dns = make_jrb();
    FILE* p = fopen("/home/phungson/hyouteisan/ex/dns/webpages.txt","r");
    fscanf(p,"%d",&so_web);
    while(fscanf(p,"%s",a)!= EOF)
    {
        fscanf(p,"%d",&id);
        jrb_insert_str(dns_to_id,strdup(a),(Jval){.i=id});
        jrb_insert_int(id_to_dns,id,(Jval){.s=strdup(a)});
    }
    fclose(p);
    
}
void print_vector(igraph_vector_t *v) {
    long int i; 
    for (i = 0; i < igraph_vector_size(v); i++) {
        printf("%ld ",(long int) VECTOR(*v)[i]);
    }
    printf("\n");
}
int case1()
{
    char b[MAX];
    FILE* p = fopen("/home/phungson/hyouteisan/ex/dns/webpages.txt","r");
    fscanf(p,"%d",&so_web);
    printf("So luong webpage la: %d\n",so_web);
    printf("Url cua tung web va id tuong ung:");
    while (fgets(b,MAX,p))
    {
        puts(b);
    }
    fclose(p);
}
int case2()
{
    docfile();
    char b[MAX];
    int a,c;
    igraph_vector_init(&code,0);
    FILE* p = fopen("/home/phungson/hyouteisan/ex/dns/pageConnections.txt","r");
    while (fgets(b,MAX,p))
    {
        FILE* h = fopen("/home/phungson/hyouteisan/ex/dns/new.txt","w");
        fputs(b,h);
        fclose(h);
        h = fopen("/home/phungson/hyouteisan/ex/dns/new.txt","r");
        fscanf(h,"%d",&a);
        while(fscanf(h,"%d",&c) != EOF)
        {
            igraph_vector_push_back(&code,a);
            igraph_vector_push_back(&code,c);
        }
        fclose(h);
    }
    fclose(p);
    igraph_create(&g,&code,0,1);
    igraph_degree(&g,&code, igraph_vss_all(), IGRAPH_IN, IGRAPH_NO_LOOPS);
    int max = VECTOR(code)[0];
    int webmax;
    for (int i = 0; i < igraph_vector_size(&code); i++) {
        if (VECTOR(code)[i] > max)
        {
            max = VECTOR(code)[i];
            webmax = i;
        }   
    }
    printf("Web co nhieu lien ket toi nhat la: %s\n",jrb_find_int(id_to_dns,webmax)->val.s);
    int min = VECTOR(code)[webmax];
    int webmin;
 for (JRB ptr = jrb_first(dns_to_id); ptr != jrb_nil(dns_to_id); ptr = jrb_next(ptr)) {
        for (int j = 0; j < igraph_vector_size(&code); j++) {
            if(j == ptr->val.i && VECTOR(code)[j] < min)
                {
                    min = VECTOR(code)[j];
                    webmin = j;
                }
        }
    }
    printf("Web co it lien ket toi nhat la: %s\n",jrb_find_int(id_to_dns,webmin)->val.s);
    igraph_vector_destroy(&code);
    //print_vector(&code);
}
int case4()
{
    docfile();
    igraph_vector_init(&v,0);
     igraph_vector_init(&e,0);
    char b[MAX];
    int a,c;
    igraph_vector_init(&code,0);
    FILE* p = fopen("/home/phungson/hyouteisan/ex/dns/pageConnections.txt","r");
    while (fgets(b,MAX,p))
    {
        FILE* h = fopen("/home/phungson/hyouteisan/ex/dns/new.txt","w");
        fputs(b,h);
        fclose(h);
        h = fopen("/home/phungson/hyouteisan/ex/dns/new.txt","r");
        fscanf(h,"%d",&a);
        while(fscanf(h,"%d",&c) != EOF)
        {
            igraph_vector_push_back(&code,a);
            igraph_vector_push_back(&code,c);
        }
        fclose(h);
    }
    fclose(p);
    int sum1 = 0;
    int sum2 = 0;
    igraph_create(&g,&code,0,1);
    igraph_degree(&g,&v, igraph_vss_all(), IGRAPH_OUT, IGRAPH_NO_LOOPS);
    for (JRB ptr = jrb_first(dns_to_id); ptr != jrb_nil(dns_to_id); ptr = jrb_next(ptr)) {
        for (int j = 0; j < igraph_vector_size(&v); j++) {
            if(j == ptr->val.i && VECTOR(v)[j] == 0)
                {
                    sum1 ++;
                }
        }
    }
    //print_vector(&v);
    printf("So luong chi co den ma khong co ra la: %d\n",sum1);
    igraph_degree(&g,&e, igraph_vss_all(), IGRAPH_IN, IGRAPH_NO_LOOPS);
    for (JRB ptr = jrb_first(dns_to_id); ptr != jrb_nil(dns_to_id); ptr = jrb_next(ptr)) {
        for (int j = 0; j < igraph_vector_size(&e); j++) {
            if(j == ptr->val.i && VECTOR(e)[j] == 0)
                {
                    sum2 ++;
                }
        }
    }
    printf("So luong chi co ra ma khong co den la: %d\n",sum2);
    igraph_vector_destroy(&code);
    igraph_vector_destroy(&v);
    igraph_vector_destroy(&e);
}
int case5()
{
    int id1,id2;
    printf("Nhap vao id dinh 1: ");
    scanf("%d",&id1);
    printf("Nhap vao id dinh 2: ");
    scanf("%d",&id2);
    docfile();
    char b[MAX];
    int a,c;
    igraph_vector_init(&code,0);
    igraph_vector_init(&w,0);
    FILE* p = fopen("/home/phungson/hyouteisan/ex/dns/pageConnections.txt","r");
    while (fgets(b,MAX,p))
    {
        FILE* h = fopen("/home/phungson/hyouteisan/ex/dns/new.txt","w");
        fputs(b,h);
        fclose(h);
        h = fopen("/home/phungson/hyouteisan/ex/dns/new.txt","r");
        fscanf(h,"%d",&a);
        while(fscanf(h,"%d",&c) != EOF)
        {
            igraph_vector_push_back(&code,a);
            so_canh++;
            igraph_vector_push_back(&code,c);
            igraph_vector_push_back(&w,1);
        }
        fclose(h);
    }
    igraph_vector_init(&v,so_canh*2);
    igraph_vector_init(&e,so_canh);
    fclose(p);
    igraph_create(&g,&code,0,1);
    igraph_get_shortest_path_dijkstra(&g,&v,&e,id1,id2,&w,1);
    if(igraph_vector_size(&v) == 1)
    {
        printf("khong ton tai duong di\n");
        return -1;
    }
    else
    {
        print_vector(&v);
        printf("Khoang cach nho nhat la: %ld\n",print_range(&e,&w));
    }
    
}
int main(){
    int chon;
    while (1)
    {  
    printf("1. So luong webpage va url cua tung webpage.\n");
    printf("2. Thuat toan PageRank\n");
    printf("3. Thuat toan PageRank sau m lan lap\n");
    printf("4. So luong webpage chi co lien ket den va so luong cac spam bot\n");
    printf("5. Khoang cach nho nhat tu webpage co id1 toi webpage co id2\n");
    printf("6. Thoat\n");
    printf("Chon so tuong ung: ");
    scanf("%d",&chon);
    switch (chon)
    {
    case 1 : case1(); break; 
    case 2 : case2(); break;
    //case 3 : case3(); break;
    case 4 : case4(); break;
    case 5 : case5(); break;
    case 6: break; 
    default: printf("So ban chon khong co trong menu. Moi nhap lai\n");break;
    }
    if(chon == 6) break;
    }
}   