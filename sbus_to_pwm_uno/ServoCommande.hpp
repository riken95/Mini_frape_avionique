#ifndef SERVO_COMMANDE_H
#define SERVO_COMMANDE_H
#include <Servo.h>//the servo output library
#include "Data.hpp"
#define MAX_SYS 5
#define MIN_ANGLE 30
#define MAX_ANGLE 150



class SysServo{
    private:
    int consigne_precedente;
    const int pin;
    const bool EST_MOTEUR; //true : moteur | false : servo
    void setAngle(const int angle);
    void setConsigneMoteur(const int throttle);
    public:
    Servo servo;
    SysServo(const bool EST_MOTEUR);
    void setConsigne(const int consigne);
   
};

class ListeSystemes{
    private:
    const int LISTE_PINS[MAX_SYS] = {3,5,6,9,10};
    SysServo * l_systemes[MAX_SYS];

    public:
    ListeSystemes();
    void Appliquer_Consignes(const int * CH, const int taille);
};


#endif