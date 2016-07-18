#!/usr/bin/env bash

drush si \
      --uri=http://web \
      --root=/var/www/html \
      --db-url=mysql://${MYSQL_USER}:${MYSQL_PASSWORD}@db/${MYSQL_DATABASE} -y deninet
