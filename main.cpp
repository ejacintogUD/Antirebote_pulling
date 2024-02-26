/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "AnalogIn.h"
#include "DigitalIn.h"
#include "PinNames.h"
#include "Thread.h"
#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define T_REBOTE          5ms

DigitalIn btn(BUTTON1);


Thread hilo_rebote;

void leer_pin(void);

static bool Q0=0,Q1=0,Q2=0;
static int i=0;

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    printf("Arranque del sistema \n\r");
    hilo_rebote.start(leer_pin);
    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void leer_pin(void)
{
    
    while(true)
    {
     Q2 = Q1; // Z[n-2]
     Q1 = Q0; // Z[n-1]
     Q0 = btn;// Z[n]

     if (Q0 && !Q1  && !Q2)
        {
            printf("El conteo es: %u \n\r", i++);
            
        }
     
     ThisThread::sleep_for(T_REBOTE);
    }

}
