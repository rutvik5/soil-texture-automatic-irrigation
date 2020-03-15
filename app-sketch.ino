#include <elapsedMillis.h>
#include <SoftwareSerial.h>

// typedef long elapsedMillis;
elapsedMillis time_elapsed_short,time_elapsed_long;


// intialize pins for sensors
const int temp_sensor_pin= A0; 
const int motor_pin= 4;
const int pir_sensor_pin= 6; 
const int led_pin= 13;
const int alarm_pin= 8;
SoftwareSerial mySerial(9, 10); //GSM pins

//const float crop_moisture_required= 50; //soil moisture level required by the crop 
const float soil_holding_capacity= 30;// soil water holding capacity in percecntage% 
const float kc= 0.78; //predefined crop factor which varies with the crop
const int set_pir_value= 250; // analog value for pir sensor to detect intrusion
int hours= 10; // no.of hours for which the supply time interval is set
const float area= 1; //area of the farm in sq metres

int pir_value=0,current_moisture,i;
float ETo, ETcrop, temp, p, supply_time,difference,supply, crop_water_supply, motor_on_interval;
bool supply_flag= false;



void setup() {
	   mySerial.begin(9600);   // Setting the baud rate of GSM Module  
     Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
     delay(100);

     pinMode(pir_sensor_pin, INPUT);
	   pinMode(led_pin, OUTPUT);
     pinMode(alarm_pin, OUTPUT);
	 
     pinMode(motor_pin, OUTPUT);

	  crop_water_supply= crop_water_req();
	 // Serial.println("Crop water Supply from etcrop value");
    //Serial.println(crop_water_supply);
    
    float req_water= crop_water_supply *1000*area; // calculates the amount of water req by crop after analysis
   // Serial.println("Amount of water required based on ETcrop (mililitres) : ");
    //Serial.println(req_water);   
     
    supply= ((req_water/soil_holding_capacity)*100)/1000; // calculates the amt of water to be actually supplied in litres
   // Serial.println("Actual amount of water to be supplied to the crop after soil analysis (litres): ");
    //Serial.println(supply);
    
    supply_time= (supply/ 0.54) ; //total time required to supply water in minutes based on speed of motor (converts water required to time)
	 // Serial.println("Total water-supply time required throughout the day (minutes): ");
    //Serial.println(supply_time);
	  
	  motor_on_interval= (supply_time/hours)*60000; // time for which motor will be on per hour
   //Serial.println("Time for which the motor is on in every hour interval (minutes):  ");
    //Serial.println(motor_on_interval/60000);
}

float crop_water_req(){

  temp= analogRead(temp_sensor_pin);
	temp= temp * 0.488; //returns temp value in C

 
    ETo= 0.28*(0.46 * temp + 8);

   // Serial.println("ETo:");
    //Serial.println(ETo);

    ETcrop= ETo * kc;

    //erial.println("ETcrop:");
    //Serial.println(ETcrop);
  
   return ETcrop;
}


  
void loop() {
	
  pir_value= analogRead(pir_sensor_pin);
  
  Serial.print("PIR value: ");
  Serial.println(pir_value);
  //delay(1000);
  if(pir_value>set_pir_value){
	  
	  // Start of GSM Module
	 if (Serial.available()>0){
    
		     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        // delay(1000); 
         mySerial.println("AT+CMGS=\"+917718961959\"\r");
         //delay(1000);
         mySerial.println("Alert! Alert! You have an intruder in your farm");// The SMS text you want to send
         //delay(100);
         mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
         //delay(1000);
     
        }

	  
	  // End of GSM Module
    
	  // Start of Farm Security Module
    for(i = 0; i < 255; i = i + 2)
        {
            analogWrite(led_pin, i);
            analogWrite(alarm_pin, i);
            delay(10);
        }
        for(i = 255; i > 1; i = i - 2)
        {
            analogWrite(led_pin, i);
            analogWrite(alarm_pin, i);
            delay(5);
        }
        for(i = 1; i <= 10; i++)
        {
            analogWrite(led_pin, 255);
            analogWrite(alarm_pin, 200);
            delay(100);
            analogWrite(led_pin, 0);
            analogWrite(alarm_pin, 25);
            delay(100);
        }
    
   
  }   
   //pir_value=0;
   
   // End of Farm Security Module
   
   // Start water supply for every interval
      Serial.print("Time elapsed long: ");
      Serial.println(time_elapsed_long);
      digitalWrite(motor_pin, HIGH);
     if(hours>0){
      
      if(time_elapsed_long>10000){
        supply_required_water();
        hours--;
       // Serial.print("Hours: ");
        //Serial.println(hours);
        time_elapsed_long= 0;
      }
    } 
	
	// End of water supply interval module
}	

void supply_required_water(){  
        time_elapsed_short=0;
        digitalWrite(motor_pin, LOW);
        while(time_elapsed_short < motor_on_interval){  
             // Serial.print("Time elapsed short");
              //Serial.println(time_elapsed_short);  
                   
              
         }
        
         
} 

