#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNINITIALISED -1
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
    int *data;
    int len;
    int cap;
} vec_t;

typedef struct {
    vec_t *adj;
    int v;
} graph_t;

void init_graph(graph_t *g, int v);
void add_edge(graph_t *g, int u, int v);
void articulation_points(graph_t *g);
void free_graph(graph_t *g);

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    graph_t g;
    init_graph(&g, n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(&g, u, v);
    }

    articulation_points(&g);
    free_graph(&g);
    return 0;
}

void init_vec(vec_t *v) {
    v->data = NULL;
    v->len = 0;
    v->cap = 0;
}

void resize_vec(vec_t *v) {
    if (!v->cap) {
        v->data = (int *)malloc(sizeof(int));
        v->cap++;
        return;
    }
    v->cap *= 2;
    v->data = (int *)realloc(v->data, sizeof(int) * v->cap);
}

void push_vec(vec_t *v, int d) {
    if (!v)
        init_vec(v);
    if (v->len == v->cap)
        resize_vec(v);
    v->data[v->len++] = d;
}

void init_graph(graph_t *g, int v) {
    g->v = v;
    g->adj = (vec_t *)malloc(v * sizeof(vec_t));
    for (int i = 0; i < v; ++i)
        init_vec(&g->adj[i]);
}

void free_graph(graph_t *g) {
    for (int i = 0; i < g->v; ++i)
        free(g->adj[i].data);
    free(g->adj);
}

void add_edge(graph_t *g, int u, int v) {
    push_vec(g->adj + u, v);
    push_vec(g->adj + v, u);
}

void _articulation_points(graph_t *g, int u, bool *visited,
                          int *disc, int *low,
                          int *time, int parent,
                          bool *is_ap) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++(*time);
    for (int i = 0; i < g->adj[u].len; i++) {
        int v = g->adj[u].data[i];
        if (!visited[v]) {
            children++;
            _articulation_points(g, v, visited, disc, low, time, u, is_ap);

            low[u] = MIN(low[u], low[v]);

            if (parent != UNINITIALISED && low[v] >= disc[u])
                is_ap[u] = true;
        } else if (v != parent) {
            low[u] = MIN(low[u], disc[v]);
        }
    }
    if (parent == UNINITIALISED && children > 1)
        is_ap[u] = true;
}

void articulation_points(graph_t *g) {
    int *disc = (int *)calloc(g->v, sizeof(int));
    int *low = (int *)malloc(sizeof(int) * g->v);
    bool *visited = (bool *)calloc(g->v, sizeof(bool));
    bool *is_ap = (bool *)calloc(g->v, sizeof(bool));
    int time = 0;
    int par = UNINITIALISED;

    for (int i = 0; i < g->v; ++i) {
        if (!visited[i]) {
            _articulation_points(g, i, visited, disc, low, &time, par, is_ap);
        }
    }

    for (int i = 0; i < g->v; ++i) {
        if (is_ap[i]) {
            printf("%d ", i);
        }
    }
    putchar('\n');
    free(disc);
    free(low);
    free(visited);
    free(is_ap);
}
