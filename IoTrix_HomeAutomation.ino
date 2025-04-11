#include <SPI.h>
#include <MFRC522.h>
#define sensor1 2   // blue
#define sensor2 3   // purple
#define SS_PIN 10
#define RST_PIN 9
#define door_O_pin 7
#define door_C_pin 8
#define led_pin 4
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 6



MFRC522 rfid(SS_PIN, RST_PIN);

byte keyTagUID[4] = {0xE3, 0x76, 0x8E, 0x12};  
 

int sensorState1 = 1;
int sensorState2 = 1;
int count = 0;
int outside = 0;
int goingout = 0;
int goingin=0;
int i = 1;
bool printedCount = false; // Flag to track if count has been printed
const int num_data = 4;
unsigned long prev_timer = 0;
const long interval = 3000;
int temp, humid;

int sensorData;
int timer1;

int sensorPin=A2;

//Buzzer

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
unsigned long cur_timer = millis();
const int buzzerPin = 5;

void beep(int note, int duration) {
  // Play tone on buzzerPin
  tone(buzzerPin, note, duration);
  delay(duration);
  noTone(buzzerPin);
}

void firstSection() {
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
 
}

void setup() {
 Serial.begin(9600); // Initialize serial communication
 pinMode(sensorPin,INPUT);
 pinMode(sensor1, INPUT);
 pinMode(sensor2, INPUT);
 pinMode(buzzerPin, OUTPUT);


 SPI.begin(); // init SPI bus
 rfid.PCD_Init(); // init MFRC522
 //pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
 //digitalWrite(RELAY_PIN, HIGH); // lock the door

 Serial.println("Tap RFID/NFC Tag on reader");
 pinMode(door_O_pin,OUTPUT); 
 pinMode(door_C_pin,OUTPUT);
 
 pinMode(led_pin, OUTPUT);
 digitalWrite(door_O_pin, LOW); // Door Open 
 digitalWrite(door_C_pin, HIGH);// Door Close  

 delay(200);
}
void fetch_data(){
 DHT.read(DHT11_PIN);
 temp = DHT.temperature;
 humid = DHT.humidity;
  sensorData = analogRead(sensorPin);
 Serial.print(String(temp)+','+String(humid)+','+String(sensorPin)+','+String(10));
 Serial.println();
  unsigned long cur_timer = millis();
        
  Serial.print("Sensor Data:");
  Serial.println(sensorData);
  delay(500);   
       
  if(cur_timer - prev_timer >= interval){
    prev_timer = cur_timer;
    fetch_data();
  }
}


void visitor_count(){
  if (!digitalRead(sensor1) && i == 1 && sensorState1) {
  outside = 1;
  delay(100);
  i++;
  sensorState1 = 0;
 } else if (!digitalRead(sensor2) && i == 2 && sensorState2) {
  Serial.println("Entering inside the room");
  outside = 1;
  delay(100);
  i = 1;
  count++;
  goingin++;
  Serial.print(goingin);
  Serial.println(" ENTERED SO FAR");
  printedCount = false; // Reset flag to allow printing
  sensorState2 = 0;
 } else if (!digitalRead(sensor2) && i == 1 && sensorState2) {
  outside = 1;
  delay(100);
  i = 2;
  sensorState2 = 0;
 } else if (!digitalRead(sensor1) && i == 2 && sensorState1) {
  Serial.println("Exiting from room");
  outside = 1;
  delay(100);
  count = max(0, count - 1); // Ensure count doesn't go below zero
  goingout++;
  Serial.print(goingout);
  Serial.println(" EXITED SO FAR");
  printedCount = false; // Reset flag to allow printing
  i = 1;
  sensorState1 = 0;
 }

 if (digitalRead(sensor1)) {
  sensorState1 = 1;
 }
 if (digitalRead(sensor2)) {
  sensorState2 = 1;
 }

 // Print count only once after sensor activation, then reset flag
 if (!printedCount) {
  Serial.print("No. of people inside the room: ");
  Serial.println(count);
  printedCount = true;
 }

 // Relay control logic (unchanged)
  if (count <= 0) {
  digitalWrite(led_pin, LOW);
  Serial.println("No visitors");
  delay(500);
 } else if (count > 0 && count < 3) {
  digitalWrite(led_pin, HIGH); // Adjusted to HIGH for relay activation
   
  Serial.print("Visitors: ");
  Serial.println(count);
  delay(500);
 } else {
  digitalWrite(led_pin, HIGH); // Adjusted to HIGH for relay activation
  Serial.print("Visitors: ");
  Serial.println(count);
  delay(500);
 }
}
void rfid_check(){
   if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      if (rfid.uid.uidByte[0] == keyTagUID[0] &&
          rfid.uid.uidByte[1] == keyTagUID[1] &&
          rfid.uid.uidByte[2] == keyTagUID[2] &&
          rfid.uid.uidByte[3] == keyTagUID[3] ) {
        Serial.println("Access is granted");
        delay(500);
 
        digitalWrite(door_O_pin, HIGH);  // Open door
        digitalWrite(door_C_pin, LOW);
        delay(5000);
        
        digitalWrite(led_pin, HIGH);
        delay(1000);
       
      
       
    
        digitalWrite(door_O_pin, LOW);  // Close door
        digitalWrite(door_C_pin, HIGH);
    
      }
      else
      {
        Serial.print("Access denied for user with UID:");

          digitalWrite(door_O_pin, LOW);  // Door Close
          digitalWrite(door_C_pin, LOW);  // Ensure it stays closed
          firstSection();
          
        }
        Serial.println();
      }

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
}
void loop() {
  cur_timer = millis();
  rfid_check();
 int lightstatus = digitalRead(led_pin);
 rfid_check();

}
