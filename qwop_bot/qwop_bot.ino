// QWOP Bot
// Just like in the game QWOP, the bot doesn't walk very well


#include <Servo.h>

// Wheg states
#define UP   1
#define DOWN 0

class Wheg
{
  int pin;
  int speed;
  int min_us;
  int max_us;
  int cur_us;
  Servo servo;
  int state;
  boolean reverse;

  public:
    Wheg(int pin, int min, int max, int speed, boolean reverse)
      : pin(pin), min_us(min), max_us(max), speed(speed), reverse(reverse)
      {}
    
    void init()
    {
        servo.attach(pin);
        state = reverse? UP : DOWN;
        cur_us = reverse? max_us : min_us;
        step();
    }
    
    void down()
    {
      state = reverse? UP : DOWN;
    }
    
    void up()
    {
      state = reverse? DOWN : UP;
    }
    
    void step()
    {
      if (state == UP)
      {
        cur_us += speed;
        if (cur_us > max_us)
          cur_us = max_us;
      }
      else
      {
        cur_us -= speed;
        if (cur_us < min_us)
          cur_us = min_us;
      }
      servo.writeMicroseconds(cur_us);
    }
    
    void set_min(int new_min)
    {
      min_us = new_min;
    }
    
    void set_max(int new_max)
    {
      max_us = new_max;
    }
};

Wheg whegs[6] = {
  Wheg( 3, 1200, 2200, 10,  true), // back right
  Wheg( 5,  800, 1800, 10, false), // middle left
  Wheg( 6,  800, 1800, 10, false), // front left
  Wheg( 9,  800, 1800, 10, false), // front right
  Wheg(10, 1200, 2200, 10,  true), // back left
  Wheg(11,  800, 1800, 10, false)  // middle right
};

void setup()
{
  int i;
  for (i = 0; i < 6; i++)
    whegs[i].init();
  Serial.begin(9600);
}

void loop()
{
  int i;
  while (Serial.available() > 0)
  {
    char cmd = Serial.read();
    switch (cmd)
    {
      case 'A':
        whegs[0].up();
        break;
      case 'a':
        whegs[0].down();
        break;
      case 'B':
        whegs[3].up();
        break;
      case 'b':
        whegs[3].down();
        break;
      case 'C':
        whegs[4].up();
        break;
      case 'c':
        whegs[4].down();
        break;
      case 'D':
        whegs[2].up();
        break;
      case 'd':
        whegs[2].down();
        break;
    }
  }
  for (i = 0; i < 6; i++)
    whegs[i].step();
  delay(10);
}

