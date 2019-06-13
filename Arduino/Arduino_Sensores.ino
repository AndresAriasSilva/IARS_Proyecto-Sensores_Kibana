//Trabajo IARS - Sensores v.2
#include <Wire.h>
#include <LiquidCrystal.h>
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD

int tmp102Address = 0x48;

float Tem1, Hum1, Vie1, Pre1, UVA1; //Loc 1
float Tem2, Hum2, Vie2, Pre2, UVA2; //Loc 2
float Tem3, Hum3, Vie3, Pre3, UVA3; //Loc 3
float Tem4, Hum4, Vie4, Pre4, UVA4; //Loc 4
float Tem5, Hum5, Vie5, Pre5, UVA5; //Loc 5


LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() 
{
  Serial.begin(9600);
  pinMode(4 , OUTPUT);  // led indicador
  Wire.begin();         //se inicializa la comunicacion i2c 
  lcd.begin(16, 2);     //se inicializa el display lcd
  lcd.setCursor(0,0);
  lcd.write("Iniciando...");
}

void loop()
{
  if (Serial.available())
  {
    randomSeed(analogRead(A0));
    int inicio = Serial.read()- 48; //ASCII 
        
    if (inicio == 1)
    {          
      for (int Id_loc = 1; Id_loc <= 5; Id_loc++) {    

        Tem1 = getTemp();                      //Temperatura sensor Loc 1
        Tem2 = Tem1 + random(100, 250)/100.0;
        Tem3 = Tem1 + random(100, 250)/100.0;
        Tem4 = Tem1 + random(100, 250)/100.0;
        Tem5 = Tem1 + random(100, 250)/100.0;
        
        lcd.setCursor(0,0); lcd.write("Loc. Sens. Valor");
        lcd.setCursor(0,1); lcd.print(Id_loc);
        lcd.setCursor(5,1); lcd.write("Temp");
        lcd.setCursor(11,1);
                   
        ////////////////////////////////////////////////////////////
        //Serial.println(Id_loc);                    //Id_localizacion
        //Serial.println(1);                         //Id_magnitud
        if (Id_loc == 1){Serial.print(Tem1,3);lcd.print(Tem1,2);}
        if (Id_loc == 2){Serial.print(Tem2,3);lcd.print(Tem2,2);}
        if (Id_loc == 3){Serial.print(Tem3,3);lcd.print(Tem3,2);}
        if (Id_loc == 4){Serial.print(Tem4,3);lcd.print(Tem4,2);}
        if (Id_loc == 5){Serial.print(Tem5,3);lcd.print(Tem5,2);}                        
        ////////////////////////////////////////////////////////////
        digitalWrite(4 , HIGH);             //indicador led Arduino
        delay(500);         
        digitalWrite(4 , LOW);       
        delay(2000); 
      }          
    } 
  }  
}


//Funcion Temperatura
float getTemp()
{
  Wire.requestFrom(tmp102Address,2); 
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 
  float Tem1 = TemperatureSum*0.0625;
  return Tem1;
}
