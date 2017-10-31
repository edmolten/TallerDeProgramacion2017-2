

word = input()

def hashing(word):
    value = []
    for i in word:
        value.append(ord(i))
    result = 0
    for i in range(len(value)):
        result += value[i] * 2**i
    return result

while(word!="."):

    for i in range(1,len(word)+1):

        if len(word)%i != 0: continue
        elif i == len(word):
            print(1)
            break
        else:
            hash_substring = hashing(word[:i])
            ok = True
            for j in range(i,len(word)+1-i,i):
                if hashing(word[j:j+i])!= hash_substring:
                    ok = False
                    break
            if ok:
                print(len(word)//i)
                break






    word = input()