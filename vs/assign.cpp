

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Facility {
    string name;
    int dayPrice;
    int nightPrice;
};

struct Booking {
    string facilityName;
    string date;
    string startTime;
    string endTime;
    bool isBooked;
    int bookingAmount;
};

void bookFacility(vector<Booking>& bookings, const Facility& facility, const string& date, const string& startTime, const string& endTime, int& totalAmount) {
    // Check if the facility is already booked for the requested time slot
    for (const Booking& existingBooking : bookings) {
        if (existingBooking.facilityName == facility.name && existingBooking.isBooked) {
            if ((startTime >= existingBooking.startTime && startTime < existingBooking.endTime) ||
                (endTime > existingBooking.startTime && endTime <= existingBooking.endTime) ||
                (startTime <= existingBooking.startTime && endTime >= existingBooking.endTime)) {
                cout << "Booking Failed, Already Booked" << endl;
                return;
            }
        }
    }

    // Create a new booking
    Booking newBooking;
    newBooking.facilityName = facility.name;
    newBooking.date = date;
    newBooking.startTime = startTime;
    newBooking.endTime = endTime;
    newBooking.isBooked = true;

    // Calculate booking amount based on time slots
    if (startTime >= "10:00" && endTime <= "16:00") {
        newBooking.bookingAmount = (stoi(endTime.substr(0, 2)) - stoi(startTime.substr(0, 2))) * facility.dayPrice;
    } else if (startTime >= "16:00" && endTime <= "22:00") {
        newBooking.bookingAmount = (stoi(endTime.substr(0, 2)) - stoi(startTime.substr(0, 2))) * facility.nightPrice;
    } else {
        cout << "Invalid booking time" << endl;
        return;
    }

    // Update total amount and add the new booking
    totalAmount += newBooking.bookingAmount;
    bookings.push_back(newBooking);

    cout << "Booked, Rs. " << newBooking.bookingAmount << endl;
}

int main() {
    const int MAX_BOOKINGS = 100; // Maximum number of bookings, adjust as needed
    vector<Facility> facilities = {{"Clubhouse", 100, 500}, {"Tennis Court", 50, 50}};
    vector<Booking> bookings;
    int totalAmount = 0;

    // Test cases
    bookFacility(bookings, facilities[0], "26-10-2020", "16:00", "22:00", totalAmount);
    bookFacility(bookings, facilities[1], "26-10-2020", "16:00", "20:00", totalAmount);
    bookFacility(bookings, facilities[0], "26-10-2020", "16:00", "22:00", totalAmount);
    bookFacility(bookings, facilities[1], "26-10-2020", "17:00", "21:00", totalAmount);
    bookFacility(bookings, facilities[0], "26-10-2020", "14:00", "22:00", totalAmount);

    cout << "Total Amount: Rs. " << totalAmount << endl;

    return 0;
}