#define frequence_sinus 28
#define nb_ech 1000
#define pin_trig 7


int table_sinus[nb_ech];
int i=0;
unsigned long delai; //en microsecondes
unsigned long memo_temps;
unsigned long temps_actuel;



void generer_table_sinus(void);



void setup() {
  pinMode(pin_trig,INPUT);
  analogWriteResolution(12);
  Serial.begin(2000000);
  generer_table_sinus();
  delai=(unsigned long)(1000000/(frequence_sinus*nb_ech));
  temps_actuel=micros();
  }

void loop() {
  if(digitalRead(pin_trig))
  {
  memo_temps=temps_actuel;
  analogWrite(DAC0, table_sinus[i]);  
  analogWrite(DAC1, table_sinus[i]);  

  i++;
  if(i == nb_ech)  
    i = 0;
  
  while(temps_actuel-memo_temps<delai)
  {
    temps_actuel=micros();
  }
  
  } 
  else
  {
     analogWrite(DAC0, 2047);  
     analogWrite(DAC1, 2047);
     i=0;
  }
  //delayMicroseconds(delai);
}




void generer_table_sinus(void)
{
  for(int i=0;i<nb_ech;i++)
  {
    table_sinus[i]=map(0.5*sin(2*PI*i/nb_ech)*2048,-2048,2048,0,4095);
  }
}
