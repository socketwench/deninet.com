FROM php:5-apache
MAINTAINER tess@deninet.com

RUN apt-get update && apt-get install -y \
            libfreetype6-dev \
            libjpeg62-turbo-dev \
            libmcrypt-dev \
            libpng12-dev \
            libicu-dev

RUN docker-php-ext-install gd json intl pdo pdo_mysql mbstring mysql mysqli

RUN a2enmod rewrite

COPY deninet.dev.conf /etc/apache2/sites-available/deninet.dev.conf
#COPY xdebug.ini /etc/php5/mods-available/xdebug.ini

RUN a2dissite 000-default && \
    a2ensite deninet.dev
