const byte buzzerPin = 4;
const byte ledPin = 3;
const byte trigPin= 8;
const byte echoPin= 9;
const byte soundSensorPin = 6;
const byte fanPin = 11;

byte choice = 0;
bool isOneChoice = false;

void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(soundSensorPin, INPUT);
  pinMode(fanPin, OUTPUT);

}
  
void loop() {
  
byte handDis = 10;
byte maxChoice = 4;

Serial.println(distance());

  if(distance() <= handDis && distance() > 0 && !isOneChoice) {

    waitChoice();
    choice = 0;
    int i = 1;
    while(i <= 1000) {

      if(distance() <= handDis && distance() > 0 && choice <= maxChoice) {

        tone(buzzerPin, 100);
        choice++;
        delay(1000);
        noTone(buzzerPin);
        delay(2000);
        
      }
      i++;
      if(choice == maxChoice) break;
      
    }
    
    //
    if(choice >= 1) {

      waitChoice();
      int i = 1;
      while(i <= 1000) {

          if(distance() <= handDis && distance() > 0) {

            isOneChoice = true;
            tone(buzzerPin, 100);
            delay(1000);
            noTone(buzzerPin);
            break;

          }
          i++;

      }
      analogWrite(ledPin, 100);
      delay(500);
      analogWrite(ledPin, 0);
      
    }
    
  }

  switch(choice) {

    case 1 : { gasAmount(); break; }
    case 2 : { digiLed(isSoundExist()); break; }
    case 3 : { anaFanMove(distance()); break; }
    case 4 : { digiFanMove(isSoundExist());
               digiLed(isSoundExist()); break; }
    default : { gasAmount(); }

  }

}


//Functions:


//Distance sensor
int distance() {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return (int) ((pulseIn(echoPin, HIGH) * 0.034) / 2);

}


//Gas sensor
void gasAmount() {

  byte GasAmount = analogRead(A0);
  Serial.println(GasAmount);

  if(GasAmount > 400) {

    tone(buzzerPin, 1000);
    digiLed(1);

  } else if(GasAmount > 300) {

    tone(buzzerPin, 700);
    digiLed(1);

  } else if(GasAmount > 200) {

    tone(buzzerPin, 500);
    digiLed(1);

  } else if(GasAmount > 150) {

    tone(buzzerPin, 300);
    digiLed(1);

  } else if(GasAmount > 100) {

    digiLed(1);
    noTone(buzzerPin);

  } else if(GasAmount > 90) {

    for(int i = 0; i <= 3; i++) {

      digiLed(1);
      delay(250);
      digiLed(0);

    }
    noTone(buzzerPin);

  } else {

    noTone(buzzerPin);
    digitalWrite(ledPin, 0);

  }
 
  delay(100);
  
}


//Led
void digiLed(bool isPlay) {

  digitalWrite(ledPin, isPlay);

}


//Sound sensor
bool isSoundExist() {

  return digitalRead(soundSensorPin);
  
}


//Fan
void anaFanMove(int fanSpeed) {

  if(fanSpeed <= 0) {

    analogWrite(fanPin, 0);

  } else if(fanSpeed > 128) {
    
    analogWrite(fanPin, 256);
    
  } else {

    analogWrite(fanPin, fanSpeed * 2);

  }

}

void digiFanMove(bool isPlay) {

  digitalWrite(fanPin, isPlay);
  
}


//Buzzer
void yesBuzzer() {
  
  int melody[] = {1000, 2000, 2000, 3000, 2000, 0, 4000, 1000};

  int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

  for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);


    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
    
  }

}


//waitChoice
void waitChoice() {

  yesBuzzer();
  delay(3000);

}
