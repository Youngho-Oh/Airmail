# Airmail - IOT protocol development by 802.15.4


## Overview

 It is a project to make opensource IoT protocol stack using IEEE 802.15.4

 For making opensource IoT protocol, we use opensource compiler and protocol stack.
 Comiler uses [SDCC](http://sdcc.sourceforge.net/)(for cc2530's compiler).
 Based protocol stack uses [CONTIKI](http://www.contiki-os.org/)'s protocol stack.
 
 This README file contains installation guide for development.


## Getting stared

 - Development enviornment : WSL (case of using windows10)
    → [INSTALL GUIDE](http://wsl-guide.org/en/latest/installation.html)
 - Compiler : SDCC (case of using CC2530)
    → [DOWNLOAD LINK](https://sourceforge.net/projects/sdcc/files/)  

 <Setting of SDCC compiler> (Optional)
   1) Go to SDCC's download link page
   
   2) Download SDCC compiler source file  
      → [3.8.0 verison](https://sourceforge.net/projects/sdcc/files/sdcc/3.8.0/sdcc-src-3.8.0-rc1.tar.bz2/download)
   
   3) Decompress downloaded zip file and copy to C root location.
   
   4) typing below command  
     4-1) cd [sdcc root location]  
     4-2) ./configure --disable-z80-port --disable-z180-port --disable-r2k-port --disable-r3ka-port --disable-gbz80-port --disable-avr-port --disable-ds390-port --disable-hc08-port --disable-s08-port --disable-stm8-port --disable-pic-port --disable-pic16-port --disable-xa51-port --disable-ucsim --disable-pic14-port --disable-pic16-port --prefix="[sdcc root location to copy]" --datarootdir="[sdcc root location to copy]"  
     4-3) make  
     4-4) make install prefix="[sdcc root location to copy]"  
     4-5) cd device  
     4-6) cd lib  
     4-7) make model-mcs51-xstack-auto


## Features

 

## License

 

## Contact

 If you have questiones, Contact below.
 
 Conact Me : ohyoungho88@gmail.com