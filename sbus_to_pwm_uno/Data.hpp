#ifndef DATA_H
#define DATA_H
#include <Arduino.h>
#define MAX_CHANNELS 18

class Data{
    private: 
    public:
    uint16_t CH[MAX_CHANNELS];
    void ReadDatas(const uint8_t *buf);
};


#endif