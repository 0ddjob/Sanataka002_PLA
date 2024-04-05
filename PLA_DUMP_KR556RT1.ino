/*
PLA Dumper
Heavily modified to dump (Soviet) КР556РТ1 PLA using a Freetronics EtherMega
Brett Hallen, 4-Apr-2024
https://www.youtube.com/@brfff
If reading the PLA in-circuit, remember to isolate Vcc (pin 28)
otherwise the target board will try to power itself from your
poor Arduino.

Original source:
ROM Reader. Quick Arduino program to read a parallel-accessed ROM and dump it to the serial
port in hex.
Oddbloke. 16th Feb 2014.
https://danceswithferrets.org/geekblog/?p=315
 */

// Write data to SD card 
#include <SPI.h>
#include <SD.h>
static const int cspin = 4;
File plaFile;
char plaFileName[] = "KR556RT1.BIN";

// Freetronics Ethermega pin -> КР556РТ1 pin
static const int kPin_A1  = 53;    // pin 27
static const int kPin_A2  = 51;    // pin 26
static const int kPin_A3  = 49;    // pin 25
static const int kPin_A4  = 47;    // pin 24
static const int kPin_A5  = 45;    // pin 23
static const int kPin_A6  = 43;    // pin 22
static const int kPin_A7  = 41;    // pin 21
static const int kPin_A8  = 39;    // pin 20
static const int kPin_A9  = 37;    // pin 9
static const int kPin_A10 = 35;    // pin 8 
static const int kPin_A11 = 33;    // pin 7
static const int kPin_A12 = 31;    // pin 6
static const int kPin_A13 = 29;    // pin 5
static const int kPin_A14 = 27;    // pin 4
static const int kPin_A15 = 25;    // pin 3
static const int kPin_A16 = 23;    // pin 2

static const int kPin_Y1 = 28;      // pin 18
static const int kPin_Y2 = 30;      // pin 17 
static const int kPin_Y3 = 32;      // pin 16
static const int kPin_Y4 = 34;      // pin 15
static const int kPin_Y5 = 36;      // pin 13
static const int kPin_Y6 = 38;      // pin 12
static const int kPin_Y7 = 40;      // pin 11
static const int kPin_Y8 = 42;      // pin 10

// additional pins on the КР556РТ1 (KR556RT1)
// pin 1 = РП вход разрешения программирования = programming enable input -> GND
// pin 14 = GND
// pin 19 = РВ вход разрешения выборки = sample enable input = GND
// pin 28 = Vcc
  
void setup()
{
  Serial.begin(115200);
  
  // initialise the SD card
  Serial.print("Initialising SD card ... ");
  if (!SD.begin(cspin)) 
  {
    Serial.println("failed!");
    Serial.println(">>> HALTING <<<");
    while (1);
  }
  Serial.println("done.");

  Serial.print("Creating ");
  Serial.print(plaFileName);
  Serial.print(" ... ");
  plaFile = SD.open(plaFileName, FILE_WRITE);
  if (!plaFile)
  {
    Serial.println("failed!");
    Serial.println(">>> HALTING <<<");
    while (1);
  }
  Serial.println("done.");

  Serial.println("Setting pins");
  // set the address lines as outputs ...
  pinMode(kPin_A1, OUTPUT);     // pin 27
  pinMode(kPin_A2, OUTPUT);     // pin 26
  pinMode(kPin_A3, OUTPUT);     // pin 25
  pinMode(kPin_A4, OUTPUT);     // pin 24
  pinMode(kPin_A5, OUTPUT);     // pin 23
  pinMode(kPin_A6, OUTPUT);     // pin 22
  pinMode(kPin_A7, OUTPUT);     // pin 21
  pinMode(kPin_A8, OUTPUT);     // pin 20
  pinMode(kPin_A9, OUTPUT);     // pin 9
  pinMode(kPin_A10, OUTPUT);    // pin 8 
  pinMode(kPin_A11, OUTPUT);    // pin 7
  pinMode(kPin_A12, OUTPUT);    // pin 6
  pinMode(kPin_A13, OUTPUT);    // pin 5
  pinMode(kPin_A14, OUTPUT);    // pin 4
  pinMode(kPin_A15, OUTPUT);    // pin 3
  pinMode(kPin_A16, OUTPUT);    // pin 2

  // set the data lines as inputs ... the PLA has open collector
  // outputs so need to set internal pullups 
  pinMode(kPin_Y1, INPUT_PULLUP);      // pin 18
  pinMode(kPin_Y2, INPUT_PULLUP);      // pin 17 
  pinMode(kPin_Y3, INPUT_PULLUP);      // pin 16
  pinMode(kPin_Y4, INPUT_PULLUP);      // pin 15
  pinMode(kPin_Y5, INPUT_PULLUP);      // pin 13
  pinMode(kPin_Y6, INPUT_PULLUP);      // pin 12
  pinMode(kPin_Y7, INPUT_PULLUP);      // pin 11
  pinMode(kPin_Y8, INPUT_PULLUP);      // pin 10

  Serial.println("Setup completed.");
}

