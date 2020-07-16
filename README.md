"%[^:]" => đọc đến dấu 2 chấm thì dừng 

"%*[:]" => xóa hết dấu : ở đầu buffer của scanf, k lưu vào gì cả

" %[^>\n]s" => bỏ qua các khoảng trắng hoặc \n (nếu có) ở đầu buffer, rồi đọc cho đến \n hoặc > lưu vào chuỗi đọc được vào s

"%*[>]" => như "%*[:]"

"%[\n]" => Gần giống " %[^\n]s".
Khác ở chỗ là nếu có \n ở đầu thì nó vẫn đọc. 
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "igraph/igraph.h"

igraph_t graph;    //khởi tạo đồ thị

igraph_vector_t vector;        //khởi tạo vector đồ thị
igraph_vector_init( &vector, 0 );


graph_destroy( &graph );   //free graph
igraph_vector_destroy( &vector );  //free vector


igraph_integer_t int;  //biến kiểu số nguyên trong igraph


igraph_vector_push_back( &vector, int ); //thêm vào vector một phần tử  kiểu nguyên


igraph_add_edge( &graph, from, to ); //thêm 1 cạnh from -> to vào đồ thị


igraph_read_graph_edgelist( &graph, file, 0, IGRAPH_DIRECTED);  //đọc danh sách cạnh từ file và tạo đồ thị
                                    //con trỏ tới file 


igraph_create( &graph, &edge, vertix_num, IGRAPH_UNDIRECTED );   //tạo đồ thị từ 1 danh sách cạnh
                      //danh sách cạnh       
                             //số lượng đỉnh
                                         //vô hướng hay có hướng ( IGRAPH_DIRECTED )


igraph_is_dag(&graph,&res);  //đồ thị DAG / không chu trình , có hướng hay không
                     // trả về TRUE/1 hoặc FALSE/0


igraph_topological_sorting(&graph,&vector,IGRAPH_OUT); //sắp xếp đồ thị DAG theo kiểu topo, đưa ra thứ tự thực hiện
                                   //vector lưu kết quả sắp xếp thứ tự đỉnh
                                          //kết quả theo chiều xuôi, ngược với IGRAPH_IN 


igraph_get_shortest_path_dijkstra( &graph, &vector, &edge, from, to, &weights, IGRAPH_ALL );
                                           //vector lưu kết quả sắp xếp thứ tự đỉnh
                                                    //vector kết quả sắp xếp theo id cạnh
                                                           //id đỉnh nguồn
                                                                  //id đỉnh đích
                                                                       //vector trọng số lần lượt theo id cạnh ở trên
                                                                               //vô hướng, lấy có hướng xuôi với IGRAPH_OUT, ngược với IGRAPH_IN


for ( long int i = 0; i < igraph_vector_size(&vector); i++ ) {        //duyệt vector igraph
     printf(" %li ", (long int)VECTOR(vector)[i] );              //in phần tử trong vector
}



////////////////////////////////////////////////////////////////////////////////////////////////////
#include "c-vector/cvector.h"

cvector_vector_type(int) vector = NULL;          //khởi tạo vector thuộc một kiểu nào đó

cvector_free(vector);              //free vector

cvector_push_back(vector, int);           //thêm 1 phần tử mới vào sau

cvector_pop_back(vector);          //bỏ 1 phần tử ở cuối


printf("pointer : %p\n", (void *)vector );                    //in con trỏ
printf("capacity: %lu\n", cvector_capacity(vector) );          //in capacity
printf("size    : %lu\n", cvector_size(vector) );              //in size


if (vector) {
	size_t i;
	for (i = 0; i < cvector_size(vector); ++i) {                 //duyệt kiểu index như mảng thông thường
		printf("vector[%lu] = %d\n", i, vector[i]);
	}
}


