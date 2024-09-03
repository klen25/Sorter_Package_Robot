#include <Servo.h>

//--------------------Inisialisasi PIN
#define swcapit 2
#define IRputar 6

#define capit   3
#define lengan  4
#define putar   5
//------------------------------------

//--------Inisialisasi Konstanta Servo
#define stopp 1550
#define kanan 1600 //1700
#define kiri  1400 //1000

#define awal 55
#define turun 35
#define naik 75
//------------------------------------

Servo servocapit, servolengan, servoputar;

char input;
int putaran = 0;
int a = 0;

int IRCounter = 0;
int IRState = 0;
int lastIRState = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(swcapit, INPUT);
  pinMode(IRputar, INPUT);

  pinMode(capit, OUTPUT);
  pinMode(lengan, OUTPUT);
  pinMode(putar, OUTPUT);
  
  servocapit.attach(capit);
  servolengan.attach(lengan);
  servoputar.attach(putar);

  servocapit.write(0);
  servolengan.write(awal);
  while(digitalRead(IRputar) == HIGH)
  { servoputar.writeMicroseconds(kanan); }
  servoputar.writeMicroseconds(stopp);

  delay(100);
  Serial.println("Ready");
}

void loop()
{
  if(Serial.available() > 0)
  {
    input = Serial.read();
    angkat();
    if (input == '0'){dalampulau();}
    if (input == '1'){luarpulau();}
    if (input == '2'){luarnegeri();}
  }
}

void angkat()
{
  servolengan.write(turun); delay(300); //lengan turun
  while(digitalRead(swcapit) == LOW) // capit benda paket
  {
    servocapit.write(putaran); delay(30);
    if(putaran == 110) { putaran = 0; delay(30);}
    putaran++;
  }
  servolengan.write(naik); delay(300); // lengan naik
}

void capitbuka()
{
  servolengan.write(turun); delay(300); //lengan turun
  servocapit.write(0); delay(300);   //capit buka
  servolengan.write(awal); delay(300); //lengan ke posisi awal
}

void balikawal(int a, int arah)
{
  IRCounter = 0;
  while(IRCounter != a)
  {
    servoputar.writeMicroseconds(arah);
//    delay(100);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial.println(IRCounter);
      }
//    delay(50);
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp);
}

void dalampulau()
{
  IRCounter = 0;
  while(IRCounter != 1)
  {
    servoputar.writeMicroseconds(kanan);
//    delay(100);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial.println(IRCounter);
      }
//    delay(50);
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp);
  
//  delay(1000);
  balikawal(1, kiri);
}

void luarpulau()
{
  IRCounter = 0;
  while(IRCounter != 2)
  {
//    delay(100);
    servoputar.writeMicroseconds(kanan);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial.println(IRCounter);
      }
//    delay(50);
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp);

//  delay(1000);
  balikawal(2, kiri);
}

void luarnegeri()
{
  IRCounter = 0;
  while(IRCounter != 1)
  {
//    delay(100);
    servoputar.writeMicroseconds(kiri);
    IRState = digitalRead(IRputar);
    if (IRState != lastIRState) 
    {
      if (IRState == LOW)
      {
        IRCounter++;
        Serial.println(IRCounter);
      }
//    delay(50);
    }
    lastIRState = IRState;
  }
  servoputar.writeMicroseconds(stopp);

//  delay(1000);
  balikawal(1, kanan);
}
