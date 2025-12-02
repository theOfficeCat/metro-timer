typedef enum {
    ADD_STATION = 0,
    VIEW_STATIONS,
    START_RUN,
    NEW_RUN_RETURN,
    NEW_RUN_ITEMS
} new_run_options_t;

char *new_run_texts[NEW_RUN_ITEMS] = {
    (char*)"Add station",
    (char*)"View stations",
    (char*)"Start run",
    (char*)"Return"
};

int new_run_menu = ADD_STATION;


void new_run_render() {
    render_ui("New run", new_run_texts, NEW_RUN_ITEMS, new_run_menu);
}

void new_run_action() {
    action(&new_run_menu, NEW_RUN_ITEMS, &new_run_render);

    if (button_pressed_pull_up(BUTTON_ENC_PIN) or button_pressed_pull_down(BUTTON_OK_PIN)) {
        Serial.println("button new run");
        if (new_run_menu == NEW_RUN_RETURN) {
            Serial.println("return pressed");
            current_menu = MAIN_MENU;
        }
    }

    if (button_pressed_pull_down(BUTTON_RETURN_PIN)) {
        current_menu = MAIN_MENU;
    }
}


