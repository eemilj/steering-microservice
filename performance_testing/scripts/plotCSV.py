import matplotlib.pyplot as plt
import sys
import pandas as pd

def plotToSCV():
    dataFile = pd.read_csv('./outputCSV/' + sys.argv[1] + '.csv')
    oldFile = pd.read_csv('./steering_CSV/' + sys.argv[1] + '.csv')

    previousPercentage = "Previous valid frame Percentage: " + caclulatePercentage(oldFile).__str__()
    currentPercentage = "Current valid frame Percentage:" + caclulatePercentage(dataFile).__str__()
    plt.plot([], [], ' ', label=previousPercentage)
    plt.plot([], [], ' ', label=currentPercentage)
    plt.ticklabel_format(useOffset=False)
    plt.plot(dataFile['Timestamp'], dataFile['CalculatedSteeringAngle'])
    plt.plot(dataFile['Timestamp'], oldFile['CalculatedSteeringAngle'], color='blue', label="PreviousSteeringAngle")
    plt.plot(dataFile['Timestamp'], dataFile['CalculatedSteeringAngle'], color='orange', linestyle='dashed', label="CalculatedSteeringAngle")
    plt.plot(dataFile['Timestamp'], dataFile['ActualGroundSteering'], color='green', label="ActualGroundSteering")
    plt.xlabel('Timestamp')
    plt.ylabel('CalculatedSteering/ActualGroundSteering/PreviousSteering')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.4), fancybox=True)
    plt.savefig('./graphs/' + sys.argv[1] + '.png', bbox_inches='tight')
    print(previousPercentage)
    print(currentPercentage)

def caclulatePercentage(file):
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


if __name__ == '__main__':
    plotToSCV()
    sys.exit()
