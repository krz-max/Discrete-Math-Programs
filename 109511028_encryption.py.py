def modularExponent(A, n, e):
    cipherText = 1
    power = ord(A) % int(n)
    while int(e) > 0:
        if int(e) % 2 == 1:
            cipherText = (cipherText*power)%int(n)
        power = (power*power)%int(n)
        e = int(e)/2
    return cipherText

def main():
    test = input()
    (n, e, mes) = test.split()
    for i in range(0, len(mes)):
        print(modularExponent(mes[i], n, e), end = '')
        if i != len(mes)-1:
            print(',', end = '')

if __name__ == '__main__':
    main()    

