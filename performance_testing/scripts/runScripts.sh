#!/bin/sh

service docker start

mkdir testCSV
sleep 10
./runH264.sh &
sleep 10
ls recordings
python3 testSelenium.py
python3 runSelenium.py memory


for i in 1 2 3 4 5
do
  ./runSteering.sh &
  python3 runSelenium.py $i
  echo Done with selenium
  cp -r csv testCSV
  mv ./testCSV/csv/csvOutput.csv ./testCSV/csv/$i.csv
  python3 plotCSV.py $i
  echo Done with plotting
  docker stop steering
  
done


