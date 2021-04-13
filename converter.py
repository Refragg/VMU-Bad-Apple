"""
This script assumes you have a set of frames that are 48x32 in size
and a bit-size of 1 or equivalent so that it can be converted correctly.
"""

from PIL import Image

totalbytes = bytearray()
for i in range(6073): # Iterate through all frames
    currentPath = "frames/frame" + str(i) + ".png" # Set Path to current frame (change filepath and extension accordingly)

    image = Image.open(currentPath) # Open Image at path

    curbyte = 0 # Initialise byte builder

    for i in range(31,-1,-1): # Iterate from the bottom right pixel (VMU format)
        for j in range(47,-1,-1):
            # Build the current byte (6 for each horizontal line)
            # Take the value at the current pixel and flip it by abusing python types
            # The value is shifted to it's relative position
            curbyte += (not image.getpixel((j,i))) << (j % 8)

            if 7 - (j % 8) == 7: # If the byte is finished, we add it to the bytearray
                totalbytes.append(curbyte)
                curbyte = 0

    image.close()

# Create a byte file and store everything in order for the dreamcast program to read
finalfile = open('frames.bin', 'wb')
finalfile.write(totalbytes)
finalfile.close()


### String Formatting for one frame ###
"""
for i in range(0, len(curbs), 6):
    strbuild = ""
    for byte in range(6):
        hexbyte = hex(curbs[i + byte])

        if len(hexbyte) == 3:
            strbuild += "0x0" + hexbyte[-1].upper() + ", "
            
        else:
            strbuild += hexbyte.upper() + ", "
            
    print(strbuild)
"""
