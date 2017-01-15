#!/usr/bin/env bash

#
# nuke.sh
#
# Kills all containers, then deletes all containers and images.
# This leaves your entire system squeaky clean.
# DELETES ALL DOCKER RESOURCES, NOT JUST DROPWHALE CONTAINERS.

# Save the current working directory.
CWD=$( pwd )

echo "This will delete ALL CONTAINERS, VOLUMES, AND IMAGES from you system!"
read -p "Are you sure? (y/n)" -n 1 -r
echo    # (optional) move to a new line
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    exit 1
fi

echo "Killing all containers..."
docker kill $(docker ps -q)

echo "Deleting all containers..."
docker rm $(docker ps -qa)

echo "Deleting all images..."
docker rmi -f $(docker images -q)

echo "Deleting all volumes..."
docker volume rm $(docker volume ls -q)

# Return to the cwd.
cd $CWD
