#define BLYNK_TEMPLATE_ID "TMPL2Y44q1xjb"
#define BLYNK_TEMPLATE_NAME "Projet Iot"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 26
#define DHTTYPE DHT11
#define SOILPIN 35
#define LDRPIN 34
#define RELAYPIN 23

char auth[] = "di3IxMGFI0IrrFtfB2f8uLy3pyPs_70m";
char ssid[] = "realme C55";
char pass[] = "aya 2023";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
LiquidCrystal_I2C lcd(0x27, 16, 4);

bool pumpmod = true; // Mode automatique par défaut
bool pumpState = false; // État de la pompe

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(DHTPIN, INPUT);
  pinMode(LDRPIN, INPUT);
  pinMode(SOILPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, HIGH);

  timer.setInterval(100L, readSensors); // Lire les capteurs toutes les 100ms

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Test the LCD by displaying a message
  lcd.setCursor(0, 0);
  lcd.print("LCD Initializing");
  delay(500);
}

void loop() {
  Blynk.run();
  timer.run();
}

void readSensors() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int soilHumidity = analogRead(SOILPIN);
  int ldrValue = analogRead(LDRPIN);
  
  // Convertir les valeurs d'humidité du sol en pourcentage
  float soilHumidityPercentage = map(soilHumidity, 1450, 4095, 100, 0);
  soilHumidityPercentage = constrain(soilHumidityPercentage, 0, 100);

  Serial.print("Humidité: ");
  Serial.println(h);
  Serial.print("Température: ");
  Serial.println(t);
  Serial.print("Humidité du sol: ");
  Serial.print(soilHumidityPercentage);
  Serial.println(F(" %"));

  Serial.print(F("Valeur LDR: "));
  Serial.println(ldrValue);

  String sunlight = (ldrValue > 2000) ? "Soleil" : "No soleil";
  Serial.println((ldrValue > 2000) ? F("Il y a du soleil.") : F("Il n'y a pas de soleil."));

  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V23, soilHumidityPercentage);

  // Contrôler la pompe en mode automatique
  if (pumpmod) {
    if (soilHumidityPercentage < 30) {
      digitalWrite(RELAYPIN, HIGH);  // Activer la pompe
      pumpState = true;
      Serial.println(F("Mode automatique: Pompe allumée."));
    } else {
      digitalWrite(RELAYPIN, LOW);  // Désactiver la pompe
      pumpState = false;
      Serial.println(F("Mode automatique: Pompe éteinte."));
    }
  }

  // Mettre à jour l'affichage LCD
  lcd.clear();
  

  lcd.setCursor(0, 1);
  lcd.print("LDR: ");
  lcd.print(sunlight);
  
  lcd.setCursor(0, 2);
  lcd.print("Pompe: ");
  lcd.print(pumpState ? "ON" : "OFF");

  lcd.setCursor(0, 3);
  lcd.print("H_sol: ");
  lcd.print(soilHumidityPercentage);

  lcd.setCursor(0, 4);
  lcd.print("Temp: ");
  lcd.print(t);
}

// Fonction pour gérer le mode automatique
BLYNK_WRITE(V7) {
  pumpmod = param.asInt();
  Serial.print(F("Mode automatique (BLYNK_WRITE): "));
  Serial.println(pumpmod ? "Activé" : "Désactivé");
}

// Fonction pour contrôler la pompe manuellement via Blynk
BLYNK_WRITE(V34) {
  if (!pumpmod) {
    int pumpControl = param.asInt();
    if (pumpControl == 1) {
      digitalWrite(RELAYPIN, LOW);  // Activer la pompe
      pumpState = true;
      Serial.println(F("Contrôle manuel: Pompe allumée."));
    } else {
      digitalWrite(RELAYPIN, HIGH);  // Désactiver la pompe
      pumpState = false;
      Serial.println(F("Contrôle manuel: Pompe éteinte."));
    }
  }
}
