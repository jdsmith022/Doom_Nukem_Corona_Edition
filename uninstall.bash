#!/bin/bash

function osUninstall {
    #uninstall dependencies
	echo "Uninstalling dependencies..."
	brew uninstall gcc
    brew uninstall SDL2
    brew uninstall SDL2_ttf
    brew uninstall SDL2_mixer
}

OS_NAME=`uname -s`

if [[ $OS_NAME=="Darwin" ]]; then
    osUninstall
else
    echo "Error: $OS_NAME is not supported"
    exit 1
fi
