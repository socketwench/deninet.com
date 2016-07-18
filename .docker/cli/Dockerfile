FROM drush/drush:php5
MAINTAINER tess@deninet.com

RUN apt-get update && \
    apt-get -yq install supervisor

COPY php.ini /etc/php5/cli/php.ini

COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

COPY rebuild.sh /root/scripts/rebuild.sh
COPY demo.sh /root/scripts/demo.sh

RUN chmod +x /root/scripts/rebuild.sh
RUN chmod +x /root/scripts/demo.sh

CMD ["-n"]
ENTRYPOINT ["/usr/bin/supervisord"]
