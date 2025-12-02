typedef enum {
    ADD_STATION,
    VIEW_STATIONS,
    START_RUN,
    NEW_RUN_ITEMS
} new_run_options_t;

char *new_run_texts[NEW_RUN_ITEMS] = {
    (char*)"Add station",
    (char*)"View stations",
    (char*)"Start run"
};

int new_run_menu = ADD_STATION;


void new_run_render() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(31, 0);
    display.println("New run");

    for (int i = 0; i < NEW_RUN_ITEMS; ++i) {
        display.setCursor(15, 15 + 10 * i);
        display.println(new_run_texts[i]);
    }

    display.setCursor(5, 15 + 10 * new_run_menu);
    display.print(">");

    display.display();
}

void new_run_action() {
    new_run_render();
}


