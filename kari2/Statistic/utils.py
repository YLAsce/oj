# -.- encoding: utf-8 -.-

from Problem.models import Problem
from User.models import User
from django.http import HttpResponse
from hashlib import md5
from django.shortcuts import render_to_response, render, redirect
from kari.const import Const
from Problem.forms import addProblemForm
from django.core.files.storage import default_storage
from Contest.models import ContestProblem, Contest
from Statistic.models import Board
from Submission.models import Submission
import os
import json

def getContestResult(c):
    try:
        allSub = Submission.submissionList(c=c)
        allProb = c.getContestProblem()
        ac_cnt={}
        sub_cnt={}
        for pinfo in allProb:
            ac_cnt[pinfo.problem_index]=0
            sub_cnt[pinfo.problem_index]=0
        
        for sinfo in allSub:
            if sinfo.status == "Accepted":
                ac_cnt[sinfo.problem_index.problem_index]+=1
            sub_cnt[sinfo.problem_index.problem_index]+=1
        res=[]
        for pinfo in allProb:
            tdict={}
            tdict["ac_cnt"]=ac_cnt[pinfo.problem_index]
            tdict["sub_cnt"]=sub_cnt[pinfo.problem_index]
            if sub_cnt[pinfo.problem_index] == 0:
                tdict["ac_ratio"]=0.00
            else:
                tdict["ac_ratio"]=round(ac_cnt[pinfo.problem_index]*100.0/sub_cnt[pinfo.problem_index],2)
            res.append(tdict)
        return res
    except Exception as e:
        return []

def getContestUserResult(c, u):
    try:
        allSub = Submission.submissionList(c=c)
        allProb = c.getContestProblem()
        ac_cnt={}
        for pinfo in allProb:
            ac_cnt[pinfo.problem_index]=0
        
        for sinfo in allSub:
            if u != sinfo.user:
                continue
            if sinfo.status == "Accepted":
                ac_cnt[sinfo.problem_index.problem_index] = 1
        res=[]
        for pinfo in allProb:
            res.append(ac_cnt[pinfo.problem_index])
        return res
    except Exception as e:
        return []

