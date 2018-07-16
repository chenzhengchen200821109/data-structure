#ifndef _BACKTRACK_H
#define _BACKTRACK_H

//#include "Stack.h"
#include "MyStack.h"

struct Queen {
    int x_, y_;
    Queen(int x = 0, int y = 0) : x_(x), y_(y) {};
    bool operator==(Queen const& q) 
    {
        return (x_ == q.x_) || (y_ == q.y_) || (x_ + y_ == q.x_ + q.y_) || (x_ - y_ == q.x_ - q.y_);
    }
    bool operator!=(Queen const& q) 
    {
        return !(*this == q);
    }
};

/*
 * input -- the number of Queens.
 * output -- the number of solutions given the input.
 */
int QueenSolution(int N)
{
    Stack<Queen> solu;
    Queen q(0, 0);
    int nsolu = 0;

    do {
        if (solu.size() >= N || q.y_ >= N) {
            q = solu.pop();
            q.y_++;
        } else {
            while ((q.y_ < N) && (solu.find(q) >= 0 ))
                q.y_++;
            if (q.y_ < N) {
                solu.push(q);
                if (solu.size() >= N)
                   nsolu++;
                q.x_++;
                q.y_ = 0;
            }
        }
    
    } while ((q.x_ > 0) || (q.y_ < N));

    return nsolu;
}

typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;
typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN;

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1) }

struct Cell
{
    int x, y;
    Status status;
    ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];

inline Cell* neighbor(Cell* cell)
{
    switch (cell->outgoing) {
        case EAST : return cell + LABY_MAX;
        case SOUTH: return cell + 1;
        case WEST: return cell - LABY_MAX;
        case NORTH: return cell - 1;
        default: exit(-1);
    }
}

inline Cell* advance(Cell* cell)
{
    Cell* next;
    switch (cell->outgoing) {
        case EAST: next = cell + LABY_MAX; next->incoming = WEST; break;
        case SOUTH: next = cell + 1; next->incoming = NORTH; break;
        case WEST: next = cell - LABY_MAX; next->incoming = EAST; break;
        case NORTH: next = cell - 1; next->incoming = SOUTH; break;
        default: exit(-1);
    }
    return next;
}

#endif
