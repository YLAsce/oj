from Privilege.models import Root, AdminInfo
from User.models import User, Admin

r = Root.objects.create(root_name='kari', root_name_cn='kari')
u = User.addUser(username='jffifa', passwd='123456', root=r)
r = Root.objects.create(root_name='bupt', root_name_cn='bupt')
u = User.addUser(username='keyang', passwd='123456', root=r)
a = Admin.objects.create(user=u, parent=None)
ai = AdminInfo.objects.create(admin=a, contest_lim=-1)
u2 = User.addUser(username='zhangyu', passwd='123456', root=r)
a2 = Admin.objects.create(user=u2, parent=a)
ai2 = AdminInfo.objects.create(admin=a2, contest_lim=-1)
