from sys import argv, exit
from cs50 import get_string

if len(argv) != 2:
    print(f"Usage {argv[0]} key")
    exit(1)
else:
    if argv[1].isnumeric() == False:
        print(f"Usage {argv[0]} key")

    key = int(argv[1])
    s = get_string("plaintext: ")

    print("ciphertext: ", end="")

    for c in s:
        code = ord(c)

        if c.isupper():
            new_code = ord("A") + (code - ord("A") + key) % 26
        elif c.islower():
            new_code = ord("a") + (code - ord("a") + key) % 26
        else:
            new_code = code

        print(chr(new_code), end="")

    print()

