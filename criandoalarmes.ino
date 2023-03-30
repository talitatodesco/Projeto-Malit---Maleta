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

int a[4] = {};
int b[4] = {};

struct tm timeinfo;


#define led1 14
#define led2 13
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


  a[0] = {00};
  b[0] = {42};
  
  if(hrs == a[0] && mins == b[0] ){
    digitalWrite(led1, HIGH); 
   }else{
     digitalWrite(led1, LOW);
   }


  a[1] = {00};
  b[1] = {43};
  
  if(hrs == a[1] && mins == b[1] ){
    digitalWrite(led2, HIGH); 
   }else{
     digitalWrite(led2, LOW);
   }
  
}


void loop()
{
  AlarmTools();
  
  delay(1000);
  printLocalTime();
}