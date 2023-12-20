#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>

using namespace std;
typedef unsigned int Vertex;

typedef unsigned int Weight;

class Edge {
public:
	Weight weight;
	Edge(): weight(0) {} 
	Edge(Weight _weight): weight(_weight) {} 
};


class DigraphAM {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;
    public:
        DigraphAM(unsigned int);
        ~DigraphAM();
        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex u, Vertex v){return adj[u][v].weight;}
};

DigraphAM::DigraphAM(unsigned int num_vertices): num_vertices(num_vertices), num_edges(0){
    const unsigned int LINES = num_vertices;
    const unsigned int COLUMNS = num_vertices;
    adj = new Edge*[LINES];
    for(unsigned int i = 0; i < LINES; i++){
        adj[i] = new Edge[COLUMNS];
    }
}

DigraphAM::~DigraphAM(){
    const unsigned int LINES = num_vertices;
    for(unsigned int i = 0; i < LINES; ++i){
        delete[] adj[i];
    }
    delete[] adj;
}

void DigraphAM::add_edge(Vertex u, Vertex v){
    if (u == v)
        return;
    Edge edge{1};
    if(adj[u][v].weight == 1)
        return;
    adj[u][v] = edge;
    num_edges++;
}

void DigraphAM::remove_edge(Vertex u, Vertex v){
    Edge edge{0};
    if(adj[u][v].weight == 0)
        return;
    adj[u][v] = edge;
    num_edges--;
}

list<Vertex>DigraphAM::get_adj(Vertex u){
    list<Vertex> values;
    for(unsigned int v = 0; v < num_vertices; ++v){
        if(adj[u][v].weight != 0){
            values.push_back(v);
        }
    }
    return values;
}

void display_matadj_graph(DigraphAM &g){
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;

    for(unsigned int i = 0; i < g.get_num_vertices(); i++){
        // Line values
        for(unsigned int j = 0; j < g.get_num_vertices(); j++){
            cout << g.get_weight_edge(i, j) << " ";
        }
        cout << endl;
    }
}

void input_graph(DigraphAM &g, unsigned int num_edges) {
    Vertex u = 0, v = 0;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v;
        g.add_edge(u, v);
    }
}

int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;

    DigraphAM g{num_vertices};
    input_graph(g, num_edges);
    display_matadj_graph(g);

    return 0;
}

// 4 7 0 1 1 0 1 2 0 2 0 3 3 0 3 2
// 4 8 0 1 1 0 1 2 0 2 0 3 3 0 3 2 1 0
// 10 15 0 3 0 7 1 8 4 2 5 9 6 0 6 5 7 1 7 2 8 6 8 7 9 0 9 1 9 7 9 8
// 15 24 0 4 0 8 0 10 1 13 2 1 2 7 2 10 3 4 3 8 3 12 3 14 4 6 5 9 6 3 7 9 8 12 10 5 11 1 11 2 11 13 13 0 13 7 14 5 14 7