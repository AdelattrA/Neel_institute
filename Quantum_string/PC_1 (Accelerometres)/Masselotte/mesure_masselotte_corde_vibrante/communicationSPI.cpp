#include <arduino.h>
#include "communicationSPI.h"
#include <SPI.h>

#define SPI_CS_pin 19


void initSPI(void)
{
  pinMode(SPI_CS_pin, OUTPUT);
  digitalWrite(SPI_CS_pin, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
}

byte read_single_byte_register_SPI(byte registre)
{
  byte data;
  digitalWrite(SPI_CS_pin, LOW);
  SPI.transfer((registre<<1)|0x01);
  data=SPI.transfer(0);
  digitalWrite(SPI_CS_pin, HIGH);
  return(data);
}


void write_single_byte_register_SPI(byte registre, byte val)
{
  digitalWrite(SPI_CS_pin, LOW);
  SPI.transfer(registre<<1);
  SPI.transfer(val);
  digitalWrite(SPI_CS_pin, HIGH);
}

int read_axis_data_register_SPI(byte registre)
{
  byte dataH, dataL;
  int data;
  digitalWrite(SPI_CS_pin, LOW);
  SPI.transfer((registre<<1)|0x01);
  dataH=SPI.transfer(0);
  dataL=SPI.transfer(0);
  digitalWrite(SPI_CS_pin, HIGH);
  data=(dataH<<8 |dataL)>>4;
  return(data);
}

int read_double_byte_register_SPI(byte registre)
{
  byte dataH, dataL;
  int data;
  digitalWrite(SPI_CS_pin, LOW);
  SPI.transfer((registre<<1)|0x01);
  dataH=SPI.transfer(0);
  dataL=SPI.transfer(0);
  digitalWrite(SPI_CS_pin, HIGH);
  data=dataH<<8 |dataL;
  return(data);
}

void write_double_byte_register_SPI(byte registre, int val)
{
  byte dataH, dataL;
  dataL=(byte)(val&0x00FF);
  dataH=(byte)(val>>8);
  digitalWrite(SPI_CS_pin, LOW);
  SPI.transfer(registre<<1);
  SPI.transfer(dataH);
  SPI.transfer(dataL);
  digitalWrite(SPI_CS_pin, HIGH);
}
