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
    generations = [i * 100 for i in range(len(means))]
    colors = ["green", "blue"]
    line_styles = ["-", "--"]
    labels = ["Fitness Mean", "Fitness Variance"]

    plt.plot(generations, means,
             color=colors[0], linestyle=line_styles[0], label=labels[0])
    # plt.plot(generations, variances,
    #          color=colors[1], linestyle=line_styles[1], label=labels[1])

    plt.legend(loc='upper right')
    plt.xlabel("Generations")
    plt.ylabel("Means")
    plt.title('Population Statics')
    plt.show()


rows = readData()
chartData(rows[0], rows[1])
