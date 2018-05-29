#include <TinyGPS++.h>                                  // Tiny GPS Plus Library
#include <SoftwareSerial.h>                             // Software Serial Library so we can use other Pins for communication with the GPS modul
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>  // OLED display (SDA to Pin 4), (SCL to Pin 5)
#include <NMCU.h>

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

static const int RXPin = 12, TXPin = 13;                // Ublox 6m GPS module to pins 12 and 13
static const uint32_t GPSBaud = 9600;                   // Ublox GPS default Baud Rate is 9600

TinyGPSPlus gps;                                        // Create an Instance of the TinyGPS++ object called gps
SoftwareSerial ss(RXPin, TXPin);                        // The serial connection to the GPS device

void setup()
{  
  Serial.begin(115200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  Serial.println("Initialized");
  
  display.display();
   
  display.clearDisplay();                                // Clear OLED display
  display.setTextSize(2);                               // Set OLED text size to small
  display.setTextColor(WHITE);                          // Set OLED color to White
  display.setCursor(0,0);                               // Set cursor to 0,0
  display.println("GPS example");  
  display.println(TinyGPSPlus::libraryVersion());
  display.display();
//  display.update();                                     // Update display
  delay(1500);                                          // Pause 1.5 seconds  
  ss.begin(GPSBaud);                                    // Set Software Serial Comm Speed to 9600    
}

void loop()
{   
  display.clearDisplay();
  display.setCursor(0,0); 
  //display.print("Lat: ");
  display.println(gps.location.lat(), 5);
 // display.print("Long: ");
  display.println(gps.location.lng(), 4);
  display.print("Satellites: ");
  display.println(gps.satellites.value());
  //display.print("Elevation : ");
   //display.print(gps.altitude.feet());
   //display.println("ft"); 
   //display.print("Time UTC  : ");
   //display.print(gps.time.hour());                       // GPS time UTC 
   //display.print(":");
   //display.print(gps.time.minute());                     // Minutes
   //display.print(":");
   //display.println(gps.time.second());                   // Seconds
   //display.print("Heading   : ");
   //display.println(gps.course.deg());
   //display.print("Speed     : ");
   //display.println(gps.speed.mph());
  display.display();
  delay(200); 
  
  
  smartDelay(500);                                      // Run Procedure smartDelay

  if (millis() > 5000 && gps.charsProcessed() < 10)
    display.println(F("No GPS data received: check wiring"));
}

static void smartDelay(unsigned long ms)                // This custom version of delay() ensures that the gps object is being "fed".
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}





