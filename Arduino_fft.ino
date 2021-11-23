/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "complex.hh"
#include "fft.hh"



/******** Directives of C Pre-processor *********/

/********* Conditional Compilation **********/

#define DEBUGGING                 /* Use directive when debugging some lines  */



/********** Symbolic  Constants ***********/

/* ---------------------- Constants to Exit Functions ----------------------- */

#define SUCCEED              1    /* Succeeded ending in function execution   */
#define FAIL                 0    /* Failed    ending in function execution   */

/* ---------------------- Analysis in Frequency Domain ---------------------- */

#define FORWARD              1    /* Forward direction for FFT computation    */
#define REVERSE              0    /* Reverse direction for FFT computation    */

/* -------- Default Values for Iteration in Time & Frequency Domain --------- */

#define MAX_TIME_SAMPLES     128 /* Testing default value for time_samples */
#define PADDING_POWER        2                /* Default padding power factor */
#define MAX_FREQ_SAMPLES     MAX_TIME_SAMPLES<<PADDING_POWER  /* freq_samples */

static COMPLEX_T Sine_at_60Hz[MAX_FREQ_SAMPLES];

int analogPin = A0;
long D;


/*********** Main Function ************/
void setup (){
  Serial.begin(2000000);

  int i;
  int direction = FORWARD;
 
 int time_samples = MAX_TIME_SAMPLES;
  int freq_samples = MAX_FREQ_SAMPLES;
  int power = Find_Power( freq_samples );
//Signal sampling//
for( i = 0; i < time_samples; i++ ){
  Sine_at_60Hz[i].real = analogRead(analogPin);
  delay(3);
  } 
//FFT computing//
  long previous_time = micros();
  Compute_FFT( direction, power, Sine_at_60Hz );
  D = micros() - previous_time;
//FFT transmision//
  for( int i = 0; i < MAX_FREQ_SAMPLES/2; i++ ){
    Serial.println("\n");
    //Serial.println(D);
    Serial.println(cplx_Magnitude( Sine_at_60Hz[i] ));
    Serial.println("\n");
  }

}

void loop (){
   
} 
