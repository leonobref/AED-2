#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>

using namespace  std;

typedef unsigned int Vertex;
typedef unsigned int Weight;

class Edge {
public:
	Weight weight;
	Edge(): weight(0) {} 
	Edge(Weight _weight): weight(_weight) {} 
};

class GraphAM {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;
    
    public:
        GraphAM(unsigned int);
        ~GraphAM();
        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices(){return num_vertices;}
        unsigned int get_num_edges(){return num_edges;}
        list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex, Vertex);
};

GraphAM::GraphAM(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0) {
    const unsigned int LINES = num_vertices;
    const unsigned int COLUMNS = num_vertices;
    adj = new Edge*[LINES];
    for(unsigned int i = 0; i < LINES; ++i){
        adj[i] = new Edge[COLUMNS];
    }
}

GraphAM::~GraphAM() {
    const unsigned int LINES = num_vertices;
    for(unsigned int i = 0; i < LINES; ++i){
        delete[] adj[i];
    }
    delete[] adj;
}

void GraphAM::add_edge(Vertex u, Vertex v){
    if (u == v)
        return;
    Edge edge{1};
    if(adj[u][v].weight == 1)
        return;
    if(adj[v][u].weight == 1)
        return;
    adj[u][v] = edge;
    adj[v][u] = edge;
    num_edges++;
}

void GraphAM::remove_edge(Vertex u, Vertex v) {
    Edge edge{0};
    if(adj[u][v].weight == 0){
        return;
    }
    adj[u][v] = edge;
    adj[v][u] = edge;
    num_edges--;
}

list<Vertex> GraphAM::get_adj(Vertex u) {
    list<Vertex> values;
    for(unsigned int v = 0; v < num_vertices; ++v){
        if(adj[u][v].weight != 0){
            values.push_back(v);
        }
    }
    return values;
}

Weight GraphAM::get_weight_edge(Vertex u, Vertex v) {
    return adj[u][v].weight;
}

void display_matadj_graph(GraphAM &g) {
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

void input_graph(GraphAM &g, unsigned int num_edges) {
    Vertex u = 0, v = 0;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v;
        g.add_edge(u, v);
    }
}

int main()
{
    unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	cin >> num_vertices >> num_edges;
    GraphAM g{num_vertices};
    input_graph(g, num_edges);
    display_matadj_graph(g);

    return 0;
    
}

// 9 12 0 1 0 2 0 3 1 4 2 4 3 4 4 5 4 6 4 7 5 8 6 8 7 8
// 10 15 0 1 0 6 1 4 1 5 1 6 1 9 2 6 3 4 3 7 3 9 4 6 5 7 5 8 5 9 6 9
// 15 29 0 9 0 11 0 12 0 14 1 6 1 7 1 11 2 4 2 6 2 7 2 12 3 5 3 11 3 12 3 14 4 13 4 14 5 6 6 10 7 9 7 10 7 14 8 9 8 14 9 10 9 14 10 13 11 13 11 14