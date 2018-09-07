#define enA 2
#define in1 3
#define in2 4
#define enB 7
#define in3 5
#define in4 6

#define triggerM 8
#define echoM 9
#define triggerR 10
#define echoR 11
#define triggerL 12
#define echoL 13

#define ledL 41
#define ledM 40
#define ledR 39

#define SR A4 
#define SMR A3 
#define SM A2 
#define SML A1 
#define SL A0 

int rights; 
int middleright; 
int middle; 
int middleleft; 
int lefts; 
int counterultra;

float Rvalue; 
float MRvalue; 
float Mvalue; 
float MLvalue; 
float Lvalue; 

byte input;
byte dummy;
byte curmode = 5;
int cusspeed = 150;
int durationR=0;
int durationM=0;
int durationL=0;
long distanceR=0;
long distanceM=0;
long distanceL=0;
bool drive=false;
int nachultra=0;
int timeultra=100;

void setup()
{
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);  
    pinMode(in2, OUTPUT);  
    pinMode(enB, OUTPUT); 
    pinMode(in3, OUTPUT);  
    pinMode(in4, OUTPUT); 
    pinMode(triggerM, OUTPUT);
    pinMode(echoM, INPUT); 
    pinMode(triggerR, OUTPUT);
    pinMode(echoR, INPUT); 
    pinMode(triggerL, OUTPUT);
    pinMode(echoL, INPUT);
    pinMode(ledL, OUTPUT);
    pinMode(ledM, OUTPUT);
    pinMode(ledR, OUTPUT);
    pinMode(SR, INPUT); 
    pinMode(SMR, INPUT); 
    pinMode(SM, INPUT); 
    pinMode(SML, INPUT); 
    pinMode(SL, INPUT); 
    
    Serial.begin(9600);
}


void forward()
{
    analogWrite(enA,cusspeed);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(enB,cusspeed);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);  
}
void backward()
{
    analogWrite(enA,cusspeed);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(enB,cusspeed);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
}
void hardstop()
{
    analogWrite(enA,LOW);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(enB,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    drive=false;  
}
void left()
{
    analogWrite(enA,cusspeed);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(enB,cusspeed);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);  
}
void right()
{
    analogWrite(enA,cusspeed);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(enB,cusspeed);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);  
}void leftline()
{
    analogWrite(enA,cusspeed);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(enB,cusspeed);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);  
}
void rightline()
{
    analogWrite(enA,cusspeed);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(enB,cusspeed);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);  
}

void linetracker()
{
    cusspeed = 150;
    rights = analogRead(SR); 
    middleright = analogRead(SMR); 
    middle = analogRead(SM); 
    middleleft = analogRead(SML); 
    lefts = analogRead(SL); 
    
    Rvalue = (float)rights *5.0/1023.0; 
    MRvalue = (float)middleright *5.0/1023.0; 
    Mvalue = (float)middle *5.0/1023.0; 
    MLvalue = (float)middleleft *5.0/1023.0; 
    Lvalue = (float)lefts *5.0/1023.0; 
    
    if(Rvalue < 1.5 && Mvalue > 3.5 && Lvalue < 1.5) 
    { 
      forward(); 
    } 
    else if(((Lvalue > 3.5 && MLvalue < 1.5) || (Lvalue < 1.5 && MLvalue > 3.5) || (Lvalue > 3.5 && MLvalue > 3.5)) /*&& Mvalue < 1.5 && MLvalue < 1.5 && Lvalue < 1.5*/) 
    { 
      leftline(); 
    } 
    else if(((Rvalue > 3.5 && MRvalue < 1.5) || (Rvalue < 1.5 && MRvalue > 3.5) || (Rvalue > 3.5 && MRvalue > 3.5)) /*&& Mvalue < 1.5 && MRvalue < 1.5 && Rvalue < 1.5*/) 
    { 
      rightline(); 
    } 
    else if(Rvalue < 1.5 && MRvalue < 1.5 && Mvalue < 1.5 && MLvalue < 1.5 && Lvalue < 1.5) 
    { 
      backward(); 
    } 
}

void bluetooth()
{
  //if (Serial.available() > 0) {input = Serial.read();Serial.println(input);}
  if (curmode == '8' && cusspeed != 150)
  {
    cusspeed -= 50;
    curmode = 0;
    Serial.println("speed set to: ");Serial.println(cusspeed);
  }
  
  if(curmode == '9' && cusspeed != 250)
  {
    cusspeed += 50;
    curmode = 0;
    Serial.println("speed set to: ");Serial.println(cusspeed);
  }
  
  if(curmode == '1')
  {//forward
      forward();
      drive=true;
      curmode = 0;
  }
  
  if(curmode == '0')
  {//stop
      hardstop();
      curmode = 0;
  }
  
  if (curmode == '2')
  {//backward
      backward();
      curmode = 0;
  }
  
  if(curmode == '3')
  {//left
      left();
      curmode = 0;
    }
  if(curmode == '4')
  {//right
      right();
      curmode = 0;
  }
}

void ultraschall()
{
    cusspeed = 250;
    digitalWrite(triggerM,LOW);
    digitalWrite(triggerM,HIGH);
    digitalWrite(triggerM,LOW);
    durationM = pulseIn(echoM, HIGH);
    distanceM = (durationM/2)/29.1;
    digitalWrite(triggerL,LOW);
    digitalWrite(triggerL,HIGH);
    digitalWrite(triggerL,LOW);
    durationL = pulseIn(echoL, HIGH);
    distanceL = (durationL/2)/29.1;
    digitalWrite(triggerR,LOW);
    digitalWrite(triggerR,HIGH);
    digitalWrite(triggerR,LOW);
    durationR = pulseIn(echoR, HIGH);
    distanceR = (durationR/2)/29.1;
    
    if((distanceL  > 15 && distanceM > 15 && distanceR > 15)&& counterultra == 0)
    {
      forward();
    }
     if((distanceL  < 15 && distanceM > 15 && distanceR > 15 || distanceL  < 15 && distanceM < 15 && distanceR > 15)&& counterultra == 0)
    {
      right();
    }
      if((distanceL  > 15 && distanceM > 15 && distanceR < 15 || distanceL  > 15 && distanceM < 15 && distanceR < 15) && counterultra == 0)
    {
      left();
    }
      if(distanceL  < 15 && distanceM < 15 && distanceR < 15 || distanceL  < 15 && distanceM > 15 && distanceR < 15)
    {
      left();
      counterultra= counterultra+1;
      if (counterultra == 3);
      {
        counterultra = 0;
      }
    }
}

void loop()
{
  dummy = curmode;
  if (Serial.available() > 0) {curmode = Serial.read();}
  else if(curmode != '6' && curmode != '7')
  {
    bluetooth();
  }
  else if(curmode == '6')
  {
    if(millis()-nachultra > timeultra)
    {
      linetracker();
      nachultra = millis();
    }
  }
  else if(curmode == '7')
  {
    if(millis()-nachultra > timeultra)
    {
      ultraschall();
      nachultra = millis();
    }
  }
}
