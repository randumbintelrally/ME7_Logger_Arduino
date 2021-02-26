void printLabels() {
  for (int t = 0; t<variableQuantity; t++) {
    if(t<10) {
      Serial.print("0");
    }
    Serial.print(t);
    Serial.print("   Name: ");
    for (int n = 0; n<0x0F; n++) {
      Serial.print(variables[t].variableName[n]);
    }
    Serial.print("Address:  0x");
    if(variables[t].variableAddress<0x100000){
      Serial.print("00");
    }
    Serial.print(variables[t].variableAddress, HEX);
    Serial.print("  ");
    if(variables[t].variableSize == 1) {
      Serial.print(" 8 bit  BM: 0x");
      }
    else {
      Serial.print("16 bit  BM: 0x");
    }
    if(variables[t].variableBitmask<0x1000) {
      Serial.print("000");
    }
    Serial.print(variables[t].variableBitmask, HEX);
    Serial.print("  S = ");
    Serial.print(variables[t].variableSigned);
    Serial.print("  A = ");
    Serial.print(variables[t].variableConversionA, 7);
    Serial.print("  B = ");
    Serial.println(variables[t].variableConversionB);
  }
}
