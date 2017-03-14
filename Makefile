#CC           = avr-gcc
#CFLAGS       = -Wall -mmcu=atmega16 -Os -Wl,-Map,test.map
#OBJCOPY      = avr-objcopy
CC           = gcc
CFLAGS       = -Wall -g -Os -Wl,-Map,test.map
OBJCOPY      = objcopy

# include path to AVR library
INCLUDE_PATH = /usr/lib/avr/include
# splint static check
SPLINT       = splint main.c aes.c -I$(INCLUDE_PATH) +charindex -unrecog

.SILENT:
.PHONY:  lint clean


rom.hex : aes
	# copy object-code to new image and format in hex
	$(OBJCOPY) -j .text -O ihex aes rom.hex

main.o : main.c
	# compiling test.c
	$(CC) $(CFLAGS) -c main.c -o main.o

aes.o : aes.h aes.c
	# compiling aes.c
	$(CC) $(CFLAGS) -c aes.c -o aes.o

aes : aes.o main.o
	# linking object code to binary
	$(CC) $(CFLAGS) aes.o main.o -o aes

small: aes
	$(OBJCOPY) -j .text -O ihex aes rom.hex

clean:
	rm -f *.OBJ *.LST *.o *.gch *.out *.hex *.map aes

lint:
	$(call SPLINT)
