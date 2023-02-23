#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 3
int FAIL_LED_PIN = 5;
int WARNING_LED_PIN = 6;
int SUCCESS_LED_PIN = 7;
MFRC522 mfrc522(SS_PIN, RST_PIN);

typedef struct {
  char UID[32];
  int balance;
} CardInformation;

CardInformation CardInformations[2];

void setup()
{
  Serial.begin(9600);    //Initiate a serial communication
  SPI.begin();       //Initiate  SPI bus
  mfrc522.PCD_Init();    //Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  //writeInitialValues();
  readAnythingFromEEPROM(CardInformations);
  delay(300);

}
void loop()
{
  digitalWrite(WARNING_LED_PIN, LOW);
  digitalWrite(FAIL_LED_PIN, LOW);
  digitalWrite(SUCCESS_LED_PIN, LOW);

  //Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  //Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();

  int isExists = isCardExists(content.substring(1));

  if (isExists != -1)
  {

    if (CardInformations[isExists].balance == 0) {
      digitalWrite(WARNING_LED_PIN, HIGH);

      Serial.println("Unauthorized access");
      Serial.println("Because your balance is zero");
    }

    else {
      digitalWrite(SUCCESS_LED_PIN, HIGH);

      CardInformations[isExists].balance--;
      writeAnythingToEEPROM(CardInformations);

      Serial.println("Authorized access");
      Serial.println("Your balance is " + String(CardInformations[isExists].balance));

    }

    Serial.println();
    delay(3000);
  }

  else   {
    digitalWrite(FAIL_LED_PIN, HIGH);
    Serial.println("Invalid card");
    Serial.println();
    delay(3000);
  }
}

int isCardExists(String cardId) {
  int count;

  for (count = 0; count < sizeof(CardInformations); count = count + 1) {
    if (String(CardInformations[count].UID) == cardId) {
      return count;
    }
  }

  return -1;
}

void writeInitialValues() {
  CardInformation ci1;
  CardInformation ci2;

  ci1.balance = 3;
  ci2.balance = 100;
  strcpy(ci1.UID, "B1 15 90 1C");
  strcpy(ci2.UID, "B7 05 1C 39");
  
  CardInformation InitialCardInformations[2];
  InitialCardInformations[0] = ci1;
  InitialCardInformations[1] = ci2;

  writeAnythingToEEPROM(InitialCardInformations);
  delay(300);
}

template <typename T>
unsigned int writeAnythingToEEPROM(const T& value)
{
  const byte * p = (const byte*) &value;
  unsigned int i;
  for (i = 0; i < sizeof value; i++)
  {
    EEPROM.update(i, *p++);
  }
  return i;
}

template <typename T>
unsigned int readAnythingFromEEPROM(T& value)
{
  byte * p = (byte*) &value;
  unsigned int i;
  for (i = 0; i < sizeof value; i++)
  {
    *p++ = EEPROM.read(i);
  }
  return i;
}
