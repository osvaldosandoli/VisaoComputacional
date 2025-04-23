#include<DHT.h>
#include<ArduinoJson.h>


#define dhtpin 7
#define dhttype DHT11
#define echo 8
#define trigger 9
#define led 10

DHT dht(dhtpin, dhttype);

int dist = 0;

void setup() {
  dht.begin();
  Serial.begin(9600);

  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);

}

void loop() {
  int temp = dht.readTemperature();
  int umi = dht.readHumidity();

  //criando o JSON
  StaticJsonDocument<100>json;

  //criando os atributos e passando valor
  json["Temperatura"] = temp;
  json["Umidade"] = umi;
  json["Distancia"] = dist;

/*  serializeJson(json, Serial);
  Serial.println();
  delay(2000); */
//Comentarios
//Parte 1 - Inicio
/* 
  Serial.println("Temperatura: "+String(temp) + "ºC");
  Serial.println("Umidade: "+String(umi) + "%");
  delay(2000);
*/
//Parte 1 - Fim



digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

dist = pulseIn(echo, HIGH);
dist /= 58;

serializeJson(json, Serial);
Serial.println();

if(dist < 50){
  digitalWrite(led, HIGH);
}else{
  digitalWrite(led, LOW);
}
delay(500);
}
