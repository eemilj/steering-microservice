import matplotlib.pyplot as plt
import sys
import pandas as pd

dataFile = pd.read_csv('./outputCSV/' + sys.argv[1] + '.csv')

plt.plot(dataFile['Timestamp'], dataFile['CalculatedSteeringAngle'])

try:
    oldFile = pd.read_csv('./steering_CSV/' + sys.argv[1] + '.csv')
    plt.plot(dataFile['Timestamp'], oldFile['CalculatedSteeringAngle'], color='blue', label="PreviousSteeringAngle")
except Exception:
    print("No such file found")

plt.plot(dataFile['Timestamp'], dataFile['CalculatedSteeringAngle'], color='orange',linestyle='dashed', label="CalculatedSteeringAngle")
plt.plot(dataFile['Timestamp'], dataFile['ActualGroundSteering'], color='green', label="ActualGroundSteering")

plt.xlabel('Timestamp')
plt.ylabel('CalculatedSteering/ActualGroundSteering/PreviousSteering')
plt.plot([], [], ' ', label="Previous valid frame Percentage:")
plt.plot([], [], ' ', label="Current valid frame Percentage:")
plt.legend()
plt.savefig('./graphs/' + sys.argv[1] +'.png')

sys.exit()
