word = input()
while word != ".":
    sublen = 1
    for i in range(1, len(word)):
        while word[i] != word[i % sublen]:
            sublen += 1
    i += 1
    if i % sublen == 0:
        print(i // sublen)
    else:
        print(1)
    word = input()

