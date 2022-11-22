#include "arduinoFFT.h"
#include "Metro.h"

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

const uint16_t samples = 128;
const double samplingFrequency = 16;
const int delay_ms = 1000/samplingFrequency;

Metro sampler = Metro(delay_ms);

const uint16_t LPF = (0.5/samplingFrequency)*samples;
const uint16_t HPF = (2.0/samplingFrequency)*samples;


double vReal[samples];
double vImag[samples];
arduinoFFT FFT;

void setup() {
  Serial.begin(115200);
  //Serial.println("Start");
  pinMode(A0,INPUT);

  FFT = arduinoFFT();
}

void loop() {
  Serial.println("Measuring:-");
  int i=0;
  while(i<samples) {
    if(sampler.check() == 1) {
      if(i%16 == 0) Serial.println(".");
    
      vReal[i] = analogRead(A0)/1024.0;
      vImag[i] = 0;

      //Serial.print(i);
      //Serial.print(" ");
      //if (vReal[i] != 0) Serial.println(vReal[i]);
      i++;
    }
  }
  Serial.println();

  //FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  double time_delay;
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, samples);
  Serial.println("FFT:-");
  time_delay = PrintVector(vReal, LPF, HPF, SCL_FREQUENCY);
  
  uint16_t peak = LPF;
  double peakMag = vReal[LPF];
  for(int i=LPF+1; i<HPF; i++) {
    if(vReal[i] > peakMag) {
      peakMag = vReal[i];
      peak = i;
    }
  }
  double peakFreq = (60.0*samplingFrequency*peak)/samples;
  Serial.print("Heart rate: ");
  Serial.println(peakFreq, 3);
  
  double T_d = ((60000/peakFreq) - (time_delay*1000));
  double SBP = (184.3 - 1.329*peakFreq + 0.0848*T_d);
  double DBP = (55.96 - 0.02912*peakFreq + 0.02302*T_d);
  Serial.print("Systolic Blood Pressure: ");
  Serial.println(SBP, 3);
  Serial.print("Diastolic Blood Pressure: ");
  Serial.println(DBP, 3);
}

double PrintVector(double *vData, uint16_t start, uint16_t bufferSize, uint8_t scaleType)
{ uint16_t i_max = start;
  double abscissa_max = 1;
  uint16_t i_min = start;
  double abscissa_min = 0.5;
  double abscissa_array[bufferSize - start];

  for (uint16_t i = start; i < bufferSize; i++)
  {
    double abscissa;
    
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
  break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
  break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
  break;
    }
    if ( vData[i] > vData[i_max] ){
      abscissa_max = abscissa;
      i_max = i;
    }
    abscissa_array[i-4] = abscissa;
    
      
    Serial.print(abscissa, 6);
    Serial.print(" ");
    Serial.print(vData[i], 4);
    Serial.println();
  }

  for (int i = start; i < i_max; i++){
    if (vData[i] < vData[i_min]){
      i_min = i;
      abscissa_min = abscissa_array[i - 4];
    }

  }

  double abscissa_value = abscissa_max - abscissa_min;
  //Serial.println(abscissa_max);
  //Serial.println(abscissa_min);
  
  return abscissa_value;
}
