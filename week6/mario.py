from cs50 import get_int

while True:
    height = get_int("Height: ");

    if height > 0 and height < 9:
        break

for i in range(height):
    i += 1
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print(" ", end=" ")
    print("#" * i, end="")
    print()