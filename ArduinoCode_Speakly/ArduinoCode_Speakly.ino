// DECODIFICA CODICE MORSE IN PAROLE
// PROGETTO MCHPA - SPEAKLY

#include "fast.h"               // File con codici di frasi predefinite
#include <SoftwareSerial.h>     // Libreria per gestione istruzioni modulo Bluetooth

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) /sizeof(arg[0])))

// VARIABILI
String code = "";               // Parola digitata dall'utilizzatore
unsigned long pres_len = 0, rel_time, pres_time = 0, old_pres = 0;
int unit_delay = 80;            // Tempo per il punto
int min_delay = 10;             // Ritardo per cambiare simbolo
String parola = "";             // Parola per invio via Bluetooth
String phrase = "";             // Frase per invio via Bluetooth
const int debug = 1;            // Debug (0: non stampa su seriale)

bool ONE = true;                // Disegna uno spazio alla volta
unsigned long t1;               // Tempo per spazio tra parole

// BLUETOOTH
const int rxpin = 2;                    // Pin 2 per ricezione dati (collegato a TXD modulo)
const int txpin = 3;                    // Pin 3 per trasmissione dati (collegato a RXD modulo)
SoftwareSerial bluetooth(rxpin, txpin); // Configurazione modulo Bluetooth

// FUNZIONE PER CALCOLARE LA DURATA DELLA PREMUTA                               
unsigned long pres() {
    while (digitalRead(4) == HIGH) {}   // No touch
    old_pres = rel_time; 
    pres_time = millis();
    while (digitalRead(4) == LOW) {}    // Touch
    rel_time = millis();
    pres_len = rel_time - pres_time;
    return pres_len;
}

// FUNZIONE PER IL RICONOSCIMENTO PUNTO/TRATTO
char MakeString() { 
    if (pres_len < (unit_delay * 3) && pres_len > 50)
        return '.';  // Punto
    else if ((pres_len > (unit_delay * 3)) && (pres_len < (unit_delay * 13)))
        return '-';  // Tratto
    else
        return ' ';  // Spazio
}

// FUNZIONE PER DECODIFICARE SIMBOLI IN LETTERE  
void Morse_decod() {
    t1 = millis();  // Tempo da inizio decodifica (fine simbolo)
    static String morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
                               "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                               ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "!"};
    for (int i = 0; i < NUMITEMS(morse) - 1; i++) {
        if (morse[i] == code) {
            if (debug)
                Serial.print(char('A' + i));
            parola += char('A' + i);
            break;
        }
    }
}

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);  // Inizializzazione modulo Bluetooth
    pinMode(4, INPUT);       // Pin 4 come input
    code = Serial.readString();  // Lettura della stringa inserita
}

void loop() {
    unsigned long start = pres();  // Accensione
    unsigned long endloop = 0;      // Spegnimento
    if (start >= 2000) {
        if (debug)
            Serial.print("START ");
        bluetooth.print("ON");
        code = "";  // Reset variabili
        parola = "";
        
        while (endloop < 7500) {
            while (digitalRead(4) == HIGH) {}  // No touch
            old_pres = rel_time;
            pres_time = millis();
            while (digitalRead(4) == LOW) {}  // Touch
            rel_time = millis();
            pres_len = rel_time - pres_time; 
            if (pres_len > min_delay) {  // Cambia simbolo
                char symbol = MakeString();
                if (symbol != ' ') {
                    code += symbol;
                    Morse_decod();  // Decodifica
                }
            }
            if (pres_len > 5000) {  // Spegnimento dopo 5 sec
                endloop = 8000;
                if (debug)
                    Serial.println(" STANDBY UTENTE ");
                bluetooth.print("OFF");
                phrase = "";
                break; 
            }
            while ((millis() - rel_time) < (unit_delay * 3)) {  // Cambia lettera
                if (digitalRead(4) == LOW) {
                    char symbol = MakeString();
                    if (symbol != ' ') {
                        code += symbol;
                        Morse_decod();  // Decodifica
                    }
                }
            } 
            while (digitalRead(4) == HIGH) {  // Spegnimento dopo 100 sec inattività
                unsigned long t0 = millis(); 
                if ((t0 - t1) > (300 * unit_delay)) {
                    endloop = 8000;
                    if (debug)
                        Serial.println(" STANDBY ");
                    bluetooth.print("OFF");
                    phrase = "";
                    break;
                }
            }
        }
    } else {
        start = pres();  // Ricalcola durata premuta
        endloop = 0;
    }
}
