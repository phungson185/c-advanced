#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libfdr/jrb.h"
#include "c-vector/cvector.h"
#include "mylib/containers.h"
#include "DebugPrintf/debug_printf.h"
#include "igraph/igraph.h"

typedef struct {
  char *station;
  char *route;
} BStop;

int prints(void *key, void *val, void *u) {
  printfInfo("%s:%s", ((Jval*)key)->s, (char*)u);
  return 0;
}

int collect_id(void *key, void *val, void *u) {
  igraph_vector_t *tmp = (igraph_vector_t*)u;
  int id = ((Jval*)val)->i;
  igraph_vector_push_back(tmp, id);
  return 0;
}

int transfer_to_igraph(void *val, void *u) {
  int value = *(int*)val;
  igraph_vector_push_back((igraph_vector_t*)u, value);
  return 0;
}

int print_bstop(void *key, void *val, void *u) {
  BStop *bstop = ((Jval*)val)->v;
  printfInfo("%d: (%s, %s)",
      ((Jval*)key)->i,
        bstop->station, bstop->route);
}

JRB stations = NULL;
JRB id_bstop = NULL;
cvector_vector_type(int) from = NULL;
cvector_vector_type(int) to = NULL;
cvector_vector_type(int) w = NULL;
const int kNext = 1;
const int kChange = 100000;
int vertices_count = 0;

void free_id_bstop() {
  JRB ptr;
  jrb_traverse(ptr, id_bstop) {
    BStop *bs = (BStop*)ptr->val.v;
    free(bs->station);
    free(bs->route);
    free(bs);
  }
  jrb_free_tree(id_bstop);
}

void free_stations() {
  JRB ptr;
  jrb_traverse(ptr, stations) {
    JRB routes_on_stop = ptr->val.v;
    JRB r;
    jrb_traverse(r, routes_on_stop) {
      free(r->key.s);
    }
    jrb_free_tree(r);
    free(ptr->key.s);
  }
  jrb_free_tree(stations);
}

int read_input(const char *inp_name) {
  stations = make_jrb();
  id_bstop = make_jrb();
  char stop[1000];
  char route[100];
  FILE *f = fopen(inp_name, "r");
  int id = 0;
  while(!feof(f)) {
    fscanf(f, "%[^:]", route);
    fscanf(f, "%*[:]");
    int first = 1;
    int prev, curr;
    while (fscanf(f, " %[^>\n]s", stop) > 0) {
      int len = strlen(stop);
      while (isspace(stop[len - 1]) && len > 0) {
        stop[len - 1] = '\0';
        --len;
      }
      JRB node = jrb_find_str(stations, stop);
      JRB routes_on_stop = NULL;
      if (node) {
        routes_on_stop = node->val.v;
        printfInfo("found station! on %s", stop);
        jrb_foreach(routes_on_stop, prints, stop);
      } else {
        routes_on_stop = make_jrb();
        jrb_insert_str(stations, strdup(stop),
          (Jval){.v = routes_on_stop});
      }
      node = jrb_find_str(routes_on_stop, route);
      if (node) {
        printfError("Duplicate station on route %s (%s)", route, stop);
        return 1;
      } else {
        jrb_insert_str(routes_on_stop, strdup(route), (Jval){.i = id});
        printfInfo("(%s, %s):%d", stop, route, id);
        BStop *bstop = (BStop*)malloc(sizeof(BStop));
        bstop->station = strdup(stop);
        bstop->route = strdup(route);
        jrb_insert_int(id_bstop, id, (Jval){.v = bstop});
        printfInfo("%s - %s", bstop->station, bstop->route);
        jrb_foreach(routes_on_stop, prints, stop);
        if (first) {
          prev = id;
          first = 0;
        } else {
          curr = id;
          cvector_push_back(from, prev);
          cvector_push_back(to, curr);
          cvector_push_back(w, kNext);
          prev = curr;
          printfInfo("Edge(%d, %d):%d",
                from[cvector_size(from) - 1],
                to[cvector_size(to) - 1],
                w[cvector_size(w) - 1]);
        }
        ++id;
      }
      fscanf(f, "%*[>]");
      if (fscanf(f, "%[\n]", stop) > 0) {
        first = 1;
        break;
      }
    }
  }
  fclose(f);
  vertices_count = id;
  return 0;
}

void define_route_change() {
  for (jrb_iter iter = jrb_begin(stations);iter != jrb_end(stations); jrb_move(iter)) {
    JRB routes = iter->val.v;
    for (jrb_iter i1 = jrb_begin(routes);i1 != jrb_end(routes); jrb_move(i1)) {
      for (jrb_iter i2 = jrb_begin(routes);i2 != jrb_end(routes); jrb_move(i2)) {
        if (i1 != i2) {
          cvector_push_back(from, i1->val.i);
          cvector_push_back(to, i2->val.i);
          cvector_push_back(w, kChange);
          printfInfo("Edge(%d, %d):%d",
                from[cvector_size(from) - 1],
                to[cvector_size(to) - 1],
                w[cvector_size(w) - 1]);
        }
      }
    }
  }
}

