#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <igraph.h>
#include <jrb.h>
#include <debug_printf.h>
#include <cvector.h>
int jset_insert_str(JRB tree, char *key, Jval val) {
    if (jrb_find_str(tree,key)==NULL){
        char *s=(char*)malloc(sizeof(key));
        strcpy(s,key);
        jrb_insert_str(tree,s,val);
        return 1;
    }
    return 0;
}
int main(int argc, char *argv[]) {
    if (argc==1) {
        printf("-1");
        return 0;
    }
    JRB j1 = make_jrb();
    JRB j2 = make_jrb();
    FILE *inp = fopen("/home/phungson/hyouteisan/ex/inp.txt","r");
    char get1[11],get2[12];
    int i=0, check, count=0, take, x=0, sum=0;
    cvector_vector_type(int) z = NULL;
    cvector_vector_type(int) w = NULL;
    while(!feof(inp)){
        if(feof(inp)) break;
        fscanf(inp,"%s",get1);
        fscanf(inp,"%s",get2);
        fscanf(inp,"%d",&take);
        printfInfo("%s %s %d\n",get1,get2,take);
        x++;
        check = jset_insert_str(j1, get1, (Jval){.i = i});
        if(check){
            count++;
            jrb_insert_int(j2,i,(Jval){.s=strdup(get1)});
            ++i;
        }
        cvector_push_back(z, (jrb_find_str(j1,get1))->val.i );
        check = jset_insert_str(j1, get2, (Jval){.i = i});
        if(check){
            count++;
            jrb_insert_int(j2,i,(Jval){.s=strdup(get2)});
            ++i;
        }
        cvector_push_back(z, (jrb_find_str(j1,get2))->val.i );
        cvector_push_back(w, take);
    }
    igraph_vector_t weights;
    igraph_vector_init(&weights, x);
    igraph_vector_t v;
    igraph_vector_init(&v, 0);
    igraph_vector_t e;
    igraph_vector_init(&e, 0);
    igraph_t g;
    igraph_create(&g, &v, count, IGRAPH_UNDIRECTED);
    for (size_t i=0;i<cvector_size(z)-1;i+=2)
        igraph_add_edge(&g,z[i],z[i+1]);
    for (size_t i=0; i<cvector_size(w); i++)
        VECTOR(weights)[i] = w[i];
    JRB tm;
    tm = (jrb_find_str(j1,argv[1])) ;
    if (tm==NULL) {
        printf("-1");
        return 0;
    }
    igraph_integer_t from = tm->val.i;
    tm = (jrb_find_str(j1,argv[2])) ;
    if (tm==NULL) {
        printf("-1");
        return 0;
    }
    igraph_integer_t to = tm->val.i;
    if (from==to) {
        printf("0\n%s ",jrb_find_int(j2,from)->val.s);
        return 0;
    }
    else {
        igraph_get_shortest_path_dijkstra(&g,&v,&e,from,to,&weights,IGRAPH_ALL);
        if(igraph_vector_size(&v)==1) {
        printf("-1");
        return 0;
    }
    for (long int i = 0; i < igraph_vector_size(&e); ++i)
        sum+= (long int)VECTOR(weights)[ (long int)VECTOR(e)[i] ];
    printf("%d\n",sum);
    for (long int i = 0; i < igraph_vector_size(&v); ++i) {
        JRB tmp = jrb_find_int(j2,(long int)VECTOR(v)[i]);
        printf("%s ",tmp->val.s);
    }
    }
    cvector_free(z);
    cvector_free(w);
    igraph_destroy(&g);
    igraph_vector_destroy(&v);
    igraph_vector_destroy(&e);
    igraph_vector_destroy(&weights);
    fclose(inp);
    return 0;
}