//Trabajo IARS - Sensores v.3 Final
#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
DHT dht(DHTPIN, DHTTYPE);

int inicio=0; //Variable global
int tmp102Address = 0x48;
float Tem1, Hum1, Vie1, Pre1, UVA1; //Loc 1
float Tem2, Hum2, Vie2, Pre2, UVA2; //Loc 2
float Tem3, Hum3, Vie3, Pre3, UVA3; //Loc 3
float Tem4, Hum4, Vie4, Pre4, UVA4; //Loc 4
float Tem5, Hum5, Vie5, Pre5, UVA5; //Loc 5

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);   //led indicador
  dht.begin();          //se inicializa la comunicacion dht 
  lcd.begin(16, 2);     //se inicializa el display lcd
  lcd.setCursor(0,0);
  lcd.write("Iniciando...");
}
////////////////// P R I N C I P A L ///////////////////////
////////////////////////////////////////////////////////////
void loop(){
  if (Serial.available()){
    randomSeed(analogRead(A0)); //Semilla
    inicio = Serial.read()- 48; //ASCII 
        
    if (inicio >= 1){ // valor de inicio desde NODE-RED
    //PROGRAMA SE EJECUTA CADA 1 HORA en NODE-RED
    
    //LECTURA DE TODOS LOS VALORES AL INICIO (60s aprox)
    delay(5000); // Espera 5s 
    temperatura(); humedad(); viento(); presion(); indice_uv(); 
    ///////////////////////////////////////////////////////////

    // Minuto 15 - Lee Temperatura
    lcd_espera (); 
    delay(900000); //delay(900000); //900s = 15min
    temperatura(); 

   // Minuto 30 - Lee Temperatura,Viento y UV
    lcd_espera ();
    delay(900000);     //delay(900000); //900s = 15min
    temperatura(); viento(); indice_uv();

    // Minuto 45 - Lee Temperatura
    lcd_espera ();
    delay(900000);     //delay(900000); //900s = 15min
    temperatura();
    
    // Resetea variable de inicio y se sincroniza con NODE-RED
    lcd_espera ();
    inicio == 0;          
    }
  }  
}
////////////////// F U N C I O N E S ///////////////////////
////////////////////////////////////////////////////////////

//FUNCION SENSORES TEMPERATURA
void temperatura () {
  Tem1 = dht.readTemperature();          //Temp sensor1
  Tem2 = Tem1 + random(40, 140)/100.00;
  Tem3 = Tem1 + random(60, 160)/100.00;
  Tem4 = Tem1 + random(50, 150)/100.00;
  Tem5 = Tem1 + random(100, 200)/100.00;             
  for (int Id_loc = 1; Id_loc <= 5; Id_loc++){ //TEMPERATURA       
    ////////////////////////////////////////////////////////////
    lcd.setCursor(0,0); lcd.write("ID Sensor  Valor");
    lcd.setCursor(0,1); lcd.print(Id_loc);
    lcd.setCursor(3,1); lcd.write("Temper.");
    lcd.setCursor(11,1);                   
    ////////////////////////////////////////////////////////////
    Serial.println(1);                         //Id_magnitud 1
    Serial.println(Id_loc);                    //Id_localizacion
    if (Id_loc == 1){Serial.print(Tem1,2);lcd.print(Tem1,2);}
    if (Id_loc == 2){Serial.print(Tem2,2);lcd.print(Tem2,2);}
    if (Id_loc == 3){Serial.print(Tem3,2);lcd.print(Tem3,2);}
    if (Id_loc == 4){Serial.print(Tem4,2);lcd.print(Tem4,2);} 
    if (Id_loc == 5){Serial.print(Tem5,2);lcd.print(Tem5,2);}                        
    ////////////////////////////////////////////////////////////
    parpadea_led(); //función parpadeo led
  }
}

//FUNCION SENSORES HUMEDAD
void humedad() {             
  Hum1 = dht.readHumidity();                         
  Hum2 = Hum1 + random(-15, 15)/10.0;
  Hum3 = Hum1 + random(-15, 15)/10.0;
  Hum4 = Hum1 + random(-15, 15)/10.0;
  Hum5 = Hum1 + random(-15, 15)/10.0;
  for (int Id_loc = 1; Id_loc <= 5; Id_loc++){ //HUMEDAD    
    ////////////////////////////////////////////////////////////
    lcd.setCursor(0,0); lcd.write("ID Sensor  Valor");
    lcd.setCursor(0,1); lcd.print(Id_loc);
    lcd.setCursor(3,1); lcd.write("Humedad");
    lcd.setCursor(11,1);                   
    ////////////////////////////////////////////////////////////
    Serial.println(2);                         //Id_magnitud 2
    Serial.println(Id_loc);                    //Id_localizacion
    if (Id_loc == 1){Serial.print(Hum1,2);lcd.print(Hum1,2);}
    if (Id_loc == 2){Serial.print(Hum2,2);lcd.print(Hum2,2);}
    if (Id_loc == 3){Serial.print(Hum3,2);lcd.print(Hum3,2);}
    if (Id_loc == 4){Serial.print(Hum4,2);lcd.print(Hum4,2);}
    if (Id_loc == 5){Serial.print(Hum5,2);lcd.print(Hum5,2);}                        
    ////////////////////////////////////////////////////////////
    parpadea_led(); //función parpadeo led
  }
}

