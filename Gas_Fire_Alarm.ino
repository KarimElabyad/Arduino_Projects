/*
 Arduino MQ4 gas sensor - Geekstips.com
 This example is to calculate the gas concentration using the R0
 calculated in the example above

*/

/*    Max6675 Module  ==>   Arduino
 *    CS              ==>     D10
 *    SO              ==>     D11
 *    SCK             ==>     D12
 *    Vcc             ==>     Vcc (5v)
 *    Gnd             ==>     Gnd      */


#define MAX6675_CS   10
#define MAX6675_SO   11
#define MAX6675_SCK  12


int buzzer = 9; //Buzzer pin
int gas_sensor = A1; //Sensor pin
float m = -0.318; //Slope
float b = 1.133; //Y-Intercept
float R0 = 11.820; //Sensor Resistance in fresh air from previous code

void setup() {
  Serial.begin(9600); //Baud rate
  pinMode(buzzer, OUTPUT); //Set buzzer as output
  digitalWrite(buzzer, LOW); // Turn buzzer off
  pinMode(gas_sensor, INPUT); //Set gas sensor as input
}

void loop() {
  float temperature_read = readThermocouple(); 
  float sensor_volt; //Define variable for sensor voltage
  float RS_gas; //Define variable for sensor resistance
  float ratio; //Define variable for ratio
  float sensorValue = analogRead(gas_sensor); //Read analog values of sensor

  
  sensor_volt = sensorValue * (5.0 / 1023.0); //Convert analog values to voltage
  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0; //Get value of RS in a gas
  ratio = RS_gas / R0;   // Get ratio RS_gas/RS_air

  double ppm_log = (log10(ratio) - b) / m; //Get ppm value in linear scale according to the the ratio value
  double ppm = pow(10, ppm_log); //Convert ppm value to log scale
  double percentage = ppm / 10000; //Convert to percentage
  if (sensorValue > 500 or temperature_read > 50) {
    //Check if ppm value is greater than 500
    digitalWrite(buzzer, HIGH); //Turn buzzer on
  } else {
    digitalWrite(buzzer, LOW);
    //Turn buzzer off
  }
  
  Serial.print("Ratio = "); //display ratio
  Serial.print(ratio); //display value of ratio
  Serial.print('\n');

  Serial.print("SenorValue = "); //display MQ4 raw
  Serial.print(sensorValue); //display value of MQ4 Raw
  Serial.print('\n');
  
  Serial.print("ppm = "); //display ppm
  Serial.print(ppm); //display value of ppm
  Serial.print('\n');
  Serial.print("Temp = "); //display Temp
  Serial.print(temperature_read); //display value of Temp
  Serial.print('\n');
  delay(1000); //Wait 1 second
}

double readThermocouple() {

  uint16_t v;
  pinMode(MAX6675_CS, OUTPUT);
  pinMode(MAX6675_SO, INPUT);
  pinMode(MAX6675_SCK, OUTPUT);
  
  digitalWrite(MAX6675_CS, LOW);
  delay(1);

  // Read in 16 bits,
  //  15    = 0 always
  //  14..2 = 0.25 degree counts MSB First
  //  2     = 1 if thermocouple is open circuit  
  //  1..0  = uninteresting status
  
  v = shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  v <<= 8;
  v |= shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  
  digitalWrite(MAX6675_CS, HIGH);
  if (v & 0x4) 
  {    
    // Bit 2 indicates if the thermocouple is disconnected
    return NAN;     
  }

  // The lower three bits (0,1,2) are discarded status bits
  v >>= 3;

  // The remaining bits are the number of 0.25 degree (C) counts
  return v*0.25;
}
