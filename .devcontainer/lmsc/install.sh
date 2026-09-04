#!/bin/env sh

# Get the latest LMSC Daemon from its official product page
wget -q $(wget -qO- https://updates.iar.com/?product=LMSCDAEMON | grep -Po '(?<=href=")[^"]*(?=")' | grep -i '^https://.*deb')

apt install -y ./iar-lmsc-tools_*_amd64.deb