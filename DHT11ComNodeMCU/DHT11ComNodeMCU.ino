#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(115200);

}

void loop() {
  int umidade = dht.readHumidity();
  int temp = dht.readTemperature(false);
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" *C ");
  Serial.print("  ");
  Serial.print("Humidade: ");
  Serial.println(umidade);
  delay(5000);

}
