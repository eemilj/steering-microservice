#!/bin/sh

./runopendlv.sh &
docker build https://github.com/chalmers-revere/opendlv-video-h264-decoder.git#v0.0.4 -f Dockerfile.amd64 -t h264decoder:v0.0.4
./runscripts.sh
ls