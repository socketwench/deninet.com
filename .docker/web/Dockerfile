FROM socketwench/drupal-base:7-xdebug
MAINTAINER tess@deninet.com

RUN a2enmod rewrite

COPY deninet.dev.conf /etc/apache2/sites-available/deninet.dev.conf
COPY php.ini /usr/local/etc/php/php.ini
# COPY xdebug.ini /etc/php5/mods-available/xdebug.ini

RUN a2dissite 000-default && \
    a2ensite deninet.dev

RUN yes '' | pecl install -f memcache
