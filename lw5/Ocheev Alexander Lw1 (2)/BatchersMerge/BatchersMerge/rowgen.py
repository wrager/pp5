import random
import sys

def GenerateRandomNumbersRow(output, count):
    f = open(output, "w")
    for i in range(0, count):
        f.write(str(random.randint(1, count)))
        f.write(' ')
    f.close()



if __name__ == "__main__":
    if (len(sys.argv) != 3):
        print('enter <output file> <power of 2>')
    else:
       output = sys.argv[1]
       count = 2 ** int(sys.argv[2])
       GenerateRandomNumbersRow(output, count) 
