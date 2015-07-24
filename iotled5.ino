#include <SoftwareSerial.h>
SoftwareSerial BT1(2, 3); // RX | TX
String W =" ";
char w ;

//DECLARACIÓN DE VARIABLES PARA CONTROLAR EL MOTOR 1
int pinm1_1=6;
int pinm1_2=7;
int pinvel_m1=5; // Pin para controlar la velocidad del motor 1 con PWM.
int vel_adelante=255;    //Velocidad hacia adelante en PWM. 
int vel_atras=180;       //Velocidad hacia atrás en PWM.
//DECLARACIÓN DE VARIABLES PARA CONTROLAR EL MOTOR 1

//DECLARACIÓN DE VARIABLES PARA CONTROLAR EL MOTOR 2
int pinm2_1=8;
int pinm2_2=4;
int pinvel_m2=9; // Pin para controlar la velocidad del motor 1 con PWM.
//DECLARACIÓN DE VARIABLES PARA CONTROLAR EL MOTOR 1


void setup()
   {  Serial.begin(9600);
      BT1.begin(9600);
      SetUpWIFI();
      pinMode(pinm1_1, OUTPUT);
      pinMode(pinm1_2, OUTPUT);
      pinMode(pinvel_m1, OUTPUT);
      pinMode(pinm2_1, OUTPUT);
      pinMode(pinm2_2, OUTPUT);
      pinMode(pinvel_m2, OUTPUT);
      pinMode(13, OUTPUT);
      pinMode(12, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(10, OUTPUT);
   }

void loop()
   {  if (BT1.available())                // Lo que entra por WIFI à Serial
         { w = BT1.read() ;
           Serial.print(w);
           W = W + w ;                    // Vamos montando un String con lo que entra
         }
      if (Serial.available())             // Lo que entra por Serial à WIFI
         {  char s = Serial.read();
            BT1.print(s);
         }
      if ( w == '\n')                     // Sin han pulsado intro
         { if ( W.indexOf("P13") > 0 )    // Comprobamos si P13 esta incluido en el string
               { digitalWrite( 13, !digitalRead(13)) ;
                 Serial.println("Invirtiendo pin 13");
                 W = "" ;  w = ' ' ;                    // Limpiamos las variables
               }
           
           if ( W.indexOf("moveradelante") > 0 )    
               { digitalWrite( 12, !digitalRead(12)) ;
                 Serial.println("Invirtiendo pin 12");
                 mover_adelante();
                 Serial.println("mover adelante");
                 W = "" ;  w = ' ' ;                    // Limpiamos las variables
               }
               
           if ( W.indexOf("moveratras") > 0 )   
               { digitalWrite( 11, !digitalRead(11)) ;
                 Serial.println("Invirtiendo pin 11");
                 mover_atras();
                 Serial.println("mover atras");
                 W = "" ;  w = ' ' ;                    // Limpiamos las variables
               }
               
           if ( W.indexOf("moverderecha") > 0 )    
               { digitalWrite( 12, !digitalRead(12)) ;
                 Serial.println("Invirtiendo pin 12");
                 mover_derecha();
                 Serial.println("mover derecha");
                 W = "" ;  w = ' ' ;                    // Limpiamos las variables
               }
               
           if ( W.indexOf("moverizquierda") > 0 )   
               { digitalWrite( 11, !digitalRead(11)) ;
                 Serial.println("Invirtiendo pin 11");
                 mover_izquierda();
                 Serial.println("mover izquierda");
                 W = "" ;  w = ' ' ;                    // Limpiamos las variables
               }
               
           if ( W.indexOf("parar") > 0 )    
               { digitalWrite( 10, !digitalRead(10)) ;
                 Serial.println("Invirtiendo pin 10");
                 parar();
                 Serial.println("parar");
                 W = "" ;  w = ' ' ;                    // Limpiamos las variables
               }
                                     
         }
  }
  
String GetLineWIFI()
   {   String S = "" ;
       if (BT1.available())
          {    char c = BT1.read(); ;
                while ( c != '\n' )            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = BT1.read();
                   }
                 return( S ) ;
          }
   }
   


void SetUpWIFI()
   {  String ordenes[]=
       {  //"AT+RST",
          "AT+CIOBAUD=9600",
          "AT+CWMODE=3",
          //"AT+CWQAP", 
          //"AT"AT+CWLAP",
          "AT+CWJAP=\"TP-LINK_9DFEB2\",\"lideracasa2\"",
          "AT+CIFSR" ,
          "AT+CIPMUX=1",
          "AT+CIPSERVER=1,80",
          "END"          
       };

      int index = 0;
      while(ordenes[index] != "END")
        {  BT1.println(ordenes[index++]);
           while ( true)
              {   String s = GetLineWIFI();
                  if ( s!= "") Serial.println(s);
                  if ( s.startsWith("no change"))  
                       break;
                 if ( s.startsWith("OK"))   
                       break;
                 if ( s.startsWith("ready"))  
                       break;
                 if ( s.indexOf("192.168.4.1") > 0)  
                       break;
              }
          Serial.println("....................");
        }  
   }

void mover_adelante()
{
  analogWrite(pinvel_m1,0);
  analogWrite(pinvel_m2,0);
  delay(300);
  analogWrite(pinvel_m1, vel_adelante);
  analogWrite(pinvel_m2, vel_adelante);
  digitalWrite(pinm1_1, 1);
  digitalWrite(pinm1_2, 0);
  digitalWrite(pinm2_1, 1);
  digitalWrite(pinm2_2, 0);
}
//Función para mover hacia atras
void mover_atras()
{
  analogWrite(pinvel_m1,0);
  analogWrite(pinvel_m2,0);
  delay(300);
  analogWrite(pinvel_m1, vel_atras);
  analogWrite(pinvel_m2, vel_atras);
  digitalWrite(pinm1_1, 0);
  digitalWrite(pinm1_2, 1);
  digitalWrite(pinm2_1, 0);
  digitalWrite(pinm2_2, 1);
}

//Función para girar a la derecha
void mover_derecha()
{
  analogWrite(pinvel_m1,0);
  analogWrite(pinvel_m2,0);
  delay(300);
  analogWrite(pinvel_m1, vel_atras);
  analogWrite(pinvel_m2, vel_atras);
  digitalWrite(pinm1_1, 1);
  digitalWrite(pinm1_2, 0);
  digitalWrite(pinm2_1, 0);
  digitalWrite(pinm2_2, 1);
}

//Función para girar a la izquierda
void mover_izquierda()
{
  analogWrite(pinvel_m1,0);
  analogWrite(pinvel_m2,0);
  delay(300);
  analogWrite(pinvel_m1, vel_atras);
  analogWrite(pinvel_m2, vel_atras);
  digitalWrite(pinm1_1, 0);
  digitalWrite(pinm1_2, 1);
  digitalWrite(pinm2_1, 1);
  digitalWrite(pinm2_2, 0);
}

//Función para detener el motor
void parar()
{
  digitalWrite(pinm1_1, 0);
  digitalWrite(pinm1_2, 0);
  digitalWrite(pinm2_1, 0);
  digitalWrite(pinm2_2, 0);
}
