FROM socketwench/drupal-cli:7
MAINTAINER tess@deninet.com

COPY php.ini /etc/php5/cli/php.ini

COPY rebuild.sh /root/scripts/rebuild.sh
COPY demo.sh /root/scripts/demo.sh

RUN chmod +x /root/scripts/rebuild.sh
RUN chmod +x /root/scripts/demo.sh
