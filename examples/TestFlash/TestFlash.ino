/*
 *----------------------------------------------------------------------------------------------------------------------------------*
 |                                                W25Q80BV - Winbond 64 Mbit (1MB) Flash                                            |
 |                                                      SPIFlash library test v1.2.0                                                |
 |----------------------------------------------------------------------------------------------------------------------------------|
 |                                                          Prajwal Bhattaram                                                       |
 |                                                              23.06.2015                                                          |
 |----------------------------------------------------------------------------------------------------------------------------------|
 |                                     (Please make sure your Serial monitor is set to 'No Line Ending')                            |
 |                                     *****************************************************************                            |
 |                                                                                                                                  |
 |                     # Please pick from the following commands and type the command number into the Serial console #              |
 |    For example - to write a byte of data, you would have to use the write_byte function - so type '3' into the serial console.   |
 |                                                    --------------------------------                                              |
 |                                                                                                                                  |
 |  1. Get ID                                                                                                                       |
 |   '1' gets the JEDEC ID of the chip                                                                                              |
 |                                                                                                                                  |
 |  2. Write Byte [page] [offset] [byte]                                                                                            |
 |   '2' followed by '100' and then by '20' and then by '224' writes the byte 224 to page 100 position 20                           |
 |                                                                                                                                  |
 |  3. Read Byte [page] [offset]                                                                                                    |
 |   '3' followed by '100' and then by '20' returns the byte from page 100 position 20                                              |
 |                                                                                                                                  |
 |  4. Write Page [page]                                                                                                            |
 |   '4' followed by '33' writes bytes from 0 to 255 sequentially to fill page 33                                                   |
 |                                                                                                                                  |
 |  5. Read Page [page]                                                                                                             |
 |   '5' followed by 33 reads page 33                                                                                               |
 |                                                                                                                                  |
 |  6. Read All Pages                                                                                                               |
 |   '6' reads all 4096 pages and outputs them to the serial console                                                                |
 |   This function is to extract data from a flash chip onto a computer as a text file.                                             |
 |   Refer to 'Read me.md' in the library for details.                                                                              |
 |                                                                                                                                  |
 |  7. Erase sector                                                                                                                 |
 |   '7'  followed by 2 erases a 4KB sector containing the page to be erased                                                        |
 |   Page 0-15 --> Sector 0; Page 16-31 --> Sector 1;......Page 4080-4095 --> Sector 255                                            |
 |                                                                                                                                  |
 |  8. Erase sector                                                                                                                 |
 |   '8'  followed by 2 erases a 32KB block containing the page to be erased                                                        |
 |   Page 0-15 --> Sector 0; Page 16-31 --> Sector 1;......Page 4080-4095 --> Sector 255                                            |
 |                                                                                                                                  |
 |  9. Erase sector                                                                                                                 |
 |   '9'  followed by 2 erases a 64KB block containing the page to be erased                                                        |
 |   Page 0-15 --> Sector 0; Page 16-31 --> Sector 1;......Page 4080-4095 --> Sector 255                                            |
 |                                                                                                                                  |
 |  10. Erase Chip                                                                                                                  |
 |   '10' erases the entire chip                                                                                                    |
 |                                                                                                                                  |
 ^----------------------------------------------------------------------------------------------------------------------------------^
 */



#include<SPIFlash.h>
#include<SPI.h>
const int cs = 10;
uint8_t pageBuffer[256];
String serialCommand;
char printBuffer[128];
uint16_t page;
uint8_t offset, dataByte;
uint16_t dataInt;


SPIFlash flash(cs);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Initialising Flash memory"));
  for (int i = 0; i < 10; ++i)
  {
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println();
  commandList();
}

