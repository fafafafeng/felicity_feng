#include <iostream>
#include <math.h>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    double principal, interestRate;
    int numberOfMonths;
    char command;

    double m;
    int monthsPast;

    double monthlyPayment, interestPortion, principalPortion, remainingPrincipal;

    cin >> principal >> interestRate >> numberOfMonths;

    double principalOutstanding = principal;

    m = interestRate / (12 * 100);
    monthlyPayment = (principal * m * pow(1 + m, numberOfMonths)) / (pow(1 + m, numberOfMonths) - 1);

    cin >> command;

    while (command != 'e') {
        if (command == 'p') {
            cout << monthlyPayment << endl;
        }
        else if (command == 'd') {
            cin >> monthsPast;

            if (monthsPast >= 1 && monthsPast <= numberOfMonths) {
                for (int i = 1; i <= monthsPast; ++i) {
                    interestPortion = principalOutstanding * m;
                    principalPortion = monthlyPayment - interestPortion;
                    remainingPrincipal = principalOutstanding - principalPortion;
                    principalOutstanding = remainingPrincipal;
                }
            }
            cout << principalOutstanding + principalPortion << " " << interestPortion << " " << remainingPrincipal << endl;
            principalOutstanding = principal;
        }
        cin >> command;
    }
    return 0;
}
