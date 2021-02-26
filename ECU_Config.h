#define FREQUENCY 1                        //Logs Per Second
#define RXPin 0
#define TXPin 1
#define RETRYATTEMPTS 5

int variableQuantity;

struct variable{
  uint8_t variableCount;
  char variableName[0x0F];
  uint32_t variableAddress;
  uint8_t variableSize;
  uint16_t variableBitmask;
  bool variableSigned;
  float variableConversionA;
  float variableConversionB;
  uint16_t variableRaw;
  float variableValue;
};

struct variable variables[42];

void declareStructures() {
  int t=0;
  
  //Engine Speed
  strncpy(variables[t].variableName, "nmot_w          ", 0x0F);
  variables[t].variableAddress = 0x00F89E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .025;    
  variables[t].variableConversionB = 0.00;   
  t++;
    
  //Mass Air Flow
  strncpy(variables[t].variableName, "mshfm_w         ", 0x0F);
  variables[t].variableAddress = 0x00F9A6;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0277778;    
  variables[t].variableConversionB = 0.00; 
  t++;  

  //Engine Load
  strncpy(variables[t].variableName, "rl_w            ", 0x0F);
  variables[t].variableAddress = 0x00F9B8;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0234375;    
  variables[t].variableConversionB = 0.00;
  t++;
/*
  //Ignition Reatard Knock Control Cylinder 1
  strncpy(variables[t].variableName, "wkr_0           ", 0x0F);
  variables[t].variableAddress = 0x00F9D2;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = -0.75;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Ignition Reatard Knock Control Cylinder 2
  strncpy(variables[t].variableName, "wkr_1           ", 0x0F);
  variables[t].variableAddress = 0x00F9D3;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = -0.75;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Ignition Reatard Knock Control Cylinder 3
  strncpy(variables[t].variableName, "wkr_2           ", 0x0F);
  variables[t].variableAddress = 0x00F9D4;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = -0.75;    
  variables[t].variableConversionB = 0.00;
  t++;
  
  //Ignition Reatard Knock Control Cylinder 4
  strncpy(variables[t].variableName, "wkr_3           ", 0x0F);
  variables[t].variableAddress = 0x00F9D5;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = -0.75;    
  variables[t].variableConversionB = 0.00;
  t++;
*/
  //Ignition Timing Angle
  strncpy(variables[t].variableName, "zwist           ", 0x0F);
  variables[t].variableAddress = 0x00FA0A;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Ignition Timing Angle Overall
  strncpy(variables[t].variableName, "zwout           ", 0x0F);
  variables[t].variableAddress = 0x00FA0C;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Battery Voltage
  strncpy(variables[t].variableName, "ub              ", 0x0F);
  variables[t].variableAddress = 0x38099D;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.0704;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Selected Gear
  strncpy(variables[t].variableName, "gangi           ", 0x0F);
  variables[t].variableAddress = 0x3809A4;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0.00;
  t++;  

  //Ignition Retard Cylinder 1
  strncpy( variables[t].variableName, "dwkrz_0        ", 0x0F);
  variables[t].variableAddress = 0x380A8F;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Ignition Retard Cylinder 2
  strncpy( variables[t].variableName, "dwkrz_1        ", 0x0F);
  variables[t].variableAddress = 0x380A90;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;   
  t++;
   
  //Ignition Retard Cylinder 3
  strncpy( variables[t].variableName, "dwkrz_2        ", 0x0F);
  variables[t].variableAddress = 0x380A91;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;
  t++;
  
  //Ignition Retard Cylinder 4
  strncpy( variables[t].variableName, "dwkrz_3        ", 0x0F);
  variables[t].variableAddress = 0x380A92;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;    
  t++;

  //Base Ignition Angle
  strncpy(variables[t].variableName, "zwgru           ", 0x0F);
  variables[t].variableAddress = 0x380BAC;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = 0.75;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Spark Dwell Time
  strncpy(variables[t].variableName, "tsrldyn         ", 0x0F);
  variables[t].variableAddress = 0x380BB5;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.1;    
  variables[t].variableConversionB = 0;
  t++;

    //MAF Sensor Voltage
  strncpy(variables[t].variableName, "uhfm_w          ", 0x0F);
  variables[t].variableAddress = 0x380DFA;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .00488281;    
  variables[t].variableConversionB = 0.00;
  t++;
 
  //Count Misfires on Cylinder 1
  strncpy(variables[t].variableName, "fzabg_w_0       ", 0x0F);
  variables[t].variableAddress = 0x38185E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Count Misfires on Cylinder 2
  strncpy(variables[t].variableName, "fzabg_w_1       ", 0x0F);
  variables[t].variableAddress = 0x381860;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Count Misfires on Cylinder 3
  strncpy(variables[t].variableName, "fzabg_w_2       ", 0x0F);
  variables[t].variableAddress = 0x381862;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0.00;  
  t++;
  
  //Count Misfires on Cylinder 4
  strncpy(variables[t].variableName, "fzabg_w_3       ", 0x0F);
  variables[t].variableAddress = 0x381864;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Air Fuel Ratio Current 
  strncpy(variables[t].variableName, "lamsoni_w       ", 0x0F);
  variables[t].variableAddress = 0x381B2E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .000244141;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Vehicle Speed
  strncpy(variables[t].variableName, "vfil_w          ", 0x0F);
  variables[t].variableAddress = 0x381BF4;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0078125;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Boost Pressure Actual
  strncpy(variables[t].variableName, "pvdks_w         ", 0x0F);
  variables[t].variableAddress = 0x381E32;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0390625;    
  variables[t].variableConversionB = 0.00;      
  t++;

  //Boost Pressure Desired
  strncpy(variables[t].variableName, "plsol_w         ", 0x0F);
  variables[t].variableAddress = 0x381E92;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0390625;    
  variables[t].variableConversionB = 0.00; 
  t++;

  //Engine Load Requested
  strncpy(variables[t].variableName, "rlsol_w         ", 0x0F);
  variables[t].variableAddress = 0x381EE8;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0234375;    
  variables[t].variableConversionB = 0.00;      
  t++;

  //Air Fuel Ratio Desired
  strncpy(variables[t].variableName, "lamsbg_w        ", 0x0F);
  variables[t].variableAddress = 0x381F78;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .000244141;    
  variables[t].variableConversionB = 0.00;
  t++;
  
  //Adaptation Partial
  strncpy(variables[t].variableName, "fra_w           ", 0x0F);
  variables[t].variableAddress = 0x381F8A;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.0000305;    
  variables[t].variableConversionB = 0.00;
  t++;


  //Wastegate Duty Cycle After Linearization
  strncpy(variables[t].variableName, "ldtv            ", 0x0F);
  variables[t].variableAddress = 0x382366;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = .005;    
  variables[t].variableConversionB = 0.00;    
  t++;

  //Driver Requested Relative Torque
  strncpy(variables[t].variableName, "mrfa_w          ", 0x0F);
  variables[t].variableAddress = 0x38255C;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .00305176;    
  variables[t].variableConversionB = 0.00; 
  t++;

  //Lambda Control Average
  strncpy(variables[t].variableName, "frm_w           ", 0x0F);
  variables[t].variableAddress = 0x38278E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.0000305;    
  variables[t].variableConversionB = 0.00;
  t++;
  
  //Lambda Control
  strncpy( variables[t].variableName, "fr_w            ", 0x0F);
  variables[t].variableAddress = 0x382792;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.0000305;    
  variables[t].variableConversionB = 0.00;
  t++;

    //Intake Camshaft Angle
  strncpy(variables[t].variableName, "wnwise_w        ", 0x0F);
  variables[t].variableAddress = 0x382A3E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.00390625;    
  variables[t].variableConversionB = 0.00;
  t++;
  
  //Intake Temperature After Linearization
  strncpy(variables[t].variableName, "tanslin         ", 0x0F);
  variables[t].variableAddress = 0x384894;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = .75;    
  variables[t].variableConversionB = -48.00;
  t++;

  //Coolant Temperature After Linearization
  strncpy(variables[t].variableName, "tmotlin         ", 0x0F);
  variables[t].variableAddress = 0x38489C;
  variables[t].variableSize = 1;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 1;
  variables[t].variableConversionA = .75;    
  variables[t].variableConversionB = -48.00;
  t++;

  //Camshaft Angle
  strncpy(variables[t].variableName, "wnwi_w          ", 0x0F);
  variables[t].variableAddress = 0x384998;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 0.00390625;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Ambient Pressure
  strncpy(variables[t].variableName, "pu_w            ", 0x0F);
  variables[t].variableAddress = 0x384A6A;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .0390625;    
  variables[t].variableConversionB = 0.00;
  t++;

  //Driver Requested Target AFR
  strncpy(variables[t].variableName, "lamfa_w         ", 0x0F);
  variables[t].variableAddress = 0x384ACE;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .000244141;    
  variables[t].variableConversionB = 0.00;   
  t++;
  
  // Lambda Part Protection
  strncpy(variables[t].variableName, "lambts_w        ", 0x0F);
  variables[t].variableAddress = 0x384B0E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x00;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = .000244141;    
  variables[t].variableConversionB = 0.00;  
  t++;
  
/*
  //Brake Pedal Switch Condition
  strncpy(variables[t].variableName, "B_br            ", 0x0F);
  variables[t].variableAddress = 0x00FD4D;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x8000;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0;
  t++;
  
  //Clutch Pedal Switch Condition
  strncpy(variables[t].variableName, "B_kuppl        ", 0x0F);
  variables[t].variableAddress = 0x00FD4E;
  variables[t].variableSize = 2;
  variables[t].variableBitmask = 0x0008;
  variables[t].variableSigned = 0;
  variables[t].variableConversionA = 1;    
  variables[t].variableConversionB = 0;
  t++;
*/
  variableQuantity = t; 
}

void produceLoggerArray() {
  for(int t = 0; t<variableQuantity; t++) {
    if(variables[t].variableSize == 2) {
      loggingArray[t*3] = 0x40 + (variables[t].variableAddress>>16);
    }
    else{
      loggingArray[t*3] = variables[t].variableAddress>>16;
    }
    loggingArray[(t*3)+1] = variables[t].variableAddress>>8;
    loggingArray[(t*3)+2] = variables[t].variableAddress;
  }
}
