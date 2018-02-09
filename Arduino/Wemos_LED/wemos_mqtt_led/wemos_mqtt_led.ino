#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>


#define TX D1
#define RX D2

char mode = 'T';
SoftwareSerial SerialMega(RX, TX); // RX, TX

const char* ssid = "wlfsl24";
const char* password = "HNR46HH80Lohbruegge";
unsigned int localPort = 2390;      // local port to listen for UDP packets
const char* mqtt_server = "192.168.178.102"; //IP of Raspberry (MQTT-Broker)

int timecount = 0;

IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets


// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

WiFiClient espClient;
PubSubClient client(espClient);

void setup(void){
  Serial.begin(9600);
  SerialMega.begin(9600);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  udp.begin(localPort);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String strTopic = String((char*)topic);
  
  if(strTopic == "mode_led"){
    SerialMega.print("M");
    switch(payload[0]){ //ASCII conversion
      case 83:
                SerialMega.print("S");
                mode = 'S';
                break;
                
      case 84:
                SerialMega.print("T");
                mode = 'T';
                break;
                
      default:
                SerialMega.print("T");
                mode = 'T';
                break;
    }
    Serial.print("Mode  :");
    Serial.println(payload[0]);
  }else if(strTopic == "msg_led"){
    SerialMega.print("S");
    for (int i = 0; i < length; i++) {
      SerialMega.print((char)payload[i]);
    }
    Serial.print("msg_led  :");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }Serial.println("");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("WemosLEDESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("debug", "WemosLed connected");
      // ... and resubscribe
      client.subscribe("mode_led");
      client.subscribe("msg_led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void getTimeFromServer(){
   //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  
  // wait to see if a reply is available
  delay(1000);
}


void sendTimestamp(long epoch){
    SerialMega.print("T");
    
    for(int i=31;i>=0;i--){
      int tmp = 0;
      tmp = (epoch>>i) % 2;
      if(tmp==1){
        SerialMega.print("1");
      }else{
        SerialMega.print("0");
      }
    }
    Serial.println();
}


// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address){

  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);

  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision

  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}


void loop(void)

{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //if(mode =='T'){
    if(timecount == 160000){
       getTimeFromServer();
       timecount=0;
    }
    timecount++;
    
    int cb = udp.parsePacket();
    
    if (cb){  
      // We've received a packet, read the data from it
      udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
  
      if(packetBuffer[0]==1000){ 
        
      }else{ // Wenn nicht aus APP -> NTP Packet
        //the timestamp starts at byte 40 of the received packet and is four bytes,
        // or two words, long. First, esxtract the two words:
        unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
        unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    
        // combine the four bytes (two words) into a long integer
        // this is NTP time (seconds since Jan 1 1900):
        unsigned long secsSince1900 = highWord << 16 | lowWord;
    
        // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
        const unsigned long seventyYears = 2208988800UL;
    
        // subtract seventy years:
        unsigned long epoch = secsSince1900 - seventyYears;
    
        // print the hour, minute and second:
    
        epoch = epoch + (60*60*2); //+2 hours time diffrence to Greenwich Meridian (secs*min*hours)

        Serial.println("Send timestamp to Mega");
  
        sendTimestamp(epoch);
       }
    }
  //}
}
