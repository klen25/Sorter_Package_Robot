#include <Servo.h>

//--------------------Inisialisasi PIN
#define IRputar 6

#define capit   3
#define lengan  4
#define putar   5
//------------------------------------

//--------Inisialisasi Konstanta Servo
#define stopp 1550
#define kanan 1597  
#define balikkekanan 1595  
#define kiri  1410  
#define balikkekiri  1434  
#define balikkekiri2  1432

//------------------------------------

Servo servocapit, servolengan, servoputar;

char input;
int putaran = 55;
int a = 0;

int IRCounter = 0;
int IRState = 0;
int lastIRState = 0;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(IRputar, INPUT);

  pinMode(capit, OUTPUT);
  pinMode(lengan, OUTPUT);
  pinMode(putar, OUTPUT);
  
  servocapit.attach(capit);
  servolengan.attach(lengan);
  servoputar.attach(putar);

  servocapit.write(0);
  servolengan.write(55);
  while(digitalRead(IRputar) == HIGH)
  { servoputar.writeMicroseconds(kanan); }
  servoputar.writeMicroseconds(stopp);

  delay(100);
//  Serial1.println("Ready");
}

void loop()
{
  if(Serial1.available() > 0)
  {
    input = 0;
    input = Serial1.read();
    angkat();
    if (input == '0'){dalampulau();}
    if (input == '1'){luarpulau();}
    if (input == '2'){luarnegeri();}
    else{}
  }
}

void angkat()
{
  delay(1000);
  for(putaran == 55; putaran >= 37; putaran--) // lengan turun
  { servolengan.write(putaran); delay(65); }
  delay(1000);
  servocapit.write(100); delay(2000);          // capit menutup
  for(putaran == 37; putaran <= 70; putaran++) // lengan naik
  { servolengan.write(putaran); delay(50); }
  delay (1000);
}

void capitbuka()
{
  for(putaran == 70; putaran >= 30; putaran--) // lengan turun
  { servolengan.write(putaran); delay(55); }
  delay(1000);
  servocapit.write(0); delay(2000);            //capit buka
  for(putaran == 30; putaran <= 70; putaran++) // lengan naik
  { servolengan.write(putaran); delay(50); }
  delay(1000);
}

void balikawal(int a, int arah)
{
  IRCounter = 0;
  while(IRCounter != a)
  {
    servoputar.writeMicroseconds(arah);
    delay(100);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial1.println(IRCounter);
      }
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp); delay(2000);

  for(putaran == 70; putaran >= 55; putaran--) // lengan kembali ke posisi awal
  { servolengan.write(putaran); delay(55); }
  delay(1000);  
}

void dalampulau()
{
  IRCounter = 0;
  while(IRCounter != 1)
  {
    servoputar.writeMicroseconds(kanan);
    delay(100);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial1.println(IRCounter);
      }
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp); delay(2000);

  capitbuka();
  
  balikawal(1, balikkekiri);
}

void luarpulau()
{
  IRCounter = 0;
  while(IRCounter != 2)
  {
    delay(100);
    servoputar.writeMicroseconds(kanan);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial1.println(IRCounter);
      }
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp); delay(2000);

  capitbuka();
  
  balikawal(2, balikkekiri2);
}

void luarnegeri()
{
  IRCounter = 0;
  while(IRCounter != 1)
  {
    delay(100);
    servoputar.writeMicroseconds(kiri);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial1.println(IRCounter);
      }
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp); delay(2000);

  capitbuka();

  balikawal(1, balikkekanan);
}
