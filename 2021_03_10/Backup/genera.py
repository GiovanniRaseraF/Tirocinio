from random import seed
from random import randint
import sys
num = 200

if __name__ == "__main__":
    #Default 
    if len(sys.argv) != 1:
        num = int(sys.argv[1])
    #Generate
    for _ in range(num):
        value = randint(0, 200000)
        print(str(value), end = "\n")