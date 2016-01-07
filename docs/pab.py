# -*- coding: utf-8 -*-
# author:beegerous
# date  :2015.4.2
from multiprocessing import Pool
import urllib
import urllib2
import re
import cookielib
import time
import threading
import random
from time import clock
class vRuc:
    # 千万别写https T_T
    cid = '185'
    #url_root = 'http://10.105.240.51/'
    url_root = 'http://localhost/'
    url_token = url_root 
    url_login = url_root + 'login/'
    url_submit = url_root + 'submission/submit/contest/' + cid + '/problem/'
    url_first = url_root + 'contest/' + cid + '/'
    url_board = url_root + 'statistic/board/' + cid + '/'
    url_submissions = url_root + 'submission/status/contest/' + cid + '/page/'
    cookie = cookielib.CookieJar()  
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
    csrftoken = ''
    
    def startLogin(self,username,password):
    	self.getToken()
        self.login(self.csrftoken,username,password)
    
    # 日了狗了的oj密码的关键字非得是奇怪的写法
    def login(self,csrftoken,username,password):
    	# print username, password
        postData = {
            # 日了狗了的oj csrf关键字也是这么非主流
            'csrfmiddlewaretoken' : csrftoken,
            'username': username,
            'passwd': password
        }
        postData = urllib.urlencode(postData)
        loginRequest = urllib2.Request(self.url_login,data=postData)
        response = self.opener.open(loginRequest)
	# 没事多把返回页面打出来看看...
	# print response.read()

    def getToken(self):    
        request = urllib2.Request(self.url_token)
        self.opener.open(request)
        for item in self.cookie:
            if item.name=='csrftoken':
                self.csrftoken= item.value
        # print self.csrftoken
    def refresh(self):    
	rd=random.randint(1,20)
        request = urllib2.Request(self.url_submissions+str(rd)+'/?')
        self.opener.open(request)
        
    def rboard(self):    
        request = urllib2.Request(self.url_board)
        self.opener.open(request)
        
    def rfirst(self):
        request = urllib2.Request(self.url_first)
        self.opener.open(request)
        
    def submitCode(self,code):
        postData = {
            'csrfmiddlewaretoken': self.csrftoken,
            'language': 'gcc',
	 		'code': code
        }
        postData = urllib.urlencode(postData)
	rd=random.randint(65,65+7-1)
        request =  urllib2.Request(self.url_submit+chr(rd)+'/',data=postData)
        self.opener.open(request).read()
def Test(i):
  try:
    ruc = vRuc()
    username='pressure_test'+str(i)
    password='pressure_test'+str(i)
    #username='test_robot_'+str(i)
    #password='test_robot_'+str(i)
    code = u'''
    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
	int i;char ch;
	while(~scanf("%c",&ch));
	for(i=0;i<100000;i++)     
	    printf("%d\\n", random()%40+1);
        return 0;
    }
    '''
    ruc.startLogin(username, password)

    for z in range(0,10):
        if z == 30:
            ruc.submitCode(code)
            print str(i)+'s'+str(z)+'t'
    ruc.refresh()
    print str(i)+'r'
    if random.randint(0,2)==1:
        ruc.rboard()
        print str(i)+'b'
    else:
        ruc.rfirst()
        print str(i)+'f'
  except:
      print 'h'

if __name__ == '__main__':
    test_number = 200
    pls = Pool(200)
    tim = 2000
    start = clock()
    for i in range(0, tim ):
        pls.apply_async(Test, args=(random.randint(0,test_number),))
    pls.close()
    pls.join()
    finish = clock()
    print test_number,'linking,',tim,'request,start:',start,
