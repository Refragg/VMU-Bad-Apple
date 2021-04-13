# VMU Bad Apple
This repo contains the code for the video [Bad Apple!! on a Dreamcast VMU](https://youtu.be/Xot3X04KHPU). 

- The python script contains the conversion code and takes in a set amount of frames that you must provide which are of size 48x32 and 1bpp or equivalent, it outputs a readable binary file for the Dreamcast program

- If you want to use another music / video you want to overwrite the frames.bin and the music.ogg files then you want to build the Dreamcast executable again using a working [KallistiOS](https://github.com/KallistiOS/KallistiOS) environment, you can use the [elftocdi](https://github.com/R3FR4G/VMU-Bad-Apple/blob/master/elftocdi.sh) script to build a CDI image easily
