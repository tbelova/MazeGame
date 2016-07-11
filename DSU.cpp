#include "DSU.h"

int DSU::getRoot(int v) {
    if (v == parent[v]) return v;
    return parent[v] = getRoot(parent[v]);
}

DSU::DSU(int sz) {
    parent.resize(sz);
    for (int i = 0; i < sz; ++i) parent[i] = i;
}

bool DSU::areConnected(int v, int u) {
    return getRoot(v) == getRoot(u);
}

bool DSU::join(int v, int u) {
    int pv = getRoot(v);
    int pu = getRoot(u);
    parent[pv] = pu;

    return pv != pu;
}
