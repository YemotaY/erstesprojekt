# Arduino Roboterfahrzeug mit Ultraschall-Radar

Dieses Projekt steuert ein zweirädriges Roboterfahrzeug mit einem Arduino. Zur Navigation wird ein Ultraschallsensor (HC-SR04) auf einem Servo verwendet, der die Umgebung abtastet und dem Roboter ermöglicht, Hindernissen selbstständig auszuweichen.

## Funktionen

* Vorwärts und rückwärts fahren
* Links und rechts drehen
* Motoren stoppen
* Einstellbare Fahrgeschwindigkeit
* Servo-gesteuertes Radar
* Abstandsmessung mit HC-SR04
* Automatische Hinderniserkennung
* Auswahl der besten Fahrtrichtung

---

# Hardware

* Arduino Uno, Nano oder kompatibel
* Motortreiber (z. B. L293D oder L298N)
* 2 DC-Motoren
* HC-SR04 Ultraschallsensor
* Servo (z. B. SG90)
* Externe Stromversorgung für die Motoren

---

# Pinbelegung

## Motoren

| Funktion | Arduino |
| -------- | ------- |
| M1A      | A0      |
| M1B      | A1      |
| M2A      | A2      |
| M2B      | A3      |

## Radar

| Funktion | Arduino |
| -------- | ------- |
| Servo    | D9      |
| Trigger  | D7      |
| Echo     | D6      |

---

# Geschwindigkeit

Die Motorgeschwindigkeit wird per PWM eingestellt.

```cpp
int velocity = 128;
```

Wertebereich:

| Wert | Bedeutung                |
| ---- | ------------------------ |
| 0    | Motor aus                |
| 255  | maximale Geschwindigkeit |

---

# Motorfunktionen

## `drive(int direction)`

Steuert beide Motoren gleichzeitig.

| Wert | Funktion  |
| ---- | --------- |
| `0`  | Rückwärts |
| `1`  | Vorwärts  |

Beispiel

```cpp
drive(1);
```

---

## `steer(int direction)`

Dreht den Roboter auf der Stelle.

| Wert | Richtung |
| ---- | -------- |
| `0`  | Rechts   |
| `1`  | Links    |

Beispiel

```cpp
steer(1);
```

---

## `stop()`

Stoppt beide Motoren.

```cpp
stop();
```

---

# Radarfunktionen

## `servoSetAngle(int angle)`

Bewegt den Servo langsam zu einer gewünschten Position.

Beispiel

```cpp
servoSetAngle(90);
```

---

## `servoSearch()`

Lässt den Servo einmal von 0° bis 180° und wieder zurück fahren.

---

## `servoReset()`

Setzt den Servo auf die Ausgangsposition.

---

## `getDistanceCM()`

Misst den Abstand mit dem HC-SR04.

Rückgabewert:

* Abstand in Zentimetern
* `-1`, wenn kein Echo empfangen wurde

---

## `scanEnvironment()`

Der Servo misst drei Richtungen:

* Links (160°)
* Vorne (90°)
* Rechts (20°)

Anschließend wird entschieden:

| Rückgabe | Bedeutung       |
| -------- | --------------- |
| `2`      | Geradeaus frei  |
| `1`      | Links abbiegen  |
| `0`      | Rechts abbiegen |

Die Messwerte werden zusätzlich über den Serial Monitor ausgegeben.

Beispiel:

```
L:84.2 V:19.5 R:45.8
```

---

# Programmablauf

Beim Start werden

* die serielle Schnittstelle gestartet,
* alle Motorpins initialisiert,
* Ultraschallsensor eingerichtet,
* Servo auf 90° gesetzt.

---

# Automatikmodus

In der `loop()`-Funktion läuft folgender Ablauf kontinuierlich:

1. Umgebung scannen
2. Abstand links, vorne und rechts messen
3. Entscheidung treffen
4. Vorwärts fahren oder ausweichen

Pseudocode:

```text
Start
   │
   ▼
Umgebung scannen
   │
   ▼
Ist vorne frei?
 ┌───────────────┐
 │ Ja            │
 ▼               │
Vorwärts fahren  │
 │               │
 └──────► nächste Messung
 │
 Nein
 │
 ▼
Links weiter als rechts?
 │
 ├── Ja → Links drehen
 │
 └── Nein → Rechts drehen
```

---

# Projektstruktur

```
setup()
│
├── Initialisierung
│
├── Motorsteuerung
│   ├── drive()
│   ├── steer()
│   └── stop()
│
├── Radar
│   ├── servoSetAngle()
│   ├── servoSearch()
│   ├── servoReset()
│   ├── getDistanceCM()
│   └── scanEnvironment()
│
└── loop()
    ├── Umgebung scannen
    ├── Entscheidung treffen
    └── Fahren oder ausweichen
```

---

# Aktuelles Verhalten

Der Roboter arbeitet vollständig autonom.

* Das Radar schaut nacheinander nach links, vorne und rechts.
* Ist der Weg nach vorne frei (mehr als 25 cm Abstand), fährt der Roboter geradeaus.
* Ist ein Hindernis vorhanden, wird die Seite mit dem größeren freien Abstand gewählt.
* Danach wird erneut gemessen.

---

# Mögliche Erweiterungen

* Bluetooth-Steuerung
* WLAN-Steuerung (ESP8266 / ESP32)
* Linienverfolgung
* Encoder für präzisere Bewegungen
* OLED-Display
* Kartierung der Umgebung
* PID-Regelung
* Akkustandsüberwachung

---

# Hinweise

Der Code verwendet blockierende `delay()`-Aufrufe. Für flüssigere Bewegungen und schnellere Reaktionszeiten kann später auf `millis()` umgestellt werden.

Die Motorfunktionen prüfen die übergebenen Parameter und geben bei ungültigen Werten eine Fehlermeldung über die serielle Schnittstelle aus.

---

# Lizenz

Dieses Projekt steht unter der MIT-Lizenz und darf frei verwendet, verändert und erweitert werden.
