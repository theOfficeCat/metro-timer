#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CLK_PIN 2   // INTERRUPCIÓN
#define DT_PIN  4

#define BUTTON_ENC_PIN 5
#define BUTTON_OK_PIN 7
#define BUTTON_RETURN_PIN 6

typedef enum {
    MAIN_MENU = 0,
    NEW_RUN_MENU
} menus_t;

int current_menu = MAIN_MENU, old_menu = MAIN_MENU;
bool start = true;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

volatile int8_t encoderDirection = 0;
volatile bool encoderMoved = false;

void setup() {
    Serial.begin(115200);

    // Encoder rotation
    pinMode(CLK_PIN, INPUT_PULLUP);
    pinMode(DT_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(CLK_PIN), encoderISR, RISING);

    // Buttons
    pinMode(BUTTON_ENC_PIN, INPUT_PULLUP);
    pinMode(BUTTON_OK_PIN, INPUT);
    pinMode(BUTTON_RETURN_PIN, INPUT);

    // Screen initialization
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

    if (current_menu != old_menu) {
        start = true;
    }

    old_menu = current_menu;
}

