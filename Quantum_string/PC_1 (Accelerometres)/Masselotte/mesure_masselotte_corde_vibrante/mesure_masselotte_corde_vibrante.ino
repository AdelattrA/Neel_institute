#include "adxl372.h"
#include "communicationSPI.h"

#define intervalle_mesure 5 //en microsecondes
#define taille_tab_mesures 1

float tab_mesures_X[taille_tab_mesures];
float tab_mesures_Y[taille_tab_mesures];
float tab_mesures_Z[taille_tab_mesures];
float tab_mesures_t[taille_tab_mesures];
float deltaGmax_X, deltaGmax_Y, deltaGmax_Z;
int index_tab_mesures;
unsigned long memo_temps;

void setup() {
  Serial.begin(2000000);
  initSPI();
  set_mode_of_operation(FULL_BANDWIDTH_MEASUREMENT_MODE);
  set_output_data_rate(3200);
  set_bandwidth(1600);
  set_high_pass_filter_frequency(0b00000011);
  set_low_noise_operation(1); 
  //disable_HP_filter();
 
}

float mesure_deltaGmax_tab(float *tab)
{
  float Gmax=0;
  float Gmin=0;
  for(int i=0;i<taille_tab_mesures;i++)
  {
    if(tab[i]>Gmax)
      Gmax=tab[i];
    if(tab[i]<Gmin)
      Gmin=tab[i];
  }
  return(Gmax-Gmin);
}
void loop() {
  index_tab_mesures=0;
  memo_temps=micros();
  while(index_tab_mesures<taille_tab_mesures)
  {
    while(micros()-memo_temps<intervalle_mesure)
    {
     ;
    }
    memo_temps=micros();
    tab_mesures_X[index_tab_mesures]=read_gravity_value(XDATA_H);
    tab_mesures_Y[index_tab_mesures]=read_gravity_value(YDATA_H);
    tab_mesures_Z[index_tab_mesures]=read_gravity_value(ZDATA_H);
    tab_mesures_t[index_tab_mesures]= float(micros());
    index_tab_mesures++;
  }
  for(int i=0;i<taille_tab_mesures;i++)
  {
    String toprint = String(tab_mesures_t[i]) + "," + String(tab_mesures_X[i]) + "," + String(tab_mesures_Y[i]) + "," + String(tab_mesures_Z[i]);
    
    Serial.println(toprint);
  }
  //delay(5000);
/* if(not(self_test()))
    Serial.println("self test OK");
  else
    Serial.println("erreur self test");
    */
}
