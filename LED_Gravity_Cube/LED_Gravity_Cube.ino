#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// creating accelerator object
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
sensors_event_t event;

// defining pins to control LED matrix
int row[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int col[8] = {10, 11, 12, 13, 17, 16, 15, 14};
int x1 = 4;
int y1 = 4;
int x2 = 6;
int y2 = 6;
int x3 = 5;
int y3 = 4;
int x4 = 4;
int y4 = 5;
int x5 = 5;
int y5 = 5;
int x6 = 6;
int y6 = 5;
int x7 = 3;
int y7 = 3;
int x8 = 3;
int y8 = 4;

// timings
unsigned long aCzas = 0;
unsigned long zapCzasX1 = 0;
unsigned long zapCzasY1 = 0;
unsigned long zapCzasX2 = 0;
unsigned long zapCzasY2 = 0;
unsigned long zapCzasX3 = 0;
unsigned long zapCzasY3 = 0;
unsigned long zapCzasX4 = 0;
unsigned long zapCzasY4 = 0;
unsigned long zapCzasX5 = 0;
unsigned long zapCzasY5 = 0;
unsigned long zapCzasX6 = 0;
unsigned long zapCzasY6 = 0;
unsigned long zapCzasX7 = 0;
unsigned long zapCzasY7 = 0;
unsigned long zapCzasX8 = 0;
unsigned long zapCzasY8 = 0;

// coordinates of points on matrix
int occ_col[8] = {4,6,4,5,5,5,3,4};
int occ_row[8] = {4,6,5,4,5,6,3,3};

// function to turn on one pixel
void LED(int x,int y){
  for (int i = 0; i<8;i++){
    digitalWrite(col[i],LOW);
    digitalWrite(row[i],HIGH);
  }
  digitalWrite(col[y-1],HIGH);
  digitalWrite(row[x-1],LOW);
  delayMicroseconds(100);
}

// check if given point is free
bool free_cor(int x,int y,int pos){
  for(int i=0; i<8; i++){
    if(i==pos){continue;}
    if(occ_col[i]==y && occ_row[i]==x){return false;}
  }
  return true;
}

// function that controls one pixel
void point(int& x,int& y,unsigned long& zapCzasX,unsigned long& zapCzasY,int pos){
  long ran = random(50,80);
  if((abs(event.acceleration.x) > 2) && (aCzas - zapCzasX > 1/abs(event.acceleration.x)*500UL+ran)){
    if(event.acceleration.x>=0 && free_cor(x-1,y,pos)){x-=1;}
    if(event.acceleration.x<0 && free_cor(x+1,y,pos)){x+=1;}
    if(x>=8){x=8;}
    if(x<=1){x=1;}
    occ_row[pos] = x;
    zapCzasX = millis(); 
  }
  
  if((abs(event.acceleration.y) > 2) && (aCzas - zapCzasY > 1/abs(event.acceleration.y)*500UL+ran)){
    if(event.acceleration.y>=0 && free_cor(x,y-1,pos)){y-=1;}
    if(event.acceleration.y<0 && free_cor(x,y+1,pos)){y+=1;}
    if(y>=8){y=8;}
    if(y<=1){y=1;}
    occ_col[pos] = y;
    zapCzasY = millis(); 
  }
  LED(x,y);
}

void setup() {
  accel.begin();
  for(int i=0; i<8; i++){
    pinMode(row[i],OUTPUT);
    pinMode(col[i],OUTPUT);
    digitalWrite(row[i],HIGH);
  }
}

void loop() {
  accel.getEvent(&event);
  aCzas = millis();
  point(x1,y1,zapCzasX1,zapCzasY1,0);
  point(x2,y2,zapCzasX2,zapCzasY2,1);
  point(x3,y3,zapCzasX3,zapCzasY3,2);
  point(x4,y4,zapCzasX4,zapCzasY4,3);
  point(x5,y5,zapCzasX5,zapCzasY5,4);
  point(x6,y6,zapCzasX6,zapCzasY6,5);
  point(x7,y7,zapCzasX7,zapCzasY7,6);
  point(x8,y8,zapCzasX8,zapCzasY8,7);
}
