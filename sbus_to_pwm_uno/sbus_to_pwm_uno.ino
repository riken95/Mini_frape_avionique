
#include "ServoCommande.hpp"

uint16_t CH[18];//channel values are stored here
uint8_t buf[26];
char sbus_flag=0;
Data data;
ListeSystemes * l_systemes;


void setup()
{   
  l_systemes = new ListeSystemes();
  Serial.begin(100000);
}


void loop(){
  delay(5);
  l_systemes->Appliquer_Consignes(data.CH, 18);
}

void serialEvent(void){//this function is activated by serial input, and saves sbus data in buf
  //Gestion d'erreurs
  if(Serial.available()<=25)
    goto close_function;
  
  while(true)
    if((buf[0]=Serial.read())==0x0f)//the sbus communication begins with 0x0f
      break;
  
  for(int i=1;i<26;i++)
    buf[i]=Serial.read();
  
  close_function:
  data.ReadDatas(buf);
}

