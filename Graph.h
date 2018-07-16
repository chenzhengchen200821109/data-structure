#ifndef _GRAPH_H
#define _GRAPH_H

#include <climits>
#include "Stack.h"
#include "Vector.h"

// Vertex status 
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
// Edge status
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;

template<typename V, typename E>
class Graph
{
    private:
        // reset all vertexes and edges status information
        void reset()
        {
            for (int i = 0; i < n; i++) { // Vertex
                status(i) = UNDISCOVERED;
                dTime(i) = fTime(i) = -1;
                parent(i) = -1;
                priority(i) = INT_MAX;
                for (int j = 0; j < n; j++) { // Edge
                    if (exists(i, j))
                        status(i, j) = UNDETERMINED;
                }
            }
        }
        // algorithms involved in Graph
        void BFS(int, int&);
        void DFS(int, int&);
        void BCC(int, int&, Stack<int>&);
        bool TSort(int, int&, Stack<V>*);
    public:
        // operations on vertex
        int n;
        virtual int insert(V const&);
        virtual V remove(int);
        virtual V vertex(int);
        virtual int inDegree(int);
        virtual int outDegree(int);
        virtual int firstNbr(int);
        virtual int nextNbr(int);
        virtual VStatus& status(int);
        virtual int& dTime(int);
        virtual int& fTime(int);
        virtual int& parent(int);
        virtual int& priority(int);
        // operations on edge
        int e;
        virtual bool exists(int, int);
        virtual void insert(E const&, int, int, int);
        virtual E remove(int, int);
        virtual EStatus& status(int, int);
        virtual E dege(int, int);
        virtual int& weight(int, int);
        // algorithms involved in Graph
        void bfs(int);
        void dfs(int);
        void bcc(int);
        Stack<V>* tSort(int);
        void prim(int);
        void dijkstra(int);
        template<typename PU> void pfs(int, PU);
};

// vertex 
template<typename V>
struct Vertex
{
    V data_;
    int inDegree_, outDegree_;
    VStatus status_;
    int dTime_;
    int fTime_;
    int parent_;
    int priority_;
    Vertex(V const& e) :
        data_(e), inDegree_(0), outDegree_(0), status_(UNDISCOVERED),
        dTime_(-1), fTime_(-1), parent_(-1), priority_(INT_MAX) {}
};

// edge
template<typename E>
struct Edge
{
    E data_;
    int weight_;
    EStatus status_;
    Edge(E const& d, int w) : data_(d), weight_(w), status_(UNDETERMINED) {}
};

// implementation of Graph using adjacency matrix. another implementation of
// Graph is using adjacency list.
template<typename V, typename E>
class GraphMatrix : public Graph<V, E>
{
    private:
        // collection of vertexes
        Vector<Vertex<V>* > v_;
        // collection of edges
        Vector<Vector<Edge<E>* > > e_;
    public:
        GraphMatrix() { Graph<V, E>::n = Graph<V, E>::e = 0; }
        /*
         *  -------------------------
         *  |     |  A  |  B  |  C  |
         *  -------------------------
         *  |  A  |     |     |     |
         *  -------------------------
         *  |  B  |     |     |     |
         *  -------------------------
         *  |  C  |     |     |     |
         *  -------------------------
         */
        ~GraphMatrix()
        {
            for (int j = 0; j < Graph<V, E>::n; j++)
                for (int k = 0; k < Graph<V, E>::n; k++)
                    delete e_[j][k];
        }
        // operations on vertex
        virtual int insert(V const& v)
        {
            e_.insert(Vector<Edge<E>* >()); // insert a new edge
            for (int j = 0; j < Graph<V, E>::n; j++)
                e_[j].insert(NULL);
            Graph<V, E>::n++; // increase the number of vertexes
            for (int j = 0; j < Graph<V, E>::n; j++)
                e_[j].insert(NULL);
            return v_.insert(new Vertex<V>());
        }
        virtual V remove(int i) // parameter i is the index of vertex to be removed
        {
            for (int j = 0; j < Graph<V, E>::n; j++) {
                if (exists(i, j)) {
                    e_--;
                    v_[j]->inDegree_--;
                }
                if (exists(j, i)) {
                    e_--;
                    v_[j]->outDegree_--;
                }
            }
            if (exists(i, i)) e_++;
            V d = v_.remove(i)->data_;
            e_.remove(i);
            Graph<V, E>::n--;
            for (int j = 0; j < Graph<V, E>::n; j++)
                e_[j].remove(i);
            return d;
        }
        virtual V vertex(int i)
        {
            return v_[i]->data_;
        }
        virtual int inDegree(int i)
        {
            return v_[i]->inDegree_;
        }
        virtual int outDegree(int i)
        {
            return v_[i]->outDegree_;
        }
        virtual int firstBbr(int i) 
        {
            return nextNbr(i, Graph<V, E>::n);
        }
        virtual int nextNbr(int i, int j)
        {
            while ((j > -1) && (!exists(i, --j)));
            return j;
        }
        virtual VStatus& status(int i)
        {
            return v_[i]->status_;
        }
        virtual int& dTime(int i)
        {
            return v_[i]->dTime;
        }
        virtual int& fTime(int i)
        {
            return v_[i]->fTime;
        }
        virtual int& parent(int i)
        {
            return v_[i]->parent_;
        }
        virtual int& priority(int i)
        {
            return v_[i]->priority_;
        }
        // test if a specific edge exists
        virtual bool exists(int i, int j)
        {
            return (0 <= i) && (i < Graph<V, E>::n) && (0 <= j) && (j < Graph<V, E>::n) && (e_[i][j] != NULL);
        }
        // operations on edge
        virtual void insert(E const& edge, int w, int i, int j)
        {
            if (exists(i, j)) return; // edge already exists
            Graph<V, E>::e++;
            e_[i][j] = new Edge<E>(edge, w);
            v_[i]->outDegree_++;
            v_[j]->inDegree_++;
        }
        virtual E remove(int i, int j)
        {
            if (!exists(i, j)) return NULL;
            E dege = e_[i][j]->data_;
            e_--;
            e_[i][j] = NULL;
            v_[i]->outDegree_--;
            v_[j]->inDegree_--;
            return edge;
        }
        virtual EStatus& status(int i, int j)
        {
            return e_[i][j]->status_;
        }
        virtual E edge(int i, int j)
        {
            return e_[i][j]->data_;
        }
        virtual int& weight(int i, int j)
        {
            e_[i][j]->weight_;
        }
};

template<typename V, typename E>
void Graph<V, E>::bfs(int s)
{
    reset();
    int clock = 0;
    int v = s;
    do {
        if (UNDISCOVERED == status(v))
            BFS(v, clock);
    } while (s != (v = (++v % n)));
}

template<V, E>
void Graph<V, E>::BFS(int v, int& clock)
{
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while (!Q.empty()) {
        int v = Q.dequeue(); dTime(v) = ++clock;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
            if (UNDISCOVERED == status(u)) {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                status(v, u) = TREE;
                parent(u) = v;
            } else {
                status(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}

#endif
