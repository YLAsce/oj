from User.models import *
from Api.models import *
from django.http import HttpResponse
from rest_framework.renderers import JSONRenderer
import logging
logger = logging.getLogger('django')

class JSONResponse(HttpResponse):
    def __init__(self, data, **kwargs):
        content = JSONRenderer().render(data)
        kwargs['content_type'] = 'application/json'
        super(JSONResponse, self).__init__(content, **kwargs)

def userDetail(request, uid):
    try:
        u = User.getById(uid)
    except:
        return HttpResponse(status=404)
    if request.method == 'GET':
        serializer = UserSerializer(u)
        return JSONResponse(serializer.data)

def groupDetail(request, gid):
    try:
        u = Group.getById(gid)
    except:
        return HttpResponse(status=404)
    if request.method == 'GET':
        serializer = GroupSerializer(u)
        return JSONResponse(serializer.data)

def userLogin(request):
    username, password = '', ''
    if request.META.has_key('HTTP_AUTHORIZATION'):
        authmeth, auth = request.META['HTTP_AUTHORIZATION'].split(' ', 1)
        if authmeth.lower() == 'basic':
            auth = auth.strip().decode('base64')
            username, password = auth.split(':', 1)
    u = User.getUserByRawUsername(username)
    if u!=None and u!=False and u.checkPasswd(password):
        serializer = UserSerializer(u)
        return JSONResponse(serializer.data)
    return HttpResponse(status=404)
