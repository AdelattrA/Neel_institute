#include "adxl372.h"
#include "communicationSPI.h"



void enable_HP_filter(void)
{
  byte val_powerctl_register=read_single_byte_register_SPI(POWER_CTL);
  write_single_byte_register_SPI(POWER_CTL,(val_powerctl_register&0b11111011));
}



void disable_HP_filter(void)
{
  byte val_powerctl_register=read_single_byte_register_SPI(POWER_CTL);
  write_single_byte_register_SPI(POWER_CTL,(val_powerctl_register|0b00000100));
}



int self_test(void)
{
  int erreur=0;
  write_single_byte_register_SPI(SELF_TEST, 0x01);
  while(not(read_single_byte_register_SPI(SELF_TEST)&0x02))
  {
    ;
  }
  if(not(read_single_byte_register_SPI(SELF_TEST)&0x04))
  {
    erreur=1;
  }
 return erreur;
}



float read_gravity_value(byte axis_register)
{
  return((float)convert_compl_2(read_axis_data_register_SPI(axis_register))*200/2048);
}



int convert_compl_2(int value)
{
  if(((byte)(value>>11)&0b00000001)==1) //signe négatif
  {
    value=(((~value)+1)&0b00000000000000000000111111111111)*(-1);
  }
  return(value);
}




void set_mode_of_operation(byte mode)
{
  byte mode_actuel=read_single_byte_register_SPI(POWER_CTL);
  write_single_byte_register_SPI(POWER_CTL,mode_actuel|(mode&0b00000011));
}




void set_high_pass_filter_frequency(byte frequence) //fréquences: 00, 01, 10, 11
{
  write_single_byte_register_SPI(HPF,frequence);
}





void set_low_noise_operation(byte value)  //value=1: low noise, value=0: standard noise level
{
  byte val_measure_register=read_single_byte_register_SPI(MEASURE);
  if(value==1)
  {
     write_single_byte_register_SPI(MEASURE,val_measure_register|0b00001000);
  }
  else
  {
   write_single_byte_register_SPI(MEASURE,val_measure_register&0b11110111);
  }
}




void set_bandwidth(int B_value)
{
  byte bandwidth;
  byte val_measure_register;
  switch(B_value)
  {
    case 200: bandwidth=0b00000000;
              break;
    case 400: bandwidth=0b00000001;
              break;
    case 800: bandwidth=0b00000010;
               break;
    case 1600: bandwidth=0b00000011;
               break; 
    case 3200: bandwidth=0b00000100;
               break;   
    default:  bandwidth=0b00000000;
              break;                      
  }
  val_measure_register=read_single_byte_register_SPI(MEASURE);
  write_single_byte_register_SPI(MEASURE,(val_measure_register&0b00000111)|bandwidth);
}



void set_output_data_rate(int frequence)
{
  byte odr;
  byte val_timing_register;
  switch(frequence)
  {
    case 400: odr=0b00000000;
              break;
    case 800: odr=0b00100000;
              break;
    case 1600: odr=0b01000000;
               break;
    case 3200: odr=0b01100000;
               break; 
    case 6400: odr=0b100000000;
               break;   
    default:  odr=0b00000000;
              break;                      
  }
  val_timing_register=read_single_byte_register_SPI(TIMING);
  write_single_byte_register_SPI(TIMING,(val_timing_register&0b00011111)|odr);
}


void set_wakeup_rate(int periode)
{
  byte wakeup_rate;
  byte val_timing_register;
  switch(periode)
  {
    case 52: wakeup_rate=0b00000000;
              break;
    case 104: wakeup_rate=0b00000100;
              break;
    case 208: wakeup_rate=0b00001000;
               break;
    case 512: wakeup_rate=0b00001100;
               break; 
    case 2048: wakeup_rate=0b00010000;
               break;  
    case 4096: wakeup_rate=0b00010100;
               break;  
    case 8192: wakeup_rate=0b00011000;
               break;  
    case 24576: wakeup_rate=0b00011100;
               break;                              
    default:  wakeup_rate=0b00000000;
              break;                      
  }
  val_timing_register=read_single_byte_register_SPI(TIMING);
  write_single_byte_register_SPI(TIMING,(val_timing_register&0b11100011)|wakeup_rate);
}
