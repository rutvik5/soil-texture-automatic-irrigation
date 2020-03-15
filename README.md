# Automatic Irrigation System based on soil texture and Farm Securtiy
This is an Arduino Uno project used to automatically supply water based on soil texture and geolocation. It comprises five main components namely Arduino Uno, relay, alarm, PIR sensor and GSM module. The arudino sketch is written in the arduino language which comprises of C/C++ like functions. The water supply module is made available using a combination of sensors and a motor. The circuit diagram for this project is as follows:

![circuit diagram](https://github.com/rutvik5/soil-texture-automatic-irrigation/blob/master/images/circuit%20diagram.jpg)

### Descirption
In this project there are different aspects to the system as follows:

#### Identification of type of soil
Soil is identified based on the experiment performed, after which the analysis is conducted. From this, the type of the soil is identified and the corresponding water holding capacity of the particular soil is noted which is further used to supply water.

#### Automatic supply of water
The automatic supply of water is done based on the calculations that include factor like temperature, crop coefficient from which the amount of water to be supplied each day is calculated. This is then further measured based on the type of soil and its water holding capacity. The amount of water finally to be supplied is calculated and the time for which it is supplied is derived from the supply speed of the motor which is used. In this case, it is 0.5 lit/min.

#### Farm Security
The farm would be protected using infrared sensors which would trigger the alarm and flashlights once an intrusion is detected. An sms would also be sent to the user using a GSM module directly to his personal cellphone. This would prove as an extra safety measure to protect the field against wild animals and human intruders


This system analyzes the type of soil based on its water retention capacity. This approach would hoard excessive water lost due to seepage into the lower layers of the soil. Contrarily, it would also eliminate the possibility of providing less water to the crops. In addition to that, we aim to provide farm security to protect against intruders and thieves, thereby protecting the yield. The motive behind the project is to curb the extensive use of water for irrigation without any human intervention and send alerts for unusual activities in the farm to the user. Hence by implementing this method, we are able to save water which can be used for supplementary activities in the farm. The human effort required is reduced at an extensive level by implementing the automatic system.
