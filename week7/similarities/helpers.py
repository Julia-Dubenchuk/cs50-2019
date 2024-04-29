from nltk.tokenize import sent_tokenize
from math import ceil

def lines(a, b):
    """Return lines in both a and b"""
    lines = []
    for lineA in a.split("\n"):
        for lineB in b.split("\n"):
            stripLineB = lineB.strip()

            if lineA == lineB and stripLineB not in lines:
                lines.append(stripLineB)

    return lines


def sentences(a, b):
    """Return sentences in both a and b"""
    sentences = []
    tokenize_a = sent_tokenize(a, language='english')
    tokenize_b = sent_tokenize(b, language='english')

    for sentence_a in tokenize_a:
        for sentence_b in tokenize_b:

            if sentence_a == sentence_b and sentence_b not in sentences:
                sentences.append(sentence_b)

    return sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings = set()
    len_a = len(a)
    len_b = len(b)
    substr_a = set()
    substr_b = set()

    for line in a.strip().split("\n"):
        if n > len_a:
            continue

        i = 0
        end = 0
        while end < len_a:
            end = i + n
            substr_a.add(line[i:end])
            i += 1

    for line in b.strip().split("\n"):
        if n > len_b:
            continue

        i = 0
        end = 0
        while end < len_b:
            end = i + n
            substr_b.add(line[i:end])
            i += 1

    for i in substr_a:
        if i in substr_b:
            substrings.add(i)

    return list(substrings)
