#!/bin/env sh
# Product page: https://updates.iar.com/?product=LMSCDAEMON

wget https://netstorage.iar.com/FileStore/STANDARD/001/004/123/iar-lmsc-tools_1.11_amd64.deb

apt install -y ./iar-lmsc-tools_1.11_amd64.deb