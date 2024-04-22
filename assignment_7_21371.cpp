#include <iostream>

using namespace std;

struct Edge {
    int src, dest, weight;

    Edge() {}
    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

struct DisjointSet {
    int *parent, *rank;
    int n;

    DisjointSet(int n) : n(n) {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return;
        }

        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootU] = rootV;
            if (rank[rootU] == rank[rootV]) {
                rank[rootV]++;
            }
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }
};

struct Graph {
    int V, E;
    Edge* edges;

    Graph(int V, int E) : V(V), E(E) {
        edges = new Edge[E];
    }

    void addEdge(int index, int src, int dest, int weight) {
        edges[index].src = src;
        edges[index].dest = dest;
        edges[index].weight = weight;
    }

    ~Graph() {
        delete[] edges;
    }
};

void push(Edge *heap[], int& size, Edge edge) {
    heap[size++] = new Edge(edge);
    int i = size - 1;

    while (i > 0) {
        int parent_idx = (i - 1) / 2;
        if (heap[parent_idx]->weight > heap[i]->weight) {
            swap(heap[parent_idx], heap[i]);
            i = parent_idx;
        } else {
            break;
        }
    }
}

Edge* pop_min(Edge *heap[], int& size) {
    Edge* min_item = heap[0];
    heap[0] = heap[--size];
    int i = 0;

    while (true) {
        int left_child_idx = 2 * i + 1;
        int right_child_idx = 2 * i + 2;
        int smallest_idx = i;

        if (left_child_idx < size && heap[left_child_idx]->weight < heap[smallest_idx]->weight) {
            smallest_idx = left_child_idx;
        }

        if (right_child_idx < size && heap[right_child_idx]->weight < heap[smallest_idx]->weight) {
            smallest_idx = right_child_idx;
        }

        if (smallest_idx != i) {
            swap(heap[i], heap[smallest_idx]);
            i = smallest_idx;
        } else {
            break;
        }
    }

    return min_item;
}

void kruskalMST(Graph* graph, int V, int E) {
    Edge** heap = new Edge*[E];
    int heap_size = 0;

    for (int i = 0; i < E; ++i) {
        push(heap, heap_size, graph->edges[i]);
    }

    DisjointSet ds(V);

    Edge* result = new Edge[V - 1];
    int e = 0;

    while (e < V - 1 && heap_size > 0) {
        Edge* next_edge = pop_min(heap, heap_size);

        int x = ds.find(next_edge->src);
        int y = ds.find(next_edge->dest);

        if (x != y) {
            result[e++] = *next_edge;
            ds.unite(x, y);
        }

        delete next_edge;
    }

    int totalCost = 0;
    for (int i = 0; i < e; ++i) {
        totalCost += result[i].weight;
    }

    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < e; ++i) {
        cout << result[i].src << " - " << result[i].dest << " : " << result[i].weight << endl;
    }
    cout << "Total cost: " << totalCost << endl;

    delete[] heap;
    delete[] result;
}

void menu() {
    int V, E;
    cout << "Enter the number of offices (V): ";
    cin >> V;
    cout << "Enter the number of phone lines (E): ";
    cin >> E;

    Graph* graph = new Graph(V, E);

    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cout << "Enter source office, destination office, and cost of phone line " << i + 1 << ": ";
        cin >> src >> dest >> weight;
        graph->addEdge(i, src, dest, weight);
    }

    kruskalMST(graph, V, E);

    delete graph;
}

int main() {
    menu();
    return 0;
}
