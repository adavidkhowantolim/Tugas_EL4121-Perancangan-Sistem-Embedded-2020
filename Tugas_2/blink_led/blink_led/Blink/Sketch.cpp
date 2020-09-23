/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

/* SOAL 3
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
*/

/* SOAL 6 dan 7
void setup() {
	TCCR1A = 0;
	TCCR1B = 0;
	bitSet(TCCR1B, CS12);  // 256 prescaler
	bitSet(TIMSK1, TOIE1); // timer overflow interrupt
	pinMode(LED_BUILTIN, OUTPUT);
}

ISR(TIMER1_OVF_vect) {
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void loop() {
}
*/

void setup()
{
	DDRB |= B00100000;  // set pin13 to output without affecting other pins
	// above is identical to pinMode(LEDPIN, OUTPUT); using Direct Port Manipulation
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 15624;  // = (target time / timer resolution) - 1 or 1 / 6.4e-5 - 1 = 15624
	//OCR1A = 15624>>1;  // divide by two >>EDIT added this line<<
	TCCR1B |= (1 << WGM12);// CTC mode on
	TCCR1B |= (1 << CS10);// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);// timer compare intrupt
	sei();
}

void loop()
{
	// do something here unaffected by your blinking led
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= B00100000;// toggles bit which affects pin13
}
