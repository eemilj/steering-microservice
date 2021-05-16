#!/bin/sh

xhost +
#docker run --rm --net=host --ipc=host --name=steering -v /tmp:/tmp -v /home/krasen/Dokument/DIT638/2021-group-04/csv_files:/csv_files steering:latest --cid=253 --name=img --width=640 --height=480 &
docker run --rm --net=host --ipc=host --name=steering -v /tmp:/tmp -v $PWD/csv_files:/csv_files group4:latest --cid=253 --name=img --width=640 --height=480 &
echo "Running Steering" &
wait
