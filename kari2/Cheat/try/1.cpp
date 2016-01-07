
#include <unistd.h>

#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include <map>
#define GET(a, i)(a[i/32]&(1UL<<(i%32)))
#define SET(a, i)(a[i/32]|=(1UL<<(i%32)))
#define see(x) (cerr<<"Line:["<<__LINE__<<"]:"<<#x<<" = "<<x<<endl)
#define DB_QUERY_FAILED -1
#define DB_UPDATE_FAILED -1
#define DB_UPDATE_SUCCEED 1
#define DB_QUERY_SUCCEED 1
#define MAX_CODE_LENGTH 1055360
#define QUERY_QUEENING -1
#define QUERY_JUDGING 0
#define MAX_USERS 2
#define KEYNUM 15
#define SYMNUM 28
using namespace std;
typedef struct Query_Information{
	int uid;
	int contest_id;
	int solution_id[2];//be sure solution_id[0]<solution_id[1]
	char*code[2];
	double similar_score;
}QUERY;

typedef struct TRIE
{
    int num;char ch;
    struct TRIE * f;
    struct TRIE * next[30];
}TREE;
TREE * root;
TREE tree[1000];
int TOP;

char keywords[KEYNUM+1][10] = {"int","long","for","while","if","else","break","continue",
"return", "true","false","double","do","signed","unsigned"};
char symbol[SYMNUM][3] = {"[","]","{","}","(",")","&","|","^","%","+","-","*","/",":",";","?","!",".","\"","\'",",","=",
"#","<",">","_","\\"};

map<string, int>mapKeyword;

int usleep_sec[10]={1000,2000,4000,8000,16000,32000,64000,128000,256000,512000};
MYSQL*do_connect_mysql()  //Connect to database
{
	MYSQL*mysql=(MYSQL*)calloc(sizeof(MYSQL),1);
    mysql_init(mysql);   //init mysql
    if (!mysql_real_connect(mysql,"localhost","root","TheMoon123","onlinejudge",0,NULL,0))
    {   //if
        free(mysql);
		fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(mysql));
        return NULL;
    }   //if
	if(mysql!=NULL){
		int sql_ret=mysql_query(mysql,"SET NAMES utf8");
		if(sql_ret!=0){
			//log
		}
	}
    return mysql;
}
int query_next_pair(MYSQL*resource,QUERY & query_info,int thread_id){
	int sql_ret=0;
	char sql_cmd[256]={0};
	MYSQL_RES* sql_res=NULL;
	MYSQL_ROW sql_row;
	int sleep_level=0;
	//db status
	int uid1=1,uid2=2,code1=3,code2=4,id=7;
	while(true){
		if(sql_res!=NULL){
			mysql_free_result(sql_res);
			sql_res=NULL;
		}
		snprintf(sql_cmd,sizeof(sql_cmd),"SELECT * FROM rukitest2 WHERE status=%d LIMIT 1",QUERY_QUEENING);
		sql_ret=mysql_query(resource,sql_cmd);
		if(sql_ret!=0){
			//log
			return DB_QUERY_FAILED;
		}
		sql_res=mysql_store_result(resource);
		if(sql_res==NULL){
			//log
			return DB_QUERY_FAILED;
		}
		sql_row=mysql_fetch_row(sql_res);
		if(sql_row!=NULL){
			//log
			break;
		}
	//	usleep(usleep_sec[sleep_level++]);
	//	if(sleep_level>=9)sleep_level=9;
	}
	if(sql_res!=NULL){
		mysql_free_result(sql_res);
		sql_res=NULL;
	}
	snprintf(sql_cmd,sizeof(sql_cmd),"UPDATE rukitest2 SET status=%d WHERE id=%s",QUERY_JUDGING,sql_row[id]);
	sql_ret=mysql_query(resource,sql_cmd);
	if(sql_ret!=0){
		see(sql_cmd);
		return DB_QUERY_FAILED;
	}
	sscanf(sql_row[id],"%d",&query_info.uid);
	//sscanf(sql_row[contest_id],"%d",&query_info.contest_id);
	for(int i = 0;i<2;++i){
		if(query_info.code[i]==NULL){
			query_info.code[i]=(char*)calloc(MAX_CODE_LENGTH+1,1);
		}
		snprintf(query_info.code[i],MAX_CODE_LENGTH,"%s",sql_row[3+i]);
	}
	//sscanf(sql_row[solution_id_0],"%d",&query_info.solution_id[0]);
	//sscanf(sql_row[solution_id_1],"%d",&query_info.solution_id[1]);
	return DB_QUERY_SUCCEED;	
}

int update_similar_score(MYSQL*resource,QUERY&query_info,int thread_id){
	int sql_ret=0;
	char sql_cmd[256]={0};
	snprintf(sql_cmd,sizeof(sql_cmd),"UPDATE rukitest2 SET status=%d,similar_score=%lf WHERE id=%d",DB_UPDATE_SUCCEED,query_info.similar_score,query_info.uid);	
	sql_ret=mysql_query(resource,sql_cmd);
	if(sql_ret!=0){
		see(sql_cmd);
		return DB_UPDATE_FAILED;
	}
	return DB_UPDATE_SUCCEED;
}

