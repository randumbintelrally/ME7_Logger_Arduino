#include "global.h"
#include "ECU_Config.h"
#include "test.h"
#include "KWP2000.h"

void setup() {
  Serial.begin(115200);
  while(!Serial) {
  }
  Serial.println("Serial Connection Established");
  Serial.println("Declaring Structures");
  
  declareStructures();

  Serial.println("Logged Variables:");
  printLabels();
  Serial.println();
  produceLoggerArray();
  
  KWPConnectionStatus = 0;
  sampleDelay = (1000/FREQUENCY);
  pinMode(TXPin, OUTPUT);             //Configure TX of Kline as Digital Output
  digitalWrite(TXPin, HIGH);          //Idle K Line
}

void loop() {
  while(KWPConnectionStatus == 0) {     //slow init process
    if(KWPConnect()){
      KWPConnectionStatus = 1;
    }
    else {
      Serial.println("Unable to establish connection");
      while (1) {
        //stop program
      }
    }
  }

  while(KWPConnectionStatus == 1) {           //Configure Development Session and Set Speed
    StartDiagnosticDevelopmentSession();
    if(accessTimingParameters()==1) {
      KWPConnectionStatus = 2;
    }
  }

  while(KWPConnectionStatus == 2) { //configure Memory blocks
    Serial.println("Reading Memory Addresses");
    readMemoryByAddress(0x00E1B0, 4);
    readMemoryByAddress(0x00E228, 4);
    Serial.println("Writing Memory Addresses");
    writeMemoryArrayByAddress(0x387A00, 1, 0x80);
    writeMemoryArrayByAddress(0x387A80, 2, 0x80);
    writeMemoryArrayByAddress(0x387B00, 3, 0x80);
    writeMemoryArrayByAddress(0x387B80, 4, 0x80);
    writeMemoryArrayByAddress(0x387C00, 5, 0x46);
    memoryErrors = verifyWrittenData(0x387A00, 1, 0x80);
    if(memoryErrors) {
      Serial.print("0x");
      Serial.print(memoryErrors, HEX);
      Serial.println(" in block 1");        
    }
    memoryErrors = verifyWrittenData(0x387A80, 2, 0x80);
    if(memoryErrors) {
      Serial.print("0x");
      Serial.print(memoryErrors, HEX);
      Serial.println(" in block 2");        
    }
    memoryErrors = verifyWrittenData(0x387B00, 3, 0x80);
    if(memoryErrors) {
      Serial.print("0x");
      Serial.print(memoryErrors, HEX);
      Serial.println(" in block 3");        
    }
    memoryErrors = verifyWrittenData(0x387B80, 4, 0x80);
    if(memoryErrors) {
      Serial.print("0x");
      Serial.print(memoryErrors, HEX);
      Serial.println(" in block 4");        
    }
    memoryErrors = verifyWrittenData(0x387C00, 5, 0x46);
    if(memoryErrors) {
      Serial.print("0x");
      Serial.print(memoryErrors, HEX);
    }
    else {
      Serial.println("No");
    }
    Serial.println(" errors in block 5");
    Serial.println("Rereading Memory Address");
    readMemoryByAddress(0x00E228, 4);
    Serial.println("Writing Memory Address");
    writeMemoryByAddressFourBytes(0x00E228, 0x003AE100);
    Serial.println("Sending Tester Present Message");
    testerPresent();
    Serial.println("Configuring Logging Messages");
    writeLoggingArray();
    KWPConnectionStatus = 3;
    Serial.println("Setting Timing Clock");
    logClock = millis() + sampleDelay;
  }

  while(KWPConnectionStatus == 3) {
    if (logClock<= millis()) {
      Serial.println("getting Log");
      getLogData();
      for(int t=0; t<variableQuantity; t++) {
        for (int n = 0; n<0x0F; n++) {
        Serial.print(variables[t].variableName[n]);
        }
        Serial.print("= ");
        Serial.println(variables[t].variableValue, 6);
      }
      logClock = millis() + sampleDelay;
      while(1) {
      }   
    }
  }
}
