
#include "DHTesp.h"

//VELOCIDADES VENTILADOR AC
int FAN_HIGH = 36;      //VENTILADOR AC VELOCIDAD ALTA
int FAN_MEDIUM = 24;    //VENTILADOR AC VELOCIDAD MEDIA
int FAN_LOW = 25;      //VENTILADOR AC VELOCIDAD BAJA
//int FAN_OFF = ??;      //VENTILADOR AC APAGAR

//MOTOR CORTINA
int MOTOR_1_OPEN = 26;      // MOTOR 1 OPEN
int MOTOR_1_CLOSE = 27;     // MOTOR 1 CLOSE

//MOODS
int FOCO_3 = 28;      //LUCES ENTRADA Y COMEDOR
int LED_4  = 29;      //LED VIGAS 
int LED_5  = 30;      //LED NICHO SOFA
int LED_6  = 31;      //LED CABECERO LADO SALON
int LED_7  = 32;      //LED VINILO
int LED_8B  = 38;     //LED CABECERO - BLANCO
int LED_8R  = 41;     //LED CABECERO - ROJO
int LUZ_9  = 39;      //LUZ LAMPARA COLGANTE
int LED_10 = 40;      //LED CORTINERO

//SOUND SYSTEM
/*int led10 = 5;      //Bluetooth  on - off
int led11 = 18;      //on music bothroomm Ambas habitaciones
int led12 = 36;      //on music livinroom sala de estar
*/

// LUZ EXTERIOR TERRAZA
int LUZ_11 = 35;  //LAMPARA BALCON

/*EN ERTE
int led17 = 36;  // libre
int led18 = 37;   // libre
*/

int TEMP_LUNCH  = 13; //SENSOR TEMPERATURA COMEDOR   
int RST32 =12;
char tem; //PUERTO SERIAL 2 - ALMACENA TODA LA INFORMACION QUE ENTRE POR ESTA VARIABLE
char tem3; //PUERTO SERIAL 3 - ALMACENA TODA LA INFORMACION QUE ENTRE POR ESTA VARIABLE
char tem1; //PUERTO SERIAL 1 - ALMACENA TODA LA INFORMACION QUE ENTRE POR ESTA VARIABLE
int dato = 22; //TEMPERATURA DE ARRANQUE DE DISPLAY NEXTION
int temperature; //TEMPERATURA DE LECTURA DE DHT11
int bt = 0; //BLUETOOTH
int bt1 = 1; //BLUETOOTH
int bt2 = 1; //BLUETOOTH
int cont1 = 0; //CONTADOR RESET - rst esp32
int cont2 = 0; // 
int tempo1 = 0; // CONTADOR PUERTO SERIAL
int c68 = 0; //VARIABLE PULSADOR ENCENDIDO LUZ TERRAZA - HACE QUE SEA UN PULSADOR COMUN

DHTesp dht;
void setup() {

  pinMode(TEMP_LUNCH, OUTPUT); //MEGA PIN 13
  pinMode(FAN_HIGH, OUTPUT); //MEGA PIN 22
  pinMode(FAN_MEDIUM, OUTPUT); // MEGA PIN 24
  pinMode(FAN_LOW, OUTPUT); // MEGA PIN 25
  //pinMode(FAN_OFF, OUTPUT); // MEGA PIN ??
  pinMode(FOCO_3, OUTPUT);// MEGA PIN 28
  pinMode(LED_4, OUTPUT); // MEGA PIN 29
  pinMode(LED_5, OUTPUT); // MEGA PIN 30
  pinMode(LED_6, OUTPUT); // MEGA PIN 31
  pinMode(LED_7, OUTPUT); // MEGA PIN 32
  pinMode(LED_8B, OUTPUT); // MEGA PIN 41
  pinMode(LED_8R, OUTPUT); // MEGA PIN 38
  pinMode(LUZ_9, OUTPUT); // MEGA PIN 39
  pinMode(LED_10, OUTPUT); // MEGA PIN 40
  pinMode(LUZ_11, OUTPUT); // MEGA PIN 35
  pinMode(MOTOR_1_OPEN, OUTPUT); // MEGA PIN 26 
  pinMode(MOTOR_1_CLOSE, OUTPUT); // MEGA PIN 27
  pinMode(RST32, OUTPUT); // PIN 12 PARA RESETEAR EL ESP - AJUSTADO A CONTADOR DE 50 LINEAS
  //pinMode(led15, OUTPUT);
  //pinMode(led17, OUTPUT);
  //pinMode(led18, OUTPUT);
  // digitalWrite(led9, HIGH);
  dht.setup(23); // DHT11 EN PIN 23 - LECTURA SENSOR TEMPERATURA Y HUMEDAD PARA ACTIVAR RELE PIN 13 - AC
  Serial.begin(9600);/// LECTURA SERIAL MONITOR PC
  Serial1.begin(9600);// COMUNICACION SERIAL 1 RX1 - MEGA - PANT. BED 1 - PANT. BED 2
  Serial2.begin(9600); // COMUNICACION SERIAL 2 RX2 - MEGA - PANT. ENTRANCE - PANT. MOVIE
  Serial3.begin(9600); // COMUNICACION SERIAL 3 RX3 - MEGA - PANT. TERRACE - ESP32
}

