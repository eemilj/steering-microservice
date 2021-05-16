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
  cp -r csv_files testCSV
  mv ./testCSV/csv_files/csvOutput.csv ./testCSV/csv_files/$i.csv
  python3 plotCSV.py $i
  echo Done with plotting
  docker stop steering
done

docker stop h264
docker stop opendlv-vehicle-view
exit 0

