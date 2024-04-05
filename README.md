# Santaka002_PLA
{WORK IN PROGRESS}

Attempts to dump the logic from the PLAs (программируемую логическую матрицу, or "programmable logic matrix") used on the Сантака 002 (Santaka) computer, a Lithuanian/Belarusan clone of the Sinclair ZX Spectrum.

![Сантака](pictures/IMG_6042.jpeg)

The machine uses several PLAs (Soviet-era КР556РТ1, or KR556RT1) which, as far as we know, are undocumented and thus impossible to replace in a broken machine.

![КР556РТ1](pictures/IMG_6041.jpeg)

This is an attempt to figure out the logic so that they can be reproduced if needed.

The dumping is performed in-circuit using a Freetronics EtherMega (Arduino Mega compatible with SD interface).  Each combination of 16-bit inputs is applied and the resulting 8-bit output captured.  Information about wiring can be found in the Arduino sketch.

A 28-pin turned pin IC socket is used to mount the in-circuit PLA (Soviet 2.5mm pitch vs Western 2.54mm/0.1" pitch seems okay).  The cabling between the PLA and Arduino is made via this socket.

![EtherMega](pictures/IMG_6040.jpeg)

For sanity checking, a Python script is used to convert the binary dump to ASCII.

Further checking will be done on the running machine by capturing the PLA activity using a logic analyser and comparing with the ASCII file.

YouTube video showing the process here:


<a href="http://www.youtube.com/watch?feature=player_embedded&v=-ttpHL7AdvU" target="_blank"><img src="http://img.youtube.com/vi/-ttpHL7AdvU/0.jpg" 
alt="YouTube Video" width="240" height="180" border="10" /></a>
