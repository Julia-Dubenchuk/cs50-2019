from cs50 import get_string
from sys import argv, exit


def main():
    if len(argv) != 2:
        print(f"Usage: python {argv[0]} dictionary")
        exit(1)

    file = open(argv[1], "r")
    set_words = set()

    for word in file.readlines():
        set_words.add(word.strip())

    str = get_string("What message would you like to censor?\n")

    for word in str.split(" "):
        if word.lower() in set_words:
            print("*" * len(word), end=" ")
        else:
            print(word, end=" ")
    print()


if __name__ == "__main__":
    main()
