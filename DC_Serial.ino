String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String dc_command = "";
String value = "";
int int_value = 0;
int value_index = 0;

//Current values
int brightness1 = 100;
int brightness2 = 100;
int brightness3 = 100;
int temp = 85;
int lowbatt = 14;


void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.print(inputString);
    stringParse(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void stringParse(String parse){
  value_index = parse.indexOf('_');
  
  if(parse=="HELP\n"){
      Serial.println("Commands:");
      Serial.println("HELP - lists all recognized commands.");
      Serial.println("PRODUCT - returns the product name.");
      Serial.println("GETVALUES - returns current values.");
      Serial.println("BRIGHTNESS1_X - sets channel 1's max brightness to X (0-100)");
      Serial.println("BRIGHTNESS2_X - sets channel 2's max brightness to X (0-100)");
      Serial.println("BRIGHTNESS3_X - sets channel 3's max brightness to X (0-100)");
      Serial.println("TEMP_X - sets max LED temperature, in Celsius, to X (0-100)");
      Serial.println("LOWBATT_X - sets min battery voltage, in Volts, to X (9-14)");
  }else if(parse == "PRODUCT\n"){
    Serial.println("Dauntless Concepts SD0081");
  }else if(parse == "GETVALUES\n"){
    Serial.print("Channel 1 brightness: ");
    Serial.print(brightness1);
    Serial.println("%");
    Serial.print("Channel 2 brightness: ");
    Serial.print(brightness2);
    Serial.println("%");
    Serial.print("Channel 3 brightness: ");
    Serial.print(brightness3);
    Serial.println("%");
    Serial.print("Max LED temperature: ");
    Serial.print(temp);
    Serial.println(" degrees Celsius");
    Serial.print("Low battery warning: ");
    Serial.print(lowbatt);
    Serial.println(" V");
  }else if(parse == "SOFTVALUES\n"){
    Serial.println(brightness1);
    Serial.println(brightness2);
    Serial.println(brightness3);
    Serial.println(temp);
    Serial.println(lowbatt);
  }else if(value_index >= 0){
      dc_command = parse.substring(0, value_index);
      value = parse.substring(value_index+1);
      int_value = value.toInt();
      if(dc_command == "BRIGHTNESS1"){
        if(int_value>-1 and int_value<101){
          Serial.print("Setting channel 1's max brightness to ");
          Serial.print(int_value);
          Serial.println("%.");
          brightness1 = int_value;
        }else{
          Serial.print("Invalid brightness value (");
          Serial.print(int_value);
          Serial.println(").");
        }
      }
      else if(dc_command == "BRIGHTNESS2"){
        if(int_value>-1 and int_value<101){
          Serial.print("Setting channel 2's max brightness to ");
          Serial.print(int_value);
          Serial.println("%.");
          brightness2 = int_value;
        }else{
          Serial.print("Invalid brightness value (");
          Serial.print(int_value);
          Serial.println(").");
        }
      }
      else if(dc_command == "BRIGHTNESS3"){
        if(int_value>-1 and int_value<101){
          Serial.print("Setting channel 3's max brightness to ");
          Serial.print(int_value);
          Serial.println("%.");
          brightness3 = int_value;
        }else{
          Serial.print("Invalid brightness value (");
          Serial.print(int_value);
          Serial.println(").");
        }
      }
      else if(dc_command == "TEMP"){
        if(int_value>-1 and int_value<101){
          Serial.print("Setting max LED temperature to ");
          Serial.print(int_value);
          Serial.println("%.");
          temp = int_value;
        }else{
          Serial.print("Invalid temperature value (");
          Serial.print(int_value);
          Serial.println(").");
        }
      }
      else if(dc_command == "LOWBATT"){
        if(int_value>8 and int_value<15){
          Serial.print("Setting min battery voltage to ");
          Serial.print(int_value);
          Serial.println("V.");
          lowbatt = int_value;
        }else{
          Serial.print("Invalid voltage value (");
          Serial.print(int_value);
          Serial.println(").");
        }
      }
      else{
        Serial.println("Unrecognized command (" + dc_command + ")");
      }
  }
  else{
    Serial.println("Unrecognized command.");
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
