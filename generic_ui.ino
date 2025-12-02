void render_ui(char* title, char **names, int qtty, int current_item) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(31, 0);
    display.println(title);

    for (int i = 0; i < qtty; ++i) {
        display.setCursor(15, 15 + 10 * i);
        display.println(names[i]);
    }

    display.setCursor(5, 15 + 10 * current_item);
    display.print(">");

    display.display();
}
