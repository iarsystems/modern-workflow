#!/bin/env sh

apt update

apt install -y udev usbutils libusb-1.0

wget --post-data "accept_license_agreement=accepted" https://www.segger.com/downloads/jlink/JLink_Linux_V874a_x86_64.deb

dpkg --unpack ./JLink_Linux_V874a_x86_64.deb

rm /var/lib/dpkg/info/jlink.postinst

dpkg --configure jlink
