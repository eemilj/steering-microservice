#!/bin/sh

docker run --rm --net=host --ipc=host --name=h264 -e DISPLAY=$DISPLAY -v /tmp:/tmp h264decoder:v0.0.4 --cid=253 --name=img &
echo "Running H264" &
wait
