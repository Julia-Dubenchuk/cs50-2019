from cs50 import get_string
from sys import argv, exit

if len(argv) != 2:
    print(f"Usage: {argv[0]} keyword")
    exit(1)

key = argv[1]

if key.isalpha() == False:
    print(f"Usage: {argv[0]} keyword")
    exit(2)

s = get_string("plaintext: ")

lKey = len(key)
code_A = ord("A")
code_a = ord("a")
i = 0

print("ciphertext: ", end="")

for c in s:
    if i == lKey:
        i = 0

    code = ord(c)
    codeKey = ord(key[i].lower()) - code_a

    if c.isupper():
            new_code = code_A + (code - code_A + codeKey) % 26
            i += 1
    elif c.islower():
        new_code = code_a + (code - code_a + codeKey) % 26
        i += 1
    else:
        new_code = code

    print(chr(new_code), end="")
print()
