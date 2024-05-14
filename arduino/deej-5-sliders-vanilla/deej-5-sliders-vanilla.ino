const int NUM_SLIDERS = 4;
const int NUM_BUTTONS = 5;

const int analogSliderInputs[NUM_SLIDERS] = {A0, A1, A2, A3};
const int digitalButtonInputs[NUM_BUTTONS] = {2, 3, 4, 5, 6};

int analogSliderValues[NUM_SLIDERS];
int analogButtonValues[NUM_BUTTONS];

bool isMuted[NUM_BUTTONS] = {0, 0, 0, 0, 0};

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogSliderInputs[i], INPUT);
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(digitalButtonInputs[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  printSliderValues(); // For debug

  updateButtonValues();
  sendButtonValues(); // Actually send data (all the time)
  printButtonValues(); // For debug

  for (int i; i < isMuted; i++) {
    if (isMuted[i]) {
      // send faux slider value to keep muted
    } else {
      // send actual slider value
    }
  }

  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogSliderInputs[i]);
  }
}

void updateButtonValues() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
     analogButtonValues[i] = digitalRead(digitalButtonInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void sendButtonValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (analogButtonValues[i] == 1) {
      isMuted[i] = true;
    }

    builtString += String((int)analogButtonValues[i]);

    if (i < NUM_BUTTONS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void printButtonValues() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
    String printedString = String("Button #") + String(i + 1) + String(": ") + String(analogButtonValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_BUTTONS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
