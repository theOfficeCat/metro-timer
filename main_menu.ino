typedef enum {
    NEW_RUN = 0,
    VIEW_DATA,
    MAIN_MENU_ITEMS
} main_menu_options_t;

char *main_menu_texts[MAIN_MENU_ITEMS] = {
    (char*)"New run",
    (char*)"View data"
};

int main_menu = NEW_RUN;

void render_main_menu() {
    render_ui("Metro timer", main_menu_texts, MAIN_MENU_ITEMS, main_menu);
    /*
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(31, 0);
    display.println("Metro timer");

    for (int i = 0; i < MAIN_MENU_ITEMS; ++i) {
        display.setCursor(15, 15 + 10 * i);
        display.println(main_menu_texts[i]);
    }

    display.setCursor(5, 15 + 10 * main_menu);
    display.print(">");

    display.display();
    */
}

void main_menu_action() {
    if (encoderMoved) {
        encoderMoved = false;

        main_menu += encoderDirection;

        if (main_menu < 0) main_menu = 0;
        if (main_menu >= MAIN_MENU_ITEMS) main_menu = MAIN_MENU_ITEMS - 1;

        render_main_menu();
    }

    if (buttonPressed) {
        Serial.println("button");
        buttonPressed = false;
        if (main_menu = NEW_RUN) {
            current_menu = NEW_RUN_MENU;
        } else if (main_menu == VIEW_DATA) {

        }
    }
}
