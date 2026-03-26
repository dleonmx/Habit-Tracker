/* ========= LIBRERIA========= */
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "imagen.h"
 
#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_GREEN 0x07E0
/* ========= PINES LCD========= */
#define TFT_CS    7
#define TFT_DC    5
#define TFT_RST   10
#define SPI_SCK   4
#define SPI_MOSI  6

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


/* ========= PINES ENCODER========= */
#define ENC_A 2
#define ENC_B 3

const int boton=1;
volatile int encoderValue = 0;
int i =0;
int medita=0;
int eje=0;
int est=0;
int ingles=0;
const int8_t transitionTable[4][4] = {
  /* TO:  00  01  10  11 */
  /*00*/ {  0, +1, -1,  0 },
  /*01*/ { -1,  0,  0, +1 },
  /*10*/ { +1,  0,  0, -1 },
  /*11*/ {  0, -1, +1,  0 }
};
uint8_t prevState = 0;
int movementCounter = 0; // Contador de pasos

/* ========= PINES SONIDO========= */
const int buzzer =21;


// Configuración NEO PIXEL
#include <Adafruit_NeoPixel.h>

#define PIN        0   // Pin digital conectado al NeoPixel
#define NUMPIXELS  8   // Número de LEDs en la tira
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//memoria config
#include <Preferences.h>
#define NUM_DIAS 30
byte historial[NUM_DIAS]; 
Preferences preferences;
int a;
int tempo;
int pul=0;
//tiempo config
#include <WiFi.h>
#include "time.h"
const char* ssid ="TP-Link_938C";
const char* pasword="45968488";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec  =-21600;
const int  daylightOffset_sec =0;
int prevMin = -1;
unsigned long lastCheck = 0;









int prev=9;
void setup() {


  pixels.begin(); // Inicializa la tira
   pixels.setBrightness(40); // Brillo de 0 a 255 (0 = apagado, 255 = máximo)
  pinMode(boton,INPUT_PULLUP);
  Serial.begin(115200);
  delay(2000);
  config_mem();
  conectar_internet();
  configTime(gmtOffset_sec,daylightOffset_sec,ntpServer);//config hora esp32
  ini_display();
  encoder_ini();
  mostrarHabito(i+1, a-1);


}

void loop() {
  lectura_encoder();
  checar_tiempo();
  if(i==0 && prev != i){
    if(medita==0){tft.drawRGBBitmap(0, 0, medita_r, IMG_W, IMG_H);

    mostrarHabito(i+1, a-1);
    }
    else{
      tft.drawRGBBitmap(0, 0, medita_v, IMG_W, IMG_H);
      mostrarHabito(i+1, a-1);
      }
    
    
  }
  else if(i==1&& prev != i){
    if(eje==0){tft.drawRGBBitmap(0, 0, eje_r, IMG_W, IMG_H);
    mostrarHabito(i+1, a-1);
    }
    else{tft.drawRGBBitmap(0, 0, eje_v, IMG_W, IMG_H);
    mostrarHabito(i+1, a-1);
    }
    
  }
  else if(i==2 && prev != i){
    if(est==0){tft.drawRGBBitmap(0, 0, est_r, IMG_W, IMG_H);
    mostrarHabito(i+1, a-1);
    }
    else{tft.drawRGBBitmap(0, 0, est_v, IMG_W, IMG_H);
    mostrarHabito(i+1, a-1);
    }
  }
  else if(i==3 && prev != i){
    if(ingles==0){tft.drawRGBBitmap(0, 0, ingles_r, IMG_W, IMG_H);
    mostrarHabito(i+1, a-1);
    }
    else{tft.drawRGBBitmap(0, 0, ingles_v, IMG_W, IMG_H);
    mostrarHabito(i+1, a-1);
    }
  }
  else if(i==4&& prev != i){
    tft.drawRGBBitmap(0, 0, yo, IMG_W, IMG_H);
  }

  if(digitalRead(boton)==0&&i==0&&medita==0){
     tone(buzzer, 800, 25);  // tono base
    delay(30);               // pausa breve
    tone(buzzer, 1200, 40); // tono ascendente

    guardar_basico(i+1);
    mostrarHabito(i+1, a-1);
     tft.drawRGBBitmap(0, 0, medita_v, IMG_W, IMG_H);
    delay(150);
    medita=1;



   
    

  }

    if(digitalRead(boton)==0&&i==1&&eje==0){
     tone(buzzer, 800, 25);  // tono base
    delay(30);               // pausa breve
    tone(buzzer, 1200, 40); // tono ascendente
      guardar_basico(i+1);
      mostrarHabito(i+1, a-1);

     tft.drawRGBBitmap(0, 0, eje_v, IMG_W, IMG_H);
    delay(150);
    eje=1;
   
    

  }  if(digitalRead(boton)==0&&i==2&&est==0){
     tone(buzzer, 800, 25);  // tono base
    delay(30);               // pausa breve
    tone(buzzer, 1200, 40); // tono ascendente
      guardar_basico(i+1);

    mostrarHabito(i+1, a-1);
     tft.drawRGBBitmap(0, 0, est_v, IMG_W, IMG_H);
    delay(150);
    est=1;
   
    

  }
    if(digitalRead(boton)==0&&i==3&&ingles==0){
     tone(buzzer, 800, 25);  // tono base
    delay(30);               // pausa breve
    tone(buzzer, 1200, 40); // tono ascendente
    guardar_basico(i+1);
    mostrarHabito(i+1, a-1);
     tft.drawRGBBitmap(0, 0, ingles_v, IMG_W, IMG_H);
    delay(150);
    ingles=1;
   
    

  }

    prev=i;
 

}
void nuevoDia() {
  tone(buzzer, 330, 120);  // E4
  delay(140);
  tone(buzzer, 415, 180);  // G#4
  delay(200);
  noTone(buzzer);
}
void ini_display(){
delay(100);
SPI.begin(SPI_SCK, -1, SPI_MOSI, TFT_CS);
 
tft.initR(INITR_MINI160x80_PLUGIN);
testTriangles();
tft.setRotation(3);

  



delay(2000);

}
unsigned long testTriangles() {
    unsigned long start;
    int n, i, cx = tft.width() / 2 - 1,
              cy = tft.height() / 2 - 1;
    tft.fillScreen(ST77XX_BLACK);
    n = min(cx, cy);
    start = micros();
    for (i = 0; i < n; i += 5) {
      tft.drawTriangle(
        cx, cy - i,
        cx - i, cy + i,
        cx + i, cy + i,
        tft.color565(200, 20, i));
    }
    return micros() - start;
  }

