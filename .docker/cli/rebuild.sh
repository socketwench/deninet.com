#!/usr/bin/env bash

drush si --uri=http://web --root=/var/www --db-url=mysql://${DB_1_ENV_MYSQL_USER}:${DB_ENV_MYSQL_PASS}@db/${DB_1_ENV_MYSQL_DB} -y