#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Ask the user for the journey distance
double getDistance() {
    double distance;

    while (true) {
        cout << "Enter distance travelled in miles: ";

        // Only accept a number above zero
        if (cin >> distance && distance > 0) {
            return distance;
        }

        cout << "Invalid input. Enter a distance greater than 0." << endl;
        // Clear the incorrect input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Ask the user to choose a fuel type
string getFuelType() {
    string fuelType;

    while (true) {
        cout << "Enter fuel type (petrol or diesel): ";
        cin >> fuelType;

        // Check that the fuel type is valid
        if (fuelType == "petrol" || fuelType == "diesel") {
            return fuelType;
        }

        cout << "Invalid fuel type. Enter petrol or diesel." << endl;
    }
}

// Calculate the CO2 for the journey
double calculateCO2(double distance, string fuelType) {
    // Values given in the challenge instructions
    const double fuelConsumption = 9.66;
    const double dieselFactor = 2.68;
    const double petrolFactor = 2.31;
    // Work out how many litres the journey uses
    double litresUsed = (distance * fuelConsumption) / 100;

    // Use the correct value for the selected fuel
    if (fuelType == "diesel") {
        return litresUsed * dieselFactor;
    }

    return litresUsed * petrolFactor;
}

int main() {
    // Get the details and calculate the result
    double distance = getDistance();
    string fuelType = getFuelType();
    double result = calculateCO2(distance, fuelType);

    // Display the answer to two decimal places
    cout << fixed << setprecision(2);
    cout << "Estimated CO2 emissions: " << result << " kg" << endl;

    return 0;
}
