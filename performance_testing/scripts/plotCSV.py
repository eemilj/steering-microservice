import matplotlib.pyplot as plt
import sys
import pandas as pd

df = pd.read_csv('./testCSV/csv_files/' + sys.argv[1] + '.csv')
plt.plot(df['Timestamp'], df['CalculatedSteeringAngle'])
plt.plot(df['Timestamp'], df['CalculatedSteeringAngle'], label="CalculatedSteeringAngle")
plt.plot(df['Timestamp'], df['ActualGroundSteering'], label="ActualGroundSteering")

plt.xlabel('Timestamp')
plt.ylabel('CalculatedSteeringAngle/ActualGroundSteering')
plt.legend()
plt.savefig('./testCSV/csv/' + sys.argv[1] +'.png')

sys.exit()