void SetAddress(int addr)
{
  // update the address lines to reflect the address we want ...
  digitalWrite(kPin_A1, (addr & 1)?HIGH:LOW);
  digitalWrite(kPin_A2, (addr & 2)?HIGH:LOW);
  digitalWrite(kPin_A3, (addr & 4)?HIGH:LOW);
  digitalWrite(kPin_A4, (addr & 8)?HIGH:LOW);
  digitalWrite(kPin_A5, (addr & 16)?HIGH:LOW);
  digitalWrite(kPin_A6, (addr & 32)?HIGH:LOW);
  digitalWrite(kPin_A7, (addr & 64)?HIGH:LOW);
  digitalWrite(kPin_A8, (addr & 128)?HIGH:LOW);
  digitalWrite(kPin_A9, (addr & 256)?HIGH:LOW);
  digitalWrite(kPin_A10, (addr & 512)?HIGH:LOW);
  digitalWrite(kPin_A11, (addr & 1024)?HIGH:LOW);
  digitalWrite(kPin_A12, (addr & 2048)?HIGH:LOW);
  digitalWrite(kPin_A13, (addr & 4096)?HIGH:LOW);
  digitalWrite(kPin_A14, (addr & 8192)?HIGH:LOW);
  digitalWrite(kPin_A15, (addr & 16384)?HIGH:LOW);
  digitalWrite(kPin_A16, (addr & 32768)?HIGH:LOW);
}

byte ReadByte()
{
  // read the current eight-bit byte being output by the ROM ...
  byte b = 0;
  if (digitalRead(kPin_Y1)) b |= 1;
  if (digitalRead(kPin_Y2)) b |= 2;
  if (digitalRead(kPin_Y3)) b |= 4;
  if (digitalRead(kPin_Y4)) b |= 8;
  if (digitalRead(kPin_Y5)) b |= 16;
  if (digitalRead(kPin_Y6)) b |= 32;
  if (digitalRead(kPin_Y7)) b |= 64;
  if (digitalRead(kPin_Y8)) b |= 128;
  
  // Need to invert due to open collector outputs on PLA:
  // "A logical HIGH turns the transistor ON so that the output voltage on the pin becomes LOW. 
  //  A logical LOW leaves the transistor OFF so that the output voltage on the pin becomes HIGH."
  return(~b);
}

void loop()
{  
  byte yOutput = 0;
  unsigned long addr = 0;
   
  Serial.println("Reading PLA ...\n");

  for (addr = 0; addr < 0x10000; addr++)
  {
    // Set the 16-bit input
    SetAddress(addr); 
    // Read the 8-bit output
    yOutput = ReadByte(); 
    // Write to file
    plaFile.write(yOutput);
    // Print progress to serial every 0x1000
    if (addr % 0x1000 == 0)
    {
      Serial.print("Checking address 0x");
      Serial.println(addr,HEX);
    }
  }

  plaFile.close();
  Serial.print("Closed ");
  Serial.println(plaFileName);

  // All done, so lockup ...
  Serial.println();
  while (true)
  {
    Serial.println(">>> COMPLETED! <<<");
    delay(10000);
  }
}
