%module lcs
%include "typemaps.i"

%apply int *OUTPUT {int *lcs_st_a, int *lcs_st_b};
%inline %{
extern int lcs(char *a, char *b, int *lcs_st_a, int *lcs_st_b);
%}

extern int lcs(char *a, char *b, int *lcs_st_a, int *lcs_st_b);

