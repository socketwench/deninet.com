#!/usr/bin/env bash

drush si --uri=http://deninet.dev --root=/var/www --db-url=mysql://${DB_1_ENV_MYSQL_USER}:${DB_ENV_MYSQL_PASS}@db/${DB_1_ENV_MYSQL_DB} -y deninet --sites-subdir=deninet.dev

drush en --uri=http://deninet.dev --root=/var/www -y deninet_dev