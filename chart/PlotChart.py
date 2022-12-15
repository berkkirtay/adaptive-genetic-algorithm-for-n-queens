import csv
import matplotlib.pyplot as plt


def readData():
    file = open('data.csv')
    csvreader = csv.reader(file)
    rows = []
    for row in csvreader:
        rows.append(row)
    file.close()

    return rows


def chartData(means, variances):
    times = [i for i in range(len(means))]

    fig, ax1 = plt.subplots()

    ax2 = ax1.twinx()
    ax1.plot(times, means, label="Population Mean", color='y')
   # ax2.plot(times, variances, '-.', label="Variances", color='r')

    ax1.set_xlabel('Time', color='b')
    ax1.set_ylabel('Population Mean', color='y')
    #ax2.set_ylabel('Variances', color='r')

    plt.title('Population')
    plt.show()


rows = readData()
chartData(rows[0], rows[1])
