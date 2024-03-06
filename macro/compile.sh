#!/bin/bash

# Change to the directory containing the Makefile
#cd /home/sh19post/opt/GETDecoder/build

# Run the make command
#make clean
#make

#cd /home/sh19post/repos/artemis/build
#make clean
#make -j10
#make install
#
cd /home/sh19post/art_analysis/user/li/build

make clean
make install -j10

cd /home/sh19post/art_analysis/user/li/macro
