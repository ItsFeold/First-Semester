/*file rsa.c*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
//including libraries. stdlib.h needed for funcs like atoll(), string.h needed for funcs like strcmp.

//function to calculate the GCD of two integers
long long gcd(long long a, long long b)
{   
    //a and b are always positive, so this version of gcd is slightly simplified 
    if(a % b == 0)
        return b;
    return gcd(b, a % b);
}
//function to check if a number is prime or not: 
long long isPrime(long long n)
{
    if(n <= 1)
        return 0;
    //2 and 3 are primes 
    if(n <= 3)
        return 0;
    if(n % 2 == 0 || n % 3 == 0)
        return 0;
    //The smallest factor of a number greater than one cannot be greater than the square root of that number.
    for(long long i=5; i*i<=n; i+=6)
    {
        if(n % i == 0 || n % (i+2) == 0)
            return 0;
    }
    return 1;
}

//function for Modular Exponentiation
long long modExpo(long long base, long long exponent, long long modulus)
{   
    if(modulus == 1)
        return 0;
    long long result = 1;
    base = base % modulus;
    while(exponent > 0)
    {
        if(exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

//function for encrypting message 
long long encrypt(long long e, long long p, long long q, long long m)
{
    long long int N = p * q;
    return modExpo(m, e, N); 
}

//function for decrypting message
long long decrypt(long long d, long long p, long long q, long long m)
{
    long long N = p * q;
    return modExpo(m, d, N);
}

//driver code 
int main(int argc, char * argv[])
{
    //checking for correct usage of rsa. Printing instructions for incorrect input and returning 1.
    if(argc != 6)
    {
        printf("Usage: ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>\n");
        return 1;
    }
    
    //converting user input from string(since we get input from command line) to long long data type
    //also initiliazing helpful variables for later 
    long long e = atoll(argv[2]);
    long long d = atoll(argv[3]);
    long long p = atoll(argv[4]);
    long long q = atoll(argv[5]);

    //if a is a prime then phi(a) = a-1, and phi(a*b) = phi(a)*phi(b), therefore phi(N) = phi(a)*phi(b) = (p-1)*(q-1)
    long long phi_N = (p-1)*(q-1);
    
    long long N = p * q; 

    //checking for valid first arguement(has to be either enc or dec)
    if(strcmp(argv[1], "enc") != 0 && strcmp(argv[1], "dec") != 0)
    {
        printf("First argument must be 'enc' or 'dec'\n");
        return 1;
    }
    //checking for negative numbers. Return 1 if any number is negative
    if(e <= 0 || d <= 0 || p <= 0 || q <= 0)
    {
        printf("Negative numbers are not allowed\n");
        return 1;
    }
    //checking for p and q to be prime: 
    if(isPrime(p) == 0 || isPrime(q) == 0)
    {
       printf("p and q must be prime\n");
       return 1; 
    }
    //checking to see if e is cooprime with phi(N)
    //because N = p*q 
    if(gcd(e, phi_N) != 1)
    {
        printf("e is not coprime with phi(N)\n");
        return 1;
    }
    //checking if e * d mod phi(N) is 1
    if((e*d) % phi_N != 1)
    {
        printf("e * d mod phi(N) is not 1\n");
        return 1;
    }

    //read message m 
    long long m;
    //checking to see if m (message) was read correctly.
    int scanReturn = scanf("%lld", &m);
    if(scanReturn != 1)
        return 1;

    //checking if m is negative
    if(m < 0)
    {
        printf("Negative numbers are not allowed\n");
        return 1;
    }

    //checking to see if N is larger than message
    if(m >= N)
    {
        printf("Message is larger than N\n");
        return 1;
    }

    //check whether or not operation is encryption or decryption from user input and call corresponding function.
    if(strcmp(argv[1], "enc") == 0)
        printf("%lld\n", encrypt(e, p, q, m));
    else    
        printf("%lld\n", decrypt(d, p, q, m));

    //exiting.
    return 0;
}
