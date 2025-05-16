#include <Wire.h>
#include <DS3231.h>

//Global constants
int SEC_IN_HOUR = 3600;

//Global variables
int now = 0;
int previous = 0;
DS3231 clock;

void setup() {
    Serial.begin(9600);
    Serial.println("Initialize DS3231");;
    clock.begin();
    // Manual (Year, Month, Day, Hour, Minute, Second)
    clock.setDateTime(2025, 5, 16, 4, 20, 0);
}

/** 
 * Get the urrent time
 * @param: globalTime refers to which global variable to update,
 *         now or previous
*/
void getTime (int& globalTime) {
    globalTime = rtc.getDateTime().unixtime;
}

int timePassedInHours () {
    int secondsPassed = now - previous;
    int hoursPassed = secondsPassed / SEC_IN_HOUR;
    return hoursPassed;
}