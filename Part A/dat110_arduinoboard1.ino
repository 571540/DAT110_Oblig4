void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(9, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}
const int LOCKED = 1;
const int WAITING = 2;
const int UNLOCKED = 3;
int state = LOCKED;
int motion = LOW;
int btn1pushed = 0;
int btn2pushed = 0;
int count = 0;
int code [2]= { 2, 1 };

void loop()
{
  while(state == LOCKED){
    btn1pushed = 0;
    btn2pushed = 0;
    count = 0;
    digitalWrite(13, HIGH);
    motion = digitalRead(9);
    if(motion == HIGH){
      	digitalWrite(13, LOW);
    	state = WAITING;
    }
  }
  while(state == WAITING){
    digitalWrite(12, HIGH);
    while((btn1pushed==0 || btn2pushed==0)&& count<2){
    int btn1 = digitalRead(3);
      if(btn1==HIGH){
        digitalWrite(12, LOW);
        delay(50);
        digitalWrite(12, HIGH);
        delay(50);
        if(count==0){
          btn1pushed = 1;
        }else{
          btn2pushed = 1;
        }
        count++;
        
      }
  	int btn2 = digitalRead(2);
      if(btn2==HIGH){
        digitalWrite(12, LOW);
        delay(50);
        digitalWrite(12, HIGH);
        delay(50);
        if(count==0){
          btn1pushed = 2;
        }else{
          btn2pushed = 2;
        }
        count++;
      }
    }
    if((btn1pushed==code[0])&&(btn2pushed==code[1])){
    state = UNLOCKED;
    }else{
      digitalWrite(12, LOW);
      state = LOCKED;
    }
  }
  while(state == UNLOCKED){
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    state = LOCKED;
  }  
}