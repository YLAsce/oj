from django.conf.urls import patterns, url
from Statistic import views

urlpatterns = patterns('',
        #url(r'^list/(\d+)/$', views.listProblem, name='list'),
        #url(r'^list/$', views.listProblem, name='list'),
        #url(r'^p/(\d+)/$', views.showProblem, name='problem'),
        #url(r'^c/(\d+)/([A-Z]{1})/$',views.showContestProblem, name="contestproblem"), 
        #url(r'^addProblem/$',views.addProblem, name='addproblem'),
        #url(r'^addProblemSubmit',views.addProblemSubmit, name='addcommit'),
        #url(r'^updateProblem/(\d+)/$',views.updateProblem, name='updateproblem'),
        #url(r'^updateProblemSubmit/(\d+)/$',views.updateProblemSubmit, name='updatecommit'),
        #url(r'^getProblemTitle/$', views.getProblemTitle, name='title'),
        #        url(r'^addData/$', views.addData),
        #        url(r'^updateData/(\d+)/$', views.updateData),
        #url(r'^test/$',views.testPage),
        #url(r'^testUpload/$',views.testUpload, name='test'),
        #url(r'^testUploadSubmit/$',views.testUploadSubmit, name='testups'),
        url(r'^board/(\d+)/$', views.showBoardByStatus, name='boardByAC'),
        url(r'^score/(\d+)/$', views.showBoardByScore, name='boardByScore'),
        url(r'^c/(?P<cid>\d+)/index/(?P<p_index>([A-Z]))/$', views.showContestProblemStatistics, name='contest_problem_st'),
        url(r'^p/(?P<pid>\d+)/$', views.showProblemStatistics, name='problem_st'),
        )
