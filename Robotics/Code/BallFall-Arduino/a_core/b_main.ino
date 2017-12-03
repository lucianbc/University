#include "LedControl.h"
#include "LifecycleManager.h"
#include <binary.h>

LedControl lc = LedControl(12, 11, 10, 1);
LifecycleManager manager;

const int SW_pin = 2;
const int X_pin = 1;
const int Y_pin = 0;

BallFal game;

int mapJoystickValue(int value) {
//  Serial.println(value);
  if(value > 600) return 1;
  if (value < 450) return -1;
  return 0;
}

void movePoint() {
//  Serial.println("Move");
  char dir = (char)mapJoystickValue(1023 - analogRead(X_pin));
  game.moveBall(dir);
}

int getRandom(int min, int max) {
  return random(min, max);
}

void print_matrix() {
  char screen[DISPLAY_HEIGHT];
  game.print(screen);

  for (char i = 0; i < DISPLAY_HEIGHT; i++) {
     lc.setRow(0, i, screen[i]); 
  }
}

void show(LifecycleManager& mgr, long int tm);

void show(LifecycleManager& mgr, long int tm) {
  Serial.println("show");
  
  print_matrix();
  
  mgr.register_function(show, tm + 100);
}

void drop(LifecycleManager& mgr, long int tm);

void drop(LifecycleManager& mgr, long int tm) {
  Serial.println("drop");
  game.dropBall();
  mgr.register_function(drop, tm + 100);
}

void mv(LifecycleManager& mgr, long int tm);

void mv(LifecycleManager& mgr, long int tm) {
  Serial.println("mv");
  movePoint();
  mgr.register_function(mv, tm + 50);
}

void up(LifecycleManager& mgr, long int tm);
void up(LifecycleManager& mgr, long int tm) {
  Serial.print("up");
  game.padsUp();
  mgr.register_function(up, tm + 300);
}

void game_start() {
  game.startGame();
  
  long int crt_time = millis();
  manager.register_function(drop, crt_time + 150);
  manager.register_function(show, crt_time + 300);
  manager.register_function(mv, crt_time + 150); 
  manager.register_function(up, crt_time + 300);
}

void setup() {
  // put your setup code here, to run once:
  lc.setIntensity(0, 8);
  lc.shutdown(0,false);

  randomSeed(analogRead(0));

  Serial.begin(9600);

  game_start();
}

void loop() {
  // put your main code here, to run repeatedly:
  manager.execute(millis());
//  print_matrix();
//  movePoint();
}


