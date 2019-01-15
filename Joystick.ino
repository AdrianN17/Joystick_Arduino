#include <SoftwareSerial.h>
#include <math.h>


#define px A0
#define py A1

#define ax A2
#define ay A3

#define b1 9
#define b2 8
#define b3 7
#define b4 6


/*
 * 6 disparar
 * 7 recargar
 * 8 menu / cambiar arma
 * 9 correr/iniciar
 * audio pausar
*/ 
 
int x;
int y;

int cx;
int cy;

int button2=1;
int button3=1;
int pausar=1;

int timer_2=0;
int periodo_2=2000;
int timer_3=0;
int periodo_3=5000;

String pos;
SoftwareSerial BT(10, 11);

void setup() 
{
  //mandos
  pinMode(px, INPUT);
  pinMode(py, INPUT);

  pinMode(ax, INPUT);
  pinMode(ay, INPUT);

  //botones
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  
  Serial.begin(9600);  
  BT.begin(9600); 
  BT.println("Bluetooth encendido");
}

void loop() {
  //Joystick
  double angle_d;
  double vx;
  double vy;

  //botones
  int b_1;
  int b_2;
  int b_3;
  int b_4;
  

  //inicializadores
  
  x=analogRead(px);
  y=analogRead(py);
  cx=analogRead(ax);
  cy=analogRead(ay);

 
  angle_d=atan2(treatValue(cy)-4,treatValue(cx)-4);

  vx=map(treatValue(x),0,8,5,-5);
  vy=map(treatValue(y),0,8,-5,5);

  b_1=digitalRead(b1);
  b_2=digitalRead(b2);
  b_3=digitalRead(b3);
  b_4=digitalRead(b4);


  if(button3==0)
  {
    button3=1;
  }

  if(button2==0)
  {
    button2=1;
  }

  if(millis()-timer_3>=periodo_3)
  {
    if((b_3 == 0) && (button3 == 1))
    {
      button3=0;
      timer_3=millis();
    } 
  }

  if(millis()-timer_2>=periodo_2)
  {
    if((b_2 == 0) && (button2 == 1))
    {
      button2=0;
      timer_2=millis();
    }
  }
  
  pos=String(vx)+" "+String(vy)+" "+String(angle_d)+" "+String(b_1)+" "+String(button2)+" "+String(button3)+" "+String(b_4);
  BT.println(pos);
  Serial.println(pos);
}

int treatValue(int data) {
  return (data * 9 / 1024);
 }
