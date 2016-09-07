#include <SoftwareSerial.h>
 
int bluetoothTx = 1;  // TX pin of bluetooth
int bluetoothRx = 0;  // RX pin of bluetooth

int dataFromBt;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
 
void setup()
{
  Serial.begin(9600);
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");     // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");     // Enter command mode
  delay(100);               // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");
  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);    // Start bluetooth serial at 9600
  Serial.println("READY");
}
 
void loop()
{
 
  if (bluetooth.available()) // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
 
    Serial.println((char)bluetooth.read());
    dataFromBt = bluetooth.read();
 
    //Serial.println(dataFromBt);
    if (dataFromBt == '1') {
      Serial.println("led on");
      bluetooth.print("1");
    }
    if (dataFromBt == '0') {
      Serial.println("led off");
      bluetooth.print("0");
    }
  }
 
  if (Serial.available()) // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    //String myStr = (String)Serial.read();
    //char myStr1[] = "hello this is testing!";
 
    // uint8_t payload[myStr.length() + 1];
    //    myStr.getBytes(payload, myStr.length()+1);

    int bytes=Serial.available();
    //Serial.readBytes(buffer, startPosition, bytes);

    bluetooth.print((char)Serial.read());
  }
}
