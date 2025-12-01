/*********
  Versión corregida basada en tu código
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CLK_PIN 4
#define DT_PIN  3

// Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

typedef enum {
  NEW_RUN = 0,
  VIEW_DATA,
  MAIN_MENU_ITEMS
} main_menu_options_t;

const char *main_menu_texts[2] = {
  "New run",
  "View data"
};

int main_menu = NEW_RUN;

// Estado previa de A+B
int prevAB = 0;

// Tabla de transiciones (prev<<2 | curr) -> movimiento
// Valores típicos:  0 = sin movimiento, +1 paso adelante, -1 paso atrás
const int8_t trans_table[16] = {
  0,  1, -1,  0,
 -1,  0,  0,  1,
  1,  0,  0, -1,
  0, -1,  1,  0
};

void render_main_menu() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(31, 0);
  display.println("Metro timer");

  for (int i = 0; i < MAIN_MENU_ITEMS; ++i) {
    display.setCursor(15, 15 + 10*i);
    display.println(main_menu_texts[i]);
  }

  // dibuja el cursor en la opción actual (clamp por seguridad)
  int idx = constrain(main_menu, 0, MAIN_MENU_ITEMS - 1);
  display.setCursor(5, 15 + 10*idx);
  display.print(">");

  display.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);

  // leer estado inicial de A y B
  int a = digitalRead(CLK_PIN);
  int b = digitalRead(DT_PIN);
  prevAB = (a << 1) | b;

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(200);
  render_main_menu();
}

void loop() {
  // lee A y B
  int a = digitalRead(CLK_PIN);
  int b = digitalRead(DT_PIN);
  int curAB = (a << 1) | b;

  if (curAB != prevAB) {
    // calcula índice (prev<<2 | cur)
    int idx = (prevAB << 2) | curAB;
    int8_t movement = trans_table[idx];

    if (movement != 0) {
      main_menu += movement;
      // evita salirse de los límites de menú
      if (main_menu < 0) main_menu = 0;
      if (main_menu >= MAIN_MENU_ITEMS) main_menu = MAIN_MENU_ITEMS - 1;

      Serial.print("A=");
      Serial.print(a);
      Serial.print(" B=");
      Serial.print(b);
      Serial.print(" mov=");
      Serial.print(movement);
      Serial.print(" menu=");
      Serial.println(main_menu);

      render_main_menu();
    }

    // small debounce / give time for contacts to settle (ajusta si hace falta)
    delayMicroseconds(800);
  }

  prevAB = curAB;
}
