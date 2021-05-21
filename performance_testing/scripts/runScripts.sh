#!/bin/sh
echo STARTING SCRIPT
python3 runSelenium.py memory
sleep 5

for i in 1 2 3 4 5
do
  echo Start Microservice
  ./runSteering.sh &
  python3 runSelenium.py $i
  echo Done with selenium
  ls csv_files
  cp -a csv_files/. outputCSV
  mv ./outputCSV/csvOutput.csv ./outputCSV/$i.csv

  mkdir tmpCSV
  cp ./outputCSV/$i.csv tmpCSV

  python3 plotCSV.py $i
  echo Done with plotting
  docker stop steering
done

rm -rf steering_CSV/*
cp -a tmpCSV/. steering_CSV

docker stop h264
docker stop opendlv-vehicle-view
exit 0

