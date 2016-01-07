#include <stdlib.h>
#include <string.h>
#define max(a, b) (a>b?a:b)

int lcs(char *a, char *b, int *lcs_st_a, int *lcs_st_b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    int maxlen = max(len_a, len_b);

    int *f[2];
    f[0] = (int *)malloc((maxlen+1)*sizeof(int));
    memset(f[0], 0, (maxlen+1)*sizeof(int));
    f[1] = (int *)malloc((maxlen+1)*sizeof(int));
    memset(f[1], 0, (maxlen+1)*sizeof(int));

    int i, j, len=0, st_a=0, st_b=0;
    int now = 0;
    for (i = 0; i < len_a; ++i, now^=1)
        for (j = 0; j < len_b; ++j) {
            if (a[i]!='$' && b[j]!='$' && a[i]==b[j]) {
                f[now][j+1] = f[now^1][j]+1;
                if (f[now][j+1] > len) {
                    len = f[now][j+1];
                    st_a = i-len+1;
                    st_b = j-len+1;
                }
            } else {
                f[now][j+1] = 0;
            }
        }
    free(f[0]);
    free(f[1]);

    *lcs_st_a = st_a;
    *lcs_st_b = st_b;

    return len;
}

