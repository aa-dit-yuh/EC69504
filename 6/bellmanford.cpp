#include <iostream>
#include <vector>

#define INF INT_MAX

using namespace std;

typedef pair<int, int> iPair;
 
class Graph
{
    int V;
    vector< pair<iPair, int> > edges;
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
}

void Graph::addEdge(int u, int v, int w)
{
    edges.push_back(make_pair(make_pair(u, v), w));
}
 
void Graph::shortestPath(int src)
{
    vector<int> dist(V, INF);
    dist[src] = 0;
 
    vector<pair<iPair, int> >::iterator j;
    for (int i = 1; i < V; ++i) {
        for (j = edges.begin(); j != edges.end(); ++j) {
            int u = j->first.first;
            int v = j->first.second;
            int weight = j->second;

            if (dist[v] - weight > dist[u])
                dist[v] = dist[u] + weight;
        }
    }

    for (j = edges.begin(); j != edges.end(); ++j) {
        int u = j->first.first;
        int v = j->first.second;
        int weight = j->second;

        if (dist[v] - weight > dist[u])
            cout << "Negative-weight cycle exists in the graph" << endl;
    }

    cout << "Vertex   Distance from Source" << endl;
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
int main()
{
    int V;
    cout << "Enter the number of nodes: ";
    cin >> V;
    Graph g(V);
 
    int E;
    cout << "Enter the number of edges: ";
    cin >> E;

    for (int e = 0; e < E; ++e) {
        int s, d, w;
        cout << "Enter the start, end and weight of the edge " << e << ": ";
        cin >> s >> d >> w;
        g.addEdge(s, d, w);
    }

    int S;
    cout << "Enter the source node: ";
    cin >> S;
    g.shortestPath(S);
 
    return 0;
}
