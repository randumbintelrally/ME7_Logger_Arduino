int RecieveData() {
  uint8_t recieveLength;
  while (!Serial1.available()) {
  }
  recieveLength = Serial1.read();
  //Serial.println(recieveLength, HEX);
  if (recieveLength == 0) {
    for (int t=0; t<1; ) {
      if(Serial1.available()) {
        recieveLength = Serial1.read();
        t++;
      }
    }
  }
  for (int t = 0; t < recieveLength + 1; ) {
    if (Serial1.available()) {
      rxBuf[t] = Serial1.read();
      t++;
    }
  }
  return recieveLength;
}

void SendDataChksum(int messageLength) {
  checksum = 0;
  for (int t = 0; t < messageLength; t++) {
    Serial1.write(txBuf[t]);
    checksum = checksum + txBuf[t];
  }
  Serial1.write(checksum);
  Serial1.flush();
  //Serial.println();
  while(Serial1.available()<(messageLength+1)){
    if(Serial1.available() == 0x3F) {
      messageLength = 0x3F;
      break;
    }
  }
  for(int t=0; t < (messageLength+1); t++) {
    Serial1.read();
  } 
    
}

bool KWPSlowInit() {
  Serial1.end();                      //End Serial1 on Kline
  Serial.println("Establishing Connection TO ECU");
  
  pinMode(TXPin, OUTPUT);             //Configure TX of Kline as Digital Output
  digitalWrite(TXPin, HIGH);          //Set K Line High(inactive state)
  delay(350);                         //Keep K Line High for 300 ms
  Serial.println("Starting Init");
  digitalWrite(TXPin, LOW);           //Start bit
  delay(200);

  // Send address (0x11) backwards (10001000) may be in 7O1
  digitalWrite(TXPin, HIGH);
  delay(200);
  digitalWrite(TXPin, LOW);
  delay(600);
  digitalWrite(TXPin, HIGH);
  delay(200);
  digitalWrite(TXPin, LOW);
  delay(600);
  digitalWrite(TXPin, HIGH);          //Stop bit

  Serial1.begin(10400);
  timeoutClock = millis() + 700;

  for (int t=0; t<3; ) {
    if(Serial1.available()) {
      rxBuf[t] = Serial1.read();
      t++;
    }
    if(timeoutClock == millis()) {
      Serial.println("No Response From ECU");
      return 0;
    }
  }
  if (rxBuf[0] != 0x55) {
    Serial.println("Invalid Response Init Message 1");
    return 0;
  }
  if (rxBuf[1] != 0xEF) {
    Serial.println("Invalid Response Init Message 2");
    return 0;
  }
  if (rxBuf[2] != 0x8F) {
    Serial.println("Invalid Response Init Message 3");
    return 0;
  }  
  delay(25);
  Serial1.write(0x70);
  Serial1.flush();
  while(1) {
    if(Serial1.available() == 2) {
      Serial1.read();
      rxBuf[0] = Serial1.read();
      if (rxBuf[0] == 0xEE) {
        Serial.println("Init Sequence Successful");
        return 1;
      }
      else {
        Serial.println("Invalid Response From ECU");
        return 0;
      }
    }
  }
}

bool KWPConnect() {
  if (KWPConnectionStatus>0) {
    return 1;
  }
  else {
    for(int i=0; i < RETRYATTEMPTS; i++) {
      if(KWPSlowInit()) {
        return 1;
      }
    }
    return 0;
  }
}

void StartDiagnosticDevelopmentSession() {
  if(KWPConnect()) {
    Serial.println("Starting Diagnostic Development Session");
    delay(25);
    txBuf[0] = 0x03;       //Message Length
    txBuf[1] = 0x10;       //StartDiagnosticSession
    txBuf[2] = 0x86;       //Development Session
    txBuf[3] = 0x63;       //??
    SendDataChksum(4);
    returnLength = RecieveData();
    for (int t = 0; t<returnLength + 1; t++) {
      Serial.print(rxBuf[t], HEX);
      Serial.print(" ");
    }
    if (rxBuf[0] == 0x50) {
      Serial1.end();
      Serial1.begin(56000);
      Serial.println("Diagnostic Session Started");
    }
    else {
      Serial.println("Diagnostic Session Failed");
    }
  }
}

