import re


def main():
    input = askNumber()
    print(testResults(input))


def askNumber():
    while True:
        n = input("Number: ")
        return n


def testResults(input):
    if isCorrectLength(input) == False:
        return "INVALID"
    if passedLuhn(input) == False:
        return "INVALID"
    return cardType(input)


def isCorrectLength(input):
    pattern = r"^\d{13}|\d{15}|\d{16}$"
    if re.match(pattern, input):
        return True
    else:
        return False


def passedLuhn(input):
    total = 0

    for i in range(len(input) - 2, -1, -2):
        digit = int(input[i])
        doubledDigit = digit * 2

        if doubledDigit >= 10:
            total += (doubledDigit // 10) + (doubledDigit % 10)
        else:
            total += doubledDigit

    for i in range(len(input) - 1, -1, -2):
        total += int(input[i])

    if (total % 10) == 0:
        return True
    else:
        return False


def cardType(input):
    if len(input) == 15 and re.match(r"^(34|37)\d+", input):
        return "AMEX"
    elif len(input) == 16 and re.match(r"^(51|52|53|54|55)\d+", input):
        return "MASTERCARD"
    elif (len(input) == 13 or len(input) == 16) and re.match(r"^(4)\d+", input):
        return "VISA"
    else:
        return "INVALID"


main()
