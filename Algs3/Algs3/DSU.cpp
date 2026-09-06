#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>

using namespace std;

struct Point {
    double x, y;
};

struct Edge {
    int u, v;
    double w;
};

class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int v) {
        if (parent[v] == v)
            return v;

        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        if (rank[a] == rank[b])
            rank[a]++;

        return true;
    }
};

