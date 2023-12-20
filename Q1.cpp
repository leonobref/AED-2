#include <iostream>
#include <list>
using namespace std;
typedef unsigned int Vertex;

class ItemVertex{
    public:
        unsigned int value;
        ItemVertex() {}
        ItemVertex(unsigned int value): value(value) {}
};

class GraphAL{
    // Atributos
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<Vertex> *adj;

    public:
        GraphAL(unsigned int);
        ~GraphAL();

        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices(){return num_vertices;}
        unsigned int get_num_edges(){return num_edges;}
        list<Vertex> get_adj(Vertex v) {return adj[v];}
};

GraphAL::GraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    num_edges = 0;
    adj = new list<Vertex>[num_vertices];
}

void GraphAL::add_edge(Vertex u, Vertex v){
    if (u == v)
        return;
    list<Vertex>:: iterator it;
    for(it = adj[u].begin(); it != adj[u].end(); it++){
        if(*it == v){
            return;
        }
    }

    for(it = adj[v].begin(); it != adj[v].end(); it++){
        if(*it == u){
            return;
        }
    }

    adj[u].push_back(v);
    adj[v].push_back(u);
    num_edges++; 
}

void GraphAL::remove_edge(Vertex u, Vertex v) {
    list<Vertex>:: iterator it;
    bool exist = false;
    for(it = adj[u].begin(); it != adj[u].end(); it++){
        if(*it == v){
            exist = true;
        }
    }
    if(exist == true){
    adj[u].remove(v);
    adj[v].remove(u);
    num_edges--;
    }
    //else{
      //  cout << "A aresta nao existe" << endl;
    //}
}

GraphAL::~GraphAL(){
    for(unsigned int i = 0; i < num_vertices; ++i){
        adj[i].clear();
    }
    num_edges = num_vertices = 0;
}

void display_list(list<Vertex> lst){
    for(ItemVertex item_vertex: lst){
        cout << item_vertex.value << ", ";
    }
    cout << endl;
}

void display_graph(GraphAL &g) {
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
	for (unsigned int v = 0; v < g.get_num_vertices(); v++) {
		cout << v << ": ";
		list<Vertex> lst = g.get_adj(v);
		display_list( lst );
	}
}

void input_graph(GraphAL &g, unsigned int num_edges) {
	Vertex u = 0, v = 0;
	for (unsigned int i = 0; i < num_edges; ++i) {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

int main()
{
    unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	cin >> num_vertices >> num_edges;
	//cout << "num_vertices: " << num_vertices << endl;
	//cout << "num_edges: " << num_edges << endl;
	GraphAL g{num_vertices};
	input_graph(g, num_edges);
	display_graph(g);

	return 0;
}

// 9 12 0 1 0 2 0 3 1 4 2 4 3 4 4 5 4 6 4 7 5 8 6 8 7 8 
// 10 15 0 1 0 6 1 4 1 5 1 6 1 9 2 6 3 4 3 7 3 9 4 6 5 7 5 8 5 9 6 9 
// 15 29 0 9 0 11 0 12 0 14 1 6 1 7 1 11 2 4 2 6 2 7 2 12 3 5 3 11 3 12 3 14 4 13 4 14 5 6 6 10 7 9 7 10 7 14 8 9 8 14 9 10 9 14 10 13 11 13 11 14