#!/usr/bin/env bash

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

DIR=$(dirname $SCRIPT_DIR)

PS=$(cd $DIR && docker-compose ps -q)

if [[ $PS == '' ]]; then
	echo "No containers found."
	exit
fi

if [[ $1 == '' ]]; then
	echo "Starting bash..."
	docker exec -it $(cd $DIR && docker-compose ps -q php) sh -i
else
	docker exec -it $(cd $DIR && docker-compose ps -q php) sh -ic "$*"
fi