void loop() {
  
  //DHT11 - TERMOSTATO SONDA LUNCH - VER LA TEMPERATURA Y HUMEDAD A TRAVES DEL PUERTO SERIAL 
  
  if (tempo1 > 10) {
    int  temperature = dht.getTemperature();
    int  Humidity = dht.getHumidity();
    Serial.print("   temperatura  Grados :----   ");
    Serial.println(temperature);
    Serial.print("  ***************    ****************************  humedad % : ");
    Serial.println(Humidity);
    delay(550);
     
    tempo1 = 0;
  }
  
  //DHT11 - TERMOSTATO SONDA LUNCH 
  tempo1 = tempo1 + 1;
  Serial.println("    +++++++++++++++++++++    ");
  Serial.print(tempo1);
  int  temperature = dht.getTemperature();
  Serial.print("  temperatura habitacion  : ");
  Serial.print(temperature);
  Serial.print(" set-point  : ");
  Serial.print(dato);
  delay(650);
  if (temperature > dato) {
    digitalWrite(TEMP_LUNCH, 1);
  }
  if (temperature < dato) {
    digitalWrite(TEMP_LUNCH, 0);
  }


  //PUERTO SERIAL NUMERO 3//
  
  if (Serial3.available() > 0){
    tem3= Serial3.read();
     Serial.println("puerto3");
      Serial.println(tem3);
   
    if (tem3== 70) // LUZ TERRAZA CON PULSADOR EN DISPLAY NEXTION
    {
      digitalWrite(LUZ_11, 1);
      c68 = c68 + 1;
      Serial.print(c68);
      delay(100);
      if (c68 == 2) 
      
      //ENCENDIDO Y APAGADO LUZ TERRAZA - DISPLAY NEXTION TERRAZA
      {
        digitalWrite(LUZ_11, 0);
        Serial.print(c68);
        c68 = 0;
        delay(100);
      }
    }
  
  if (tem3 == 67) //  APERTURA CORTINAS MOTOR 1 - PANT. TODAS  
    {
      digitalWrite(MOTOR_1_OPEN, 1);
      digitalWrite(MOTOR_1_CLOSE, 0);
      delay (200);
      digitalWrite(MOTOR_1_OPEN, 0);
      digitalWrite(MOTOR_1_CLOSE, 0);
      Serial1.println('C');
    }
    
    if (tem3 == 68) //  CIERRE CORTINAS MOTOR 1 - PANT. TODAS
    {
    
      digitalWrite(MOTOR_1_OPEN, 0);
      digitalWrite(MOTOR_1_CLOSE, 1);
      delay (200);
      digitalWrite(MOTOR_1_OPEN, 0);
      digitalWrite(MOTOR_1_CLOSE, 0);
      Serial1.println('D');
    }

   if (tem3 == 69) //  OFF CORTINAS MOTOR 1 - PANT. TODAS
    {
   
      digitalWrite(MOTOR_1_OPEN, 1);
      digitalWrite(MOTOR_1_CLOSE, 1);
      Serial1.println('E'); 
      delay (200);
    }

//MOODS - LOS VALORES DE 1 SON OFF Y EL VALOR 0 ES ON 
   
    if (tem3 == 55) //MOOD DAY
    {
      digitalWrite(FOCO_3, 0);
      digitalWrite(LED_4, 0);
      digitalWrite(LED_5, 0);
      digitalWrite(LED_7, 0);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 1); //salida regulada
      Serial1.println('7');
    }
    if (tem3 == 56) // MOOD LOVE
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 1);
      digitalWrite(LED_7, 0);  //intensidad moderada
      digitalWrite(LED_8B, 0);  //LED BLANCO
      digitalWrite(LED_8R, 1);  //LED ROJO
      digitalWrite(LUZ_9, 0);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 0);  //intensidad moderada
      Serial1.println('8');
     
    }
    if (tem3 == 57) //MOOD SLEEP
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 0);   //intensidad baja
      digitalWrite(LED_5, 0);    //intensidad baja
      digitalWrite(LED_7, 0);  //intensidad baja
      digitalWrite(LED_8B, 1);  //rgb color ROJO
      digitalWrite(LED_8R, 0);  //rgb color BLANCO
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 0);  //intensidad baja
      Serial1.println('9');
    

    }
    if (tem3 == 54) //MOOD MOVIE
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 0);  //intensidad moderada
      digitalWrite(LED_7, 1);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 0);
      digitalWrite(LED_6, 0);    // intensidad moderada
      digitalWrite(LED_10, 1);
      Serial1.println('6');
      
    }
    if (tem3 == 53) // MOOD OFF
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 1);  //intensidad moderada
      digitalWrite(LED_7, 1);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);    // intensidad moderada
      digitalWrite(LED_10, 1);
      Serial1.println('5');
    }

    //VELOCIDADES AC - SERIAL 3
      if  (tem3 == 50 ) //FAN HIGH
    {
      digitalWrite(FAN_HIGH, 0);
      digitalWrite(FAN_MEDIUM, 1);
      digitalWrite(FAN_LOW, 1);
      Serial1.println('4');
    }
    if (tem3 == 51) //FAN MEDIUM
    {
      digitalWrite(FAN_HIGH, 1);
      digitalWrite(FAN_MEDIUM, 0);
      digitalWrite(FAN_LOW, 1);
      Serial1.println('3');
    }
    if (tem3 == 52) //FAN LOW
    {
      digitalWrite(FAN_HIGH, 1);
      digitalWrite(FAN_MEDIUM, 1);
      digitalWrite(FAN_LOW, 0);
      Serial1.println('2');
    }
    if (tem3 == 49) //  FAN STOP
    {      
      digitalWrite(FAN_HIGH, 1);
      digitalWrite(FAN_MEDIUM, 1);
      digitalWrite(FAN_LOW, 1);
      Serial1.println('1');
    }
      
  }

  
  //PUERTO SERIAL NUMERO 2
  
  if (Serial2.available() > 0) {
       tem = Serial2.read();
    
    if (temperature > dato) {
      digitalWrite(TEMP_LUNCH, 1);
    }
    if (temperature < dato) {
      digitalWrite(TEMP_LUNCH, 0);
    }

    if (tem > 18 && tem < 35) {

      if (temperature > tem) {
        digitalWrite(TEMP_LUNCH, 1);
        dato = tem;
      }
      if (temperature < tem) {
        dato = tem;
        digitalWrite(TEMP_LUNCH, 0);
      }
   

    }  Serial.print("PIR BED");
    Serial.println( temperature);
    Serial.print(" temperatura termostato nextion    ");
    Serial.println(tem);
    Serial.println("222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222 puerto");
    
    if (tem == 19) {
      Serial2.print("n0.val=");
      Serial2.print("19");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('a');
    }

    
    if (tem == 20)
    {

      Serial2.print("n0.val=");
      Serial2.print("20");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('b');
    }
    if (tem == 21) {
      Serial2.print("n0.val=");
      Serial2.print("21");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('c');
    }
    if (tem == 22) {
      Serial2.print("n0.val=");
      Serial2.print("22");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('d');
    }
    if (tem == 23) {
      Serial2.print("n0.val=");
      Serial2.print("23");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('e');
    }
    if (tem == 24) {
      Serial2.print("n0.val=");
      Serial2.print("24");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('f');
    }
    if (tem == 25) {
      Serial2.print("n0.val=");
      Serial2.print("25");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('g');

    }
    if (tem == 26) {
      Serial2.print("n0.val=");
      Serial2.print("26");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('h');

    }
    if (tem == 27) {
      Serial2.print("n0.val=");
      Serial2.print("27");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('i');
    }
    if (tem == 28) {
      Serial2.print("n0.val=");
      Serial2.print("28");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('o');
    }
   
    if (tem == 29) {
      Serial2.print("n0.val=");
      Serial2.print("29");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('p');
    }
    if (tem == 30) {
      Serial2.print("n0.val=");
      Serial2.print("30");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        Serial1.println('q');
    }

    //
    if (tem == 50 ) {
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 51 ) {
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 52 ) {
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 53 ) {
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 69) {
      Serial2.print("page ");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 70) {
      Serial2.print("page ");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 71) {
      Serial2.print("page ");
      Serial2.print("2");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if (tem == 72) {
      Serial2.print("page ");
      Serial2.print("3");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    if  (tem == 50 ) //velocidad baja0) || (x > 4
    {
      digitalWrite(FAN_HIGH, 1 );
      digitalWrite(FAN_MEDIUM, 0);
      digitalWrite(FAN_LOW, 0);
        Serial1.println('4');
    }
    if (tem == 51) //velocidad media
    {
      digitalWrite(FAN_HIGH, 0);
      digitalWrite(FAN_MEDIUM, 1);
      digitalWrite(FAN_LOW, 0);
        Serial1.println('3');
    }
    if (tem == 52) //velocidad alta
    {
      digitalWrite(FAN_HIGH, 0);
      digitalWrite(FAN_MEDIUM, 0);
      digitalWrite(FAN_LOW, 1);
        Serial1.println('2');
    }
    if (tem == 49) //  stop velocidad
    {
      digitalWrite(FAN_HIGH, 1);
      digitalWrite(FAN_MEDIUM, 1);
      digitalWrite(FAN_LOW, 1);
        Serial1.println('1');
    }

    if (tem == 70) //LUZ TERRAZA CON PULSADOR EN PANTALLA
    {
      digitalWrite(LUZ_11, 1);
      c68 = c68 + 1;
      Serial.print(c68);
      delay(100);
      if (c68 == 2) {
        digitalWrite(LUZ_11, 0);
        Serial.print(c68);
        c68 = 0;
        delay(100);
      }
 
    }
    
    // SERIAL 2 CORTINAS - PANT. TODAS
    if (tem == 67) //  APERTURA CORTINAS MOTOR 1 - PANT. TODAS
    {
      digitalWrite(MOTOR_1_OPEN, 1);
      digitalWrite(MOTOR_1_CLOSE, 0);
      delay (200);
      digitalWrite(MOTOR_1_OPEN, 0);
      digitalWrite(MOTOR_1_CLOSE, 0);
        Serial1.println('C');
    }
   
    if (tem == 68) // CIERRE CORTINAS MOTOR 1 - PANT. TODAS
    {
      digitalWrite(MOTOR_1_OPEN, 0);
      digitalWrite(MOTOR_1_CLOSE, 1);
      delay (200);
      digitalWrite(MOTOR_1_CLOSE, 0);
      digitalWrite(MOTOR_1_OPEN, 0);
        Serial1.println('D');
    }

if (tem == 69) //  OFF CORTINAS MOTOR 1 - PANT. TODAS
    {
    
      digitalWrite(MOTOR_1_OPEN, 1);
      digitalWrite(MOTOR_1_CLOSE, 1);
        Serial1.println('E');
      delay (200);
    }

    //MOODS SERIAL 2
    if (tem == 55) //MOOD DAY
    {

      digitalWrite(FOCO_3, 0);
      digitalWrite(LED_4, 0);
      digitalWrite(LED_5, 0);
      digitalWrite(LED_7, 0);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 1); ////salida regulada
     
      Serial1.println('7');
    }
    if (tem == 56) //MOOD LOVE
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 1);
      digitalWrite(LED_7, 0);  //intensidad moderada
      digitalWrite(LED_8B, 0);  //LED BLANCO
      digitalWrite(LED_8R, 1);  //LED ROJO
      digitalWrite(LUZ_9, 0);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 0);  //intensidad moderada
        Serial1.println('8');
      
    }
    if (tem == 57) //MOOD SLEEP
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 0);   //intensidad baja
      digitalWrite(LED_5, 0);    //intensidad baja
      digitalWrite(LED_7, 0);  //intensidad baja
      digitalWrite(LED_8B, 1);  //LED BLANCO
      digitalWrite(LED_8R, 0);  //LED ROJO
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 0);  //intensidad baja
        Serial1.println('9');
      
    }
    if (tem == 54) //MOOD MOVIE
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 0);  //intensidad moderada
      digitalWrite(LED_7, 1);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 0);
      digitalWrite(LED_6, 0);    // intensidad moderada
      digitalWrite(LED_10, 1);
        Serial1.println('6');
     
    }
    if (tem == 53) //MOOD SLEEP
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 1);  //intensidad moderada
      digitalWrite(LED_7, 1);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);    // intensidad moderada
      digitalWrite(LED_10, 1);
        Serial1.println('5');
   
    }
    /*if (tem == 12) //on music livinGroom sala de estar
    {
      digitalWrite(led10, 1);
      digitalWrite(led12, 1);
      digitalWrite(led11, 1);
      bt = bt + 1;

    }
    

    if (bt == 2) {
      digitalWrite(led10, 0);
      digitalWrite(led12, 0);
      digitalWrite(led11, 0);
      bt = 0;
    }
    if (tem == 11) //on music bothroomm Ambas habitaciones
    {
      digitalWrite(led12, 1);
      bt1 = bt1 + 1;
    }
    if (tem == 10) //on music bothroomm Ambas habitaciones
    {
      digitalWrite(led11, 1);
      bt2 = bt2 + 1;
    }
    if (bt1 == 2) {
      digitalWrite(led12, 0);
      
      bt1 = 0;

    }
    if (bt2 == 2) {
      digitalWrite(led11, 0);
      bt2 = 0;
    }
 
    delay(3);
    client.loop();
 */
  }
 
  //CONTADOR RST ESP32 - EL MEGA POR EL PIN 12 RESETEA EL ESP32 MEDIANTE EL PIN "EN" DESPUES DE 50 LINEAS 
  
   cont1++;
   Serial.print(" --- contador RST esp32 100  ");
     Serial.println(cont1);
  if (cont1==50)//tiempo rst esp32
  { 
    digitalWrite(RST32, 0);
      Serial.println("******************rst********************** ");
       
  cont1=0;
  delay(50);
  }
  digitalWrite(RST32, 1); 
  
  // PUERTO SERIAL 1 - TX1 AL ESP32 - RX1 PANT. BED 1 Y 2   
    if (Serial1.available() > 0) {
   
    tem1= Serial1.read();
      Serial.println("****************************************1111111111111111111111puerto11111111111111111111");
       Serial.println("**********************************++++++++++++++*************************");
      Serial.print(tem1);
      
       if (tem1 == 55) //MOOD DAY
    {

      digitalWrite(FOCO_3, 0);
      digitalWrite(LED_4, 0);
      digitalWrite(LED_5, 0);
      digitalWrite(LED_7, 0);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 1); ////salida regulada
      
        Serial1.println('7');
    }
    if (tem1 == 56) //MOOD LOVE
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 1);
      digitalWrite(LED_7, 0);  //intensidad moderada
      digitalWrite(LED_8B, 0);  //LED BLANCO
      digitalWrite(LED_8R, 1);  //LED ROJO
      digitalWrite(LUZ_9, 0);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 0);  //intensidad moderada
        Serial1.println('8');
      
    }
    if (tem1 == 57) //MOOD SLEEP
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 0);   //intensidad baja
      digitalWrite(LED_5, 0);    //intensidad baja
      digitalWrite(LED_7, 0);  //intensidad baja
      digitalWrite(LED_8B, 1);  //LED BLANCO
      digitalWrite(LED_8R, 0);  //LED ROJO
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);
      digitalWrite(LED_10, 0);  //intensidad baja
      Serial1.println('9');

    }
    if (tem1 == 54) //MOOD MOVIE
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 0);  //intensidad moderada
      digitalWrite(LED_7, 1);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 0);
      digitalWrite(LED_6, 0);    // intensidad moderada
      digitalWrite(LED_10, 1);
        Serial1.println('6');
      
    }
    if (tem1 == 53) //MOOD OFF
    {
      digitalWrite(FOCO_3, 1);
      digitalWrite(LED_4, 1);
      digitalWrite(LED_5, 1);  //intensidad moderada
      digitalWrite(LED_7, 1);
      digitalWrite(LED_8B, 1);
      digitalWrite(LED_8R, 1);
      digitalWrite(LUZ_9, 1);
      digitalWrite(LED_6, 1);    // intensidad moderada
      digitalWrite(LED_10, 1);
        Serial1.println('5');
      
    }
    if (tem1 == 70) //LUZ TERRAZA CON PULSADOR EN PANTALLA
    {
      digitalWrite(LUZ_11, 1);
      c68 = c68 + 1;
      Serial.print(c68);
      delay(100);
      if (c68 == 2) {
        digitalWrite(LUZ_11, 0);
        Serial.print(c68);
        c68 = 0;
        delay(100);
      }
  
    }
      
}
}
