#!/usr/bin/env bash

FOLDER=$1
shift
PROJNAME=$1
shift

if [ ! -d "$FOLDER" ]; then
	echo "$FOLDER is not a folder!"
	exit
fi

PROJNAMELOWER=$(echo "$PROJNAME" | tr '[:upper:]' '[:lower:]')
echo $PROJNAMELOWER
SEDPATTERN="s/##PROJNAME##/$PROJNAME/g; s/##PROJNAMELOWER##/$PROJNAMELOWER/g"

function parsefile {
	sed "$SEDPATTERN" template/$1 > $PROJNAMELOWER/$PROJNAMELOWER$1
}

function parseunit {
	parsefile $1.cpp
	parsefile $1.h
}

parseunit app
parseunit config
parseunit ecs
parseunit factory
parseunit world
parsefile main.cpp

