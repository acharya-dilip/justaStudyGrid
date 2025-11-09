#!/bin/bash

#Installing Dependencies
sudo pacman -S base-devel
sudo pacman -S cmake
sudo pacman -S gtk
sudo pacman -S gstreamer
#Building the C program
mkdir build
cd build
cmake ..
cmake --build .