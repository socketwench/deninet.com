#!/usr/bin/env bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

${DIR}/bash.sh /root/scripts/rebuild.sh

${DIR}/drush.sh en -y dblog
${DIR}/drush.sh fra -y