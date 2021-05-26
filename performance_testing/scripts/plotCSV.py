import matplotlib.pyplot as plt
import sys
import pandas as pd

def plotFromCSV():
    dataFile = pd.read_csv('./current_CSV/' + sys.argv[1] + '.csv')
    oldFile = pd.read_csv('./steering_CSV/' + sys.argv[1] + '.csv')
    timeStamps = getTimeStamps(dataFile)
    previousPercentage = "Previous valid frame Percentage: " + '{:.2f}'.format(calculatePercentage(oldFile))
    currentPercentage = "Current valid frame Percentage: " + '{:.2f}'.format(calculatePercentage(dataFile))
    plt.plot([], [], ' ', label=previousPercentage)
    plt.plot([], [], ' ', label=currentPercentage)
    plt.title(sys.argv[1])
    plt.plot(timeStamps, dataFile['CalculatedSteeringAngle'])
    plt.plot(timeStamps, dataFile['ActualGroundSteering'], color='green', label="Actual Ground Steering Request")
    plt.plot(timeStamps, dataFile['CalculatedSteeringAngle'], color='blue', label="Current Ground Steering Request")
    plt.plot(timeStamps, oldFile['CalculatedSteeringAngle'], color='orange', linestyle='dashed', label="Previous Ground Steering Request")
    plt.xlabel('Delta Time in 10⁶ µs')
    plt.ylabel('Ground Steering Request')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.4), fancybox=True)
    plt.savefig('./graphs/' + sys.argv[1] + '.png', bbox_inches='tight')

def calculatePercentage(file):
    calculatedSteerings = file['CalculatedSteeringAngle']
    actualSteerings = file['ActualGroundSteering']
    frameCounter = 0
    realFrameCounter = len(actualSteerings)
    i = 0
    for actualSteering in actualSteerings:
        upperBound = actualSteering + 0.5 * actualSteering
        lowerBound = actualSteering - 0.5 * actualSteering
        if (actualSteering > 0):
            if (calculatedSteerings[i] >= lowerBound) and (calculatedSteerings[i] <= upperBound):
                frameCounter += 1
        elif (actualSteering < 0):
            if (calculatedSteerings[i] <= lowerBound) and (calculatedSteerings[i] >= upperBound):
                frameCounter += 1
        else:
            if (calculatedSteerings[i] <= 0.05 and calculatedSteerings[i] >= -0.05):
                frameCounter += 1
        i += 1

    percentage = frameCounter / realFrameCounter * 100
    return percentage


def getTimeStamps(dataFile):
    newTimeStamps = []
    timeStamps = dataFile['Timestamp']
    first = 0
    for entry in timeStamps:
        if first == 0:
            first = entry
        entry = (entry-first)/1000000
        newTimeStamps.append(entry)
    return newTimeStamps


if __name__ == '__main__':
    plotFromCSV()
    sys.exit()
