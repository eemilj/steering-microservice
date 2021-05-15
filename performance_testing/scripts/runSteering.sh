#!/bin/sh

xhost +
docker run --rm --net=host --ipc=host --name=steering -v /tmp:/tmp -v $PWD/csv:/csv steering:latest --cid=253 --name=img --width=640 --height=480 &
echo "Running Steering" &
wait
