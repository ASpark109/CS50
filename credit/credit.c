#include <stdio.h>
#include <cs50.h>
#include <math.h>

int numOfSigns(long i);
long validity(long num, int l);
string cardType(long num);
long summation(long i);

int main()
{
    long i = get_long("Number: ");
    long res = summation(validity(i, 2)) + summation(validity(i, 1));

    if(res % 10 != 0)
    {
        printf("INVALID\n"); return 0;
    }
    printf("%s", cardType(i));
}

//determining the validity of the card
long validity(long i, int l)
{
    int u = 0;
    long sum = 0;
    int n = numOfSigns(i);
    bool z = false;

    z = (n % 2 == 0) ? true : false;

    if(l == 1)
    z = !z;

    for(long j = pow(10,n); j >= 10; j/=10)
    {   
        i = i % j;
        u = i / (j / 10);

        if(z)
        {
            u *= l;
            sum = u>=10 ? sum * 100 + u : sum * 10 + u;
        }
        z = !z;
    }
    return sum;
}

//determining the type of bank card
string cardType(long i)
{
    int u = 0;
    int n = numOfSigns(i);
    long sum = 0;

    //if the number of bits is less than 13, the card is not valid
    if(n < 13)
    return "INVALID\n";

    for(long j = pow(10,n); j >= 10; j/=10)
    {   
        u = i % j / (j / 10);
        sum = sum * 10 + u;

        //if the first number of the card is 4 - VISA
        if(sum == 4) return "VISA\n";

        //if the first numbers of the card is 34 || 37 - AMEX
        if(sum == 34 || sum == 37) return "AMEX\n";

        //if the first numbers of the card is 51 - 55, - MASTERCARD
        if(sum == 51 || sum == 52 || sum == 53 || sum == 54 || sum == 55) return "MASTERCARD\n";
    }

    return "INVALID\n";
}

//the function returns the number of digits in the number
int numOfSigns(long i)
{
    int n = 0;
    while(i > 0)
    {
        i /= 10;
        n++;
    }
    return n;
}


//summation of all digits of the number
long summation(long i)
{
    long sum = 0;
    int n = numOfSigns(i);
    for(long j = pow(10,n); j >= 10; j/=10)
    {
        sum += i % j / (j / 10);
    }
    return sum;
}
