#!/bin/sh
echo STARTING SCRIPT
cd /recordings
ITEMS=$(ls | wc -l)
echo $ITEMS
ARRAY=(*.rec)
cd ..
python3 runSelenium.py memory "${ARRAY[0]}"
sleep 5
for ((i=0; i < $ITEMS; i++));
do
  echo "${ARRAY[$i]}"
  echo Start Microservice
  ./runSteering.sh &
  python3 runSelenium.py "${ARRAY[$i]}"
  echo Done with selenium
  ls csv_files
  cp -a csv_files/. outputCSV
  mv ./outputCSV/csvOutput.csv ./outputCSV/"${ARRAY[$i]}".csv

  mkdir tmpCSV
  cp ./outputCSV/"${ARRAY[$i]}".csv tmpCSV

  python3 plotCSV.py "${ARRAY[$i]}"
  echo Done with plotting
  docker stop steering
done

rm -rf steering_CSV/*
cp -a tmpCSV/. steering_CSV

docker stop h264
docker stop opendlv-vehicle-view
exit 0

