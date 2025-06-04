#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "realme GT NEO 3T";
const char* password = "22082003@";
const char* serverURL = "http://192.168.11.78:5000/alert";

DHT dht1(4, DHT22);
DHT dht2(16, DHT22);
DHT dht3(17, DHT22);

const int MQ2_1 = 32;
const int MQ2_2 = 35;
const int MQ2_3 = 34;

const int FLAME_1 = 26;
const int FLAME_2 = 25;
const int FLAME_3 = 33;

const int BUZZER = 27;
const int EXIT_LIGHT = 14;

float TEMP_THRESHOLD = 50.0;
int SMOKE_THRESHOLD = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(FLAME_1, INPUT);
  pinMode(FLAME_2, INPUT);
  pinMode(FLAME_3, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(EXIT_LIGHT, OUTPUT);
  dht1.begin();
  dht2.begin();
  dht3.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  bool anyFire = false;

  anyFire |= checkFloor(1, dht1.readTemperature(), analogRead(MQ2_1), digitalRead(FLAME_1));
  anyFire |= checkFloor(2, dht2.readTemperature(), analogRead(MQ2_2), digitalRead(FLAME_2));
  anyFire |= checkFloor(3, dht3.readTemperature(), analogRead(MQ2_3), digitalRead(FLAME_3));

  if (anyFire) {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(EXIT_LIGHT, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(EXIT_LIGHT, LOW);
  }

  delay(5000);
}

bool checkFloor(int floor, float temp, int smoke, int flame) {
  Serial.printf("[Tầng %d] Nhiệt độ: %.2f °C | Khói: %d | Lửa: %d\n", floor, temp, smoke, flame);
  bool fire = (temp > TEMP_THRESHOLD || smoke > SMOKE_THRESHOLD || flame == LOW);
  sendAlert(floor, temp, smoke, flame);
  return fire;
}

void sendAlert(int floor, float temp, int smoke, int flame) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"floor\":\"" + String(floor) + 
                  "\",\"temperature\":" + String(temp) + 
                  ",\"smoke\":" + String(smoke) + 
                  ",\"flame\":" + String(flame) + "}";

    int httpResponseCode = http.POST(json);

    Serial.println("Đã gửi JSON:");
    Serial.println(json);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  }
}
