#include <Wire.h>
#include <Adafruit_TCS34725.h>


/* Initialise with specific int time and gain values */
Adafruit_TCS34725 g_tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
const int interruptPin = 2;
volatile boolean state = false;


//Interrupt Service Routine
void isr() {
    state = true;
}


/*  tcs.getRawData() does a delay(Integration_Time) after the sensor readout.
    We don't need to wait for the next integration cycle because we receive an interrupt when the integration cycle is complete*/
void getRawData_noDelay(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c) {
    *c = g_tcs.read16(TCS34725_CDATAL);
    *r = g_tcs.read16(TCS34725_RDATAL);
    *g = g_tcs.read16(TCS34725_GDATAL);
    *b = g_tcs.read16(TCS34725_BDATAL);
}


void setup() {
    pinMode(interruptPin, INPUT_PULLUP); //TCS interrupt output is Active-LOW and Open-Drain
    attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);

    Serial.begin(9600);

    if (g_tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1);
    }

    // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
    g_tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
    g_tcs.setInterrupt(true);

    Serial.flush();
}


void loop() {
    if (state) {
        uint16_t r, g, b, c, colorTemp, lux;
        getRawData_noDelay(&r, &g, &b, &c);
        colorTemp = g_tcs.calculateColorTemperature(r, g, b);
        lux = g_tcs.calculateLux(r, g, b);

        Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
        Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
        Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
        Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
        Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
        Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
        Serial.println(" ");
        Serial.flush();

        g_tcs.clearInterrupt();
        state = false;
    }
}
