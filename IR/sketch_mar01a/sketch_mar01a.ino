#define DECODE_NEC 1

#include <IRremote.h>

int IR_RECEIVE_PIN = 11;
int bulb = 9;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
    pinMode(bulb, OUTPUT);
}

void loop() {
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        IrReceiver.resume(); // Enable receiving of the next value

        if (IrReceiver.decodedIRData.command == 0x45) {
            Serial.println("ON");
            digitalWrite(bulb, HIGH); 
        } 
        else if (IrReceiver.decodedIRData.command == 0x47) {
            Serial.println("OFF");
            digitalWrite(bulb, LOW);
        }
    }
}