igraph_vector_t ifrom, ito;

int identify_station(igraph_vector_t *v, char *station) {
  JRB node = jrb_find_str(stations, station);
  if (node) {
    jrb_foreach(((JRB)(node->val.v)), collect_id, v);
    return 0;
  }
  printfError("Station %s not found", station);
  return 1;
}

igraph_t g;

void build_graph() {
  igraph_empty(&g, vertices_count, IGRAPH_DIRECTED);
  int m = cvector_size(from);
  igraph_vector_t edges;
  igraph_vector_init(&edges, 0);
  for (int i = 0; i < m; ++i) {
    igraph_vector_push_back(&edges, from[i]);
    igraph_vector_push_back(&edges, to[i]);
  }
  igraph_add_edges(&g, &edges, 0);
  printfInfo("Số lượng đỉnh: %d \n", igraph_vcount(&g));
  printfInfo("Số lượng cạnh: %d\n", igraph_ecount(&g));
  igraph_vector_destroy(&edges);
}

long min_cost = -1;
cvector_vector_type(cvector_vector_type(int)) paths = NULL;
void free_paths() {
  for (int i = 0; i < cvector_size(paths); ++i) {
    cvector_free(paths[i]);
  }
  cvector_free(paths);
  paths = NULL;
}
void find_shortest_paths() {
  igraph_vector_t weights;
  igraph_vector_init(&weights, 0);
  vec_foreach(w, transfer_to_igraph, &weights);
  igraph_vs_t vs_to;
  igraph_vector_ptr_t vecs, evecs;
  igraph_vector_ptr_init(&vecs, igraph_vector_size(&ito));
  igraph_vector_ptr_init(&evecs, igraph_vector_size(&ito));
  for (int i = 0; i < igraph_vector_ptr_size(&vecs); i++) {
      VECTOR(vecs)[i] = calloc(1, sizeof(igraph_vector_t));
      igraph_vector_init(VECTOR(vecs)[i], 0);
      VECTOR(evecs)[i] = calloc(1, sizeof(igraph_vector_t));
      igraph_vector_init(VECTOR(evecs)[i], 0);
  }
  igraph_vs_vector(&vs_to, &ito);

  for (int f = 0; f < igraph_vector_size(&ifrom); ++f) {
    igraph_get_shortest_paths_dijkstra(&g, &vecs,
      &evecs, VECTOR(ifrom)[f], vs_to,
      &weights, IGRAPH_OUT,
      NULL, NULL);
    long cost = 0;
    for (int i = 0; i < igraph_vector_ptr_size(&vecs); i++) {
        igraph_vector_t *edges = VECTOR(evecs)[i];
        int l = igraph_vector_size(edges);
        for (int i = 0; i < l; ++i) {
          int eid = (int)VECTOR(*edges)[i];
          int ewt = (int)VECTOR(weights)[eid];
          printfInfo(" %d:%d", eid, ewt);
          cost += ewt;
        }
        if (cost < min_cost || min_cost < 0) {
          min_cost = cost;
          free_paths();
        }
        if (cost == min_cost) {
          cvector_vector_type(int) p2 = NULL;
          igraph_vector_t *p = VECTOR(vecs)[i];
          for (int i = 0; i < igraph_vector_size(p); ++i) {
            cvector_push_back(p2, (int)VECTOR(*p)[i]);
          }
          cvector_push_back(paths, p2);
        }
    }
  }
  for (int i = 0; i < igraph_vector_ptr_size(&vecs); i++) {
    igraph_vector_destroy(VECTOR(vecs)[i]);
    free(VECTOR(vecs)[i]);
    igraph_vector_destroy(VECTOR(evecs)[i]);
    free(VECTOR(evecs)[i]);
  }
  igraph_vector_destroy(&weights);
  igraph_vector_destroy(&ifrom);
  igraph_vector_destroy(&ito);
  igraph_vs_destroy(&vs_to);
  igraph_vector_ptr_destroy(&vecs);
  igraph_vector_ptr_destroy(&evecs);
}

void display_output() {
  printf("Min cost is: %li\n", min_cost);
  for (int i = 0; i < cvector_size(paths); ++i) {
    cvector_vector_type(int) p = paths[i];
    for (int j = 0; j < cvector_size(p); ++j) {
      JRB node = jrb_find_int(id_bstop, p[j]);
      BStop *bs = (BStop*)node->val.v;
      printf("%s(%s) > ", bs->station, bs->route);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (read_input(argv[1])) {
    return 1;
  }
  define_route_change();
  igraph_vector_init(&ifrom, 0);
  igraph_vector_init(&ito, 0);
  if (identify_station(&ifrom, argv[2]) ||
      identify_station(&ito, argv[3])) {
    return 1;
  }
  build_graph();
  find_shortest_paths();
  display_output();
  free_id_bstop();
  free_stations();
  free_paths();
  cvector_free(from);
  cvector_free(to);
  cvector_free(w);
  igraph_destroy(&g);
  return 0;
}