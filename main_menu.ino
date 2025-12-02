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

void main_menu_render() {
    render_ui("Metro timer", main_menu_texts, MAIN_MENU_ITEMS, main_menu);
}

void main_menu_action() {
    action(&main_menu, MAIN_MENU_ITEMS, &main_menu_render);

    if (button_pressed_pull_up(BUTTON_ENC_PIN) or button_pressed_pull_down(BUTTON_OK_PIN)) {
        Serial.println("button encoder");
        if (main_menu == NEW_RUN) {
            current_menu = NEW_RUN_MENU;
        } else if (main_menu == VIEW_DATA) {

        }
    }

    if (button_pressed_pull_down(BUTTON_RETURN_PIN)) {
        Serial.println("button return encoder");
    }
}
