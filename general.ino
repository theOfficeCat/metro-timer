void encoderISR() {
    if (digitalRead(DT_PIN) == HIGH) encoderDirection = 1;
    else encoderDirection = -1;
    encoderMoved = true;
}

#define NUM_PINS 13

bool button_pressed(int pin, bool pullUp = true) {
    const unsigned long debounceDelay = 30;
    static unsigned long lastTime[NUM_PINS] = {0};
    static bool lastState[NUM_PINS] = {LOW};
    static bool stableState[NUM_PINS] = {LOW};

    if (pin < 0 || pin >= NUM_PINS) return false;

    bool reading = digitalRead(pin);

    bool pressed = pullUp ? (reading == LOW) : (reading == HIGH);

    if (reading != lastState[pin]) {
        lastTime[pin] = millis();
    }

    if ((millis() - lastTime[pin]) > debounceDelay) {
        if (pressed && !stableState[pin]) {
            stableState[pin] = true;
            lastState[pin] = reading;
            return true;
        }
        stableState[pin] = pressed;
    }

    lastState[pin] = reading;
    return false;
}

bool button_pressed_pull_down(int pin) {
    return button_pressed(pin, false);
}

bool button_pressed_pull_up(int pin) {
    return button_pressed(pin, true);
}