int accessTimingParameters() {
    Serial.println("Accessing Timing Parameters");
    delay(10);
    txBuf[0] = 0x07;       //Message Length
    txBuf[1] = 0x83;       //AccessTiming Parameters
    txBuf[2] = 0x03;       //setTimingParametersToGivenValues
    txBuf[3] = 0x00;       //P2min
    txBuf[4] = 0x01;       //P2Max
    txBuf[5] = 0x00;       //P3min
    txBuf[6] = 0x14;       //P3max
    txBuf[7] = 0x00;       //P4min
    SendDataChksum(8);
    Serial.println("Data Sent");
    returnLength = RecieveData();
    for (int t = 0; t < returnLength; t++) {
        Serial.print(rxBuf[t]);
        Serial.print(" ");
    }
    Serial.println();
    if (rxBuf[0] == 0xC3) {
      Serial.println("Timing Parameters Set");
      return 1;
      }
    else if(rxBuf[0] == 0x7F) {
      Serial.println("Negative Response to Set Timing Parameters");
      return 0;
      }
    else {
      Serial.println("Unknown Message");
      return 2;
    }
}

int readMemoryByAddress(uint32_t address, uint8_t bytes) {
    txBuf[0] = 0x05;               //Message Length
    txBuf[1] = 0x23;               //ReadMemoryByAddress
    txBuf[2] = address>>16;        //address
    txBuf[3] = address>>8;         //address
    txBuf[4] = address;            //address
    txBuf[5] = bytes;              //bytes to recieve
    SendDataChksum(6);
    returnLength = RecieveData();

    if (txBuf[0] == 0x63) {
      Serial.println("Positive Response to ReadMemoryByAddress");
      for (int t=0 ; t<txBuf[5] ; t++) {
        Serial.print("Byte ");
        Serial.print(t+1);
        Serial.print(": 0x");
        Serial.println(rxBuf[t+1], HEX);
      }
      return 1;
      }
    else if (rxBuf[0] == 0x7F) {
      Serial.println("Negative Response to ReadMemoryByAddress");
      return 0;
      }

    else {
      return -2;  
    }
}

uint8_t writeMemoryArrayByAddress(uint32_t address,uint8_t arrayNumber, uint8_t bytes) {
    txBuf[0] = 0x00;               //Extended Length Header
    txBuf[1] = (bytes + 0x05);               //Message Length
    txBuf[2] = 0x3D;               //Write Memory By Address
    txBuf[3] = address>>16;         //address
    txBuf[4] = address>>8;         //address
    txBuf[5] = address;         //address
    txBuf[6] = bytes;              //bytes to send
    for (int t=0; t<(bytes); t++) {
      txBuf[t+7] = memoryArray[arrayNumber-1][t];  
    }
    SendDataChksum(bytes+7);
    returnLength = RecieveData();
    if (rxBuf[0] == 0x7D) {
      Serial.println("Positive Response to WriteMemoryByAddress");
      return 1;
      }
    else if (rxBuf[0] == 0x7F) {
      Serial.println("Negative Response to WriteMemoryByAddress");
      return 0;
      }

    else {
      return -2;  
    }
}

uint8_t verifyWrittenData(uint32_t address, uint8_t arrayNumber, uint8_t bytes) {
    uint8_t errorCount = 0;
    txBuf[0] = 0x05;               //Message Length
    txBuf[1] = 0x23;               //ReadMemoryByAddress
    txBuf[2] = address>>16;        //address
    txBuf[3] = address>>8;         //address
    txBuf[4] = address;            //address
    txBuf[5] = bytes;              //bytes to recieve
    SendDataChksum(6);
    returnLength = RecieveData();

    if (rxBuf[0] == 0x63) {
      Serial.println("Positive Response to ReadMemoryByAddress");
      for (int t=0 ; t<bytes ; t++) {
        if(rxBuf[t+1] != memoryArray[arrayNumber-1][t]) {
          errorCount++;
          /*if(arrayNumber == 5) {
            Serial.print("At line 0x");
            Serial.print(t, HEX);
            Serial.print(" Expected = ");
            Serial.print(memoryArray[][t], HEX);
            Serial.print("  Read = ");
            Serial.println(rxBuf[t+1], HEX);
          }
          */
        }
      }
      return errorCount;
    }
    else if (rxBuf[0] == 0x7F) {
      Serial.println("Negative Response");
      return -1;
    }
    else{
      return -2;
    }
}

