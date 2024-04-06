# Santaka002_PLA
{WORK IN PROGRESS: 6-Apr-2024}

Attempts to dump the logic from the PLAs (программируемую логическую матрицу, or "programmable logic matrix") used on the Сантака 002 (Santaka) computer, a Lithuanian/Belarusan clone of the Sinclair ZX Spectrum.

![Сантака](pictures/IMG_6042.jpeg)

The machine uses several PLAs (Soviet-era КР556РТ1, or KR556RT1) which, as far as we know, are undocumented and thus impossible to replace in a broken machine.

![КР556РТ1](pictures/IMG_6041.jpeg)

This is an attempt to figure out the logic so that they can be reproduced if needed.

The dumping is performed in-circuit using a Freetronics EtherMega (Arduino Mega compatible with SD interface).  Obviously this isn't ideal but I'm not confident that de-soldering the chip won't result in its distruction, so let's try non-invasive methods first ...  

Each combination of 16-bit inputs is applied and the resulting 8-bit output captured.  Information about wiring can be found in the Arduino sketch.

A 28-pin turned pin IC socket is used to mount the in-circuit PLA (Soviet 2.5mm pitch vs Western 2.54mm/0.1" pitch seems okay).  The cabling between the PLA and Arduino is made via this socket.  The chip's power input pin (pin 28) is isolated from the computer's power rail and is powered from the Arduino itself.

![EtherMega](pictures/IMG_6040.jpeg)

For sanity checking, a Python script is used to convert the binary dump to ASCII.

Further checking will be done on the running machine by capturing the PLA activity using a logic analyser and comparing with the ASCII file.

YouTube video showing the process here:


<a href="http://www.youtube.com/watch?feature=player_embedded&v=-ttpHL7AdvU" target="_blank"><img src="http://img.youtube.com/vi/-ttpHL7AdvU/0.jpg" 
alt="YouTube Video" width="240" height="180" border="10" /></a>

## List of files:
* PLA_DUMP_KR556RT1.ino  
   Arduino sketch to dump contents of PLA creating a binary file (same as for EPROM)  
* pla2asc.py  
   Python3 script to extract data from the binary file for sanity checking
* D14_01_0A  
   Contents of D14 PLA
* Schematics  
   Very little information is available online about this machine - the schematics are about all there is
