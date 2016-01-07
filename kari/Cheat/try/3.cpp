#include<stdio.h>
#include<string.h>
int main()
{
    int i,j,n,num[5];
    char str[52];
    scanf("%d\n",&n);
    while(n--)
    {
              i=0;j=0;
              for(i=0;i<4;i++) num[i]=0;
              scanf("%s",str);
              if(strlen(str)<6) printf("NO\n");
              else
              {
                  for(i=0;i<strlen(str);i++)
                  {
                                            if(str[i]>='A'&&str[i]<='Z') num[0]++;
                                             else if(str[i]>='a'&&str[i]<='z') num[1]++;
                                              else if(str[i]>='0'&&str[i]<='9') num[2]++;
                                               else if(str[i]=='~'||str[i]=='!'||str[i]=='@'||str[i]=='#'||str[i]=='$'||str[i]=='%'||str[i]=='^'||str[i]=='&'||str[i]=='*'||str[i]=='('||str[i]==')'||str[i]=='-'||str[i]=='=') 
                                               num[3]++;
                  }
                  for(i=0;i<4;i++)
                  {
                                  if(num[i]==0) j++;
                  }
                  if(j<=1) printf("YES\n");
                  else printf("NO\n");
              }
    }
    //getch();
    return 0;
}
