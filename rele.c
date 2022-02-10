const byte ledPin = 13;
const byte interruptPin = 2;
const byte relaypin=3;
volatile byte state = LOW;
long timex=0;
int interrupt_variable=0;
int apumuuttuja=0;
int keskeytys_jarjestysnumero=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(relaypin, OUTPUT);
  pinMode(interruptPin, INPUT);
  EIFR|=(1<<INTF0); //The flag is cleared when the interrupt routine is executed. Alternatively, the flag can be cleared by writing a 
  //logical one to it.
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  Serial.begin(9600);
  digitalWrite(ledPin, LOW); 
}

void loop() {
 
  
  if(interrupt_variable==1&&apumuuttuja==0)
  {
    digitalWrite(relaypin,HIGH);  
    digitalWrite(ledPin, HIGH); 
    Serial.print("1 apumuuttuja: ");
    Serial.println(apumuuttuja);
    Serial.print("1 interrupt_variable: ");
    Serial.println(interrupt_variable);
    apumuuttuja=1;
    interrupt_variable=0;
    for(int i=0;i<9;i++)
    {
      Serial.print(".");
      delay(1000);
    }
    delay(1000);
    Serial.println(".");
    EIFR|=(1<<INTF0);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  }
  else if(interrupt_variable==1&&apumuuttuja==1)
  {
    digitalWrite(relaypin,LOW);
    digitalWrite(ledPin, LOW); 
     Serial.print("2 apumuuttuja: ");
    Serial.println(apumuuttuja);
    Serial.print("2 interrupt_variable: ");
    Serial.println(interrupt_variable);
    interrupt_variable=0;
    apumuuttuja=0;
    for(int i=0;i<9;i++)
    {
      Serial.print(".");
      delay(1000);
    }
    delay(1000);
    Serial.println(".");
    EIFR|=(1<<INTF0);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  }

}

void blink() 
{
  Serial.print("KESKEYTYS nro: ");
  keskeytys_jarjestysnumero++;
  Serial.println(keskeytys_jarjestysnumero);
  detachInterrupt(digitalPinToInterrupt(interruptPin));
  EIFR|=(1<<INTF0);
  //EIMSK |= (1 << INT0); //When the INT0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), the external pin interrupt 
  //SREG|=1<<7;
  //is enabled.
  //EIMSK &= ~(1 << INT0);
  //EIFR&=~(1<<INTF0);
  timex=millis();
  interrupt_variable=1;
}

