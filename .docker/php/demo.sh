#!/bin/sh

DRUPAL_USER=${DRUPAL_USER:-admin}
DRUPAL_PASSWORD=${DRUPAL_PASSWORD:-password}

drush si --uri=http://deninet.dev \
         --root=/var/www/html \
         --db-url=mysql://${MYSQL_USER}:${MYSQL_PASSWORD}@db/${MYSQL_DATABASE} \
         -y deninet \
         --sites-subdir=deninet.dev \
         --account-name=$DRUPAL_USER \
         --account-pass=$DRUPAL_PASSWORD

drush en --uri=http://deninet.dev --root=/var/www/html -y deninet_dev
