#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 10000
int main(int argc, char *argv[])
{

}
for(JRB ptr = jrb_first(id_to_name);ptr != jrb_nil(id_to_name);ptr = jrb_next(ptr))
        {
            printf("%s %d\n",ptr->val.s,ptr->key.i);
        }

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
void print_vector(igraph_vector_t *v) {
    long int i; 
    for (i = 0; i < igraph_vector_size(v); i++) {
        printf("%ld\n",(long int) VECTOR(*v)[i]);
    }
    printf("\n");
}
igraph_degree(&g, &code, igraph_vss_all(), IGRAPH_OUT, IGRAPH_NO_LOOPS);
igraph_create(&g,&code,0,1);

igraph_get_shortest_path_dijkstra(&g,&v,&e,atoi(argv[3]),data_trichdan[i].u,&w,1);
6
1 11.11.11.11
2 22.22.22.22
3 33.33.33.33
5 55.55.55.55
8 88.88.88.88
9 99.99.99.99
7
1 2 400
1 3 200
2 5 300
2 8 300
3 8 300
5 9 200
8 9 100