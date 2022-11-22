int d0;
int d1;
int d2;
int d3;
int d4;
int d5;
int d6;
int d7;

int samplingfreq = 20;
int dt = 1000/sampligfreq;

void setup() {
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
}

void loop() {
 d0 = digitalRead(5);
 d1 = digitalRead(6);
 d2 = digitalRead(8);
 d3 = digitalRead(7);
 d4 = digitalRead(9);
 d5 = digitalRead(10);
 d6 = digitalRead(12);
 d7 = digitalRead(11);
if (d0 == LOW && d1 == LOW && d2 == LOW && d3 == LOW && d4 == LOW && d5 == LOW && d6 == LOW && d7 == LOW)
{
  Serial.println("0");
}
else if (d1 == HIGH && d2 == LOW && d3 == LOW && d4 == LOW && d5 == LOW && d6 == LOW && d7 == LOW)
{
  Serial.println("1");
}
else if (d2 == HIGH && d3 == LOW && d4 == LOW && d5 == LOW && d6 == LOW && d7 == LOW)
{
  Serial.println("2");
}
else if (d3 == HIGH && d4 == LOW && d5 == LOW && d6 == LOW && d7 == LOW)
{
  Serial.println("3");
}
else if (d4 == HIGH && d5 == LOW && d6 == LOW && d7 == LOW)
{
  Serial.println("4");
}
else if (d5 == HIGH && d6 == LOW && d7 == LOW)
{
  Serial.println("5");
}
else if (d6 == HIGH && d7 == LOW)
{
  Serial.println("6");
}
else if (d7 == HIGH)
{
  Serial.println("7");
}

delay(dt);
 }
