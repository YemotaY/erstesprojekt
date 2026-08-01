# Arduino Motorsteuerung

Dieses Projekt steuert zwei Gleichstrommotoren über einen Arduino und einen Motortreiber. Die Motoren können vorwärts, rückwärts, nach links und nach rechts gesteuert sowie gestoppt werden.

## Funktionen

- Vorwärts fahren
- Rückwärts fahren
- Links lenken
- Rechts lenken
- Motoren stoppen
- Einstellbare Geschwindigkeit

## Hardware

- Arduino (Uno, Nano oder kompatibel)
- Motortreiber (z. B. L293D oder L298N)
- 2 DC-Motoren
- Externe Stromversorgung für die Motoren

## Pinbelegung

| Motor | Arduino-Pin |
| ------ | ----------- |
| M1A    | A0 |
| M1B    | A1 |
| M2A    | A2 |
| M2B    | A3 |

## Geschwindigkeit

Die Motorgeschwindigkeit wird über PWM geregelt.

```cpp
int velocity = 128;
```

Wertebereich:

- `0` = Motor aus
- `255` = maximale Geschwindigkeit

## Funktionen

### `drive(int direction)`

Steuert beide Motoren gleichzeitig.

| Wert | Funktion |
|------|----------|
| `0` | Rückwärts |
| `1` | Vorwärts |

Beispiel:

```cpp
drive(1);   // Vorwärts
drive(0);   // Rückwärts
```

---

### `steer(int direction)`

Steuert die Fahrtrichtung.

| Wert | Funktion |
|------|----------|
| `0` | Rechts |
| `1` | Links |

Beispiel:

```cpp
steer(1);   // Links
steer(0);   // Rechts
```

---

### `stop()`

Stoppt beide Motoren.

```cpp
stop();
```

## Setup

Beim Start werden:

- die serielle Verbindung mit **9600 Baud** geöffnet,
- alle Motorpins als Ausgänge definiert,
- anschließend wird einmal `steer(0)` ausgeführt.

## Hauptschleife

Die `loop()`-Funktion ist aktuell leer.

Hier kann später z. B. implementiert werden:

- autonomes Fahren
- Bluetooth-Steuerung
- Funksteuerung
- Sensoren (Ultraschall, IR usw.)
- Linienverfolgung

## Projektstruktur

```
setup()
│
├── Initialisierung
│
├── drive()
├── steer()
├── stop()
│
└── loop()
```

## Hinweise

Der aktuelle Code besitzt einige Punkte, die verbessert werden sollten:

- Die Parameterprüfung verwendet
  ```cpp
  !direction > 1
  ```
  Diese Bedingung funktioniert nicht wie beabsichtigt. Stattdessen sollte geprüft werden:

  ```cpp
  if (direction < 0 || direction > 1)
  ```

- Funktionen mit dem Rückgabetyp `void` dürfen keinen Wert zurückgeben. Statt

  ```cpp
  return "Fehler";
  ```

  genügt:

  ```cpp
  return;
  ```

- Für Textausgaben über die serielle Schnittstelle empfiehlt sich:

  ```cpp
  Serial.println("Fehler");
  ```

  anstelle von `Serial.write()`.

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz und kann frei verwendet, verändert und erweitert werden.