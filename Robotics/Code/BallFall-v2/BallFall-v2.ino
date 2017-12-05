#include "LedControl.h"
#include "ball_fall.h"
#include "EventManager.h"
#include "lifecycle_manager.h"
#include <LiquidCrystal.h>

#define REFRESH_RATE 100
#define DROP_RATE 300
#define UP_RATE 300
#define MOVE_RATE 50

// Joystick pins
const int sw_pin = 2;
const int x_pin = 1;
const int y_pin = 0;

// LCD pins
const int RS = 12;
const int EN = 8;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 7;
const int V0 = 6;

EventManager eventManager;
lifecycle_manager manager;
LedControl lc = LedControl(12, 11, 10, 1);
ball_fall game;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void show(lifecycle_manager& mgr, long int time);
void drop(lifecycle_manager& mgr, long int time);
void up(lifecycle_manager& mgr, long int time);
void move_ball(lifecycle_manager& mgr, long int time);
void set_game();

enum game_state {
    INTRO, PLAYING, OVER
} current_state;

void go_to_intro() {
    current_state = INTRO;
    manager.clear();
    game.reset();
    long int current_time = millis();
    manager.register_function(show, current_time + REFRESH_RATE);
    manager.register_function(move_ball, current_time + MOVE_RATE);
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Ball Fall");
    lcd.setCursor(0, 1);
    lcd.print("click to play");
}

void go_to_playing() {
    current_state = PLAYING;
    set_game();
    game.start_game();
}

void go_to_over() {
    current_state = OVER;
    game.reset();
    manager.clear();
    long int current_time = millis();
    manager.register_function(show, current_time + REFRESH_RATE);
    manager.register_function(move_ball, current_time + MOVE_RATE);
}

void set_game() {
    manager.clear();
    long int current_time = millis();
    manager.register_function(drop, current_time + DROP_RATE);
    manager.register_function(show, current_time + REFRESH_RATE);
    manager.register_function(move_ball, current_time + MOVE_RATE);
    manager.register_function(up, current_time + UP_RATE);
}

int get_random(int min, int max) {
    return random(min, max);
}

int map_joystick_value(int value) {
    if (value > 600) return 1;
    if (value < 450) return -1;
    return 0;
}

void print_matrix() {
    char screen[DISPLAY_HEIGHT];
    game.print(screen);

    for (char i = 0; i < DISPLAY_HEIGHT; i++) {
        lc.setRow(0, i, screen[i]);
    }
}

void show(lifecycle_manager& mgr, long int time) {
    print_matrix();
    mgr.register_function(show, time + REFRESH_RATE);
}

void drop(lifecycle_manager& mgr, long int time) {
    game.drop_ball();
    mgr.register_function(drop, time + DROP_RATE);
}

void up(lifecycle_manager& mgr, long int time) {
    int keep_playing = game.pads_up();
//    Serial.println(keep_playing);
    if (!keep_playing) eventManager.queueEvent(EventManager::kEventUser0, 2);
    mgr.register_function(up, time + UP_RATE);
}

void move_ball(lifecycle_manager& mgr, long int time) {
    char direction = (char) map_joystick_value(1023 - analogRead(x_pin));
    game.move_ball(direction);
    mgr.register_function(move_ball, time + MOVE_RATE);
}

bool is_button_pressed(int button_pin) {
    static int lastButtonState = LOW;
    static int buttonState;
    static long int lastDebounceTime = 0;
    static long int debounceDelay = 50;

    int reading = digitalRead(button_pin);

    bool isPressed = false;

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;

            if (buttonState == HIGH) {
                isPressed = true;
            }
        }
    }

    lastButtonState = reading;
    return isPressed;
}

void button_listener(int event_code, int event_param) {
    if (current_state == INTRO) go_to_playing();
    if (current_state == OVER) go_to_playing();
}

void over_listener(int event_code, int event_param) {
    if (current_state == PLAYING) go_to_over();
}

void setup() {
    // put your setup code here, to run once:
    lc.setIntensity(0, 8);
    lc.shutdown(0, false);

    pinMode(V0, OUTPUT);
    analogWrite(V0, 120);
    
    lcd.begin(16, 2);

    eventManager.addListener(EventManager::kEventKeyPress, button_listener);
    eventManager.addListener(EventManager::kEventUser0, over_listener);

    randomSeed(analogRead(0));

    go_to_intro();

    pinMode(sw_pin, INPUT);
    digitalWrite(sw_pin, HIGH);


    Serial.begin(9600);
}

int btn_times = 0;

void loop() {
    // put your main code here, to run repeatedly:
    eventManager.processEvent();
    manager.execute(millis());

    if (is_button_pressed(sw_pin)) {
        btn_times += 1;
        if (btn_times > 1) {
            eventManager.queueEvent(EventManager::kEventKeyPress, 0);
        }
    }
}