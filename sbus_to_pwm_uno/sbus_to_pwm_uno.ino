#include <Servo.h>//the servo output library

uint16_t CH[18];//channel values are stored here
uint8_t buf[26];
char sbus_flag=0;
const int minAngle = 30; // servo angle range
const int maxAngle = 150;
int anglePrecedent = -1;

//On crée une array contenant tous les servos
Servo g_liste_servos[5];


void setup()
{   
  int liste_pins_servos[5] = {3,5,6,9,10};
  int i(0);
  //On assigne à chaque servo un pin
  for(Servo &servo : g_liste_servos)
    servo.attach(liste_pins_servos[i++]);
  Serial.begin(100000);
}

void setServoAngle(Servo s, const int angle) {//mapping the channel value to pwm output for servos
  if(angle != anglePrecedent){
    anglePrecedent = angle;
    int Angle = map(angle, 512, 1536, minAngle, maxAngle);
    s.write(Angle);
  }
}

void moteur(Servo &servo,const int throttle) {//the mapping of throttle is different than servos
  int rot = map(throttle, 512, 1536, 60, 130);
  servo.write(rot);
}

void loop(){
  delay(5);
  int i(0);
  for(Servo &servo : g_liste_servos)
    if(i == 2)
      moteur(servo,CH[i++]);
    else
      setServoAngle(servo,CH[i++]);
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
  Sbus_Data_Count(buf);
}

void Sbus_Data_Count(const uint8_t *buf){//function translating sbus data to integers
  if(buf[0]==0x0f&&buf[24]==0x00){
    CH[ 0] = ((int16_t)buf[ 1] >> 0 | ((int16_t)buf[ 2] << 8 )) & 0x07FF;
    CH[ 1] = ((int16_t)buf[ 2] >> 3 | ((int16_t)buf[ 3] << 5 )) & 0x07FF;
    CH[ 2] = ((int16_t)buf[ 3] >> 6 | ((int16_t)buf[ 4] << 2 )  | (int16_t)buf[ 5] << 10 ) & 0x07FF;
    CH[ 3] = ((int16_t)buf[ 5] >> 1 | ((int16_t)buf[ 6] << 7 )) & 0x07FF;
    CH[ 4] = ((int16_t)buf[ 6] >> 4 | ((int16_t)buf[ 7] << 4 )) & 0x07FF;
    CH[ 5] = ((int16_t)buf[ 7] >> 7 | ((int16_t)buf[ 8] << 1 )  | (int16_t)buf[ 9] <<  9 ) & 0x07FF;
    CH[ 6] = ((int16_t)buf[ 9] >> 2 | ((int16_t)buf[10] << 6 )) & 0x07FF;
    CH[ 7] = ((int16_t)buf[10] >> 5 | ((int16_t)buf[11] << 3 )) & 0x07FF;
    CH[ 8] = ((int16_t)buf[12] << 0 | ((int16_t)buf[13] << 8 )) & 0x07FF;
    CH[ 9] = ((int16_t)buf[13] >> 3 | ((int16_t)buf[14] << 5 )) & 0x07FF;
    CH[10] = ((int16_t)buf[14] >> 6 | ((int16_t)buf[15] << 2 )  | (int16_t)buf[16] << 10 ) & 0x07FF;
    CH[11] = ((int16_t)buf[16] >> 1 | ((int16_t)buf[17] << 7 )) & 0x07FF;
    CH[12] = ((int16_t)buf[17] >> 4 | ((int16_t)buf[18] << 4 )) & 0x07FF;
    CH[13] = ((int16_t)buf[18] >> 7 | ((int16_t)buf[19] << 1 )  | (int16_t)buf[20] <<  9 ) & 0x07FF;
    CH[14] = ((int16_t)buf[20] >> 2 | ((int16_t)buf[21] << 6 )) & 0x07FF;
    CH[15] = ((int16_t)buf[21] >> 5 | ((int16_t)buf[22] << 3 )) & 0x07FF;
  }
}