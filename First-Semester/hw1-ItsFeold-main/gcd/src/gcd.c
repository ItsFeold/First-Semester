/*File: gcd.c*/
#include <stdio.h>
#include <stdlib.h>
//stdio.h needed for output and stdlib needed for atoi()  and llabs()

//function to calculate the GCD of two integers
long long int gcd(long long int a, long long int b)
{   
    //no need to check if a or b is equal to 0, do the same in main
    if(a % b == 0)
        return llabs(b);

    return gcd(b, a % b);
}

int main(int argc, char * argv[])
{
    //check for incorrect usage of gcd program
    if(argc != 3)
    {
        printf("Usage: ./gcd <num1> <num2>\n");
        return 1; 
    }

    //convert numbers entered by user in command line (which are string by default) from string to long long int data type
    long long int num1 = atoll(argv[1]); 
    long long int num2 = atoll(argv[2]);

    //check if either num1 or num2 are 0, in which case program exits with exit code 1; 
    if(num1 == 0 || num2 == 0)
    {
        printf("Error: The given integers must be non-zero");
        return 1;
    }
        
    //calculating result by calling the gcd function 
    long long int result = gcd(num1, num2);
    printf("gcd(%lld, %lld) = %lld", num1, num2, result);
    return 0;   
}
