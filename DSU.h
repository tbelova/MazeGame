#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Consts.h"

#ifndef __DSU__
    #define __DSU__

    class DSU {
    private:
        std::vector<int> parent;

        int getRoot(int v);

    public:
        DSU(int sz);

        bool areConnected(int v, int u);
        bool join(int v, int u);
    };

#endif
