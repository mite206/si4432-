//四個輸出，輸出模式為延時暫態。
#include <SPI.h>
#include <RH_RF22.h>

// Singleton instance of the radio driver
RH_RF22 rf22;

#define led1 9
#define led2 8
#define led3 7
#define led4 6
unsigned long ggtime;
unsigned long cutime;
void setup() 
{
  Serial.begin(9600);
  if (!rf22.init())
    Serial.println("init failed");  
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
}

void loop()
{
  if (rf22.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf22.recv(buf, &len))
    {
//      RF22::printBuffer("request: ", buf, len);
//      rf22.printBuffer("request: ", buf,len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
//      Serial.println(rf22.lastRssi(), DEC);

//  比較字串是否一樣，一樣時輸出。字串要定義String
     String bu=(char*)buf;
     if (bu == "mite key a")
     {
        lcdchange(led1,1000);//使用副程式.led1為定訂名稱，後面數字1000為延時毫秒數
        Serial.println("按鍵a");
        delay(10);
     }

       if (bu == "mite key b")
     {
        //digitalWrite(led2,HIGH);
        lcdchange(led2,1500);//使用副程式
        Serial.println("按鍵b");
        delay(10);
     }

      if (bu == "mite key c")
     {
        //digitalWrite(led3,HIGH);
        lcdchange(led3,1500);//使用副程式
        Serial.println("按鍵c");
        delay(10);
     }

      if (bu == "mite key d")
     {
        //digitalWrite(led4,HIGH);
        lcdchange(led4,1500);//使用副程式
        Serial.println("按鍵d");
        delay(10);
     }
      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf22.send(data, sizeof(data));
      rf22.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}

//------------------------------------
void lcdchange(char na,int dalaytime){
  ggtime=millis();//記錄收到信號後的秒數
  Serial.println(ggtime);
  //unsigned long cutime;
  //digitalWrite(na,HIGH);
  //delay(1000);
  //digitalWrite(na,LOW);
  //unsigned long ggtime=cutime;
  while (millis()<ggtime+dalaytime)
  {
  digitalWrite(na,HIGH);
  Serial.print(millis());
  Serial.print("/");
  Serial.print(ggtime);
  Serial.print("/");
  Serial.println(dalaytime);
  }
  digitalWrite(na,LOW);
}
