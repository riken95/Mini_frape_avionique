#include "ServoCommande.hpp"


// ================== CLASSE SysServo
SysServo::SysServo(const bool EST_MOTEUR) : EST_MOTEUR(EST_MOTEUR){

}


void SysServo::setConsigne(const int consigne){
    if(this->EST_MOTEUR)
        this->setConsigneMoteur(consigne);
    else
        this->setAngle(consigne);
}

void SysServo::setAngle(const int angle){
    if(angle != this->consigne_precedente){
        this->consigne_precedente = angle;
        int Angle = map(angle, 512, 1536, MIN_ANGLE, MAX_ANGLE);
        this->servo.write(Angle);
    }
}



void SysServo::setConsigneMoteur(const int throttle){
  int rot = map(throttle, 512, 1536, 60, 130);
  this->servo.write(rot);
}
// ================ CLASSE LISTE_SYSTEMES

ListeSystemes::ListeSystemes(){
    int i(0);
    for (SysServo * systeme : this->l_systemes) {
        if (i == 2)
            systeme = new SysServo(true);
        else
            systeme = new SysServo(false);

        systeme->servo.attach(this->LISTE_PINS[i++]);
    }
}

void ListeSystemes::Appliquer_Consignes(const int * CH, const int taille){
    int i(0);
    for(SysServo * sys : this->l_systemes)
        if(i >= taille)
            return;
        else
            sys -> setConsigne(CH[i++]);
}

