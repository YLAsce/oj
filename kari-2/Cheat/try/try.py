# -*- coding: utf-8 -*-

from datetime import datetime, timedelta
import math
import re
import copy
from lcs import lcs
# Create your models here.


keywords=["int","long","for","while","if","else","break","continue","return","true","false","double","do","signed","unsigned"]
symbol=["[","]","{","}","(",")","&","|","^","%","+","-","*","/",":",";","?","!",".","\"","\'",",","=","#","<",">","_","\\","\n","\r"]
mapKeyword={}
mapSymbol={}
treeMem=[] 

def init():
    for i in range(0,KEYNUM):
        mapKeyword[keywords[i]]=chr(i+ord('a'))

    for i in range(0,26):
        tmp=chr(ord('a')+i)
        tmp2=chr(ord('A')+i)
        mapSymbol[tmp]=i
        mapSymbol[tmp2]=i+26
        if i<10:
            tmp3=chr(ord('0')+i)
            mapSymbol[tmp3]=i+52
    for i in range(0,SYMNUM):
        tmp=symbol[i]
        mapSymbol[tmp]=62+i

def solve2(Str,len1,len2):
    code0 = copy.deepcopy(Str[0])
    code1 = copy.deepcopy(Str[1])
    tlen = len(code0)
    plen = len(code1)
    ans = 0
    MML = 4
    MaxLen=MML+1
    whileTime = 0
    td = 0
    while MaxLen>MML:
        whileTime += 1
        MaxLen = MML
        j = 1
        now_i=0
   #     t1 = datetime.now()
        dp=[65536*[0],65536*[0]]
        
        k,s,t = lcs(Str[0],Str[1])

   #     t2 = datetime.now()
    #    print t2-t1

#        print k
 #       print code0[s:s+k]+"   XXX  "+code1[t:t+k]+"   OOO  "
            
        if k<MaxLen:
            continue
            #print code0[s:s+k]
            #print code1[t:t+k]

        if s+k<tlen and code0[s+k]!='$':
            code0 = code0[0:s]+"$"+code0[s+k:tlen]
        else:
            code0 = code0[0:s]+code0[s+k:tlen]
        tlen=len(code0)
        if t+k<plen and code1[t+k]!='$':
            code1 = code1[0:t]+"$"+code1[t+k:plen]
        else:
            code1 = code1[0:t]+code1[t+k:plen]
        plen=len(code1)

        ans+=k
        MaxLen = k
    #Set=[]
     #   print k
      #  print Str
    print whileTime
    print td
    return ans

def probably2(s,len1,len2):
    return 2.0*float(s)/(float(len1+len2))

"""
def probably1(cls,s,len1,len2):
    return float(s)/(float(len1+len2)*0.5)
"""

def test2(codes):
    length=[0]*2
    similar=0
    Str=['','']
    for j in range(0,2):
        code=open(codes[j])
        try:
            all_code=code.read()
        finally:
            code.close()
        lent=len(all_code)
        for i in range(0,lent):
            if i<lent-1 and all_code[i]=='/' and all_code[i+1]=='/':
                while i<lent and all_code[i]!='\n':
                    i+=1
                continue
            if i<lent-1 and all_code[i]!='/' and all_code[i+1]=='*':
                while i<lent-1 and not (all_code[i]=='*' and all_code[i+1]=='/'):
                    i+=1
                continue
            if all_code[i]!=' ' and all_code[i]!='\r' and all_code[i]!='\n':
                Str[j]+=str(all_code[i])#.append(query_info.codes[j][i])
                length[j]+=1

   # print "str2="
   # print Str
    t1 = datetime.now()
    print 't1=',t1
    similar=solve2(Str,length[0],length[1])
    t2 = datetime.now()
    print 't2=',t2
    tdelta = t2-t1
    print 'td=',tdelta.total_seconds()
   # print similar
    return probably2(similar,length[0],length[1])*100

codes = ['./1.cpp', './2.cpp',]
test2(codes)
