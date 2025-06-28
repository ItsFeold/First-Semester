/*File: factor.c*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// typedef and unistd.h needed to store 128bit integers.
typedef __int128_t i128;

// Modular multiplication to prevent overflow
i128 modular_multiply(i128 a, i128 b, i128 mod) {
  i128 result = 0;
  a = a % mod;
  b = b % mod;

  while (b > 0) {
    if (b & 1) {
      result += a;
      if (result >= mod) result -= mod;
    }
    a <<= 1;
    if (a >= mod) a -= mod;
    b >>= 1;
  }
  return result;
}

// Updated polynom function using modular multiplication
i128 polynom(i128 x, i128 b, i128 n) {
  return (modular_multiply(x, x, n) + b) % n;
}

// abs() funtion for 128bit integers
i128 int128_tABS(i128 n) {
  if (n < 0)
    return -n;
  else
    return n;
}

// function to calculate the GCD of two 128bit integers
i128 gcd(i128 a, i128 b) {
  while (b != 0) {
    i128 temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// function to turn string into an 128bit integer. (need not check for negative
// values as they will NOT be given) this is very similiar to atoi
i128 atoint128_t(const char *s) {
  // initializing pointer to start of string
  const char *p = s;
  i128 val = 0;

  // while character in string is a digit
  while (*p >= '0' && *p <= '9') {
    val = (10 * val) + (*p - '0');
    // go to next value by incrementing pointer
    p++;
  }
  // returning the 128bit integer!
  return val;
}

// function to print 128bit integers (by turning number into string)
//(it's important we go from right to left)
int print_int128(i128 n) {
  if (n == 0) return printf("0\n");

  // can hold up to 40 digits (enough for 128bits)
  char str[40] = {0};
  char *s = str + sizeof(str) - 1;  // start at the end
  while (n != 0) {
    // if it goes over 40 digits, which cant happen for 128bit numbers.
    if (s == str) return -1;  // never happens

    // decrement value of pointer to go to next digit
    *--s =
        "0123456789"[n % 10];  // save last digit (from this array that contains
                               // all digits, get the one we want by n % 10)
    n /= 10;                   // go to next digit
  }
  return printf("%s", s);
}

// function to check if a number is prime or not:
i128 isPrime(i128 n) {
  if (n <= 1) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0 || n % 3 == 0) return 0;
  // The smallest factor of a number greater than one cannot be greater than the
  // square root of that number.
  for (i128 i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return 0;
  }
  return 1;
}

// driver code
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./factor <semiprime>\n");
    return 1;
  }

  // convert number from string (since it comes from command line) to an 128bit
  // integer type.
  i128 N = atoint128_t(argv[1]);

  // sole edge case since our x and y later start at 2:
  if (N == 4) {
    printf("Factors: 2 2\n");
    return 0;
  }

  // Rho's algorithm implementation:
  i128 x;
  i128 y;
  i128 d;

  // need many different constants c for polyonym.
  for (i128 c = N / 2; c <= N; c++) {
    x = 2;
    y = 2;
    d = 1;
    while (d == 1) {
      x = polynom(x, c, N);
      y = polynom(polynom(y, c, N), c, N);
      d = gcd(int128_tABS(x - y), N);
    }
    // failed
    if (d == N || isPrime(d) == 0 || isPrime(N / d) == 0) continue;
    // If d != 1 and d == 1, print the factors.
    printf("Factors: ");
    print_int128(d);
    printf(" ");
    i128 otherprime = N / d;
    print_int128(otherprime);
    printf("\n");
    return 0;
  }

  // terminate gracefully.
  printf("Error! The number you gave is not semiprime/couldn't be factored!\n");
  return 1;
}
