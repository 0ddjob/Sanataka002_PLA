# PLA binary dump -> ASCII
# Brett Hallen, 5-Apr-2024

import sys
import os

pla_filename = "KR556RT1.BIN"
asc_filename = "KR556RT1.TXT"
current_addr = 0

with open(pla_filename,'rb') as pla_fp:
    print(f">> Opened {pla_filename} for reading")
    asc_fp = open(asc_filename,'w')
    print(f">> Opened {asc_filename} for writing")
    asc_fp.write("AAAAAAAAAAAAAAAA  YYYYYYYY\n")
    asc_fp.write("0000000001111111  00000000\n")
    asc_fp.write("1234567890123456  12345678\n")
    asc_fp.write("----------------  --------\n")
    
    while (byte := pla_fp.read(1)):
        ascii_line = f"{current_addr:016b}  {int.from_bytes(byte):08b}\n"
        asc_fp.write(ascii_line)
        current_addr += 1
        if (current_addr % 0x1000 == 0):
            print(f"Converted {current_addr} bytes")
    asc_fp.close()
    pla_fp.close()
    print(">> Finished!")
    
    
        
