#ifndef _MATCH_H
#define _MATCH_H
#include <cstring>

/***************************************************
 * Text     : 0 1 2 . . . i-j . . . i . . n-1
 *            -------------|--------|--------
 * Pattern  :              0  . . . j . .
 * The result has threee casee:
 * 1: full match <---> 0 <= i-j <= n-m
 * 2: partial match <---> n-m < i-j < n
 * 3: no match <---> i-j = n
 **************************************************/
int match_br1(char* p, char* t) // Brute-force
{
    size_t n = strlen(p), i = 0;
    size_t m = strlen(t), j = 0;
    while (j < m && i < n) {
        if (t[i] == p[j]) {
            i++;
            j++;
        } else {
            i -= j - 1;
            j = 0;
        }
    }
    return i - j;
}

/***************************************************
 * Text    : 0 1 2 . . . i i+1 . . . i+j . . n-1
 *           ------------|------------|---------
 * Pattern :             0  1  . . .  j  . .
 * The result has three cases:
 * 1: full match <---> 0 <= i <= n-m
 * 2: partial match <---> n-m < i <= n-1
 * 3: no match <---> i > n-1
 ***************************************************/
int match_br2(char* p, char* t) // Brute-force
{
    size_t n = strlen(t), i = 0;
    size_t m = strlen(p), j;
    for (i = 0; i < n-m+1; i++) {
        for (j = 0; j < m; j++) {
            if (t[i+j] != p[j])
                break;
        }
        if (j >= m)
            break;
    }
}


int* buildNext(char* p);
/****************************************************
 *
 *
 *
 ****************************************************/
int match_kmp(char* p, char* t)
{
    int* next = buildNext(p);
    int n = (int)strlen(t), i = 0;
    int m = (int)strlen(p), j = 0;
    while ((j < m) && (i < n)) {
        if (0 > j || t[i] == p[j]) {
            i++;
            j++;
        } else
            j = next[j];
    }
    delete [] next;
    return i - j;
}

int* buildNext(char* p)
{
    size_t m = strlen(p), j = 0;
    int* Next = new int[m];
    int t = Next[0] = -1;
    while (j < m-1) {
        if (t < 0 || p[j] == p[t]) {
            j++;
            t++;
            Next[j] = t;
        } else
            t = Next[t];
    }
    return Next;
}

/*
 * painter's algorithm
 */
int* buildBC(char* P)
{
    int* bc = new int[256];
    for (size_t j = 0; j < 256; j++)
        bc[j] = -1;
    for (size_t m = strlen(P), j = 0; j < m; j++)
        bc[P[j]] = j;
    return bc;
}

/*
 * Boyer-Morre algorithm
 */
int match_bm(char* P, char* T)
{
    int* bc = buildBC(P);
    int* gs = buildGS(P);
    size_t i = 0;

    while (strlen(T) >= i + strlen(P)) {
        int j = strlen(P) - 1;
        while (P[j] == T[i+j])
            if (0 > --j) break;
        if (0 > j)
            break;
        else
            i += __max(gs[j], j-bc[T[i+j]]);
    }
    delete [] gs; delete [] bc;
    return i;
}

#define M 97
#define R 10
#define DIGIT(S, i) ((S)[i] - '0')
typedef __int64 HashCode;
bool check1by1(char* P, char* T, size_t i);
HashCode prepareDm(size_t m);
void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm);

bool check1by1(char* P, char* T, size_t i)
{
    for (size_t m = strlen(P), j = 0; j < m; j++, i++)
        if (P[j] != T[i]) return false;
    return true;
}

void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm) {
    hashT = (hashT - DIGIT(T, k - 1) * Dm) % M;
    hashT = (hashT * R + DIGIT(T, k + m - 1)) % M;
    if (0 > hashT) hashT += M;
}

HashCode prepareDm(size_t m) {
    HashCode Dm = 1;
    for (size_t i = 1; i < m; i++)
        Dm = (R * Dm) % M;
    return Dm;
}

/*
 * Karp-Rabin algorithm
 */
int match_kr(char* P, char* T) 
{
    size_t m = strlen(P), n = strlen(T);
    HashCode Dm = prepareDm(m), hashP = 0, hashT = 0;
    for (size_t i = 0; i < m; i++) {
        hashP = (hashP * R + DIGIT(P, i)) % M;
        hashT = (hashT * R + DIGIT(T, i)) % M;
    }
    for (size_t k = 0; ; ) {
        if (hashT == hashP)
            if (check1by1(P, T, k)) return k;
        if (++k > n - m) return k;
        else updateHash(hashT, T, m, k, Dm);
    }
}

#endif
