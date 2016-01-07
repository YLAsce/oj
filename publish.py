import sys,os
from datetime import *
sys.path.append('/home/buptacm/oj/kari/');
os.environ['DJANGO_SETTINGS_MODULE']='kari.settings'

from Problem.models import Problem;
p=Problem.objects.all();
tar=p.get(pk=83);
for i in [616,614,605,604,440,620,621,619,617]:
    x=p.get(pk=i)
    x.course = tar.course
    x.course_id = tar.course_id
    x.prob_priv = tar.prob_priv
    x.save();

