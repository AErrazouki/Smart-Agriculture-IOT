# Smart Agriculture 
Utilisation de l'IoT pour connecter et automatiser les processus agricoles. Cette approche permet d'améliorer l'efficacité et la productivité agricole grâce à l'arrosage automatique, contrôlé localement ou à distance par des capteurs qui surveillent les conditions du sol en temps réel.
J'ai intègre des capteurs connectés à l'ESP32, qui envoie des données à une plateforme Blynk via Wi-Fi. Les utilisateurs peuvent surveiller et contrôler l'arrosage à distance via l'application mobile Blynk.

# Matériel et Logiciel:
## ESP32 : 
   Utilisé pour ses capacités Wi-Fi et Bluetooth.
## Capteurs : 
   Capteurs d’humidité du sol, de température (DHT11), photorésistance (LDR) pour mesurer l'intensité lumineuse.
## Pompe et Relais : 
   Pour l'irrigation contrôlée.
## LCD : 
   Pour afficher les informations.
## Pour le logiciel: 
   J'ai utilisé Arduino IDE avec des bibliothèques spécifiques comme DHT, WiFi, Wire et LiquidCrystal_I2C, et la plateforme Blynk pour la création d'interfaces graphiques.

# Instructions d'Installation
  ## Ouvrez le fichier Projet_iot_blynk_1.ino dans Arduino IDE :
     Ouvrez Arduino IDE puis allez au File > Open, puis naviguez jusqu'au dossier cloné et sélectionnez le fichier 'Projet_iot_blynk_1.ino'.
  ## Installez les bibliothèques nécessaires :
     Allez à Sketch > Include Library > Manage Libraries.
     Recherchez et installez les bibliothèques suivantes : ESP32 , WiFi, et Blynk , DHT, Wire et LiquidCrystal_I2C.
  ## Configurez les identifiants WiFi et de la plateforme Blynk:
     const char* ssid = "votre-SSID";
     const char* password = "votre-MOT_DE_PASSE";
     #define BLYNK_TEMPLATE_ID "votre-TEMPLATE_ID"
     #define BLYNK_TEMPLATE_NAME "votre-TEMPLATE_NAME"
     #define BLYNK_AUTH_TOKEN "votre-AUTH_TOKEN"
 ## Connectez l'ESP32 à l'ordinateur et téléchargez le code :
     Utilisez un câble USB pour connecter l'ESP32 à votre ordinateur.
     Dans Arduino IDE, sélectionnez la carte appropriée (ESP32) Tools > Board et le port Tools > Port.
     Cliquez sur le bouton Upload pour télécharger le code sur l'ESP32.
     
