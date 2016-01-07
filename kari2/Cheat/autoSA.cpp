#include <string>
#include <cstring>

using std::pair;
using std::make_pair;
typedef pair<pair<int, int>, int> Pair;

struct LCS {
    static const int N = 100000;
    int prev[N], step[N], children[N][26], node_count;
    
    void clear(int u) {
        prev[u] = step[u] = 0;
        memset(children[u], 0, sizeof(children[u]));
    }

    void copy_data(int from, int to) {
        prev[to] = prev[from];
        memcpy(children[to], children[from], sizeof(children[from]));
    }

    void build (std::string string) {
        node_count = 1;
        clear(1);
        for (int i = 0, last = 1, u, node; i < (int)string.length(); ++ i, last = u) {
            int key = string[i] - 'a';
            clear(u = ++ node_count);
            step[u] = step[last] + 1;
            for (node = last; node && children[node][key] == 0; node = prev[node]) {
                children[node][key] = u;
            }
            if (node == 0) {
                prev[u] = 1;
                continue;
            }
            int v = children[node][key];
            if (step[v] == step[node] + 1) {
                prev[u] = v;
            } else {
                int nv = ++ node_count;
                copy_data(v, nv);
                step[nv] = step[node] + 1;
                prev[u] = prev[v] = nv;
                for (; node && children[node][key] == v; node = prev[node]) {
                    children[node][key] = nv;
                }
            }
        }
    }

    Pair get_LCS(std::string source, std::string string) {
        build(source);
        int answer = 0, pivot = -1;
        for (int i = 0, u = 1, current = 0; i < (int)string.length(); ++ i) {
            int key = string[i] - 'a';
            if (children[u][key]) {
                current ++;
                u = children[u][key];
            } else {
                while (u && children[u][key] == 0) {
                    u = prev[u];
                }
                if (children[u][key]) {
                    current = step[u] + 1;
                    u = children[u][key];
                } else {
                    current = 0;
                    u = 1;
                }
            }
            if (current > answer) {
                answer = current;
                pivot = i;
            }
        }
        return make_pair(make_pair(pivot - answer + 1, pivot), answer);
    }
} test;

#include <iostream>

int main () {
    std::string a, b;
    std::cin >> a >> b;
    Pair result = test.get_LCS(a, b);
    printf("Length: %d\n", result.second);
    printf("Position: %d %d\n", result.first.first, result.first.second);
    return 0;
}
