from sys import argv, exit
import crypt

if len(argv) != 2:
    print(f"Usage: {argv[0]} hash")
else:
    l = 52
    letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    hash = argv[1]
    salt = hash[0:2]
    key = ""

    for fifth in range(l):
        for fourth in range(l):
            for third in range(l):
                for second in range(l):
                    for first in range(l):
                        key = key if first == 0 else key + letters[first]
                        key = key if second == 0 else key + letters[second]
                        key = key if third == 0 else key + letters[third]
                        key = key if fourth == 0 else key + letters[fourth]
                        key = key if fifth == 0 else key + letters[fifth]

                        if crypt.crypt(key, salt) == hash:
                            print(f"Key: {key}")
                            exit(0)

                        key = ""

print("Password couldn't be cracked!")

