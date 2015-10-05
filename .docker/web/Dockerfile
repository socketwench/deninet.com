FROM debian:latest
MAINTAINER tess@deninet.com

RUN apt-get update
RUN apt-get install -yq apache2

RUN apt-get install -yq php5 php5-mysql php5-imagick php5-imap \
                        php5-mcrypt php5-curl php5-cli php5-gd \
                        php5-sqlite php5-common php-apc php-pear \
                        php5-json php5-memcache php5-intl

RUN a2enmod rewrite

COPY deninet.dev.conf /etc/apache2/sites-available/deninet.dev.conf

RUN a2dissite 000-default && \
    a2ensite deninet.dev

EXPOSE 80

CMD ["-D", "FOREGROUND"]
ENTRYPOINT ["apachectl"]