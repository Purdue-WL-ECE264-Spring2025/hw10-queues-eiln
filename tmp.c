
#include <stdio.h>
#include <math.h>
int get_value();
void validate(int);
void rotate(int);
int check_prime(int);
int rotateNum(int, int);
void print_status(int, int, int);
void print_rotations(int);

int main()
{
  int num_eval;
  //num_eval = get_value();
  num_eval = 497944;
  rotate(num_eval);
  return 0;
}

int get_value()
{
  int num;
  do
  {
    printf("Enter a number to evaluate -> ");
    scanf("%d", &num);
    if (num <= 0)
    {
      printf("Error! Number must be greater than zero.\n");
    }
  }
  while (num <= 0);  return (num);
}

void rotate(int n)
{
  int original = n;
  int prime = 1;
  int onlyPrime = 0;
  int print_One = 0;  int digits = 0;
  int total = n;
  while (total != 0)
  {
    digits++;
    total /= 10;
  }

  int rotation = n;
  do
  {
    if (check_prime(rotation))
    {
      print_One = 1;
      onlyPrime = 1;
    }
    else
    {
      prime = 0;
    }
    rotation = rotateNum(rotation, digits);
  }
  while (rotation != original);
  print_status(prime, onlyPrime, original);
}

//functions in rotate

int check_prime(int number)
{
    for (int i = 2; i < number; i++) {
        if (number % i == 0 && i != number) return 0;
    }
    return 1;
}

int rotateNum (int n, int digitCount)
{
  int last_digit;
  int remain;
  int final;
  int power = 1;
  int i;  last_digit = n % 10;
  remain = n / 10;  for (i = 1; i < digitCount; i++)
  {
    power *= 10;
  }  final = last_digit * power + remain;
  return(final);
}

//print status
void print_status(int prime,int onlyPrime, int original)
{
  if (prime)
  {
    printf("Status: %d is a fully circular prime. \n", original);
  }
  else if (onlyPrime)
  {
    printf("Status: %d contains primes in the following rotations: ", original);
    print_rotations(original);
    printf("\n");
  }
  else
  {
    printf("Status: %d is not a circular prime and no rotation is prime. \n", original);
  }
}

void print_rotations(int n)
{
  int original = n;
  int firstPrint = 0;
  int digitCount = 0;
  int value = n;
  while (value != 0)
  {
    digitCount++;
    value /= 10;
  }
  int rotation = n;
  do
  {
    if (check_prime(rotation))
    {
      if (!firstPrint)
      {
        printf("%d",rotation);
        firstPrint = 1;
      }
      else
      {
        printf(" %d", rotation);
      }
    }
    rotation = rotateNum(rotation, digitCount);
  }
  while (rotation != original);
  return;
}
