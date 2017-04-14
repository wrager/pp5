import random

count = 2 ** 20

f = open("input.txt", "w")
for i in range(0, count):
    f.write(str(random.randint(1, 2 ** 20)))
    f.write(' ')
f.close()
