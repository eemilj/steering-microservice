#!/bin/sh
echo STARTING SCRIPT
python3 runSelenium.py memory
sleep 5

for i in 1 2 3 4 5
do
  ./runSteering.sh &
  python3 runSelenium.py $i
  echo Done with selenium
  cp -r csv_files testCSV
  mv ./testCSV/csv/csvOutput.csv ./testCSV/csv/$i.csv
  python3 plotCSV.py $i
  echo Done with plotting
  docker stop steering
done

docker stop h264
docker stop opendlv-vehicle-view
exit 0

