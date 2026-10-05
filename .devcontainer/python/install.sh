#!/bin/env sh

# Update APT databasse
apt update

# Install Python 3
apt install -y \
  python3 \
  python3-dev \
  python3-pip \
  python-is-python3
