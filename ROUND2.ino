/*PINES DISPONIBLES

18
33
34
36
37
41
44

*/


int set222;
int SETNEXTION;
int TEMPLUNCH = 23;          //Pin DATA de DHT22 a pin digital 23 mega
int TEMPERATURA;
int HUMEDAD = 0;
int T;
int X = 26;                 //temperatura de arranque  26 grados
int ONOFFAC  = 13;          //Apaga y enciende el ventilador del AC - ACTIVA O DESACTIVA EL FAN EN BASE A LA DIFERENCIA DEL DISPLA
int FANHIGH = 22;           //Ventilador velocidad alto
int FANMED = 24;            //Ventilador velocidad media
int FANLOW = 25;            //Ventilador velocidad baja
int OPEN = 26;              //Apertura Motor cortinero
int CLOSE = 27;             //Cierre Motor cortinero
int FOCO1 =50;              //Foco vinilo baño
int FOCO3 = 28;             //Focos entrada y lunch 
int LED4  = 29;             //Leds vigas
int LED5  = 30;             //Leds nicho lunch
int LED6  = 31;             //Led nicho sofa
int LED7  = 32;             //Led vinilo Bed
int LED8  = 38;             //Led cabecero cama
int LUZ9  = 39;             //Lampara colgante
int LED10 = 40;             //Led cortinero
int LUZ11 = 35;             //Luz Terraza

int RST32 =12;              //Reseteo ESP32 - Contador 50
int val;
int on_off=1;

int dato = 22;
int SETNEXTIONperature;
int bt = 0;
int bt1 = 1;
int bt2 = 1;
int CONTRST32 = 0;         //rst esp32
int cont2 = 0;
int SETNEXTIONpo1 = 0;
int PTERRACE = 0;          //Pulsador Nextion Luz11 - Pant Terrace 

const int OPENDOOR=53;     //Contacto puerta
const int OPENWINDOW=5;    //contacto balcon



/*LIBRERIA DHT*/

#include <SoftwareSerial.h>
#include <DHT.h>                // importa la Librerias DHT
#include <DHT_U.h>

SoftwareSerial SerialV (10,11); //rx10 tx11

DHT dht(TEMPLUNCH, DHT22);      // creacion del objeto, cambiar segundo parametro
                                // por DHT11 si se utiliza en lugar del DHT2




void setup() {
  pinMode(OPENDOOR,INPUT);      //Contacto puerta
  pinMode(OPENWINDOW, INPUT);   //contacto balcon
  pinMode(ONOFFAC, OUTPUT);     //pin 13 mega
  pinMode(FANHIGH, OUTPUT);
  pinMode(FANMED, OUTPUT);
  pinMode(FANLOW, OUTPUT);
  pinMode(CLOSE, OUTPUT);
  pinMode(OPEN, OUTPUT);
  pinMode(FOCO1, OUTPUT); 
  pinMode(FOCO3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LUZ9, OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LUZ11, OUTPUT);
  pinMode(RST32, OUTPUT);


  
  
  dht.begin();
  Serial.begin(9600);     //Monitor serial PC Y COMUNICACION  ESP32                 PANT TERRACE
  Serial1.begin(9600);    //Conunicacion Serial1 PANTALLA 1   5PULGADAS             PANT BED1
  Serial2.begin(9600);    //Comunicacion Serial2 PANTALLA 2   5PULGADAS             PANT BED2
  Serial3.begin(9600);    //Comunicacion Serial3 PANTALLA 3   7PULGADAS             PANT ENTRANCE
  SerialV.begin(9600);    //Comunicacion serialV PANTALLA 4   5PULGADAS RX10 TX11   PANT MOVIE
  delay(2500);
  
      digitalWrite(FANHIGH,1);
      digitalWrite(FANMED,1);
      digitalWrite(FANLOW,1);
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      digitalWrite(FOCO1, 0);
      digitalWrite(FOCO3,1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);      
      digitalWrite(LED10, 1); 
      digitalWrite(LUZ11, 1);
                        
      delay(500);
}

