#include <TinyGPS++.h>
//#include <SoftwareSerial.h>
#include <WiFi.h>
#include <Preferences.h>
TinyGPSPlus gps;
//SoftwareSerial Serial1(1, 3); 
#define RXD1 4
#define TXD1 2

const char* ssid = "RED ACCESA";
const char* password = "037E32E7";

float Latitude , Longitude;
int year , month , date, hour , minute , second;
String DateString , TimeString , LatitudeString , LongitudeString;
//
// instancia de eeprom
Preferences preferences;

//  OBJETOS
class ClassGPS {       // The class
  public:             // Access specifier
    String latitud;        
    String longitud;
    String anio;
    String mes;
    String dia;
    String hora;
    String minuto;
    String segundo;
};

ClassGPS gps_neo;

WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);// serial1 pines 4 y 2
  Serial.println("\n \n \n \n \n \n");
  Serial.println();
  Serial.println();
  Serial.println("-----------------------------------");
  // LECTURA DE VARIABLES
  preferences.begin("my-app", false);
  lectura_eeprom();
  preferences.end();
  //
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(""); 
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  delay(5000);
}

void loop()
{   
   // This sketch displays information every time a new sentence is correctly encoded.
  gps_serial();
  
  //delay(100);
}

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void gps_serial(){
  if (Serial1.available() > 0){
//    Serial.print(".");
    gps.encode(Serial1.read());
    if (gps.location.isUpdated()){
      // Latitude in degrees (double)
//      Serial.print("Latitude= "); 
//      Serial.print(gps.location.lat(), 6);      
//      // Longitude in degrees (double)   
//      Serial.print(" Longitude= "); 
//      Serial.println(gps.location.lng(), 6); 
//      // Year (2000+) (u16)
//      Serial.print("Year = "); 
//      Serial.println(gps.date.year()); 
//      // Month (1-12) (u8)
//      Serial.print("Month = "); 
//      Serial.println(gps.date.month()); 
//      // Day (1-31) (u8)
//      Serial.print("Day = "); 
//      Serial.println(gps.date.day()); 
//      // Hour (0-23) (u8)
//      Serial.print("Hour = "); 
//      Serial.println(gps.time.hour()); 
//      // Minute (0-59) (u8)
//      Serial.print("Minute = "); 
//      Serial.println(gps.time.minute()); 
//      // Second (0-59) (u8)
//      Serial.print("Second = "); 
//      Serial.println(gps.time.second()); 
      ///////////////////////////////////////////////////////
      preferences.begin("my-app", false);
      
      String eeprom_latitud   = "latitud";
      String eeprom_longitud  = "longitud";
      String eeprom_anio      = "anio";
      String eeprom_mes       = "mes";
      String eeprom_dia       = "dia";
      String eeprom_hora      = "hora";
      String eeprom_minuto    = "minuto";
      String eeprom_segundo   = "segundo";

      gps_neo.latitud   =  String(gps.location.lat(),6);
      gps_neo.longitud  =  String(gps.location.lng(),6);
      gps_neo.anio      =  gps.date.year();
      gps_neo.mes       =  gps.date.month();
      gps_neo.dia       =  gps.date.day();
      gps_neo.hora      =  gps.time.hour();
      gps_neo.minuto    =  gps.time.minute();
      gps_neo.segundo   =  gps.time.second();
      // GUARDAR EN EEPROM
      preferences.putDouble(eeprom_latitud.c_str(), (gps.location.lat()));
      preferences.putDouble(eeprom_longitud.c_str(), (gps.location.lng()));
      preferences.putUInt(eeprom_anio.c_str(), (gps.date.year()));
      preferences.putUInt(eeprom_mes.c_str(), (gps.date.month()));
      preferences.putUInt(eeprom_dia.c_str(), (gps.date.day()));
      preferences.putUInt(eeprom_hora.c_str(), (gps.time.hour()));
      preferences.putUInt(eeprom_minuto.c_str(), (gps.time.minute()));
      preferences.putUInt(eeprom_segundo.c_str(), (gps.time.second()));

       preferences.end();
      
      

  Serial.println("latitud:" + String(gps_neo.latitud));
  Serial.println("longitud:" + String(gps_neo.longitud));
  Serial.println("anio:" + String(gps_neo.anio));
  Serial.println("mes:" + String(gps_neo.mes));
  Serial.println("dia:" + String(gps_neo.dia));
  Serial.println("hora:" + String(gps_neo.hora));
  Serial.println("minuto:" + String(gps_neo.minuto));
  Serial.println("segundo:" + String(gps_neo.segundo));
  Serial.println("^^^^^^^^^ GPS ACTUALIZADO ^^^^^^^^^^");
  delay(500);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void lectura_eeprom(){
  Serial.println("******** LECTURA DE DATOS GPS ********");
  String eeprom_latitud   = "latitud";
  String eeprom_longitud  = "longitud";
  String eeprom_anio      = "anio";
  String eeprom_mes       = "mes";
  String eeprom_dia       = "dia";
  String eeprom_hora      = "hora";
  String eeprom_minuto    = "minuto";
  String eeprom_segundo   = "segundo";
       
      //Se lee
      gps_neo.latitud = String(preferences.getDouble(eeprom_latitud.c_str(), 0),6);
      gps_neo.longitud = String(preferences.getDouble(eeprom_longitud.c_str(), 0), 6);
      gps_neo.anio = String(preferences.getUInt(eeprom_anio.c_str(), 0),DEC);
      gps_neo.mes = String(preferences.getUInt(eeprom_mes.c_str(), 0));
      gps_neo.dia = String(preferences.getUInt(eeprom_dia.c_str(), 0));
      gps_neo.hora = String(preferences.getUInt(eeprom_hora.c_str(), 0));
      gps_neo.minuto = String(preferences.getUInt(eeprom_minuto.c_str(), 0));
      gps_neo.segundo = String(preferences.getUInt(eeprom_segundo.c_str(), 0));

      // SE IMPRIME
      Serial.println("latitud:" + String(gps_neo.latitud));
      Serial.println("longitud:" + String(gps_neo.longitud));
      Serial.println("anio:" + String(gps_neo.anio));
      Serial.println("mes:" + String(gps_neo.mes));
      Serial.println("dia:" + String(gps_neo.dia));
      Serial.println("hora:" + String(gps_neo.hora));
      Serial.println("minuto:" + String(gps_neo.minuto));
      Serial.println("segundo:" + String(gps_neo.segundo));

     
}
