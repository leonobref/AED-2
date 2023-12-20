#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>
#include <limits>
using namespace  std;
typedef unsigned int Vertex;
typedef float Weight;

float inf = numeric_limits<float>::infinity();

// class Edge {
//     public:
//         Weight weight;
//         Edge(): weight() {}
//         Edge(Weight _weight): weight(_weight) {}
// };

class WeightedDigraphAM {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Weight **adj;
    public:
        WeightedDigraphAM(unsigned int);
        ~WeightedDigraphAM();
        void add_edge(Vertex, Vertex, Weight);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<Vertex> get_adj(Vertex u);
        Weight get_weight_edge(Vertex u, Vertex v) {return adj[u][v];}
};

WeightedDigraphAM::WeightedDigraphAM(unsigned int num_vertices): num_vertices(num_vertices), num_edges(0){
    const unsigned int LINES = num_vertices;
    const unsigned int COLUMNS = num_vertices;
    adj = new Weight*[LINES];
    for(unsigned int i = 0; i < LINES; ++i){
        adj[i] = new Weight[COLUMNS];
    }

    for(unsigned int i = 0; i < LINES; i++){
        for(unsigned int j = 0; j < COLUMNS; j++){
            adj[i][j] = inf;
        }
    }
}

WeightedDigraphAM::~WeightedDigraphAM(){
    const unsigned int LINES = num_vertices;
    for(unsigned int i = 0; i < LINES; ++i){
        delete[] adj[i];
    }
    delete[] adj;
}

void WeightedDigraphAM::add_edge(Vertex u, Vertex v, Weight w){
    if (u == v)
        return;
    Weight edge{w};
    if(adj[u][v] != inf)
        return;
    adj[u][v] = edge;
    num_edges++;
}

void WeightedDigraphAM::remove_edge(Vertex u, Vertex v){
    Weight edge{inf};
    if(adj[u][v] == inf)
        return;
    adj[u][v] = edge;
    num_edges--;
}

list<Vertex>WeightedDigraphAM::get_adj(Vertex u){
    list<Vertex> values;
    for(unsigned int v = 0; v < num_vertices; ++v){
        if(adj[u][v] != 0){
            values.push_back(v);
        }
    }
    return values;
}

void display_matadj_graph(WeightedDigraphAM &g){
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
    // build each line of the matrix
    for(unsigned int i = 0; i < g.get_num_vertices(); i++){
        // Line values
        for(unsigned int j = 0; j < g.get_num_vertices(); j++){
            cout << g.get_weight_edge(i, j) << " ";
        }
        cout << endl;
    }
}

void input_graph(WeightedDigraphAM &g, unsigned int num_edges){
    Vertex u = 0, v = 0;
    Weight w = 0;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
}

int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    WeightedDigraphAM g{num_vertices};
    input_graph(g, num_edges);
    display_matadj_graph(g);

    return 0;
}
// 4 7 0 1 -1.0 1 0 3.1 1 2 1.2 0 2 -1.0 0 3 0.0 3 0 1.4 3 2 6.4
// 10 21 0 1 6.8 0 4 4.4 1 4 6.6 1 5 8.0 1 7 4.0 1 8 3.4 2 4 6.5 2 6 9.6 3 2 7.4 3 5 4.2 3 6 7.8 3 7 6.6 3 8 3.8 4 3 1.7 5 2 6.5 5 8 8.7 7 8 4.3 8 0 5.0 8 9 6.9 9 2 9.9 9 5 2.5 
// 15 53 0 2 10.9 0 3 10.7 0 4 6.2 0 5 10.0 0 8 8.9 0 14 8.4 1 7 10.0 1 10 10.5 1 12 7.6 2 0 3.6 2 9 5.5 2 12 2.0 2 13 3.1 3 0 8.4 3 4 5.8 3 5 11.0 3 7 2.1 3 12 4.4 3 13 5.3 4 3 8.0 4 5 9.9 4 6 9.8 5 4 6.6 5 10 7.2 5 11 3.5 5 13 6.2 6 9 4.2 7 2 4.2 7 8 10.5 7 13 1.7 8 7 4.2 9 1 9.3 9 2 9.1 9 3 2.8 9 4 10.2 10 5 10.7 10 7 1.4 11 3 6.6 11 8 2.2 11 9 8.4 11 10 8.7 11 13 2.2 12 0 6.0 12 1 6.5 12 3 3.2 12 9 5.5 13 3 1.7 13 5 6.1 13 12 3.8 14 3 6.0 14 9 9.7 14 10 10.7 14 11 1.9