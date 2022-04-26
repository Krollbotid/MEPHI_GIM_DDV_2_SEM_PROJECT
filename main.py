import matplotlib.pyplot as plt
import csv

filename = 'results.csv'
with open(filename) as csvfile:
    reader = csv.reader(csvfile, delimiter="/")
    data = list(reader)
    number_of_lines = len(data)
    for i in range(number_of_lines):
        for index in range(len(data[i])):
            try:
                data[i][index] = int(float(data[i][index]))
            except:
                pass

plt.title('graph of the dependence of the sorting time on the number of elements')
plt.xlabel('number of sorted items')
plt.ylabel('time, µs')

for i in range(number_of_lines - 1):
    number_of_elements = len(data[i+1])
    print(number_of_elements)
    plt.plot(data[0][1:number_of_elements], data[i+1][1:number_of_elements], label=data[i+1][0], marker='^')

plt.legend()
plt.show()