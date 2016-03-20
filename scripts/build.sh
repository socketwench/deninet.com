#!/usr/bin/env bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

${DIR}/bash.sh /root/scripts/demo.sh

${DIR}/drush.sh fra -y