void loop() {


  /*GENERICOS*/ 
  /*ESCENA WELCOME */

val=digitalRead(OPENDOOR);
if  (val==0){
  
  Serial.print("          ");
  Serial.print("OPENDOOR : cerrado  ");
  Serial.print("OPENWINDOW : cerrado ");
  Serial.println("          ");
 
  delay(200);}

else { 

  Serial.print("          ");
  Serial.print ("OPENDOOR :  Abierto");
  Serial.println("          ");
  
 delay(200);}
 
if (on_off==1){
if (val==1){
  
  Serial.print("          ");
  Serial.print("OPENDOOW: Escena WELCOME ");
  Serial.println("          ");

   delay(1000);     // TRAS 1 SEG. APERTURA PUERTA SE ACCIONAN LAS SIGUIENTES LUCES              
        digitalWrite(FOCO1, 1);
        digitalWrite(FOCO3,0);
        digitalWrite(LED4, 0);
        digitalWrite(LED5, 1);
        digitalWrite(LED6, 0);
        digitalWrite(LED7, 0);
        digitalWrite(LED8, 0);
        digitalWrite(LUZ9, 0);      
        digitalWrite(LED10, 1); 
        digitalWrite(LUZ11, 1);
     
   delay(5000);     // TRAS 5 SEG. ACCIONAMIENTO LUCES - APERTURA CORTINA   
        digitalWrite(CLOSE, 1);   
        digitalWrite(OPEN, 0);    
     
   delay (400);
        digitalWrite(OPEN, 1);    
        digitalWrite(CLOSE, 1);   
        
   delay(5000);     // TRAS 5 SEG. INICIO APERTURA CORTINA - CAMBIO ILUMINACION A 
        digitalWrite(FOCO1, 0);
        digitalWrite(FOCO3,0);
        digitalWrite(LED4, 0);
        digitalWrite(LED5, 0);
        digitalWrite(LED6, 1);
        digitalWrite(LED7, 0);
        digitalWrite(LED8, 0);
        digitalWrite(LUZ9, 1);      
        digitalWrite(LED10, 1); 
        digitalWrite(LUZ11, 0);
 
     on_off=0;  
}
}

  
  
  /*TERMOSTATO SONDA*/
  
   TEMPERATURA = dht.readTemperature();
   HUMEDAD = dht.readHumidity();
    Serial.print("      ");
    Serial.print("Temperatura set-point :  ");
    Serial.print(X );
    Serial.print("C");
    Serial.print("      ");
    Serial.print("ROOM TEMPERATURE: ");
    Serial.print(TEMPERATURA);
    Serial.print("C");
    Serial.print("      ");
    Serial.print(" Humedad : ");
    Serial.print(HUMEDAD);
    Serial.println("%");
    delay(150);
 


  /*TERMOSTATO MEGA*/
    
  if (TEMPERATURA>X){
    digitalWrite(ONOFFAC,0);
  }
   if (TEMPERATURA<X){
    digitalWrite(ONOFFAC,1);
  }
  /*GENERICOS FIN*/  



///     ///     ///     ///     SERIAL0     ///     ///     ///     ///

  /*SERIAL 0 - ESP+PANT.TERRACE*/
  
  if (Serial.available()>0){
      SETNEXTION=Serial.read();
      Serial.println("//Serial 0 ESP32 + Pant. Terrace//");
      Serial.println(" DATO SERIAL 0000 ESP32  :: ");
      Serial.print(SETNEXTION);
   
     if (SETNEXTION== 70) {        //LUZ TERRAZA CON PULTADOR EN PANTALLA
      digitalWrite(LUZ11, 1);
      PTERRACE = PTERRACE + 1;
      Serial.print(PTERRACE);
      delay(100);
      
     if (PTERRACE == 2) {
      digitalWrite(LUZ11, 0);     //SERIAL 0000 ESP32
      Serial.print(PTERRACE);
      PTERRACE = 0;
      delay(10);
      }
    }



  /*SERIAL 0 - ESP+PANT.TERRACE*/       
  /*CONTROL MOTOR CORTINA*/

     if (SETNEXTION == 65) {        //OPEN COURTAIN
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 0);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      Serial1.println("PANT. TERRACE OPEN");
      }
    
    if (SETNEXTION == 66) {         //CLOSE COURTAIN
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 1);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      Serial1.println("PANT. TERRACE CLOSE");
      }
   
     if (SETNEXTION == 69) {        //STOP COURTAIN  
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 0);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
        delay (200);
      Serial1.println("PANT. TERRACE OFF");
      }



  /*SERIAL 0 - ESP+PANT.TERRACE*/  
  /*FAN*/

  /*FAN HIGH*/
    if (SETNEXTION == 52)  {          //FAN HIGH
      digitalWrite(FANHIGH, 0);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
       Serial1.println("PANT. TERRACE HIGH SPEED");
      }
      Serial2.print("bt4.val=");      //NEXTION HIGH
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(100);
      
   /*FAN MEDIUM*/    
     if (SETNEXTION == 51) {          //FAN MEDIUM
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 0);
      digitalWrite(FANLOW, 1);
        Serial1.println("PANT. TERRACE MEDIUM SPEED");
      }
      Serial2.print("bt5.val=");      //NEXTION MED 
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);


   /*FAN LOW*/   
    if  (SETNEXTION == 50 ) {         //FAN LOW
      digitalWrite(FANHIGH, 1 );
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 0);
        Serial1.println("PANT. TERRACE LOW SPEED");
      }
      Serial2.print("bt6.val=");      //NEXTION LOW
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(100);

  
    /*FAN OFF*/      
     if (SETNEXTION == 85) {          //FAN OFF
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
       Serial1.println("PANT. TERRACE FAN STOP");
     }     
      Serial2.print("bt10.val=");     //NEXTION OFF
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(100);


      Serial2.print("bt7.val=");     //NEXTION ON 
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(100);
    }
  










///     ///     ///     ///     SERIALV     ///     ///     ///     ///

