#include "graph.h"

//n is number of verticies
Graph::Graph(int n) {
    nVertices = n;
    adjList = new Vertex*[n];
    for (int i = 0; i < n; i++) {
        adjList[i] = nullptr;
    }
}

void Graph::addEdge(int from, int to)
{
    if ((from >= Graph::nVertices) || (to >= nVertices) || (from < 0) || (to < 0))// Check if the 'from' node is valid
        return; // Do nothing if 'from' is invalid

    if (adjList[from] == nullptr)
    {
        adjList[from] = new Vertex{to, nullptr};
        return ;
    }

    Vertex *node = adjList[from];
    Vertex *prevNode;
    prevNode = node;
    while(node != nullptr)
    {
        if (node->v == to) // Check if the edge is already available
            return ;
        prevNode = node;
        node = node->next; //Traverse till you reach the end of the linkedlist
    }

    prevNode->next = new Vertex{to, nullptr};
    return;
}

void Graph::removeEdge(int from, int to)
{
    if ((from >= nVertices) || (to >= nVertices) || (from < 0) || (to < 0)) // Check if the 'from' node is valid
        return; // Do nothing if 'from' is invalid

    Vertex *currNode = adjList[from];
    Vertex *prevNode;

    if (currNode == nullptr)
        return;

    if (currNode->v == to)
    {
        adjList[from] = currNode->next;
        return;
    }

    prevNode = currNode;
    currNode = currNode->next;

    for (; currNode!=nullptr; currNode = currNode->next)
    {
        if (currNode->v == to)
        {
            prevNode->next = currNode->next;
            return;
        }
    }
    return;
}

Vertex* Graph::getNeighbours(int vertex)
{
    if ((vertex <= nVertices) && (vertex >=0))
        return adjList[vertex];
    return nullptr;
}

bool isEdgeNew(Edge* head, Edge* newEdge)
{
    for(Edge* edge = head; edge != nullptr; edge = edge->next)
    {
        if ((edge->u == newEdge->u) && (edge->v == newEdge->v))
            return false;
    }
    return true;
}

Edge* Graph::getEdges()
{
    Edge *head = nullptr, *tail = nullptr;
    for (int i = 0; i < nVertices; i++)
    {
        Vertex* currNode = adjList[i];
        while(currNode != nullptr)
        {
            Edge* newEdge = new Edge{i, currNode->v, nullptr};
            if (isEdgeNew(head, newEdge))
            {
                if (head == nullptr)
                {
                    head = newEdge;
                    tail = newEdge;
                }
                else
                {
                    tail->next = newEdge;
                    tail = tail->next;
                }
            }
            currNode = currNode->next;
        }
    }
    return head;
}

bool addItIfIsNotAlreadyInTheList(Vertex* reachableNodes, int it)
{
    Vertex* node = reachableNodes;
    while(node->next != nullptr)
    {
        if (node->v == it)
            return false;
        node = node->next;
    }
    if (node->v == it)
        return false;

    node->next = new Vertex{it, nullptr};
    return true;
}

bool updateReachableNodes(Vertex* reachableNodes, Vertex* neighbours, int to)
{
    bool updateFlag = false, found = false;
    for(Vertex* node = neighbours; node != nullptr; node=node->next)
    {
        updateFlag |= addItIfIsNotAlreadyInTheList(reachableNodes, node->v);
        found |= (node->v == to);
    }
    return found;
}

void cleanUp(Vertex* &reachableNodes)
{
    Vertex* nextNode = reachableNodes;
    for(Vertex* node=reachableNodes; node!=nullptr; )
    {
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
    reachableNodes = nullptr;
}

bool Graph::isReachable(int from, int to)
{
    if ((from >= nVertices) || (to >= nVertices) || (from < 0) || (to < 0))// Check if the 'from' node is valid
        return false; // False if 'from' is invalid

    if (from == to)
        return true;

    if (adjList[from] == nullptr)
        return false;

    Vertex* reachableNodes = new Vertex {from, nullptr};

    bool found = false;
    for (Vertex* currNode = reachableNodes; currNode!=nullptr; currNode = currNode->next)
    {
        found = updateReachableNodes(reachableNodes, getNeighbours(currNode->v), to);
        if (found)
        {
            cleanUp(reachableNodes);
            return true;
        }
    }
    cleanUp(reachableNodes);
    return false;
}


//Undirected Graph

UndirectedGraph::UndirectedGraph(int n) : Graph(n)
{}

void UndirectedGraph::addEdge(int from, int to)
{
    if (from == to)
        return;
    Graph::addEdge(from,to);
    Graph::addEdge(to,from);
}

void UndirectedGraph::removeEdge(int from, int to)
{
    if (from == to)
        return;

    Graph::removeEdge(from,to);
    Graph::removeEdge(to,from);
}