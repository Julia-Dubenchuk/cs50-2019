from cs50 import get_int
import math

while True:
    num = get_int("Number: ")

    if num > 0:
        break

length = int(math.log10(num)) + 1
digits = []
digits2 = []

i = length - 1
while i >= 0:
    digits.append(num % 10)
    num //= 10
    i -= 1

digits.reverse()

j = length - 2
while j >= 0:
    digits2.append(digits[j] * 2)
    j -= 2

sum = 0

for k in range(length // 2):
    if digits2[k] > 9:
        sum += digits2[k] // 10 + digits2[k] % 10
    else:
        sum += digits2[k]

i = length - 1
while i >= 0:
    sum += digits[i]
    i -= 2

if (length > 10 and sum % 10 == 0):
    if digits[0] == 3:
        if digits[1] == 4 or digits[1] == 7:
            print("AMEX")
        else:
            print("INVALID")
    elif digits[0] == 4:
        print("VISA")
    elif digits[0] == 5:
        if digits[1] > 0 and digits[1] < 6:
            print("MASTERCARD")
        else:
            print("INVALID")
else:
    print("INVALID")
