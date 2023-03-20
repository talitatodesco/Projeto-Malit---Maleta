//TIMESTAMP: ACIONAMENTO LED POR TEMPO

//Bibliotecas
#include <NTPClient.h>  // Biblioteca do NTP.
#include <WiFi.h>       // Biblioteca do WiFi.

//Conexão com wifi
const char* ssid = "CLARO_2G544AC8";
const char* password = "96544AC8";

// --------------Configuração de relógio online -------------------
const char* ntpServer1 = "c.st1.ntp.br"; //Endereço 1
const char* ntpServer2 = "pool.ntp.org";//Endereço 2
const long gmtOffset_sec = 0; 
const int daylightOffset_sec = -3600*3;

int hrs = 0;
int mins = 0;

int a = 18;
int b = 39;

struct tm timeinfo;


#define led1 13
#define led2 12
#define led3 32
#define led4 35



void printLocalTime() {

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Não foi possivel obter o tempo");
    return;
  } //Caso não consiga buscar o horario
  Serial.println(&timeinfo, "%H:%M");  //Saida horario monitor serial

  delay(1000);
}


void setup() {
  Serial.begin(115200);


  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2); //Configuração Time

  pinMode(led1, OUTPUT);  //Define o pino como saída
  digitalWrite(led1, LOW);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  
  Serial.println(" WIFI CONECTADO!");
  delay(1000);

}

void AlarmTools(){
  hrs = timeinfo.tm_hour; 
  mins = timeinfo.tm_min;

  if(hrs == a && mins == b ){
    digitalWrite(led1, HIGH); 
   }else{
     digitalWrite(led1, LOW);
   }
  
}


void loop()
{
  AlarmTools();
  // hrs = timeinfo.tm_hour; 
  // mins = timeinfo.tm_min;

  // if(hrs == a && mins == b ){
  //   digitalWrite(led1, HIGH); 
  //  }else{
  //    digitalWrite(led1, LOW);
  //  }
  
  delay(1000);
  printLocalTime();
}