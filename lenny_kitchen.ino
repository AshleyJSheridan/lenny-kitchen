unsigned char digits[11][8] = {
  {4, 5, 6, 8, 12, 13, 13, 13},    // 0
  {6, 12, 12, 12, 12, 12, 12, 12}, // 1
  {5, 6, 7, 8, 13, 0, 0, 0},       // 2
  {5, 6, 7, 12, 13, 0, 0, 0},      // 3
  {4, 6, 7, 12, 0, 0, 0, 0},       // 4
  {5, 4, 7, 12, 13, 0, 0, 0},      // 5
  {5, 4, 7, 8, 12, 13, 0, 0},      // 6
  {5, 6, 12, 0, 0, 0, 0, 0},       // 7
  {4, 5, 6, 7, 8, 12, 13, 0},      // 8
  {4, 5, 6, 7, 12, 0, 0, 0},       // 9
  {2, 3, 4, 5, 6, 8, 12, 13}       // 10
};

unsigned long lastTime = 0;
unsigned short int clockDelay = 1000;
char currentDigit = 10;
bool countdownOn = false;
unsigned char countdownButtonPin = 11;
unsigned char buzzerPin = 9;
unsigned short buzzerDuration = 500;
unsigned short buzzerFrequency = 2000;
unsigned short hobLightsPin = A0;

void setup() {
  Serial.begin(9600);

  // clock display pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(countdownButtonPin, INPUT);
  digitalWrite(countdownButtonPin, HIGH);
}

void loop() {
  unsigned long currentTime = millis();

  if(currentTime - lastTime >= clockDelay)
  {
    lastTime = currentTime;

    clearDigits();
    if(countdownOn)
    {
      outputDigit(currentDigit);

      currentDigit--;
      if(currentDigit < 0)
      {
        countdownOn = false;
        currentDigit = 10;

        tone(buzzerPin, buzzerFrequency, buzzerDuration);
      }
    }
  }

  unsigned char countdownButtonPushed = digitalRead(countdownButtonPin);
  if(countdownButtonPushed == 0)
  {
    countdownOn = true;
  }
}

void outputDigit(int number)
{
  for(unsigned char i=0; i<8; i++)
  {
    digitalWrite(digits[number][i], HIGH);
  }
}

void clearDigits()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
