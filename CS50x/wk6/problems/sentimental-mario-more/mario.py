# TODO
def main():
    height = getHeight()
    for i in range(height):
        printSpaces(height - (i + 1))
        printHashes(i + 1)
        print("  ", end="")
        printHashes(i + 1)
        print()


def getHeight():
    while True:
        try:
            n = int(input("Height: "))
            if 0 < n < 9:
                return n
        except ValueError:
            print("Not an integer")


def printSpaces(n):
    print(" " * n, end="")


def printHashes(n):
    print("#" * n, end="")


main()
