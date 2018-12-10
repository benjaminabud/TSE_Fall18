#include <MIDI_Controller.h> // Include the library


//For buttons
const uint8_t velocity = 0b1111111; // Maximum velocity (0b1111111 = 0x7F = 127) - Sets velocity maximum all the time, related to calling 'Digital' class
const uint8_t C4 = 60;              // Note number 60 is defined as middle C in the MIDI specification
const uint8_t F4 = 65;              
const uint8_t G4 = 67;
const uint8_t a4 = 69;

// Create a new instance of the class 'Digital', called 'button', on pin 2, that sends MIDI messages with note 'C4' (60) on channel 1, with velocity 127
Digital button1(2, C4, 1, velocity);
Digital button2(3, F4, 1, velocity);
Digital button3(4, G4, 1, velocity);
Digital button4(5, a4, 1, velocity);


//For potentiometers
// Create a new instance of the class 'Analog', called 'potentiometer', on pin A0, 
// that sends MIDI messages with controller 7 (channel volume) on channel 1
Analog potentiometer(A0, MIDI_CC::Channel_Volume, 1);

const int minimumValue = 3;    // the analog value read when the potentiometer is in the minimum position.
const int maximumValue = 1020; // the analog value read when the potentiometer is in the maximum position.

int mapCalibrated(int value) {
  value = constrain(value, minimumValue, maximumValue); // make sure that the analog value is between the minimum and maximum value
  return map(value, minimumValue, maximumValue, 0, 1023); // map the value from [minimumValue, maximumValue] to [0, 1023]
}


void setup() {
  //For potentiometers
  potentiometer.map(mapCalibrated); // apply the 'mapCalibrated' function on the analog input of 'potentiometer'
}

void loop() {
  //For both buttons and potentiometers
  // Refresh the button (check whether the button and potentiometer's state has changed since last time, if so, send it over MIDI)
  MIDI_Controller.refresh();

  //For potentiometers
  // Refresh the MIDI controller (check whether the potentiometer's input has changed since last time, if so, send the new value over MIDI)
  //MIDI_Controller.refresh();
}
