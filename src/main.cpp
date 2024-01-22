#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "RTC_DS3231_DST.h"

// Clock Pins
const byte PIN_CLK_RED = A0;
const byte PIN_CLK_GREEN = A1;
const byte PIN_CLK_ORANGE = A2;

// Screen pins
const byte PIN_RED_1 = 3;
const byte PIN_RED_2 = 4;
const byte PING_RED_3 = 5;

const byte PIN_GREEN_1 = 6;
const byte PING_GREEN_2 = 7;
const byte PING_GREEN_3 = 8;

const byte PIN_DIO_O1 = 9;
const byte PIN_DIO_O2 = 10;
const byte PIN_DIO_O3 = 11;

// Other
const byte PIN_GREEN_AM = 13;
const byte PIN_GREEN_PM = 12;
const byte PIN_RED_YELLOW_AM = 2;
const int BACKLIGHT = 100;
const int YEAR_ORANGE = 2018;

// RED Displays
SevenSegmentExtended red1(PIN_CLK_RED, PIN_RED_1);
SevenSegmentTM1637 red2(PIN_CLK_RED, PIN_RED_2);
SevenSegmentExtended red3(PIN_CLK_RED, PING_RED_3);

// GREEN Displays
SevenSegmentExtended green1(PIN_CLK_GREEN, PIN_GREEN_1);
SevenSegmentTM1637 green2(PIN_CLK_GREEN, PING_GREEN_2);
SevenSegmentExtended green3(PIN_CLK_GREEN, PING_GREEN_3);

// ORANGE Displays
SevenSegmentExtended orange1(PIN_CLK_ORANGE, PIN_DIO_O1);
SevenSegmentTM1637 orange2(PIN_CLK_ORANGE, PIN_DIO_O2);
SevenSegmentExtended orange3(PIN_CLK_ORANGE, PIN_DIO_O3);

RTC_DS3231 rtc;

void setup()
{

    pinMode(PIN_CLK_RED, OUTPUT);
    pinMode(PIN_CLK_GREEN, OUTPUT);
    pinMode(PIN_CLK_ORANGE, OUTPUT);
    pinMode(PIN_DIO_O1, OUTPUT);
    pinMode(PIN_DIO_O2, OUTPUT);
    pinMode(PIN_DIO_O3, OUTPUT);
    pinMode(PIN_GREEN_1, OUTPUT);
    pinMode(PING_GREEN_2, OUTPUT);
    pinMode(PING_GREEN_3, OUTPUT);
    pinMode(PIN_RED_1, OUTPUT);
    pinMode(PIN_RED_2, OUTPUT);
    pinMode(PING_RED_3, OUTPUT);
    pinMode(PIN_GREEN_AM, OUTPUT);
    pinMode(PIN_GREEN_PM, OUTPUT);
    pinMode(PIN_RED_YELLOW_AM, OUTPUT);

    Serial.begin(9600);

    orange1.init();
    orange2.init();
    orange3.init();
    orange1.setBacklight(BACKLIGHT);
    orange2.setBacklight(BACKLIGHT);
    orange3.setBacklight(BACKLIGHT);

    green1.init();
    green2.init();
    green3.init();
    green1.setBacklight(BACKLIGHT);
    green2.setBacklight(BACKLIGHT);
    green3.setBacklight(BACKLIGHT);

    red1.init();
    red2.init();
    red3.init();
    red1.setBacklight(BACKLIGHT);
    red2.setBacklight(BACKLIGHT);
    red3.setBacklight(BACKLIGHT);

#ifndef ESP8266
    while (!Serial)
        ; // for Leonardo/Micro/Zero
#endif

    Serial.begin(9600);

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, lets set the time!");
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    digitalWrite(PIN_RED_YELLOW_AM, HIGH);
}

void serialPrintDatetime(DateTime now)
{
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void syncRedAmPm(uint8_t hour)
{
    if (hour >= 13)
    {
        digitalWrite(PIN_GREEN_AM, LOW);
        digitalWrite(PIN_GREEN_PM, HIGH);
    }
    else
    {
        digitalWrite(PIN_GREEN_AM, LOW);
        digitalWrite(PIN_GREEN_PM, HIGH);
    }
}

void loop()
{
    DateTime now = rtc.now();

    serialPrintDatetime(now);
    syncRedAmPm(now.hour());

    red1.printTime(11, 9, false);
    red2.print(now.year() + 8);
    red3.printTime(10, 07, false);

    green1.printTime(now.month(), now.day(), false);
    green2.print(now.year());
    green3.printTime(now.hour(), now.minute(), false);

    orange1.printTime(11, 9, false);
    orange2.print(YEAR_ORANGE);
    orange3.printTime(01, 24, false);

    delay(1000);
}