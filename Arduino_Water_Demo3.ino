
// Variables used:
int FAN_1_RAW_VALUE; 
int FAN_1_RAW_VALUE_LIFETIME_SUM; 
int FAN_1_CALCULATED_RPM;
int FAN_2_RAW_VALUE; 
int FAN_2_RAW_VALUE_LIFETIME_SUM; 
int FAN_2_CALCULATED_RPM;
 
// The pin location of the sensors. Arduino UNO only supports Interrupts on PIN 2 & 3
// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ 

int FAN_1_PIN = 2;
int FAN_2_PIN = 3;

void FAN_1_INCREASE ()
  // This is the function that gets called when FAN_1 PIN RAISED (changed from 0 to 1)
  { 
    FAN_1_RAW_VALUE++;
    FAN_1_RAW_VALUE_LIFETIME_SUM++;
  }
  
void FAN_2_INCREASE ()
  // This is the function that gets called when FAN_2 PIN RAISED (changed from 0 to 1)
  { 
    FAN_2_RAW_VALUE++;
    FAN_2_RAW_VALUE_LIFETIME_SUM++; 
  }
  
void setup()
  { 
    pinMode(FAN_1_PIN, INPUT);
    pinMode(FAN_2_PIN, INPUT);
    Serial.begin(9600);
    
    // Every half revolution of each fan will cause an interrupt that we count up. Two fans need two individual interrupts.
    attachInterrupt(digitalPinToInterrupt(FAN_1_PIN), FAN_1_INCREASE, RISING); 
    attachInterrupt(digitalPinToInterrupt(FAN_2_PIN), FAN_2_INCREASE, RISING); 
   }
 
void loop ()
  {
    // Reset counters to 0 to be able to calculate the RPM per FAN over the next second.
    FAN_1_RAW_VALUE = 0;
    FAN_2_RAW_VALUE = 0; 
    
    // Enables interrupts for the next ~1 second (due to delay)
    interrupts();
    // Wait 1 second and gather interrupts on pins during that second
    delay (1000);
    // Disable interrupts while doing calculations using new interrupt command: https://forum.arduino.cc/index.php?topic=130583.0 
    noInterrupts();
    
    // calculates fan RPM. According to Wikipedia the fan will give a signal every half revolution, hence multiplied by 30 gives the RPM.
    FAN_1_CALCULATED_RPM = (FAN_1_RAW_VALUE * 30);
    FAN_2_CALCULATED_RPM = (FAN_2_RAW_VALUE * 30);

  
    // Prints the number calculated above
    Serial.print ("FAN 1 RPM: ");
    Serial.print (FAN_1_CALCULATED_RPM, DEC);
    Serial.print ("\tFAN 1 Lifetime Revs: ");
    Serial.print ((FAN_1_RAW_VALUE_LIFETIME_SUM/2), DEC);
    
    Serial.print ("\t\tFAN 2 RPM: ");
    Serial.print (FAN_2_CALCULATED_RPM, DEC);
    Serial.print ("\tFAN 2 Lifetime Revs: ");
    Serial.print ((FAN_2_RAW_VALUE_LIFETIME_SUM/2), DEC);
        
    //Prints a new line
    Serial.print ("\r\n");
  
  } 
