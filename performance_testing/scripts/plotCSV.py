import matplotlib.pyplot as plt
import sys
import pandas as pd

def plotToSCV():
    dataFile = pd.read_csv('./oldCSV/' + sys.argv[1] + '.csv')
    oldFile = pd.read_csv('./steering_CSV/' + sys.argv[1] + '.csv')

    plt.plot(dataFile['Timestamp'], dataFile['CalculatedSteeringAngle'])
    plt.plot(dataFile['Timestamp'], oldFile['CalculatedSteeringAngle'], color='blue', label="PreviousSteeringAngle")
    plt.plot(dataFile['Timestamp'], dataFile['CalculatedSteeringAngle'], color='orange', linestyle='dashed', label="CalculatedSteeringAngle")
    plt.plot(dataFile['Timestamp'], dataFile['ActualGroundSteering'], color='green', label="ActualGroundSteering")
    plt.xlabel('Timestamp')
    plt.ylabel('CalculatedSteering/ActualGroundSteering/PreviousSteering')
    previousPercentage = caclulatePercentage(oldFile)
    currentPercentage = caclulatePercentage(dataFile)
    plt.plot([], [], ' ', label="Previous valid frame Percentage: " + previousPercentage.__str__())
    plt.plot([], [], ' ', label="Current valid frame Percentage:" + currentPercentage.__str__())
    plt.legend()
    plt.savefig('./graphs/' + sys.argv[1] + '.png')

def caclulatePercentage(file):
    currentSteering = file['CalculatedSteeringAngle']
    actualSteering = file['ActualGroundSteering']
    frameCounter = 0
    realFrameCounter = len(actualSteering)
    i = 0
    for steering in actualSteering:
        upperBound = actualSteering[i] + 0.5 * actualSteering[i]
        lowerBound = actualSteering[i] - 0.5 * actualSteering[i]
        if ((actualSteering[i] > 0) and (currentSteering[i] >= lowerBound) and (currentSteering[i] <= upperBound)):
            frameCounter += 1
        elif (((actualSteering[i] < 0) and (currentSteering[i] <= lowerBound) and (currentSteering[i] >= upperBound))):
            frameCounter += 1
        else:
            if (currentSteering[i] <= 0.05 and currentSteering[i] >= -0.05):
                frameCounter += 1
        realFrameCounter += 1
        i += 1

    percentage = frameCounter / realFrameCounter * 100
    return percentage


if __name__ == '__main__':
    plotToSCV()
    sys.exit()