/*SERIAL VIRTUAL PANT MOVIE   RX10  TX11*/
  
  if (SerialV.available()>0){
      SETNEXTION=SerialV.read();
      Serial.println("Serial Virtual    Pant. Movie");
      Serial.println("rx10   tx11");
       
      Serial.print(SETNEXTION);
      delay(150);


  /*SERIAL VIRTUAL PANT MOVIE   RX10  TX11*/
  /*MOODS/ LOS RELES VAN A LA INVERSA (1-OFF / 0-ON)*/
  
   if (SETNEXTION == 55)          //MOOD DAY
    {
      digitalWrite(FOCO1, 1);
      digitalWrite(FOCO3,0);
      digitalWrite(LED4, 0);
      digitalWrite(LED5, 0);
      digitalWrite(LED6, 1);
      digitalWrite(LED7, 0);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);      
      digitalWrite(LED10, 1); 
      digitalWrite(LUZ11, 1);
       Serial1.println("PANT. MOVIE MOOD DAY");
    }
    
    if (SETNEXTION == 56)         //MOOD LOVE
    {
      digitalWrite(FOCO1, 1);
      digitalWrite(FOCO3,1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED7, 0);
      digitalWrite(LED8, 0);
      digitalWrite(LUZ9, 0);      
      digitalWrite(LED10, 0); 
      digitalWrite(LUZ11, 1);
       Serial1.println("PANT. MOVIE MOOD LOVE");
     
    }
    if (SETNEXTION == 57)         //MOOD NIGHT
    {
      digitalWrite(FOCO1, 1);
      digitalWrite(FOCO3,1);
      digitalWrite(LED4, 0);
      digitalWrite(LED5, 0);
      digitalWrite(LED6, 1);
      digitalWrite(LED7, 0);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);      
      digitalWrite(LED10, 0); 
      digitalWrite(LUZ11, 1);    
       Serial1.println("PANT. MOVIE MOOD NIGHT");
    
    }
    if (SETNEXTION == 54)        //MOOD MOVIE
    {
      digitalWrite(FOCO1, 1);
      digitalWrite(FOCO3,1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 0);
      digitalWrite(LED6, 0);
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 0);      
      digitalWrite(LED10, 1); 
      digitalWrite(LUZ11, 1);
       Serial1.println("PANT. MOVIE MOOD MOVIE");
      
    }
    if (SETNEXTION == 53)       //MOOD SLEEP
    {
      digitalWrite(FOCO1, 1);
      digitalWrite(FOCO3,1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);      
      digitalWrite(LED10, 1); 
      digitalWrite(LUZ11, 1);
       Serial1.println("PANT. MOVIE MOOD SLEEP");
    }

  /*SERIAL VIRTUAL PANT MOVIE   RX10  TX11*/
  /*CONTROL MOTOR CORTINA*/

     if (SETNEXTION == 65)         //OPEN COURTAIN
     {
     
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 0);
      delay (200);
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
       Serial1.println("PANT. MOVIE OPEN");
      
    }
    if (SETNEXTION == 66)         //CLOSE COURTAIN
    {
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 1);
      delay (200);
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
       Serial1.println("PANT. MOVIE CLOSE");
    }
   

   if (SETNEXTION == 69)          //STOP  CORTINAS OFF CORTINAS  
    {
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 0);
      delay (200);
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
       Serial1.println("PANT. MOVIE OFF");
      delay (200);
    }

       

  /*SERIAL VIRTUAL PANT MOVIE   RX10  TX11**/  
  /*TERMOSTATO*/


 if  (SETNEXTION == 50 )           //FAN LOW
    {
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 0);
        Serial1.println("PANT. MOVIE FAN LOW");
    }
    if (SETNEXTION == 51)         //FAN MEDIUM
    {
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 0);
      digitalWrite(FANLOW, 1);
        Serial1.println("PANT. MOVIE FAN MEDIUM");
    }
    if (SETNEXTION == 52)         //FAN HIGH
    {
      digitalWrite(FANHIGH, 0);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
       Serial1.println("PANT. MOVIE FAN HIGH");
    }
    

 if (SETNEXTION == 85) //  stop velocidad
    {
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
      
      Serial1.println("PANT. MOVIE FAN STOP");
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt10.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt7.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
    }



