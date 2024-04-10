// graph_algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <random>

#include "Timer.h"
int count = 0;
static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
static std::mt19937 generator;
static float GetRandomFloat() {
    return distribution(generator);
}
class Graph
{
public:
    Graph() = default;
    Graph(uint32_t nr_vertices, uint32_t nr_edges);

    void AddEdge(uint32_t v, uint32_t w, bool bidirectional = true);
    void DFS(uint32_t v);
    void DFS_intern(uint32_t v, std::unordered_map<uint32_t, bool>& visited);
    void BFS(uint32_t v);
private:
    std::unordered_map<int, std::vector<int>> m_Edges;
};

void Graph::AddEdge(uint32_t v, uint32_t w, bool bidirectional) {
    m_Edges[v].push_back(w);
    if (bidirectional) {
        m_Edges[w].push_back(v);
    }
}
Graph::Graph(uint32_t nr_vertices, uint32_t nr_edges) 
{
    if (nr_edges < nr_vertices) {
        std::cout << "Error: not enough connections!" << std::endl;
        count++;
    }

    int remaining_edges = nr_edges;
    bool* map = new bool[nr_vertices * nr_vertices];
    //map = { 0 };
    memset(map, 0, nr_vertices * nr_vertices * sizeof(bool));

    for (uint32_t i = 0; i < nr_vertices; i++) {

        std::string signature = std::to_string(i);
        uint32_t j;
        do {
            j = GetRandomFloat() * nr_vertices;
            signature += std::to_string(j);
        } while (map[j * nr_vertices + i] && i != j);
        std::string inv_signature = std::to_string(j);
        inv_signature += std::to_string(i);

        // Register the connection

        map[j * nr_vertices + i] = true;
        map[i * nr_vertices + j] = true;

        AddEdge(i, j);
    }
    remaining_edges -= nr_vertices;
    while (remaining_edges > 0) {
        uint32_t src;
        uint32_t dst;
        std::string signature;
        do {
            src = GetRandomFloat() * nr_vertices;
            dst = GetRandomFloat() * nr_vertices;
            signature = std::to_string(src);
            signature += std::to_string(dst);
        } while (map[dst * nr_vertices + src] && src != dst);

        std::string inv_signature = std::to_string(dst);
        inv_signature += std::to_string(src);

        // Register the connection

        map[dst * nr_vertices + src] = true;
        map[src * nr_vertices + dst] = true;

        AddEdge(src, dst);

        remaining_edges--;
    }
}
void Graph::DFS(uint32_t v) {
    std::unordered_map<uint32_t, bool> visited;
    DFS_intern(v, visited);
}
void Graph::DFS_intern(uint32_t v, std::unordered_map<uint32_t, bool>& visited) {
    visited[v] = true;
    //std::cout << v << " ";
    for (uint32_t i = 0; i < m_Edges[v].size(); i++) {
        uint32_t adj_node = m_Edges[v][i];
        if (!visited[adj_node])
            DFS_intern(adj_node, visited);
    }
}
void Graph::BFS(uint32_t v) {
    std::unordered_map<uint32_t, bool> visited;

    std::queue<uint32_t> queue;
    queue.push(v);
    while (!queue.empty()) {
        uint32_t current_node = queue.front();
        queue.pop();
        if (!visited[current_node]) {
            visited[current_node] = true;
            //std::cout << current_node << " ";

            for (uint32_t i = 0; i < m_Edges[current_node].size(); i++) {
                uint32_t adj_node = m_Edges[current_node][i];
                if (!visited[adj_node])
                    queue.push(adj_node);
            }
        }
    }
}

int main()
{
    //Graph graph;
    //graph.AddEdge(1, 2);
    //graph.AddEdge(1, 5);
    //graph.AddEdge(2, 5);
    //graph.AddEdge(2, 3);
    //graph.AddEdge(3, 4);
    //graph.AddEdge(4, 5);
    //graph.AddEdge(4, 6);

    //graph.BFS(1);

    //Graph graph2(10000, 10000);

    //std::cout << "graph generation finished\n";

    //graph2.BFS(0);

    std::ofstream file("output_01.csv");

    //uint32_t nr_vertices = 100;
    std::vector<uint32_t> nr_vertices = { 100, 250, 500, 750, 1000 };
    uint32_t max_edges = (1000 * 1000 - 1000) / 2;

    //uint32_t max_edges = 1000000;
    uint32_t step = max_edges / 10;
    uint32_t start_edges = 1000;
    step = 1000;
    for (uint32_t bound = start_edges; bound <= max_edges; bound += step) {
        file << bound << ", ";
    }
    file << "\n";

    for (uint32_t i = 0; i < nr_vertices.size(); i++) {
        uint32_t max_edges = (nr_vertices[i] * nr_vertices[i] - nr_vertices[i]) / 2;

        for (uint32_t current_edges = start_edges; current_edges <= max_edges; current_edges += step) {
            std::cout << current_edges << "\n";
            Graph test_graph(nr_vertices[i], current_edges);

            Timer timer;
            uint32_t test_count = 1;
            float time_millis = 0;
            for (uint32_t i = 0; i < test_count; i++) {
                timer.Reset();

                test_graph.DFS(0);
                time_millis += timer.ElapsedMillis();

            }
            time_millis = time_millis / test_count;

            file << time_millis << ",";
        }
        file << "\n";
    }
    for (uint32_t i = 0; i < nr_vertices.size(); i++) {
        uint32_t max_edges = (nr_vertices[i] * nr_vertices[i] - nr_vertices[i]) / 2;

        for (uint32_t current_edges = start_edges; current_edges <= max_edges; current_edges += step) {
            std::cout << current_edges << "\n";
            Graph test_graph(nr_vertices[i], current_edges);

            Timer timer;
            uint32_t test_count = 1;
            float time_millis = 0;
            for (uint32_t i = 0; i < test_count; i++) {
                timer.Reset();

                test_graph.BFS(0);
                time_millis += timer.ElapsedMillis();

            }
            time_millis = time_millis / test_count;

            file << time_millis << ",";
        }
        file << "\n";
    }

    std::cout << count;
    std::cout << "--------------------------------------------------\n";
}