TREE * create(int nxt)
{
    TREE * p = &tree[++TOP];
    p->num = 0;
    for(int i = 0;i<=28;i++)p->next[i] = NULL;
    return p;
}
void insert(TREE*p, char* s, int num){
     if(s[0]==0){
         p->num = num;
     //    cout<<"insert:"<<p->num<<endl;
         return ;
     }
 //    int nxt = (s[0]==' ')?26:(s[0]-'a');
     if(p->next[s[0]-'a']==NULL)
           p->next[s[0]-'a'] = create(s[0]-'a');
   //  cout<<"insert:"<<s[0]<<endl;
     return insert(p->next[s[0]-'a'], &s[1], num);
}
void init(){
     for(int i = 0;i<26;++i){
     build_tree();
             string tmp,tmp2;
             tmp+=(char)(i+'a');
             tmp2+=(char)(i+'A');
             mapKeyword[tmp] = i;
             mapKeyword[tmp2] = i+26;
             if(i<10){
                      string tmp3;
                      tmp3+=(char)(i+'0');
                      mapKeyword[tmp3] = i+52;
             }
     }
     for(int i = 0;i<SYMNUM;++i){
             string tmp = symbol[i];
             mapKeyword[tmp] = 62+i;
     }
}
int search(TREE*p, char*s, int & pos){
    if(s[0]==0)return p->num;
    if(p->num>0){
         if((s[0]>='a'&&s[0]<='z')||(s[0]>='A'&&s[0]<='Z')||(s[0]>='0'&&s[0]<='9'))
               return 0;
         return p->num;
    }
    if(!(s[0]>='a'&&s[0]<='z'))return 0;
    if(p->next[s[0]-'a']==NULL)return 0;
    else{
         pos++;
         int nxt = search(p->next[s[0]-'a'], &s[1], pos);
         if(nxt==0)pos--;
         return nxt;
    }
}
char str[2][MAX_CODE_LENGTH];
unsigned int bits1[MAX_CODE_LENGTH/32] = {0};
unsigned int bits2[MAX_CODE_LENGTH/32] = {0};
double solve1(int len1,int len2){
       int pre = 0;
       int m,t = 0;
    //   int MW = 0;
       int MW = max(0,min(len1,len2)/2-1);
     //  cout<<"MW="<<MW<<endl;
     //  double p = 0.1;
      // while(pre<len1&&pre<len2&&(str[0][pre]==str[1][pre]))pre++;
      // m = pre;
       m = 0;
       memset(bits1,0,sizeof(bits1));
       memset(bits2,0,sizeof(bits2));
       for(int i = 0;i<len1;++i){
             for(int j = max(0,i-MW);j<len2&&j<=i+MW;++j){
                     if(!GET(bits2,j)&&(str[0][i]==str[1][j])){
                            SET(bits1,i);
                            SET(bits2,j);
                            m++;
                            break;
                     }
             }  
       }
       for(int i = 0,j = 0;i<len1&&j<len2;++i){
               if(!GET(bits1,i))continue;
               while(j<len2&&!GET(bits2,j))j++;
               if(j<len2&&str[0][i]!=str[1][j])t++;
               j++;
       }
       double ans = 0.0;
     //  cout<<"add="<<(double)pre*p*(1.0-ans)<<endl;
      //   cout<<"m="<<m<<endl;
        // cout<<"len1="<<len1<<endl;
        // cout<<"len2="<<len2<<endl;
       if(m>0){
               ans = ((double)m/max(len1,len2)+(double)m/max(len1,len2)+(double)(m-t)/max(len1,len2))/3.0;
             //ans = ((double)m/min(len1,len2)+(double)(m-t/2.0)/m)/3.0;
            //   ans+=(double)pre*p*(1.0-ans);
       }
       return ans;
}
int main(int argv,char **argc){
	int thread_id=atoi(argc[1]);
	QUERY query_info;
	memset(&query_info,0,sizeof(query_info));
	MYSQL*mysql=do_connect_mysql();	
	if(mysql==NULL){
		//log
		exit(0);
	}
	while(true){
		int query_ret=query_next_pair(mysql,query_info,thread_id);
		if(query_ret!=DB_QUERY_SUCCEED){
			//log
			see("query failed");
			break;
		}
	//	query_ret=query_next_code(mysql,query_info);
	//	see("here?");
	//	if(query_ret!=DB_QUERY_SUCCEED){
			//log
	//		see("get code error");
	//		break;
	//	}
	//	see("this");
		similar_judge(query_info);
		see("flag");
		query_ret=update_similar_score(mysql,query_info,thread_id);
		if(query_ret!=DB_UPDATE_SUCCEED){
			see("update failed");
			//log
			break;
		}
	}
}
