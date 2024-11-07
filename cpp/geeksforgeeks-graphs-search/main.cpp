// C++ program for BFS of an undirected graph
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS from given source s
void bfsOri(vector<vector<int>>& adj, int s,
                 vector<bool>& visited) 
{
    // Create a queue for BFS
    queue<int> q;

    // Mark the source node as visited and 
    // enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate over the queue
    while (!q.empty()) {
      
        // Dequeue a vertex from queue and print it
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        // Get all adjacent vertices of the dequeued 
        // vertex curr If an adjacent has not been 
        // visited, mark it visited and enqueue it
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

void bfs(vector<vector<int>>& adj, int s,
                 vector<bool>& visited) 
{
    queue<int> q;

    q.push( s );
    int v = 0;
    while( q.size() > 0 )
    {
        v = q.front();
        q.pop();
        if( !visited[v] )
        {
            visited[v] = true;
            cout << v << " ";
            for( int i = 0; i < adj[v].size(); i++ )
            {
                q.push( adj[v][i] );
            }
        }
    }
}

void dfs(vector<vector<int>>& adj, int s,
                 vector<bool>& visited) 
{
    queue<int> q;

    q.push( s );
    int v = 0;
    while( q.size() > 0 )
    {
        v = q.front();
        q.pop();
        if( !visited[v] )
        {
            visited[v] = true;
            cout << v << " ";
            for( int i = 0; i < adj[v].size(); i++ )
            {
                q.push( adj[v][i] );
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(vector<vector<int>>& adj, int u, int v) 
{
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected Graph
}

// Function to add an edge to the graph
void printGraph(vector<vector<int>>& adj) 
{
    for( int i = 0; i < adj.size(); i++ )
    {
        for( int j = 0; j < adj[i].size(); j++ )
        {
            cout << i << " -> " << adj[i][j] << " ";
        }
        cout << endl;
    }
}

int main() 
{
    // Number of vertices in the graph
    int V = 5;

    // Adjacency list representation of the graph
    vector<vector<int>> adj(V);

    // Add edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    printGraph( adj );

    // Mark all the vertices as not visited
    vector<bool> visited1(V, false);
    vector<bool> visited2(V, false);

    // Perform BFS traversal starting from vertex 0
    cout << "BFS starting from 0 : " << endl;
    bfs(adj, 0, visited1);
    cout << endl;
    cout << "BFS starting from 0 : " << endl;
    bfsOri(adj, 0, visited2);
    cout << endl;
    cout << "DFS starting from 0 : " << endl;
    dfs(adj, 0, visited2);
    cout << endl;

    return 0;
}