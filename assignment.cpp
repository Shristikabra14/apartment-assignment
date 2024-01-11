#include <iostream>
#include <vector>
#include <string>
using namespace std;

//facilities - name, price , booked or not
struct facility {
    string name; //name of the facility(clubhouse , tennis court)
    int day; // price per hour during day
    int night; //price per hour during night
    bool isBooked; // indicating whether facility is currently booked or not 
};

//booking - name, date, start time, end time, booked or not, booking amount
struct Booking{
    string facilityname; //name of the facility being booked
    string date;  //date of booking
    string starttime;  //start time of booking 
    string endtime; //end time of booking 
    bool isBooked;  //indicating whether booking is confirmed
    int bookingamt; // amount to be paid fr booking
};

//to book facility 
void bookfacility (vector<Booking>& bookings, const facility& facility, const string& date, const string& starttime, const string& endtime, int& totalamt){
    // time slot is available for booking or not
    for(const Booking& booking : bookings){
        if(booking.facilityname == facility.name && booking.date == date && booking.isBooked){
            if((starttime >= booking.starttime && starttime < booking.endtime) || (endtime > booking.starttime && endtime <= booking.endtime) || (starttime <= booking.starttime && endtime >= booking.endtime)){
                // time slot is already booked 
                cout << "booking failed, already booked" << endl;
                return;
            }
        }
    }

    //time slot is available, create a new booking
    Booking newbooking;
    newbooking.facilityname = facility.name;
    newbooking.date = date;
    newbooking.starttime = starttime;
    newbooking.endtime = endtime;
    newbooking.isBooked = true;

    //calculation for pricing based on time slots
    if (starttime >= "10:00" && endtime <= "16:00") {
        newbooking.bookingamt = (stoi(endtime.substr(0, 2)) - stoi(starttime.substr(0, 2))) * facility.day;
    } 

    else if (starttime >= "16:00" && endtime <= "22:00") {
        newbooking.bookingamt = (stoi(endtime.substr(0, 2)) - stoi(starttime.substr(0, 2))) * facility.night;
    } 

    else {
        //  time slot is invalid
        cout << "Invalid booking time" << endl;
        return;
    }

    // update total amount nd add new booking 
    totalamt += newbooking.bookingamt;
    bookings.push_back(newbooking);

    cout << "Booked, Rs. " << newbooking.bookingamt << endl;
}



int main(){
    vector<facility> facilities = {{"Clubhouse", 100, 500, false} , {"Tennis court", 50, 50, false}};

    vector<Booking> bookings;

    int totalamt = 0; 

    bookfacility(bookings, facilities[0] , "26-10-2020", "16:00", "22:00", totalamt);
    bookfacility(bookings, facilities[1] , "26-10-2020", "16:00", "20:00", totalamt);
    bookfacility(bookings, facilities[0] , "26-10-2020", "16:00", "22:00", totalamt);
    bookfacility(bookings, facilities[1] , "26-10-2020", "17:00", "21:00", totalamt);
    bookfacility(bookings, facilities[0] , "26-10-2020", "10:00", "16:00", totalamt);
    bookfacility(bookings, facilities[1] , "26-10-2020", "12:00", "14:00", totalamt);

    return 0;
}