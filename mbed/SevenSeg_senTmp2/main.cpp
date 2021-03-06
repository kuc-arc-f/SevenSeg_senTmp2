#include "mbed.h"
#include <stdio.h>
#include <string>

//pin
DigitalOut mPin_1( dp1);
DigitalOut mPin_2( dp2);
DigitalOut mPin_4( dp4);
DigitalOut mPin_5( dp5);
DigitalOut mPin_6( dp6);
DigitalOut mPin_9( dp9);
DigitalOut mPin_10(dp10);

DigitalOut mPin_11(dp11);
DigitalOut mPin_14(dp14);

AnalogIn inSen1(dp13);

//pin
DigitalOut mCathod[2] ={mPin_5, mPin_14  };
DigitalOut mAnode[7]=  {mPin_1, mPin_2, mPin_4, mPin_11, mPin_6, mPin_9, mPin_10 };
int mCount=0;
int   mAnode_pin[7]  ={3, 4, 2, 1, 0, 5, 6 };
int   mCathod_pin[2]   ={0, 1 };

Serial mPc(USBTX, USBRX);

//define
const int mBit_MAX=8;
const int mLED_MAX=3;
const int mWait_US=5;

bool Num_Array[10][8]={
// a b c d e f g dp 
{ 1,1,1,1,1,1,0,0}, //0 :0
{ 0,1,1,0,0,0,0,0}, //1 :1
{ 1,1,0,1,1,0,1,0}, //2 :2
{ 1,1,1,1,0,0,1,0}, //3 :3
{ 0,1,1,0,0,1,1,0}, //4 :4
{ 1,0,1,1,0,1,1,0}, //5 :5
{ 1,0,1,1,1,1,1,0}, //6 :6
{ 1,1,1,0,0,0,0,0}, //7 :7
{ 1,1,1,1,1,1,1,0}, //8 :8
{ 1,1,1,1,0,1,1,0}, //9 :9   
};

int mMaxCathode=2;

int mSTAT =0;
int mSTAT_RSV_START=1;
int mSTAT_DISP=3;
string mResponse="";
string mReceive="";

//
void init_proc(){
  // cathod
  for(int i=0;i<mMaxCathode; i++){
      mCathod[i]=0;
  }
  for(int j=0;j<7; j++){
      //mCathod[j]=0;
      mAnode[ j ]=0;
  }
}

//
void set_cahod(int pinAnode){
  for(int i=0;i <mMaxCathode; i++){
    if(mCathod_pin[i]==pinAnode){
       mCathod[i]=0;
    }else{
       mCathod[i]=1;
    }
  }
}

//
void NumPrint(int Number){
  for (int i=0; i< 7; i++){
//printf("i=%d, mAnode_pin=%d\n", i, mAnode_pin[i]);
    if(Num_Array[Number][i]==1){
       mAnode[mAnode_pin[i]]=1;
//printf("1");
    }
    else{
//printf("0");
    }
//printf(" \n");    
    wait_us(500);
    if(Num_Array[Number][i]==1){
       mAnode[mAnode_pin[i]]=0;
    }
    mAnode[mAnode_pin[i]]=0;
  }
}

    
//
void proc_display(int iTemp){
  int iDeg =iTemp;
  int iDeg_10= iDeg / 10;
  int iDeg_1 = iDeg % 10;
   // dig-1
   for(int i=0;  i< 200; i++ ){
       set_cahod(mCathod_pin[0]);
       NumPrint(iDeg_10);
       // dig-10
       set_cahod(mCathod_pin[1]);
       NumPrint(iDeg_1 );
   }
}

//
int getTempNum(int reading){
  int iRet=0;
  float voltage = ((long)reading * 3300) / 1024;
//  float voltage = ((long)reading * 5000) / 1024;

  // 温度に変換 ,0度 オフセット= 500mVを引く
    float tempC = (voltage - 500) / 10;
    iRet= (int)tempC;
    
    if(iRet > 99){
        iRet=0;
    }
    return iRet;
}
//
int main() {
   mSTAT = mSTAT_RSV_START;
   mPc.baud(9600 );
   mPc.printf("#Start-main \n");    
   init_proc();
   while(1){
           float fSen  = inSen1;
           int reading  = int(fSen  * 1000);
           int iTemP = getTempNum(reading);            
printf("reading=%d , iTemP=%d \n" ,  reading ,iTemP);
           proc_display( iTemP);
           wait_ms(100);
           wait(1);
               
           mSTAT =mSTAT_RSV_START;
   }
}