if (vector) {
	int *it;
	int i = 0;
	for (it = cvector_begin(vector); it != cvector_end(vector); ++it) {             //duyệt kiểu con trỏ
		printf("vector[%d] = %d\n", i, *it);
		++i;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
#include "libfdr/jrb.h"

JRB j = make_jrb(); //khởi tạo 

for (JRB iter = jrb_begin(j); iter != jrb_end(j); jrb_move(iter))  //clean up
     free(iter->key.s);
jrb_free_tree(j); //free tree


JRB jrb_insert_str(JRB tree, char *key, Jval val);             //các hàm insert key và val vào cây jrb
JRB jrb_insert_int(JRB tree, int ikey, Jval val);
JRB jrb_insert_dbl(JRB tree, double dkey, Jval val);
JRB jrb_insert_gen(JRB tree, Jval key, Jval val, int (*func)(Jval,Jval));


JRB jrb_find_str(JRB root, char *key);                         //các hàm tìm kiếm theo key
JRB jrb_find_int(JRB root, int ikey);
JRB jrb_find_dbl(JRB root, double dkey);
JRB jrb_find_gen(JRB root, Jval, int (*func)(Jval, Jval));


for(JRB ptr = jrb_first(j); ptr != jrb_nil(j); ptr = jrb_next(ptr))        //duyệt jrb tree
      printf("%s\n",ptr->key.s);


int jset_insert_str(JRB tree, char *key, Jval val) { // hàm kiểm tra key đã tồn tại chưa, nếu chưa thì insert vào 1 bản sao nhờ strdup
    if (jrb_find_str(tree,key)==NULL){
        jrb_insert_str(tree,strdup(key),val);
        return 1;
    }
    return 0;
}

jset_insert_str(j, key, (Jval){.i = i}); //tạo nhanh 1 biến jval có jval.i = i;


////////////////////////////////////////////////////////////////////////////////////////////////////
#include "libfdr/jval.h"

  Jval new_jval_i(int);                   //khởi tạo 1 biến Jval với các kiểu khác nhau
  Jval new_jval_l(long);
  Jval new_jval_f(float);
  Jval new_jval_d(double);
  Jval new_jval_v(/* void */);
  Jval new_jval_s(char *);
  Jval new_jval_c(char);

  int jval_i(Jval);                       //lấy giá trị từ biến Jval
  long jval_l(Jval);
  float jval_f(Jval);
  double jval_d(Jval);
  void *jval_v(Jval);
  char *jval_s(Jval);
  char jval_c(Jval);

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "libfdr/dllist.h"

typedef struct dllist {
  struct dllist *flink;
  struct dllist *blink;
  Jval val;
} *Dllist;

Dllist list = new_dllist(); //khởi tạo
free_dllist(list); // free dllist

for (ptr = list->flink; ptr != list; ptr = ptr->flink) { //duyệt xuôi
};

for (ptr = list->blink; ptr != list; ptr = ptr->blink) { //duyệt ngược
};



////////////////////////////////////////////////////////////////////////////////////////////////////
#include "libfdr/fields.h"

typedef struct inputstruct {                         //Cấu trúc của con trỏ IS thao tác file
  char *name;               /* File name */
  FILE *f;                  /* File descriptor */
  int line;                 /* Line number */
  char text1[MAXLEN];       /* The line */
  char text2[MAXLEN];       /* Working -- contains fields */
  int NF;                   /* Number of fields */
  char *fields[MAXFIELDS];  /* Pointers to fields */
  int file;                 /* 1 for file, 0 for popen */
} *IS;

IS is;        //khởi tạo con trỏ

jettison_inputstruct(is);          //free

is = new_inputstruct(FILENAME);          //đường dẫn file, nếu đọc STDIN thì để là NULL

while (get_line(is) >= 0) {        //lấy dữ liệu từng dòng cho đến hết file

is->text1;           //dữ liệu trong dòng


};


////////////////////////////////////////////////////////////////////////////////////////////////////

char* trim(char* token){   //lọai bỏ khoảng trắng thừa đầu cuối
  while (isspace((unsigned)token[0])) token++;
  while (isspace((unsigned)token[strlen(token)-1])) token[strlen(token)-1] = '\0';
  return strdup(token);
}

int **matrix;
    matrix = (int**)malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++)
        matrix[i] = (int*)malloc(sizeof(int)*n);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            matrix[i][j]=0;