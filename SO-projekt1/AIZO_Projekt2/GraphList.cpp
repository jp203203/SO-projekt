#include <iostream>
#include "GraphList.h"

GraphList::GraphList(int no_of_vertexes, int no_of_edges) {
    this -> no_of_vertexes = no_of_vertexes;
    this -> no_of_edges = no_of_edges;
    list = new AdjList[no_of_vertexes];

    for(int i = 0; i < no_of_vertexes; i++) {
        list[i].first_node = nullptr; //na początku brak węzłów
    }
}

GraphList::Node* GraphList::createNode(int vertex, int weight) {
    Node* newNode = new Node;
    newNode -> dest_vertex = vertex;
    newNode -> weight = weight;
    newNode -> next = nullptr;  // nullptr - brak następnego węzła
    return newNode;
}

//tworzy nową krawędź
void GraphList::newEdge(int u, int v, int weight) {
    Node* newNode = createNode(v, weight); //węzeł dla grafu skierowanego, od u do v
    newNode -> next = list[u].first_node;
    list[u].first_node = newNode; //na początek listy
    newNode -> is_directed = true;

    newNode = createNode(u, weight); //węzeł dla grafu nieskierowanego, od v do u
    newNode -> next = list[v].first_node;
    list[v].first_node = newNode;
    newNode -> is_directed = false;
}

//wyświetl graf (skierowany i nieskierowany
void GraphList::displayGraph() const {
    std::cout<<"Postac listowa:\n"
             <<"graf skierowany\n";
    for(int i = 0; i < no_of_vertexes; i++) {
        std::cout<<i<<":";
        Node* node = list[i].first_node;
        while(node != nullptr) {
            if(node -> is_directed) {
                std::cout<<" -> "<< node -> dest_vertex<<" ("<<node -> weight<<"),";
            }
            node = node -> next;
        }
        std::cout<<"\n";
    }
    std::cout<<"graf nieskierowany\n";
    for(int i = 0; i < no_of_vertexes; i++) {
        std::cout<<i<<":";
        Node* node = list[i].first_node;
        while(node != nullptr) {
            std::cout<<" -> "<< node -> dest_vertex<<" ("<<node -> weight<<"),";
            node = node -> next;
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}