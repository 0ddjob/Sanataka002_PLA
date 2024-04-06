# PLA binary dump -> ASCII
# Brett Hallen, 5-Apr-2024

import sys
import os

# Input binary dump file
pla_filename = "KR556RT1.BIN"
# Output sanity check file
asc_filename = "KR556RT1.TXT"
# Loop through each combination of input bits
current_addr = 0
# Dictionary of unique outputs
# Write the set of input bits
outputs = {}
outputs_filename = ""

with open(pla_filename,'rb') as pla_fp:
    print(f">> Opened {pla_filename} for reading")
    asc_fp = open(asc_filename,'w')
    print(f">> Opened {asc_filename} for writing")
    # Write a header to the sanity check file 
    asc_fp.write("AAAAAAAAAAAAAAAA  YYYYYYYY\n")
    asc_fp.write("0000000001111111  00000000\n")
    asc_fp.write("1234567890123456  12345678\n")
    asc_fp.write("----------------  --------\n")
    # Read each byte in the input file
    while (byte := pla_fp.read(1)):
        # Generate bit strings
        bit_from_byte = f"{int.from_bytes(byte):08b}"
        input_bits = f"{current_addr:016b}"
        # Create output file for each unique output
        outputs_filename = bit_from_byte+".TXT"
        # Redundant because of setdefault, but I wanted to print
        # out each time a new output file is created
        if (outputs.get(outputs_filename,-1) == -1):
            print(f">> Created new outputs file {outputs_filename}")
            new_output_file={outputs_filename:open(outputs_filename,'w')}
            outputs.update(new_output_file)
        # setdefault resulted in some output files having a lot of null (0x00) bytes at the start
        # outputs.setdefault(outputs_filename, open(outputs_filename,'w')) 
        # Write the input bit string to the ouput
        outputs[outputs_filename].write(f"{input_bits}\n")
        # Also write input bits & output bits to sanity check file
        asc_fp.write(f"{input_bits}  {bit_from_byte}\n")
        # Move on to the next set of input bits
        current_addr += 1
        # Output some progress to the screen
        if (current_addr % 0x1000 == 0):
            print(f"Converted {current_addr} bytes")
    # Close files
    asc_fp.close()
    pla_fp.close()
    print(f">> Closed {pla_filename}")
    print(f">> Closed {asc_filename}")
 
    for key in outputs:
        outputs[key].close()
        print(f">> Closed {key}")
    print(">> Finished!")
