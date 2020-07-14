#include "igraph/igraph.h"
#include <jrb.h>
#include <jval.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int id = 0;
int size = 0;
int check = 0;
int sizecheck = 0;
int sizeofv=0;
int dinh =0 ;
int jset_insert_str(JRB tree, char *key, Jval val){
    char* m =(char*)malloc(strlen(key)+1);
    strcpy(m,key);
  if(jrb_find_str(tree, m)==NULL)
  {
      jrb_insert_str(tree,m,val);
      return 1;
  }
}
long int tong_trong_so(igraph_vector_t *canh, igraph_vector_t *trongso) {
    long int i,a; 
    long int sum = 0;
    for (i = 0; i < igraph_vector_size(canh); i++) {
        a=(long int) VECTOR(*canh)[i];
        sum += (long int)VECTOR(*trongso)[a];
    }
    return sum;
}
void print_vector_dinh(igraph_vector_t *v,JRB tree) {
    long int i,a; 
    JRB p;
    for (i = 0; i < igraph_vector_size(v); i++) {
        a=(long int) VECTOR(*v)[i];
        p = jrb_find_int(tree,a);
        printf("%s ",p->val.s);
    }
    printf("\n");
}
void print_vector_canh(igraph_vector_t *v) {
    long int i,a; 
    for (i = 0; i < igraph_vector_size(v); i++) {
        a=(long int) VECTOR(*v)[i];
        printf("%ld ",a);
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    JRB key_id = make_jrb();
    JRB id_key = make_jrb();
    igraph_vector_t trongso;
    igraph_vector_t dinh;
    igraph_vector_t canh;
    igraph_vector_t v;
    char word[11];
    JRB q;
    int i=0,j=0;
    igraph_t g;
    igraph_bool_t isdag;
    FILE *p;
    if((p=fopen("/home/phungson/hyouteisan/ex/inp.txt","r"))==NULL)
        {
            printf("Loi ko mo file\n");
            return -1;
        }
    while(fscanf(p,"%s",word) != EOF)
    {
        size++;
        if(size%3 != 0){
        sizeofv ++;
        check = jset_insert_str(key_id,word,(Jval){.i = id});
        if(check == 1)
        {
            char* s =(char*)malloc(strlen(word)+1);
            strcpy(s,word);
            jrb_insert_int(id_key,id,(Jval){.s=s});  
            id++;
            check =0;
        }
        }
    }
    
    igraph_vector_init(&v,sizeofv);
    igraph_vector_init(&dinh,sizeofv);
    igraph_vector_init(&canh,sizeofv/2);
    igraph_vector_init(&trongso,sizeofv/2);
    fclose(p);
    if((p=fopen("/home/phungson/hyouteisan/ex/inp.txt","r"))==NULL)
        {
            printf("Loi ko mo file\n");
            return -1;
        }
    while(fscanf(p,"%s",word) != EOF)
    {
        sizecheck++;
        if(sizecheck % 3 !=0)
        {
        q = jrb_find_str(key_id,word);
        VECTOR(v)[i]=q->val.i;
        i++;
        }
        else{
            VECTOR(trongso)[j]=atoi(word);
            j++;
        }
    }
    igraph_create(&g,&v,0,1);
    igraph_is_dag(&g,&isdag);
    if(!isdag)
        {
            printf("-1");
            return -1;
        }
    q = jrb_find_str(key_id,*(argv+1));
    i=q->val.i;
    q = jrb_find_str(key_id,*(argv+2));
    j=q->val.i;
    if(!igraph_get_shortest_path_dijkstra(&g,&dinh,&canh,i,j,&trongso,1))
    {
    printf("%li\n",tong_trong_so(&canh,&trongso));
    print_vector_dinh(&dinh,id_key);
    print_vector_canh(&canh);
    }
    else
    {
        printf("%d",-1);
    }
    igraph_destroy(&g);
    jrb_free_tree(key_id);
    jrb_free_tree(id_key);
    fclose(p);  
}