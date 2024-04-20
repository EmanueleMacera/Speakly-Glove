# Speakly

Speakly is a smart glove designed to translate Morse code into spoken words emitted by a smartphone. This wearable device aids individuals with reduced verbal skills, aiming to improve their communication fluency. Unlike existing devices, Speakly requires the use of only two fingers—the index finger and thumb—allowing freedom of movement for the rest of the body. For instance, many devices on the market utilize screens that require eye movement to navigate, but with Speakly, users have maximum freedom of expression through visual cues and gestures.

The primary advantage of Speakly is its direct emission of sentences from the smartphone, making it universally understandable for everyone interacting with individuals using the device. While sign language is known to only a few, learning Morse code enables users to communicate effectively with Speakly.

Moreover, Speakly is highly accessible due to its extremely low production and construction costs, making it an affordable option for all.

## Components

Speakly utilizes two conductive copper plates placed on the index finger and thumb. When these plates are in contact, a current flows through the circuit connected to the Arduino Uno. The first plate is connected to GND, while the second is connected to digital pin 4. The circuit is powered by 3.3V via a 10KΩ resistor. Additionally, an HC-06 Bluetooth module is connected to 5V, GND, pin 2 for transmitting, and pin 3 for receiving. To simulate real-world usage, a battery is incorporated into the design, connected to GND and Vin via a power button for device on/off control.

### List of Parts:
- **Arduino Uno SMD**
- **DSD TECH HC-06 Bluetooth Module** - [Amazon](https://www.amazon.com/) - $8.99
- **Copper Foil Tape (30mm x 40mm)** - [Amazon](https://www.amazon.com/) - $2.99
- **Jumper Wire (120 pcs)** - [Amazon](https://www.amazon.com/) - $5.99
- **10 KΩ Resistor** - [Amazon](https://www.amazon.com/) - $0.50
- **Powerfulcell 9V Battery and Adapter** - Electronic Market - $5.00
- **Pushbutton** - Electronic Market - $0.90

## Usage

The primary function of Speakly is to translate Morse code into words sent to a smartphone via Bluetooth for fast transmission. Morse code was chosen due to its "dot and dash" structure, which reduces the potential for hardware errors.

### Getting Started

1. Activate Bluetooth and enable location on your mobile device.
2. Download the "App_Speakly" application.
3. Click the "Connect" button and select the HC-06 device from the list.
4. Once "Connected" appears in green, you can disconnect if needed.
5. To begin typing words or phrases, press the plates together for at least 4 seconds; you'll hear a confirmation sound and feel a vibration.
6. Compose Morse code by contacting the two plates:
   - Short contact: dot
   - Long contact (three times the short one): dash
7. After typing ".....", the smartphone will synthesize the word/phrase.
8. To delete a sentence, type the code "-..-.".
9. To add a space between words, wait approximately one second before typing the next letter.
10. To turn off the device, press and hold for at least 4 seconds; otherwise, it will enter standby mode after 30 seconds of inactivity.

### Common Phrases

Speakly includes common phrases that can be easily modified or expanded to personalize the user experience. For example, typing the code "..- .." will prompt the smartphone to emit the phrase "Could you tell me where the bathroom is, please?". 

### Emergency Feature

In emergency situations, users can type '-....' or '-.....', and a message will be sent to a predefined contact requesting help and location.

### Morse Code

Each common sentence is generated by two codes to guarantee error control. For example:
- "Hi, my name is Speakly" -> "-.... -....."
- "My allergens are: lactose and nuts" -> ".-... .-...."
- "Could you tell me where the bathroom is, please?" -> "..-.. ..-..."
- "My phone number is 347 74 25 22" -> "...-. ....-."
- "I need help" -> "....- .....-"
- "I live in Genoa in Piazza De Ferrari, number 7" -> "-...- -....-"

### Letter Code
- **A** -> ".-"
- **B** -> "-..."
- **C** -> "-.-."
- **D** -> "-.."
- **E** -> "."
- **F** -> "..-."
- **G** -> "--."
- **H** -> "...."
- **I** -> ".."
- **J** -> ".---"
- **K** -> "-.-"
- **L** -> ".-.."
- **M** -> "--"
- **N** -> "-."
- **O** -> "---"
- **P** -> ".--."
- **Q** -> "--.-"
- **R** -> ".-."
- **S** -> "..."
- **T** -> "-"
- **U** -> "..-"
- **V** -> "...-"
- **W** -> ".--"
- **X** -> "-..-"
- **Y** -> "-.--"
- **Z** -> "--.."

## Implementation

The Arduino code consists of three functions:
1. Measure the pressing time.
2. Distinguish between dot and dash.
3. Register the symbols, decode them into letters, and save the words.
The on, off, and word detachment times are managed in the loop. The Bluetooth connection is implemented in the app, and the TextToSpeech translation module runs automatically.

---

This project originated from a university project at the University of Genoa.