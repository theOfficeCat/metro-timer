#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CLK_PIN 2   // INTERRUPCIÓN
#define DT_PIN  4

#define BUTTON_PIN 3

typedef enum {
    MAIN_MENU = 0,
    NEW_RUN_MENU
} menus_t;

int current_menu = MAIN_MENU;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

volatile int8_t encoderDirection = 0;
volatile bool encoderMoved = false;
volatile bool buttonPressed = false;

void encoderISR() {
    if (digitalRead(DT_PIN) == HIGH) encoderDirection = 1;
    else encoderDirection = -1;
    encoderMoved = true;
}

void buttonISR() {
    buttonPressed = true;
    Serial.println("meow");
}

void setup() {
    Serial.begin(115200);

    pinMode(CLK_PIN, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(DT_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(CLK_PIN), encoderISR, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
}

void loop() {
    if (current_menu == MAIN_MENU) {
        main_menu_action();
    } else if (current_menu == NEW_RUN_MENU) {
        new_run_action();
    }
}

