#ifndef SETUP_H_INCLUDED
#define SETUP_H_INCLUDED



/*
typedef struct {
    int style;
    int height;
    char* label;
    int value;
} line;
*/

typedef struct {
    char* name;
    byte temperature;
    byte humidity;
    int duration;
} target_point;




#endif // SETUP_H_INCLUDED
