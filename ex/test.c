#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#include"c-vector/cvector.h"

void print_vector(igraph_vector_t *v, FILE *f) {
    long int i;
    for (i = 0; i < igraph_vector_size(v); i++) {
        fprintf(f, " %li", (long int) VECTOR(*v)[i]);
    }
    fprintf(f, "\n");
}

int main() {

    igraph_t g;
    igraph_vector_t v, seq;
    int ret;
    igraph_integer_t mdeg, nedges;
    long int i;
    long int ndeg;

    /* Create graph */
    igraph_vector_init(&v, 8);
    VECTOR(v)[0] = 0;
    VECTOR(v)[1] = 1;
    VECTOR(v)[2] = 1;
    VECTOR(v)[3] = 2;
    VECTOR(v)[4] = 2;
    VECTOR(v)[5] = 3;
    VECTOR(v)[6] = 2;
    VECTOR(v)[7] = 2;
    igraph_create(&g, &v, 0, IGRAPH_DIRECTED);

    igraph_degree(&g, &v, igraph_vss_all(), IGRAPH_OUT, IGRAPH_NO_LOOPS);
    print_vector(&v, stdout);
    
    igraph_degree(&g, &v, igraph_vss_all(), IGRAPH_OUT, IGRAPH_LOOPS);
    print_vector(&v, stdout);

    igraph_degree(&g, &v, igraph_vss_all(), IGRAPH_IN, IGRAPH_NO_LOOPS);
    print_vector(&v, stdout);

    igraph_degree(&g, &v, igraph_vss_all(), IGRAPH_IN, IGRAPH_LOOPS);
    print_vector(&v, stdout);

    igraph_degree(&g, &v, igraph_vss_all(), IGRAPH_ALL, IGRAPH_NO_LOOPS);
    print_vector(&v, stdout);

    igraph_degree(&g, &v, igraph_vss_all(), IGRAPH_ALL, IGRAPH_LOOPS);
    print_vector(&v, stdout);

}