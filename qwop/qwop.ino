class Button
{
  int prev;
  int pin;
public:
  Button(int pin) : prev(HIGH), pin(pin) {}
  void init()
  {
    pinMode(pin, INPUT_PULLUP);
  }
  boolean changed()
  {
    int cur = digitalRead(pin);
    if (cur != prev) {
      prev = cur;
      return true;
    }
    return false;
  }
  boolean down()
  {
    return !digitalRead(pin);
  }
};

Button ButtonA(7);
Button ButtonB(8);
Button ButtonC(9);
Button ButtonD(10);

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  Serial1.begin(9600);
  Serial2.begin(9600);
  ButtonA.init();
  ButtonB.init();
  ButtonC.init();
  ButtonD.init();  
}

void controller()
{
  if (ButtonA.changed())
  {
    if (ButtonA.down())
    {
      Serial1.write('A');
      digitalWrite(RED_LED, HIGH);
    }
    else
      Serial1.write('a');
  }
  if (ButtonB.changed())
  {
    if (ButtonB.down())
    {
      Serial1.write('B');
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }
    else
      Serial1.write('b');
  }
  if (ButtonC.changed())
  {
    if (ButtonC.down())
    {
      Serial1.write('C');
      digitalWrite(BLUE_LED, HIGH);
    }
    else
      Serial1.write('c');
  }
  if (ButtonD.changed())
  {
    if (ButtonD.down())
    {
      Serial1.write('D');
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
    }
    else
      Serial1.write('d');
  }
}

void bot()
{
  if (Serial2.available() > 0)
  {
    switch (Serial2.read())
    {
      case 'A':
        digitalWrite(GREEN_LED, HIGH);
        break;
      case 'a':
        digitalWrite(GREEN_LED, LOW);
        break;
      case 'B':
        digitalWrite(BLUE_LED, HIGH);
        break;
      case 'b':
        digitalWrite(BLUE_LED, LOW);
        break;
    }
  }
}

void loop()
{
  controller();
  bot();
  delay(50);
}
