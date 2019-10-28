#include <Wire.h>
#include "MCP4728.h"

MCP4728 dac;

void setup()
{
    Serial.begin(115200);  // initialize serial interface for print()

    Wire.begin();
    dac.attatch(Wire, 12);
    dac.readRegisters();

    dac.selectVref(MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD);
    dac.selectPowerDown(MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM);
    dac.selectGain(MCP4728::GAIN::X1, MCP4728::GAIN::X1, MCP4728::GAIN::X1, MCP4728::GAIN::X1);
    dac.analogWrite(MCP4728::DAC_CH::A, 111);
    dac.analogWrite(MCP4728::DAC_CH::B, 222);
    dac.analogWrite(MCP4728::DAC_CH::C, 333);
    dac.analogWrite(MCP4728::DAC_CH::D, 444);

    dac.enable(true);

    dac.readRegisters();
    printStatus();
    //delay(5000);
}


void loop()
{
  int i=0;
char chr,str[16];
for(int j=0;j<16;j++){
  str[j]='\n';
}

if(Serial.available()>0) {
    chr=Serial.read();
    while(chr!='\n'&&i<16){
      if(Serial.available()>0) {
      str[i]=chr;
      chr=Serial.read();
      i++;
      }
    }
}
if(i){
int x=0,y=0;
//Serial.println(str);

sscanf(str,"%i %i",&x,&y);
Serial.println(x);
Serial.println(y);
x=map(x, 0, 640, 1228, 4095);
y=map(y, 0, 480, 4095, 1228);
  /*  int analog = 0;
    analog=analogRead(A0);
    analog=map(analog, 0, 1023, 1228, 4095);
    */

  if(x&&y)  dac.analogWrite(x, y, x, y);

    delay(10);
//    dac.readRegisters();
//    printStatus();
}
}

void printStatus()
{
    Serial.println("NAME     Vref  Gain  PowerDown  DACData");
    for (int i = 0; i < 4; ++i)
    {
        Serial.print("DAC");
        Serial.print(i, DEC);
        Serial.print("   ");
        Serial.print("    ");
        Serial.print(dac.getVref(i), BIN);
        Serial.print("     ");
        Serial.print(dac.getGain(i), BIN);
        Serial.print("       ");
        Serial.print(dac.getPowerDown(i), BIN);
        Serial.print("       ");
        Serial.println(dac.getDACData(i), DEC);

        Serial.print("EEPROM");
        Serial.print(i, DEC);
        Serial.print("    ");
        Serial.print(dac.getVref(i, true), BIN);
        Serial.print("     ");
        Serial.print(dac.getGain(i, true), BIN);
        Serial.print("       ");
        Serial.print(dac.getPowerDown(i, true), BIN);
        Serial.print("       ");
        Serial.println(dac.getDACData(i, true), DEC);
    }
    Serial.println(" ");
}
