import matplotlib.pyplot as plt
import csv

filename = 'results.csv'
with open(filename) as csvfile:
    reader = csv.reader(csvfile, delimiter="/")
    data = list(reader)
    for row in data:
        for index in range(1, len(row)):
            row[index] = int(row[index].split('.')[0])

    for i in range(4):
        plt.subplot(2, 2, i+1)
        if i == 0: newdata = data
        if i == 1: newdata = data[0:1] + data[5:6] + data[7:9] + data[10:11]
        if i == 2: newdata = data[0:1] + data[2:3] + data[4:5]
        if i == 3: newdata = data[0:2] + data[3:4] + data[6:7] + data[9:10] + data[11:12]
        for row in newdata:
            if row != newdata[0]:
                number_of_elements = len(row)
                plt.plot(data[0][1:number_of_elements], row[1:number_of_elements], label=row[0], marker='^')

        plt.title('зависимость времени сортировки от количества элементов')
        plt.xlabel('количество сортируемых элементов')
        plt.ylabel('время, мкс')
        plt.legend()

    plt.show()