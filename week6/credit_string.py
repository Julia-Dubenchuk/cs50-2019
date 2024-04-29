from cs50 import get_string

while True:
    num = get_string("Number: ")

    if num.isnumeric():
        break

l = len(num)
sum = 0
even = l % 2 == 0
for i in range(l):
    if (even == False and i % 2 != 0) or (even == True and i % 2 == 0):
        mul = int(num[i]) * 2
        if (mul > 9):
            sum += (mul // 10) + (mul % 10)
        else:
            sum += mul

    if (even == False and i % 2 == 0) or (even == True and i % 2 != 0):
        sum += int(num[i])

if l > 10 and sum % 10 == 0:
    if num[0] == "3":
        if num[1] == "4" or num[1] == "7":
            print("AMEX")
        else:
            print("INVALID")
    elif num[0] == "4":
        print("VISA")
    elif num[0] == "5":
        if int(num[1]) > 0 and int(num[1]) < 6:
            print("MASTERCARD")
        else:
            print("INVALID")
else:
    print("INVALID")
