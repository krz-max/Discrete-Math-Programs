from math import sqrt

def Euler(n):
    i = int(sqrt(int(n)))
    if i % 2 == 0:
        i -= 1
    while i >= 2:
        if int(n) % int(i) == 0:
            return (int(i)-1) * (int(n) // int(i) - 1)
        i -= 2

def modinv(e, phiN) : 
    phiN0 = phiN 
    y = 0
    x = 1
  
    if (phiN == 1) : 
        return 0
  
    while (int(e) > 1) : 
        # q is quotient 
        q = int(e) // phiN 
  
        t = phiN 
  
        # phiN is remainder now, process 
        # same as Euclid's algo 
        phiN = int(e) % phiN 
        e = t
        t = y 
  
        # Update x and y 
        y = x - q * y 
        x = t 
  
  
    # Make x positive 
    if (x < 0) : 
        x = x + phiN0 
  
    return x 


def modularExponent(A, n, e):
    cipherText = 1
    power = int(A) % int(n)
    while int(e) > 0:
        if int(e) % 2 == 1:
            cipherText = (cipherText*power)%int(n)
        power = (power*power)%int(n)
        e = e >> 1
    return chr(cipherText)

def main():
    test = input()
    (n, e, c) = test.split()
    cipherMessage = c.split(',')
    phiN = Euler(n) 
    x = modinv(e, phiN)
    for A in cipherMessage:
        print(modularExponent(A, n, x), end = '')

if __name__ == '__main__':
    main()