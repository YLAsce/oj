#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[2][66666];

int main() {
    int i, j, k;
    memset(f, 0, sizeof f);
    char *s = new char[66666];
    char *t = new char[66666];
    memset(s, 0, sizeof s);
    memset(t, 0, sizeof t);
    FILE *file;
    file = fopen("./1.cpp", "r");
    fread(s, 1, 99999, file);
    fclose(file);
    file = fopen("./2.cpp", "r");
    fread(t, 1, 99999, file);
    fclose(file);
    int ans = 0, now = 0;
    int sl = strlen(s), tl = strlen(t);
    for (i = 1; i <= sl; ++i, now^=1)
        for (j = 1; j <= tl; ++j) {
            if (s[i-1]==t[j-1]) {
                f[now][j] = f[now^1][j-1]+1;
                ans = max(ans, f[now][j]);
            } else {
                f[now][j] = 0;
            }
        }
    printf("%d\n", ans);
    delete []s;
    delete []t;
    return 0;
}
