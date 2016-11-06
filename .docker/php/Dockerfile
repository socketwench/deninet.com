FROM php:5-fpm
MAINTAINER tess@ten7.com

RUN apt-get update && apt-get install -y \
    libfreetype6-dev \
    libjpeg62-turbo-dev \
    libmcrypt-dev \
    libpng12-dev \
    libicu-dev \
    libmemcached-dev

RUN docker-php-ext-install gd json intl pdo pdo_mysql mbstring opcache sockets

RUN yes '' | pecl install memcached

COPY php.ini /usr/local/etc/php/php.ini

RUN echo extension=memcached.so >> /usr/local/etc/php/conf.d/memcached.ini