void loop() {
  while (Serial.available() > 0) {
    uint8_t commandNo = Serial.parseInt();
    if (commandNo == 0) {
      commandList();
    }
    else if (commandNo == 1) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                      Function 1 : Get JEDEC ID                                                   "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      flash.getID();
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 2) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 2 : Write Byte                                                    "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to modify: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      Serial.print(F("Please enter the position on the page (0-255) you wish to modify: "));
      while (!Serial.available()) {
      }
      offset = Serial.parseInt();
      Serial.println(offset);
      Serial.print(F("Please enter the value of the byte (0-255) you wish to save: "));
      while (!Serial.available()) {
      }
      dataByte = Serial.parseInt();
      Serial.println(dataByte);
      flash.writeByte(page, offset, dataByte);
      clearprintBuffer();
      sprintf(printBuffer, "%d has been written to position %d on page %d", dataByte, offset, page);
      Serial.println(printBuffer);
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 3) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 3 : Read Byte                                                     "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.print(F("Please enter the number of the page (0-4095) the byte you wish to read is on: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      Serial.print(F("Please enter the position of the byte on the page (0-255) you wish to read: "));
      while (!Serial.available()) {
      }
      offset = Serial.parseInt();
      Serial.println(offset);
      clearprintBuffer();
      sprintf(printBuffer, "The byte at position %d on page %d is: ", offset, page);
      Serial.print(printBuffer);
      Serial.println(flash.readByte(page, offset));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 4) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 4 : Write Word                                                    "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to modify: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      Serial.print(F("Please enter the position on the page (0-255) you wish to modify: "));
      while (!Serial.available()) {
      }
      offset = Serial.parseInt();
      Serial.println(offset);
      Serial.print(F("Please enter the value of the word (>255) you wish to save: "));
      while (!Serial.available()) {
      }
      dataInt = Serial.parseInt();
      Serial.println(dataInt);
      flash.writeWord(page, offset, dataInt);
      clearprintBuffer();
      sprintf(printBuffer, "%d has been written to position %d on page %d", dataInt, offset, page);
      Serial.println(printBuffer);
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 5) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 5 : Read Word                                                     "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.print(F("Please enter the number of the page (0-4095) the byte you wish to read is on: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      Serial.print(F("Please enter the position of the word on the page (0-255) you wish to read: "));
      while (!Serial.available()) {
      }
      offset = Serial.parseInt();
      Serial.println(offset);
      clearprintBuffer();
      sprintf(printBuffer, "The unsigned int at position %d on page %d is: ", offset, page);
      Serial.print(printBuffer);
      Serial.println(flash.readWord(page, offset));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 6) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 6 : Write Page                                                    "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will write a sequence of bytes (0-255) to the page selected."));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to write to: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      for (int i = 0; i < 256; ++i) {
        pageBuffer[i] = i;
      }
      flash.writePage(page, pageBuffer);
      clearprintBuffer();
      sprintf(printBuffer, "Values from 0 to 255 have been written to the page %d", page);
      Serial.println(printBuffer);
      Serial.print("Type 1 to read the page you have just written. Type 0 to continue: ");
      while (!Serial.available()) {
      }
      uint8_t choice = Serial.parseInt();
      Serial.println(choice);
      if (choice == 1) {
        Serial.print("Would you like your output in decimal or hexadecimal? Please indicate with '1' for HEX or '2' for DEC: ");
        while (!Serial.available()) {
        }
        uint8_t outputType = Serial.parseInt();
        Serial.println(outputType);
        flash.printPage(page, outputType);
      }
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 7) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 7 : Read Page                                                    "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will read the entire page selected."));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to read: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      Serial.print("Would you like your output in decimal or hexadecimal? Please indicate with '1' for HEX or '2' for DEC: ");
      while (!Serial.available()) {
      }
      uint8_t outputType = Serial.parseInt();
      Serial.println(outputType);
      flash.printPage(page, outputType);
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 8) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                     Function 8 : Read All Pages                                                  "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will read the entire flash memory."));
      Serial.println(F("This will take a long time and might result in memory issues. Do you wish to continue? (Y/N)"));
      char c;
      while (!Serial.available()) {
      }
      c = (char)Serial.read();
      if (c == 'Y' || c == 'y') {
        Serial.print("Would you like your output in decimal or hexadecimal? Please indicate with '1' for HEX or '2' for DEC: ");
        while (!Serial.available()) {
        }
        uint8_t outputType = Serial.parseInt();
        Serial.println(outputType);
        flash.printAllPages(outputType);
      }
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 9) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 9 : Erase sector                                                  "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will erase a 4KB sector."));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to erase: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      flash.eraseSector(page);
      clearprintBuffer();
      sprintf(printBuffer, "A 4KB sector containing page %d has been erased", page);
      Serial.println(printBuffer);
      Serial.print("Type 1 to read the page you have just erased. Type 0 to continue: ");
      while (!Serial.available()) {
      }
      uint8_t choice = Serial.parseInt();
      Serial.println(choice);
      if (choice == 1) {
        Serial.print("Would you like your output in decimal or hexadecimal? Please indicate with '1' for HEX or '2' for DEC: ");
        while (!Serial.available()) {
        }
        uint8_t outputType = Serial.parseInt();
        Serial.println(outputType);
        flash.printPage(page, outputType);
      }
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 10) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 10 : Erase 32KB Block                                              "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will erase a 32KB block."));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to erase: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      flash.eraseBlock32K(page);
      clearprintBuffer();
      sprintf(printBuffer, "A 32KB block containing page %d has been erased", page);
      Serial.println(printBuffer);
      Serial.print("Type 1 to read the page you have just erased. Type 0 to continue: ");
      while (!Serial.available()) {
      }
      uint8_t choice = Serial.parseInt();
      Serial.println(choice);
      if (choice == 1) {
        Serial.print("Would you like your output in decimal or hexadecimal? Please indicate with '1' for HEX or '2' for DEC: ");
        while (!Serial.available()) {
        }
        uint8_t outputType = Serial.parseInt();
        Serial.println(outputType);
        flash.printPage(page, outputType);
      }
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 11) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                       Function 11 : Erase 64KB Block                                              "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will erase a 64KB block."));
      Serial.print(F("Please enter the number of the page (0-4095) you wish to erase: "));
      while (!Serial.available()) {
      }
      page = Serial.parseInt();
      Serial.println(page);
      flash.eraseBlock64K(page);
      clearprintBuffer();
      sprintf(printBuffer, "A 64KB block containing page %d has been erased", page);
      Serial.println(printBuffer);
      Serial.print("Type 1 to read the page you have just erased. Type 0 to continue: ");
      while (!Serial.available()) {
      }
      uint8_t choice = Serial.parseInt();
      Serial.println(choice);
      if (choice == 1) {
        Serial.print("Would you like your output in decimal or hexadecimal? Please indicate with '1' for HEX or '2' for DEC: ");
        while (!Serial.available()) {
        }
        uint8_t outputType = Serial.parseInt();
        Serial.println(outputType);
        flash.printPage(page, outputType);
      }
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
    else if (commandNo == 12) {
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("                                                      Function 12 : Erase Chip                                                    "));
      Serial.println(F("                                                        SPIFlash library test                                                     "));
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("This function will erase the entire flash memory."));
      Serial.println(F("Do you wish to continue? (Y/N)"));
      char c;
      while (!Serial.available()) {
      }
      c = (char)Serial.read();
      if (c == 'Y' || c == 'y') {
        flash.eraseChip();
        Serial.println(F("Chip erased"));
      }
      Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------"));
      Serial.println(F("Please type the next command. Type 0 to get the list of commands"));
    }
  }
}

void clearprintBuffer()
{
  for (uint8_t i = 0; i < 128; i++) {
    printBuffer[i] = 0;
  }
}