//FUNCION SENSORES VIENTO
void viento() {             
  Vie1 = random(50, 500)/10.0;                          
  Vie2 = Vie1 + random(-20, 20)/10.0;
  Vie3 = Vie1 + random(-20, 20)/10.0;
  Vie4 = Vie1 + random(-20, 20)/10.0;
  Vie5 = Vie1 + random(-50, 50)/10.0;
for (int Id_loc = 1; Id_loc <= 5; Id_loc++){ //VIENTO   
    ////////////////////////////////////////////////////////////
    lcd.setCursor(0,0); lcd.write("ID Sensor  Valor");
    lcd.setCursor(0,1); lcd.print(Id_loc);
    lcd.setCursor(3,1); lcd.write("Viento ");
    lcd.setCursor(11,1);                   
    ////////////////////////////////////////////////////////////
    Serial.println(3);                         //Id_magnitud 3
    Serial.println(Id_loc);                    //Id_localizacion
    if (Id_loc == 1){Serial.print(Vie1,2);lcd.print(Vie1,2);}
    if (Id_loc == 2){Serial.print(Vie2,2);lcd.print(Vie2,2);}
    if (Id_loc == 3){Serial.print(Vie3,2);lcd.print(Vie3,2);}
    if (Id_loc == 4){Serial.print(Vie4,2);lcd.print(Vie4,2);}
    if (Id_loc == 5){Serial.print(Vie5,2);lcd.print(Vie5,2);}                        
    ////////////////////////////////////////////////////////////
    parpadea_led(); //función parpadeo led
  }
}

//FUNCION SENSORES PRESIÓN
void presion() {             
  Pre1 = random(100500 , 102000)/100.0;                           
  Pre2 = Pre1 + random(-200, 200)/100.0;
  Pre3 = Pre1 + random(-200, 200)/100.0;
  Pre4 = Pre1 + random(-200, 200)/100.0;
  Pre5 = Pre1 + random(-200, 200)/100.0;
  for (int Id_loc = 1; Id_loc <= 5; Id_loc++){ //PRESIÓN   
    ////////////////////////////////////////////////////////////
    lcd.setCursor(0,0); lcd.write("ID Sensor  Valor");
    lcd.setCursor(0,1); lcd.print(Id_loc);
    lcd.setCursor(3,1); lcd.write("Presion");
    lcd.setCursor(11,1);                   
    ////////////////////////////////////////////////////////////   
    Serial.println(4);                         //Id_magnitud 4
    Serial.println(Id_loc);                    //Id_localizacion
    if (Id_loc == 1){Serial.print(Pre1,2);lcd.print(Pre1,2);}
    if (Id_loc == 2){Serial.print(Pre2,2);lcd.print(Pre2,2);}
    if (Id_loc == 3){Serial.print(Pre3,2);lcd.print(Pre3,2);}
    if (Id_loc == 4){Serial.print(Pre4,2);lcd.print(Pre4,2);}
    if (Id_loc == 5){Serial.print(Pre5,2);lcd.print(Pre5,2);}                        
    ////////////////////////////////////////////////////////////
    parpadea_led(); //función parpadeo led
  }
}

//FUNCION SENSORES ÍNDICE UV
void indice_uv() {             
  //int inicio = Serial.read()- 48; //ASCII
  if (inicio == 2){
    UVA1 =  UVA2 = UVA3 = UVA4 = UVA5 = 0.0;
  }
  else if (inicio == 1 && (dht.readTemperature())<=22){
    UVA1 = random(20, 50)/10.0;
    UVA2 = UVA1 + random(-50, 50)/100.0;
    UVA3 = UVA1 + random(-50, 50)/100.0;
    UVA4 = UVA1 + random(-50, 50)/100.0;
    UVA5 = UVA1 + random(-50, 50)/100.0;  
  }  
  else if (inicio == 1 && dht.readTemperature()>22){
    UVA1 = 5* ((dht.readTemperature())/20.0) + random(-50, 50)/100.0;
    UVA2 = UVA1 + random(-50, 50)/100.0;
    UVA3 = UVA1 + random(-50, 50)/100.0;
    UVA4 = UVA1 + random(-50, 50)/100.0;
    UVA5 = UVA1 + random(-50, 50)/100.0;  
  }                            
  for (int Id_loc = 1; Id_loc <= 5; Id_loc++){ //UV    
    ////////////////////////////////////////////////////////////
    lcd.setCursor(0,0); lcd.write("ID Sensor  Valor");
    lcd.setCursor(0,1); lcd.print(Id_loc);
    lcd.setCursor(3,1); lcd.write("indUVA    ");
    lcd.setCursor(13,1);                   
    ////////////////////////////////////////////////////////////
    Serial.println(5);                         //Id_magnitud 5
    Serial.println(Id_loc);                    //Id_localizacion
    if (Id_loc == 1){Serial.print(UVA1,1);lcd.print(UVA1,1);}
    if (Id_loc == 2){Serial.print(UVA2,1);lcd.print(UVA2,1);}
    if (Id_loc == 3){Serial.print(UVA3,1);lcd.print(UVA3,1);}
    if (Id_loc == 4){Serial.print(UVA4,1);lcd.print(UVA4,1);}
    if (Id_loc == 5){Serial.print(UVA5,1);lcd.print(UVA5,1);}                        
    ////////////////////////////////////////////////////////////
    parpadea_led(); //función parpadeo led
  }
}

//función parpadeo led
void parpadea_led () {             
  digitalWrite(4 , HIGH);            
  delay(500);         
  digitalWrite(4 , LOW);       
  delay(1500); 
}

//función modo de espera
void lcd_espera () {             
  lcd.setCursor(0,0); lcd.write("Modo  de  Espera");
  lcd.setCursor(0,1); lcd.write("                ");
}
