#include<stdio.h>
#include<string.h>
int main()
{
    int n,i,k,j,a,b,c,d,e,r;
    char m[55];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
            a=0;
            b=0;
            c=0;
            d=0;
            e=0;
            scanf("%s",m);
            k=strlen(m);
            for(j=0;j<k;j++)
            {
            if(m[j]>=65&&m[j]<=90)
            a++;
            else if(m[j]>=97&&m[j]<=122)
            b++;
            else if(m[j]>=48&&m[j]<=57)
            c++;
            else if(m[j]==126||m[j]==33||m[j]==64||m[j]==35||m[j]==36||m[j]==37||m[j]==94||m[j]==38||m[j]==42||m[j]==40||m[j]==41||m[j]==45||m[j]==61)
            d++;
            }
            if(a!=0)
            e++;
             if(b!=0)
            e++;
            if(c!=0)
            e++;
            if(d!=0)
            e++;
            if(k<6) printf("NO\n");
            else if(k>=6)
            {
                 if(e>=3)
                 printf("YES\n");
                 else
                printf("NO\n"); 
            }    
                 
    }  
    return 0;
}