uint8_t writeMemoryByAddressFourBytes(unsigned long address, unsigned long data) {
    txBuf[0] = 0x09;       //Message Length
    txBuf[1] = 0x3D;               //WriteMemoryByAddress
    txBuf[2] = address>>16;
    txBuf[3] = address>>8;
    txBuf[4] = address;
    txBuf[5] = 0x04;
    txBuf[6] = data>>24;
    txBuf[7] = data>>16;
    txBuf[8] = data>>8;
    txBuf[9] = data;
    SendDataChksum(10);

    returnLength = RecieveData();

    if (rxBuf[0] == 0x7D) {
      Serial.println("Positive Response to WriteMemoryByAddress");
      return 1;
      }
    else if (rxBuf[0] == 0x7F) {
      Serial.println("Negative Response to WriteMemoryByAddress");
      return 0;
      }

    else {
      return -2;  
    }
}

uint8_t testerPresent() {
    txBuf[0] = 0x01;
    txBuf[1] = 0x3E;
    SendDataChksum(2);

    returnLength = RecieveData();

    if (rxBuf[0] == 0x7E) {
      Serial.println("Positive Response to Tester Present");
      return 1;
    }
    else if (rxBuf[0] == 0x7F) {
      Serial.println("Negative Response to Tester Present");
      return -1;
    }
    else {
      Serial.println("Unknown Response");
      return -2;
    }
}

uint8_t writeLoggingArray() {
  txBuf[0] = 0x00;
  txBuf[1] = (variableQuantity*3)+2;
  txBuf[2] = 0xB7;
  txBuf[3] = 0x03;
  for (uint8_t t=0; t<(variableQuantity*3); t++) {
    txBuf[t+4] = loggingArray[t];
  }
  SendDataChksum(txBuf[1]+2);
  for(int t=0; t<txBuf[1]+2; t++) {
    Serial.print(txBuf[t], HEX);
    Serial.print(" ");
    if(t == 0x10 || t==0x20 || t==0x30 || t==0x40 || t==0x50 || t==0x60 || t==0x70 || t==0x80) {
      Serial.println();
    }
  }
  Serial.println();
  returnLength = RecieveData();

    if (rxBuf[0] == 0xF7) {
      Serial.println("Positive Response to Logging Configuration");
      return 1;
    }
    else if (rxBuf[0] == 0x7F) {
      Serial.println("Negative Response to Logging Configuration");
      return -1;
    }
    else {
      Serial.println("Unknown Response");
      return -2;
    }
}

uint8_t getLogData() {
  txBuf[0] = 0x01;
  txBuf[1] = 0xB7;
  SendDataChksum(2);
  returnLength = RecieveData();
  
  if (rxBuf[0] == 0xF7) {
    Serial.println("Positive Response to Get Log Data");
    for(int t=0; t<returnLength; t++) {
      Serial.print(rxBuf[t], HEX);
      Serial.print(" ");
      if(t==0x0F || t==0x1F || t==0x2F || t == 0x3F || t==0x4F || t==0x5F || t==0x6F) {
        Serial.println();
      }
    }
    Serial.println();
    int v = 0;
    for(int t = 0; t<(returnLength-2); ) {
      if(variables[v].variableSize == 2) {
        variables[v].variableRaw = (rxBuf[t+2]<<8) + rxBuf[t+1];
        t = t+2;
        v++;
      }
      else if(variables[v].variableSize == 1) {
        variables[v].variableRaw = rxBuf[t+1];
        t++;
        v++;        
      }
      else {
        Serial.println("Error");
        t++;
      }
    }
    for(int t=0; t<variableQuantity; t++) {
      if(variables[t].variableSigned) {
        signedTemp = variables[t].variableRaw;
        variables[t].variableValue = (signedTemp * variables[t].variableConversionA) + variables[t].variableConversionB;
      }
      else{
        variables[t].variableValue = (variables[t].variableRaw * variables[t].variableConversionA) + variables[t].variableConversionB;
      }
    }
    return 1;
  }
  else if (rxBuf[0] == 0x7F) {
    Serial.println("Negative Response to Get Log Data");
    return -1;
  }
  else {
    Serial.println("Unknown Response");
    return -2;
  }
}
