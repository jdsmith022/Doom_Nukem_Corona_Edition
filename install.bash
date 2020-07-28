#!/bin/bash 

#checks if homebrew is installed
if test ! $(which brew); then
    echo "Installing homebrew..."
    ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
fi

function linuxInstall {

}

function osInstall {
    # Update homebrew recipes
    brew update
    #install dependencies
    brew install SDL2
    brew install SDL2_ttf
    brew install SDL2_mixer	
}

OS_NAME = 'uname -s'

if $OS_NAME == "Darwin"; then
    osInstall
else if $OS_NAME == "Linux"; then
    linuxInstall
else
    echo "Error: OS-'$OS_NAME' is not supported"
    exit 1
fi