void encoder_ini(){
    pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  prevState = (digitalRead(ENC_A) << 1) | digitalRead(ENC_B);

 
}

void lectura_encoder(){
   uint8_t currState = (digitalRead(ENC_A) << 1) | digitalRead(ENC_B);

  if (currState != prevState) {
    int8_t movement = transitionTable[prevState][currState];

    if (movement != 0) {
      movementCounter += movement; // Acumula los pasos

      // Si completamos 4 pasos, es un giro completo horario
      if (movementCounter >= 4) {
       
        movementCounter = 0; // reiniciar contador
        if(i==0){
          i=3;
        }
        else{
          i--;
        }
        
        tone(buzzer, 900, 10);
      }
      // Si completamos -4 pasos, es un giro completo antihorario
      else if (movementCounter <= -4) {
        
        movementCounter = 0; // reiniciar contador
        if(i==3){
          i=0;
        }
        else{
          i++;
        }

        tone(buzzer, 900, 10);
      }
    }

    prevState = currState;
  }
}


void mostrarHabito(int habito, int dias) {

  for(int f = 0; f <= dias; f++) {
    Serial.print("Dia ");
    Serial.print(f+1);
    Serial.print(": ");
    Serial.println( (historial[f] >> habito) & 1 );
    if( ((historial[f] >> habito) & 1)==1){
  pixels.setPixelColor(f, pixels.Color(0, 255, 0));
  pixels.show();
  }
  else{
  pixels.setPixelColor(f, pixels.Color(255, 0, 0));
  pixels.show();}
  }}
  


void config_mem(){
  preferences.begin("habitos", false);
  if (!preferences.isKey("hist")) {
    memset(historial, 0, sizeof(historial));
    preferences.putBytes("hist", historial, sizeof(historial));
  } else {
    preferences.getBytes("hist", historial, sizeof(historial));
  }
  a = preferences.getInt("a", 0);
  tempo = preferences.getInt("tempo", -1);
 
  preferences.end();
  






}
void guardar_datos(){

preferences.begin("habitos", false);
preferences.putBytes("hist", historial, sizeof(historial));
preferences.putInt("a", a);
preferences.putInt("tempo", tempo);
preferences.end();

}



void checar_tiempo(){
 if(millis() - lastCheck >= 1000){ // cada 1 segundo
    lastCheck = millis();

    struct tm timeinfo;
    if(getLocalTime(&timeinfo)){
      if(timeinfo.tm_min != tempo){
        Serial.println("¡Pasó 1 minuto!");
        prevMin = timeinfo.tm_min;

        a++;
         if(a==NUM_DIAS){
          a=1;
          }
        tempo=timeinfo.tm_min;
        guardar_datos();
          medita=0;
        eje=0;
        est=0;
        ingles=0;
        prev=9;
        mostrarHabito(1, a-1);

        nuevoDia();


      }
    }
  }
}

void conectar_internet(){
   WiFi.begin(ssid, pasword);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println(".");

  }
  Serial.println("Conectado");
  Serial.println(WiFi.localIP());



}
void guardar_basico(int num){


    historial[a-1] |= (1 << num);
    preferences.begin("habitos", false);
    preferences.putBytes("hist", historial, sizeof(historial));
    preferences.end();
    
}
