// graph_algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <unordered_map>
#include <vector>
#include <queue>


class Graph
{
public:
    void AddEdge(char v, char w, bool bidirectional = true);
    void DFS(char v);
    void DFS_intern(char v, std::unordered_map<char, bool>& visited);
    void BFS(char v);
    void BFS_intern(char v, std::unordered_map<char, bool>& visited);
private:
    std::unordered_map<int, std::vector<int>> m_Edges;
};

void Graph::AddEdge(char v, char w, bool bidirectional) {
    m_Edges[v].push_back(w);
    if (bidirectional) {
        m_Edges[w].push_back(v);
    }
}
void Graph::DFS(char v) {
    std::unordered_map<char, bool> visited;
    DFS_intern(v, visited);
}
void Graph::DFS_intern(char v, std::unordered_map<char, bool>& visited) {
    visited[v] = true;
    std::cout << v << " ";
    for (uint32_t i = 0; i < m_Edges[v].size(); i++) {
        char adj_node = m_Edges[v][i];
        if (!visited[adj_node])
            DFS_intern(adj_node, visited);
    }
}
void Graph::BFS(char v) {
    std::unordered_map<char, bool> visited;

    std::queue<char> queue;
    queue.push(v);
    while (!queue.empty()) {
        char current_node = queue.front();
        queue.pop();
        if (!visited[current_node]) {
            visited[current_node] = true;
            std::cout << current_node << " ";

            for (uint32_t i = 0; i < m_Edges[current_node].size(); i++) {
                char adj_node = m_Edges[current_node][i];
                if (!visited[adj_node])
                    queue.push(adj_node);
            }
        }
    }
}
void Graph::BFS_intern(char v, std::unordered_map<char, bool>& visited) {

}

int main()
{
    Graph graph;
    graph.AddEdge('1', '2');
    graph.AddEdge('1', '5');
    graph.AddEdge('2', '5');
    graph.AddEdge('2', '3');
    graph.AddEdge('3', '4');
    graph.AddEdge('4', '5');
    graph.AddEdge('4', '6');

    graph.BFS('1');

}
