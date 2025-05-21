#include <Wire.h>
#include <DS3231.h>

//Global constants
int SEC_IN_HOUR = 3600;

//Global variables
int now = 0;
int lastFedTime = 0;
DS3231 clock;
int test12;
int test21;

void setup() {
    Serial.begin(9600);
    Serial.println("Initialize DS3231");
    Serial.println("Initialize DS3231");
    clock.begin();
    // Manual (Year, Month, Day, Hour, Minute, Second)
    clock.setDateTime(2025, 5, 16, 4, 20, 0);
}

/** 
 * Get the current time
 * @param: globalTime refers to which global variable to update,
 *         now or lastFedTime
*/
void getTime (int& globalTime) {
    globalTime = clock.getDateTime().unixtime;
}

int timePassedInHours () {
    int seconds = now - lastFedTime;
    int hours = seconds / SEC_IN_HOUR;
    return hours;
}