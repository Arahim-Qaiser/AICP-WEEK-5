#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

bool isValidDay(const string& day) {
    string validDays[] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
    for (const string& validDay : validDays) {
        if (day == validDay) {
            return true;
        }
    }
    return false;
}

bool isValidHour(int hour) {
    return hour >= 0 && hour <= 23;
}

bool isValidHours(int hours) {
    return hours > 0;
}

bool isValidFrequentParkingNumber(const string& number) {
    if (number.length() != 5) {
        return false;
    }

    int total = 0;
    for (int i = 0; i < 4; ++i) {
        total += stoi(number.substr(i, 1)) * (i + 1);
    }
    int checkDigit = (11 - total % 11) % 10;
    return checkDigit == stoi(number.substr(4, 1));
}

double calculatePrice(const string& day, int arrivalHour, int hours, const string& frequentNumber) {
    double price = 0;

    if (day == "SUN") {
        price = 2.0;
    }
    else if (day == "SAT") {
        price = 3.0;
    }
    else {
        if (arrivalHour < 16) {
            price = 10.0;
        }
        else {
            price = 2.0;
        }
    }

    double discount;
    if (isValidFrequentParkingNumber(frequentNumber)){
        if (arrivalHour >= 16 && arrivalHour < 24) {
            price *= (1 - 0.5);
        }
        else {
            price *= (1 - 0.1);
        }
}

    return price * hours;
}

int main() {
    string day, frequentNumber;
    int arrivalHour, hours;

    cout << "\t\t\t\t\tWelcome User to the Car Parking System :)\n\n\n";

    do {
        cout << "Enter the day (SUN, MON, TUE, WED, THU, FRI, SAT): ";
        cin >> day;
        if (!isValidDay(day)) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!isValidDay(day));

    do {
        cout << "Enter the arrival hour (0-23): ";
        cin >> arrivalHour;
        if (!isValidHour(arrivalHour)) {
            cout << "Invalid input! Please enter a value between 0 and 23." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!isValidHour(arrivalHour));

    do {
        cout << "Enter the number of hours parked: ";
        cin >> hours;
        if (!isValidHours(hours)) {
            cout << "Invalid number of hours! Please enter a positive value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!isValidHours(hours));
    
 
    
    cout << "Enter frequent parking number: ";
    cin >> frequentNumber;

    double price = calculatePrice(day, arrivalHour, hours, frequentNumber);
    cout << "The total parking fee is: $" << fixed << setprecision(2) << price << endl;

    double payment;
    do {
        cout << "Enter payment amount: $";
        cin >> payment;
        if (payment < price) {
            cout << "Insufficient payment! Please enter an amount equal to or greater than the total fee." << endl;
        }
    } while (payment < price);
    double dailyTotal = 0.0;
    dailyTotal += payment;

    cout << "Thank you for your payment." << endl;
    cout << "Daily total: $" << dailyTotal << endl;
    return 0;
}
