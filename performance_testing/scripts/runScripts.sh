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
  cp -a csv_files/. testCSV
  mv ./testCSV/csvOutput.csv ./testCSV/$i.csv

  mkdir "tmpCSV"
  cp ./testCSV/$i.csv tmpCSV

  python3 plotCSV.py $i
  echo Done with plotting
  docker stop steering
done

rm -rfv oldCSV/*
cp -a tmpCSV/. oldCSV
ls graphs
ls oldCSV
docker stop h264
docker stop opendlv-vehicle-view
exit 0

