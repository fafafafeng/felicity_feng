#include <iostream>
using namespace std;
int main()
{
    int numberOfToonies, numberOfLoonies, numberOfQuarters, numberOfDimes, numberOfNickels;
    int numberOfCents;

    cin >> numberOfToonies;
    cin >> numberOfLoonies;
    cin >> numberOfQuarters;
    cin >> numberOfDimes;
    cin >> numberOfNickels;

    numberOfCents = numberOfToonies * 200 + numberOfLoonies * 100 + numberOfQuarters * 25 + numberOfDimes * 10 + numberOfNickels * 5;

    cout << numberOfCents;

    return 0;
}
