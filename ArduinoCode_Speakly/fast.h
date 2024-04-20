// Aggiunta di frasi quotidiane con codici Morse veloci

String words[] = {
  "Ciao il mio nome è Speakly", "-....",
  "Ciao il mio nome è Speakly", "-.....", // Controllo errore
  "I miei allergeni sono: lattosio e noci", ".-...",
  "I miei allergeni sono: lattosio e noci", ".-....", // Controllo errore
  "Potrebbe indicarmi dov'è il bagno, per favore?", "..-..",
  "Potrebbe indicarmi dov'è il bagno, per favore?", "..-...", // Controllo errore
  "Il mio numero è 347 74 25 22", "...-.",
  "Il mio numero è 347 74 25 22", "....-.", // Controllo errore
  "Ho bisogno di aiuto", "....-",
  "Ho bisogno di aiuto", ".....-", // Controllo errore
  "Abito a Genova in Piazza De Ferrari, numero 7", "-...-",
  "Abito a Genova in Piazza De Ferrari, numero 7", "-....-", // Controllo errore
};

// Numero di coppie frase-codice
#define NUM_FRASES (sizeof(words) / sizeof(words[0]) / 2)

// Funzione per cercare una frase nel database
String findPhrase(String code) {
  for (int i = 0; i < NUM_FRASES; ++i) {
    if (words[i * 2 + 1] == code) {
      return words[i * 2];
    }
  }
  return "";  // Se non viene trovata corrispondenza
}
