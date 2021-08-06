#ifndef _ADXL372_H
#define _ADXL372_H



#include <arduino.h>

#define DEVID_AD 0x00
#define DEVID_MST 0x01
#define PARTID 0x02
#define REVID 0x03
#define STATUS 0x04
#define STATUS2 0x05
#define FIFO_ENTRIES2 0x06
#define FIFO_ENTRIES 0x07
#define XDATA_H 0x08
#define XDATA_L 0x09
#define YDATA_H 0x0A
#define YDATA_L 0x0B
#define ZDATA_H 0x0C
#define ZDATA_L 0x0D
#define MAXPEAK_X_H 0x15
#define MAXPEAK_X_L 0x16
#define MAXPEAK_Y_H 0x17
#define MAXPEAK_Y_L 0x18
#define MAXPEAK_Z_H 0x19
#define MAXPEAK_Z_L 0x1A
#define OFFSET_X 0x20
#define OFFSET_Y 0x21
#define OFFSET_Z 0x22
#define THRESH_ACT_X_H 0x23
#define THRESH_ACT_X_L 0x24
#define THRESH_ACT_Y_H 0x25
#define THRESH_ACT_Y_L 0x26
#define THRESH_ACT_Z_H 0x27
#define THRESH_ACT_Z_L 0x28
#define TIME_ACT 0x29
#define THRESH_INACT_X_H 0x2A
#define THRESH_INACT_X_L 0x2B
#define THRESH_INACT_Y_H 0x2C
#define THRESH_INACT_Y_L 0x2D
#define THRESH_INACT_Z_H 0x2E
#define THRESH_INACT_Z_L 0x2F
#define TIME_INACT_H 0x30
#define TIME_INACT_L 0x31
#define THRESH_ACT2_X_H 0x32
#define THRESH_ACT2_X_L 0x33
#define THRESH_ACT2_Y_H 0x34
#define THRESH_ACT2_Y_L 0x35
#define THRESH_ACT2_Z_H 0x36
#define THRESH_ACT2_Z_L 0x37
#define HPF 0x38
#define FIFO_SAMPLES 0x39
#define FIFO_CTL 0x3A
#define INT1_MAP 0x3B
#define INT2_MAP 0x3C
#define TIMING 0x3D
#define MEASURE 0x3E
#define POWER_CTL 0x3F
#define SELF_TEST 0x40
#define RESET 0x41
#define FIFO_DATA 0x42

#define FULL_BANDWIDTH_MEASUREMENT_MODE 0b00000011
#define INSTANT_ON_MODE 0b00000010
#define WAKE_UP_MODE 0b00000001
#define STANDBY_MODE 0b00000000


void enable_HP_filter(void);
void disable_HP_filter(void);
int self_test(void);
void set_mode_of_operation(byte mode);
void set_high_pass_filter_frequency(byte frequence);
void set_output_data_rate(int frequence);
void set_wakeup_rate(int periode);
void set_bandwidth(int B_value);
void set_low_noise_operation(byte value);
int convert_compl_2(int value);
float read_gravity_value(byte axis_register);



#endif
