sudo rabbitmq-server restart
sudo rabbitmqctl stop_app
sudo rabbitmqctl reset
sudo rabbitmqctl start_app

sudo service uwsgi restart
sudo supervisorctl restart all