///     ///     ///     ///     SINCRONIZACIONES    ///     ///     ///     ///

   /*SINCRONIZACION MOTOR CORTINA*/

    if (SETNEXTION == 65) {       //NEXTION OPEN COURTAIN
      Serial2.print("b4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(500);
      
      Serial2.print("b4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(500);
      }
      
    if (SETNEXTION == 66) {       //NEXTION CLOSE COURTAIN
      Serial2.print("b2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(500);
      
      Serial2.print("b2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(500);
      }
      
    if (SETNEXTION == 69) {       //NEXTION STOP COURTAIN
      Serial2.print("b6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(500);
      
      Serial2.print("b6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      delay(500);
      }


      
    /*TERMOSTATO MEGA*/
    
  if (SETNEXTION>19 && SETNEXTION<30){
      X=SETNEXTION;
    Serial.print("Contraste temperaturas");
    Serial.println(SETNEXTION);
    Serial.print("lectura Contraste temperaturas");
    Serial.println(X);
      delay(150);
     }


   
/*SINCRONIZACION TEMPERATURAS*/
   
    if (SETNEXTION == 19) {     //DISPLAY 19ºC
      Serial2.print("n0.val=");
      Serial2.print("19");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial2.println('a');
    }
    
    if (SETNEXTION == 20){      //DISPLAY 20ºC
      Serial2.print("n0.val=");
      Serial2.print("20");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('b');
    }
    
    if (SETNEXTION == 21) {    //DISPLAY 21ºC
      Serial2.print("n0.val=");
      Serial2.print("21");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('c');
    }
    
    if (SETNEXTION == 22) {    //DISPLAY 22ºC
      Serial2.print("n0.val=");
      Serial2.print("22");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     //  Serial1.println('d');
    }
    
    if (SETNEXTION == 23) {    //DISPLAY 23ºC
      Serial2.print("n0.val=");
      Serial2.print("23");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('e');
    }
    
    if (SETNEXTION == 24) {    //DISPLAY 24ºC
      Serial2.print("n0.val=");
      Serial2.print("24");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('f');
    }
    
    if (SETNEXTION == 25) {    //DISPLAY 25ºC
      Serial2.print("n0.val=");
      Serial2.print("25");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('g');
    }
    
    if (SETNEXTION == 26) {     //DISPLAY 26ºC
      Serial2.print("n0.val=");
      Serial2.print("26");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('h');
    }
    
    if (SETNEXTION == 27) {     //DISPLAY 27ºC
      Serial2.print("n0.val=");
      Serial2.print("27");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      // Serial1.println('i');
    }
    
    if (SETNEXTION == 28) {     //DISPLAY 28ºC
      Serial2.print("n0.val=");
      Serial2.print("28");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     // Serial1.println('o');
    }
   
    if (SETNEXTION == 29) {      //DISPLAY 29ºC
      Serial2.print("n0.val=");
      Serial2.print("29");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     // Serial1.println('p');
    }
    
    if (SETNEXTION == 30) {      //DISPLAY 30ºC
      Serial2.print("n0.val=");
      Serial2.print("30");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     //  Serial1.println('q');
    }
    
   
  /*SINCRONIZACION TERMOSTATO*/
    
    if (SETNEXTION == 50 ){       //FAN LOW
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
         
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
    }
    
    if (SETNEXTION == 51 ){       //FAN MEDIUM
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(300);
       
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(300);
       
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(300);
       
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(300);
       
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(300);
       
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
         
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
    }
    
    if (SETNEXTION == 52 ) {       //FAN HIGH
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff); 
    }



  /*SINCRONIZACION MOODS*/
  
    if (SETNEXTION == 53 ){     //MOOD OFF
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt8.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt9.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
    }
    
   if (SETNEXTION == 55 ){      //MOOD DAY
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt1.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        }
        
    if (SETNEXTION == 54 ){     //MOOD MOVIE
      Serial2.print("bt0.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       }
       
    if (SETNEXTION == 56 ){     //MOOD LOVE
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
         
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
         
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
         
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
       
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
         
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       }
       
     if (SETNEXTION == 57 ){      //MOOD NIGHT
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
         
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
        
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
    }
  }

  
  ///     ///     ///     ///     SERIAL3     ///     ///     ///     ///

/*SERIAL 3  PANT ENTRANCE*/
  
  
  if (Serial3.available() > 0){
    SETNEXTION= Serial3.read();
     Serial.println("SERIAL 3");
      Serial.println(SETNEXTION);
      delay(150);


  /*SERIAL 3  SINCRONIZACION CORTINAS*/

    if (SETNEXTION == 65){        //NEXTION OPEN COURTAIN 
      Serial2.print("b4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        
      Serial2.print("b4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        }
        
    if (SETNEXTION == 66){        //NEXTION CLOSE COURTAIN      
      Serial2.print("b2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        
      Serial2.print("b2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        }
        
    if (SETNEXTION == 69){         //NEXTION STOP COURTAIN   
      Serial2.print("b6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
         
      Serial2.print("b6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
        }
     

  /*SERIAL 3  TERMOSTATO*/

   if (SETNEXTION>19 && SETNEXTION<30){
    X=SETNEXTION;
     Serial.print("Contraste temperaturas");
     Serial.println(SETNEXTION);
     Serial.print("lectura Contraste temperaturas");
     Serial.println(X);
        delay(150);
     }

     
  /* if (SETNEXTION>19 && SETNEXTION<30){
  if (TEMPERATURA>SETNEXTION){
    digitalWrite(ONOFFAC,1);
  }
   if (TEMPERATURA<SETNEXTION){
    digitalWrite(ONOFFAC,0);
  }
   }*/


   
  /*SERIAL 3  SINCRONIZACION TEMPERATURAS*/
  
    if (SETNEXTION == 19) {      //DISPLAY 19ºC
      Serial2.print("n0.val=");
      Serial2.print("19");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('a');
     }

    
    if (SETNEXTION == 20){      //DISPLAY 20ºC
      Serial2.print("n0.val=");
      Serial2.print("20");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('b');
    }
    
    if (SETNEXTION == 21) {      //DISPLAY 21ºC
      Serial2.print("n0.val=");
      Serial2.print("21");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('c');
    }
    
    if (SETNEXTION == 22) {      //DISPLAY 22ºC
      Serial2.print("n0.val=");
      Serial2.print("22");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('d');
    }
    
    if (SETNEXTION== 23) {       //DISPLAY 23ºC
      Serial2.print("n0.val=");
      Serial2.print("23");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('e');
    }
    
    if (SETNEXTION == 24) {       //DISPLAY 24ºC
      Serial2.print("n0.val=");
      Serial2.print("24");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('f');
    }
    if (SETNEXTION == 25) {        //DISPLAY 25ºC
      Serial2.print("n0.val=");
      Serial2.print("25");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('g');
    }
    
    if (SETNEXTION == 26) {         //DISPLAY 26ºC
      Serial2.print("n0.val=");
      Serial2.print("26");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('h');
    }
    
    if (SETNEXTION == 27) {         //DISPLAY 27ºC
      Serial2.print("n0.val=");
      Serial2.print("27");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('i');
    }
    
    if (SETNEXTION == 28) {         //DISPLAY 28ºC
      Serial2.print("n0.val=");
      Serial2.print("28");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('o');
    }
   
    if (SETNEXTION == 29) {         //DISPLAY 29ºC
      Serial2.print("n0.val=");
      Serial2.print("29");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('p');
    }
    
    if (SETNEXTION == 30) {         //DISPLAY 30ºC
      Serial2.print("n0.val=");
      Serial2.print("30");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('q');
    }



  /*SERIAL 3  SINCRONIZACION FAN*/    
    
    if (SETNEXTION == 50 ) {    //FAN LOW
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
         
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        }
        
    if (SETNEXTION == 51 ){     //FAN MEDIUM
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
         
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
      }
      
    if (SETNEXTION == 52 ) {      //FAN HIGH
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
  
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
     
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
       
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
      }

    if (SETNEXTION == 85){     //FAN STOP
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
     // Serial1.println('1');
     
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
     
      Serial2.print("bt10.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
        }



   /*SERIAL 3  SINCRONIZACION CORTINA Y LUZ TERRAZA*/    
  
    
     if (SETNEXTION == 65){      //NEXTION OPEN COURTAIN
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 0);
        delay (200);
  
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
     // Serial1.println('A');
      }
    
    if (SETNEXTION == 66){      //NEXTION CLOSE COURTAIN
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 1);
        delay (200);
    
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
     // Serial1.println('B');
      }
      
    if (SETNEXTION == 69){      //NEXTION STOP COURTAIN 
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 0);
        delay (200);
     // Serial1.println('E');
        
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
        delay (200);
     // Serial1.println('E');
      }
    
    if (SETNEXTION== 70){      //NEXTION LUZ TERRACE
      digitalWrite(LUZ11, 1);
      PTERRACE = PTERRACE + 1;
      Serial.print(PTERRACE);
        delay(100);
   
    if (PTERRACE == 2) {
      digitalWrite(LUZ11, 0);
      Serial.print(PTERRACE);
      PTERRACE = 0;
        delay(100);
      }
    }
    
  
 
    
   /*SERIAL 3  SINCRONIZACION MOODS*/      

     if (SETNEXTION == 53 ) {     //MOOD SLEEP
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
     
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt8.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }

    if (SETNEXTION == 55 ) {      //MOOD DAY
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt1.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       delay(100);
      
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
    
    if (SETNEXTION == 54 ) {      //MOOD MOVIE
      Serial2.print("bt0.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
    
    if (SETNEXTION == 56 ) {      //MOOD LOVE
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
     
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
     
     if (SETNEXTION == 57 ) {     //MOOD NIGHT
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
    
  
   /*if (SETNEXTION == 55) //Luz ambiente DAY SOL
    {

      digitalWrite(FOCO3, 0);
      digitalWrite(LED4, 0);
      digitalWrite(LED5, 0);
      digitalWrite(LED7, 0);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 1); ////salida regulada
     // Serial1.println('7');
    }
    
    if (SETNEXTION == 56) //Luz ambiente MOOD CORAZON//3333333333333333333333333333
    {
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);
      digitalWrite(LED7, 0);  //intensidad moderada
      digitalWrite(LED8, 0); 
      digitalWrite(LUZ9, 0);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 0);  //inSETNEXTIONnsidad moderada
    //  Serial1.println('8');
     
    }
    if (SETNEXTION == 57) //Luz ambiente NIGHT
    {
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 0);   //intensidad baja
      digitalWrite(LED5, 0);    //intensidad baja
      digitalWrite(LED7, 0);  //intensidad baja
      digitalWrite(LED8, 1);  
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 0);  //intensidad baja//333333333333333333333333333333333
     // Serial1.println('9');
    
    }
    if (SETNEXTION == 54) //Luz ambiente MOVIE CINE
    {
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 0);  //intensidad moderada
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 0);
      digitalWrite(LED6, 0);    // intensidad moderada
      digitalWrite(LED10, 1);
     // Serial1.println('6');
      
    }
    if (SETNEXTION == 53) //Luz ambiente SLEEP
    {
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);  //intensidad moderada
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);    // intensidad moderada
      digitalWrite(LED10, 1);
    //  Serial1.println('5');
    }
    */



  /*SERIAL 3  FAN */  
     if  (SETNEXTION == 52){     //FAN HIGH
      digitalWrite(FANHIGH, 0);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
      //Serial1.println('4');
    }
    
    if (SETNEXTION == 51){       //FAN MEDIUM
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 0);
      digitalWrite(FANLOW, 1);
      //Serial1.println('3');
    }
   
    if (SETNEXTION == 50){       //FAN LOW
    
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 0);
      //Serial1.println('2');
    }
    
    if (SETNEXTION == 49){       //FAN STOP
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
      //Serial1.println('1');
    }
    }



///     ///     ///     ///     SERIAL2     ///     ///     ///     ///

  /*SERIAL 2 - PANT.BED2*/
 
 
     if (Serial2.available() >0) {
      SETNEXTION = Serial2.read();
      Serial.println("//PUERTO 2//");
      Serial.println(SETNEXTION);
        delay(150);

 
  
  /*SERIAL 2 - SINCRONIZACION COURTAIN*/

     if (SETNEXTION == 65) {      //OPEN COURTAIN
      Serial2.print("b4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("b4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      }
      
     if (SETNEXTION == 66) {      //CLOSE COURTAIN
      Serial2.print("b2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("b2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      }
     
     if (SETNEXTION == 69) {      //STOP COURTAIN
      Serial2.print("b6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
    
      Serial2.print("b6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      }



  /*SERIAL 2 - TERMOSTATO MEGA*/      

   if (SETNEXTION>19 && SETNEXTION<30){
    X=SETNEXTION;
    Serial.print("CONTRASTE TEMPERATURA" );
    Serial.println(SETNEXTION);
    Serial.print("LECTURA CONTRASTE TEMPERATURA" );
    Serial.println(X);
      delay(150);
   
  }
  /*  if (SETNEXTION>19 && SETNEXTION<30){
  if (TEMPERATURA>SETNEXTION){
    digitalWrite(ONOFFAC,1);
  }
   if (TEMPERATURA<SETNEXTION){
    digitalWrite(ONOFFAC,0);
  }
    }*/



   /*SERIAL 2 - SINCRONIZACIÓN TEMPERATURAS*/       
 
    if (SETNEXTION == 19) {     //DISPLAY 19ºC
      Serial2.print("n0.val=");
      Serial2.print("19");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('a');22222222222222222222222222222222222222222222222222222222
    }
    
    if (SETNEXTION == 20){      //DISPLAY 20ºC
      Serial2.print("n0.val=");
      Serial2.print("20");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('b');
      }
      
    if (SETNEXTION == 21) {     //DISPLAY 21ºC
      Serial2.print("n0.val=");
      Serial2.print("21");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('c');
      }
      
    if (SETNEXTION == 22) {     //DISPLAY 22ºC
      Serial2.print("n0.val=");
      Serial2.print("22");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      // Serial1.println('d');
     }
     
    if (SETNEXTION == 23) {     //DISPLAY 23ºC
      Serial2.print("n0.val=");
      Serial2.print("23");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('e');
      }

     if (SETNEXTION == 24) {      //DISPLAY 24ºC
      Serial2.print("n0.val=");
      Serial2.print("24");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('f');
      }
      
    if (SETNEXTION == 25) {       //DISPLAY 25ºC
      Serial2.print("n0.val=");
      Serial2.print("25");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     //Serial1.println('g');
    }
  
    if (SETNEXTION == 26) {       //DISPLAY 26ºC
      Serial2.print("n0.val=");
      Serial2.print("26");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('h');
      }
      
    if (SETNEXTION == 27) {       //DISPLAY 27ºC
      Serial2.print("n0.val=");
      Serial2.print("27");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
       // Serial1.println('i');
      }
      
    if (SETNEXTION == 28) {       //DISPLAY 28ºC
      Serial2.print("n0.val=");
      Serial2.print("28");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     //   Serial1.println('o');
    }
   
    if (SETNEXTION == 29) {       //DISPLAY 29ºC
      Serial2.print("n0.val=");
      Serial2.print("29");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      // Serial1.println('p');
      }
      
    if (SETNEXTION == 30) {       //DISPLAY 30ºC
      Serial2.print("n0.val=");
      Serial2.print("30");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //  Serial1.println('q');
    }

    
    
   /*SERIAL 2 - SINCRONIZACIÓN FAN*/    
      
    if (SETNEXTION == 50 ) {      //FAN LOW
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
  
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
     
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }
      
    if (SETNEXTION == 51 ) {      //FAN MEDIUM
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
     
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }
    
    if (SETNEXTION == 52 ) {      //FAN HIGH
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }

    
    
   /*SERIAL 2 - SINCRONIZACIÓN MOODS*/       
        
   if (SETNEXTION == 53 ) {     //MOOD SLEEP
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt8.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300); 
      }
     
    if (SETNEXTION == 55 ) {      //MOOD DAY
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt1.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
     
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
    
    if (SETNEXTION == 54 ) {      //MOOD MOVIE
      Serial2.print("bt0.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
    
    if (SETNEXTION == 56 ) {      //MOOD LOVE
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
     
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
     
     if (SETNEXTION == 57 ) {     //MOOD NIGHT
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);

      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);

      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
    
    //////////////////////////////////////////////
    ////////////////////////////////////////////
   /* if (SETNEXTION == 69) {
      Serial2.print("page ");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
    }
    */



   /*SERIAL 2 - SINCRONIZACIÓN FAN*/      
       
    if (SETNEXTION == 52){        //FAN HIGH
      digitalWrite(FANHIGH, 0 );
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
       // Serial1.println('4');
      }
    
    if (SETNEXTION == 51){       //FAN MEDIUM
    
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 0);
      digitalWrite(FANLOW, 1);
      //  Serial1.println('3');
      }
   
    if (SETNEXTION == 50){       //FAN LOW
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 0);
      //  Serial1.println('2');
      }
    
    if (SETNEXTION == 85) {      //FAN STOP
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
     // Serial1.println('1');
    
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }

   

   /*SERIAL 2 - SINCRONIZACIÓN COURTAIN*/    
   
    if (SETNEXTION == 65){      //OPEN COURTAIN 
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 0);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      //Serial1.println('A');
      }
    
    if (SETNEXTION == 66){      //CLOSE COURTAIN
      digitalWrite(CLOSE, 1);
      digitalWrite(OPEN, 0);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      //Serial1.println('B');
      }
    
    if (SETNEXTION == 69){      //STOP COURTAIN
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 0);
        delay (200);  
      //Serial1.println('E');
    
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
        delay (200);
      //Serial1.println('E');
      }



 
  /*SERIAL 2 - DEFINICION MOODS*/
   
  if (SETNEXTION == 55){        //MOOD DAY
      digitalWrite(FOCO3, 0);
      digitalWrite(LED4, 0);
      digitalWrite(LED5, 0);
      digitalWrite(LED7, 0);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 1); 
      //Serial1.println('7');
      }
    
    if (SETNEXTION == 56){      //MOOD LOVE
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);
      digitalWrite(LED7, 0); 
      digitalWrite(LED8, 0); 
      digitalWrite(LUZ9, 0);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 0);  
      //Serial1.println('8');
      }
    
    if (SETNEXTION == 57){     //MOOD NIGHT
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 0);  
      digitalWrite(LED5, 0);   
      digitalWrite(LED7, 0);  
      digitalWrite(LED8, 1); 
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 0);  
      //Serial1.println('9');
     }
    
    if (SETNEXTION == 54){     //MOOD MOVIE
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 0);  
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 0);
      digitalWrite(LED6, 0);    
      digitalWrite(LED10, 1);
      //Serial1.println('6');
      }
    
    if (SETNEXTION == 53){     //MOOD SLEEP
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);  
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);    
      digitalWrite(LED10, 1);
      //Serial1.println('5');
       }
   
    
    
   /*CONTADOR RESETEO ESP32*/

/*   CONTRST32++;
   Serial.print(" --- contador RST esp32 100  ");
     Serial.println(CONTRST32);
  if (CONTRST32==50)//tiempo rst esp32
  { 
    digitalWrite(RST32, 0);
      Serial.println("******************rst********************** ");
       
  CONTRST32=0;
  delay(50);
  }
  digitalWrite(RST32, 1);
*/
    }




  ///     ///     ///     ///     SERIAL1     ///     ///     ///     ///

  /*SERIAL 1 - PANT.BED1*/
  
   if (Serial1.available() > 0) {
     SETNEXTION= Serial1.read();
     Serial.println("//PUERTO 1//");
     Serial.print(SETNEXTION);
      delay (150);



  /*SERIAL 1 - DEFINICION MOODS*/
    
   if (SETNEXTION == 55){      //MOOD DAY
      digitalWrite(FOCO3, 0);
      digitalWrite(LED4, 0);
      digitalWrite(LED5, 0);
      digitalWrite(LED7, 0);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 1); 
      //Serial1.println('7');
      }
    
    if (SETNEXTION == 56){     //MOOD LOVE
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1);
      digitalWrite(LED7, 0);  
      digitalWrite(LED8, 0); 
      digitalWrite(LUZ9, 0);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 0); 
      //Serial1.println('8');
      }
    
    if (SETNEXTION == 57){     //MOOD NIGHT
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 0);   
      digitalWrite(LED5, 0);   
      digitalWrite(LED7, 0);  
      digitalWrite(LED8, 1);  
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1);
      digitalWrite(LED10, 0); 
      //Serial1.println('9');
      }
    
    if (SETNEXTION == 54){     //MOOD MOVIE
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 0);  
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 0);
      digitalWrite(LED6, 0);  
      digitalWrite(LED10, 1);
      //Serial1.println('6');
      }
    
    if (SETNEXTION == 53){     //MOOD SLEEP
      digitalWrite(FOCO3, 1);
      digitalWrite(LED4, 1);
      digitalWrite(LED5, 1); 
      digitalWrite(LED7, 1);
      digitalWrite(LED8, 1);
      digitalWrite(LUZ9, 1);
      digitalWrite(LED6, 1); 
      digitalWrite(LED10, 1);
      //Serial1.println('5');
      }



  /*SERIAL 1 - COURTAIN*/

    if (SETNEXTION == 65){      //OPEN COURTAIN    
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 0);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      //Serial1.println('A');
      }
    
    if (SETNEXTION == 66){       //CLOSE COURTAIN
      digitalWrite(CLOSE, 1);
      digitalWrite(OPEN, 0);
        delay (200);
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
      //Serial1.println('B');
      }
    
    if (SETNEXTION == 69){       //STOP COURTAIN
      digitalWrite(OPEN, 0);
      digitalWrite(CLOSE, 0);
        delay (200);
      // Serial1.println('E');
      
      digitalWrite(OPEN, 1);
      digitalWrite(CLOSE, 1);
        delay (200);
      // Serial1.println('E');
      }



  /*SERIAL 1 - SINCRONIZACION COURTAIN*/
     
     if (SETNEXTION == 65) {    //OPEN COURTAIN
      Serial2.print("b4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("b4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      }
     if (SETNEXTION == 66) {    //CLOSE COURTAIN
      Serial2.print("b2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("b2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      }
      
     if (SETNEXTION == 69) {    //STOP COURTAIN 
      Serial2.print("b6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("b6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      }
      
       

  /*SERIAL 1 - TERMOSTATO MEGA*/

   if (SETNEXTION>19 && SETNEXTION<30){
    X=SETNEXTION;
    Serial.print("CONTRASTE TEMPERATURA" );
    Serial.println(SETNEXTION);
    Serial.print("LECTURA CONTRASTE TEMPERATURA" );
    Serial.println(X);
      delay(150);
     }

 /*  if (SETNEXTION>19 && SETNEXTION<30){
  if (TEMPERATURA>SETNEXTION){
    digitalWrite(ONOFFAC,1);
  }
   if (TEMPERATURA<SETNEXTION){
    digitalWrite(ONOFFAC,0);
  }
    }*/



  /*SERIAL 1 - FAN*/

     if  (SETNEXTION == 52){       //FAN HIGH
    
      digitalWrite(FANHIGH, 0 );
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
      //Serial1.println('4');
      }
    
    if (SETNEXTION == 51){         //FAN MEDIUM
    
      digitalWrite(FANMED, 0);
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANLOW, 1);
      //Serial1.println('3');
      }
    
    if (SETNEXTION == 50){         //FAN LOW
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 0);
      //Serial1.println('2');
      }
    
    if (SETNEXTION == 85){         //FAN STOP
      digitalWrite(FANHIGH, 1);
      digitalWrite(FANMED, 1);
      digitalWrite(FANLOW, 1);
      //Serial1.println('1');
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }    
    
    

  /*SERIAL 1 - SINCRONIZACION TEMPERATURAS*/
     
     if (SETNEXTION == 19) {        //DISPLAY 19ºC
      Serial2.print("n0.val=");
      Serial2.print("19");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('a');
      }

    
     if (SETNEXTION == 20){         //DISPLAY 20ºC
      Serial2.print("n0.val=");
      Serial2.print("20");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      // Serial1.println('b');
      }
    
     if (SETNEXTION == 21) {        //DISPLAY 21ºC
      Serial2.print("n0.val=");
      Serial2.print("21");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('c');
      }
     
     if (SETNEXTION == 22) {        //DISPLAY 22ºC
      Serial2.print("n0.val=");
      Serial2.print("22");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('d');
      }
    
    if (SETNEXTION== 23) {          //DISPLAY 23ºC
      Serial2.print("n0.val=");
      Serial2.print("23");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      // Serial1.println('e');
      }
    
    if (SETNEXTION == 24) {         //DISPLAY 24ºC
      Serial2.print("n0.val=");
      Serial2.print("24");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('f');
      }
    
    if (SETNEXTION == 25) {         //DISPLAY 25ºC
      Serial2.print("n0.val=");
      Serial2.print("25");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('g');
      }
    
    if (SETNEXTION == 26) {         //DISPLAY 26ºC
      Serial2.print("n0.val=");
      Serial2.print("26");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      // Serial1.println('h');
      }
  
    if (SETNEXTION == 27) {         //DISPLAY 27ºC
      Serial2.print("n0.val=");
      Serial2.print("27");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('i');
      }
    
    if (SETNEXTION == 28) {         //DISPLAY 28ºC
      Serial2.print("n0.val=");
      Serial2.print("28");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('o');
      }
   
    if (SETNEXTION == 29) {         //DISPLAY 29ºC
      Serial2.print("n0.val=");
      Serial2.print("29");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('p');
      }
    
    if (SETNEXTION == 30) {         //DISPLAY 30ºC
      Serial2.print("n0.val=");
      Serial2.print("30");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      //Serial1.println('q');
      }



  /*SERIAL 1 - SINCRONIZACION FAN*/
    
    if (SETNEXTION == 50 ) {      //FAN LOW
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }
  
    if (SETNEXTION == 51 ) {      //FAN MEDIUM
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }
    
    if (SETNEXTION == 52 ) {      //FAN HIGH
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt4.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);

      Serial2.print("bt4.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt5.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt6.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt10.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt7.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      }
 
    
    
  /*SERIAL 1 - SINCRONIZACION MOODS*/
  
     if (SETNEXTION == 55 ) {       //MOOD DAY
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);

      Serial2.print("bt1.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);

      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
      
      Serial2.print("bt3.val=");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
  
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      }
    if (SETNEXTION == 54 ) {        //MOOD MOVIE
      Serial2.print("bt0.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);

      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);

      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(100);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(100);
     
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      }
    
    if (SETNEXTION == 56 ) {        //MOOD LOVE
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);

      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt2.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
  
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(500);
      
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
      
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(500);
     
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
     
     if (SETNEXTION == 57 ) {       //MOOD NIGHT
      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);

      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);

      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt3.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
      
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
         delay(300);
  
      Serial2.print("bt8.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
     
     if (SETNEXTION == 53 ) {       //MOOD SLEEP
      Serial2.print("bt0.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
  
      Serial2.print("bt1.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt2.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);

      Serial2.print("bt3.val=");
      Serial2.print("0");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      
      Serial2.print("bt8.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
       
      Serial2.print("bt9.val=");
      Serial2.print("1");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
        delay(300);
      }
      }
      }   
   
