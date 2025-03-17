#include "Sets.h"

//zbiory wierzchołków do algorytmu Kruskala
Sets::Sets(int no_of_vertexes) {
    this -> no_of_vertexes = no_of_vertexes;
    parent = new int[no_of_vertexes];
    rank = new int[no_of_vertexes];

    for(int i = 0; i < no_of_vertexes; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

Sets::~Sets() {
    delete[] parent;
    delete[] rank;
}

//szukanie znacznika zbioru krawędzi
int Sets::findSet(int u) {
    if(u != parent[u]) {
        parent[u] = findSet(parent[u]); //kompresja
    }
    return parent[u];
}

//połączenie zbiorów
void Sets::mergeSets(int u, int v) {
    int u_root = findSet(u);
    int v_root = findSet(v);

    if(u_root != v_root) { //korzysta z systemu rang
        if(rank[u_root] < rank [v_root]) {
            parent[u_root] = v_root;
        } else if(rank[u_root] > rank[v_root]) {
            parent[v_root] = u_root;
        } else {
            parent[v_root] = u_root;
            rank[u_root]++;
        }
    }
}
