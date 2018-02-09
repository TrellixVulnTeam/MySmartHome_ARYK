#include "DHT.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <math.h>

#define DHTPIN 5 //D1
#define DHTTYPE DHT22
#define A 17.27
#define B 237
#define ARRAY_SIZE 10
#define HUMID_TOLERANCE 10
#define TEMP_TOLERANCE 3

float temp_array[ARRAY_SIZE];
float humid_array[ARRAY_SIZE];
int newIndex = 0;
float t = 99;
float h = 99;
float old_h,old_t;

DHT dht(DHTPIN,DHTTYPE);

const char* sensor = "thorben"; //change this if you want to use other sensors
const char* ssid = "wlfsl24";
const char* password = "HNR46HH80Lohbruegge";
const char* mqtt_server = "192.168.178.102"; //IP of Raspberry (MQTT-Broker)

char topic_temp[80];
char topic_humid[80];
char topic_tau[80];
char topic_air[80];

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg_temp[50];
char msg_humid[50];
char msg_tau[50];
char msg_air[50];

char t_char[10];
char h_char[10];
char tau_char[10];
char air_char[50];

int value = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  for(int x=0; x <ARRAY_SIZE;x++){
    temp_array[x]= 24.0;
    humid_array[x]= 50.0;
  }

  strcpy (topic_temp,"temp_");
  strcat (topic_temp,sensor);

  strcpy (topic_humid,"humid_");
  strcat (topic_humid,sensor);

  strcpy (topic_tau,"tau_");
  strcat (topic_tau,sensor);

  strcpy (topic_air,"air_");
  strcat (topic_air,sensor);
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
}

void reconnect() {

  char str[80];
  strcpy (str,sensor);
  strcat (str," - NODEMCU with temperature publisherconnected");

  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client-Temperature-Publisher")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("debug", str);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  
  long now = millis();
  if (now - lastMsg > 2000) {

    old_h = h;
    old_t = t;

    if(h == 99 && t == 99){ //reset values
      old_h = dht.readHumidity();
      old_t = dht.readTemperature();
    }
    
    h = dht.readHumidity();
    t = dht.readTemperature();

    if((abs(old_h-h) < HUMID_TOLERANCE) && (abs(old_t-t)<TEMP_TOLERANCE)){
      temp_array[newIndex]=t;
      humid_array[newIndex]=h;
      newIndex++;
    }
      
    if(newIndex >= ARRAY_SIZE){
      newIndex = 0;
    }
    
    lastMsg = now;
    ++value;

    //Berechne Mittelwerte
    float t_mean = 0.0;
    float h_mean = 0.0;
    
    for(int x=0;x<ARRAY_SIZE;x++){
      t_mean += temp_array[x];
      h_mean += humid_array[x];
    }
    Serial.println(t_mean);
    Serial.println(h_mean);
    
    t_mean = t_mean/ARRAY_SIZE;
    h_mean = h_mean/ARRAY_SIZE;
    

    //Berechne Taupunkt
    float f = (A*t_mean)/(B+t_mean)+log(h_mean/100);
    float tau = (B*f)/(A-f);
    
    dtostrf(t_mean, 9, 2, t_char);
    dtostrf(h_mean, 9, 2, h_char);
    dtostrf(tau, 9, 2, tau_char);


    if(tau <= 2){
      snprintf (air_char,50, "Bitte nur kurz lüften! Heizung ausmachen nicht vergessen.");
    }else if(tau > 2 && tau <= 10 ){
      snprintf (air_char,50, "Bitte lüften! Heizung ausmachen nicht vergessen.");
    }else{
      snprintf (air_char,50, "Das Fenster bleibt zu!");
    }
    
    snprintf (msg_temp, 75, t_char, value);
    Serial.print("Publish message: ");
    Serial.println(msg_temp);

    snprintf (msg_humid, 75, h_char, value);
    Serial.print("Publish message: ");
    Serial.println(msg_humid);
    
    snprintf (msg_tau, 75, tau_char, value);
    Serial.print("Publish message: ");
    Serial.println(msg_tau);


    snprintf (msg_air, 75, air_char, value);
    Serial.print("Publish message: ");
    Serial.println(msg_air);
    
    client.publish(topic_temp, msg_temp);
    client.publish(topic_humid, msg_humid);
    client.publish(topic_tau, msg_tau);
    client.publish(topic_air, msg_air);

  }
}
