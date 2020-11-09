#include <IRremote.h>
#include<LiquidCrystal.h>
int ir5=10,ledpin1=13,relay1=12,acpin1=11;
int count=0,flag1=0,flag2=0,i;
float temp1,val1, value;
int temppin1=A1,ldrpin1=A0;
int ldrstatus1;
IRrecv irrecv(10);
decode_results results;

  const int rs=9,en=8,d4=5,d5=4,d6=3,d7=2;
  LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
  


void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
 
  pinMode(ir5,INPUT);
  
  pinMode(ledpin1,OUTPUT);
  
  pinMode(relay1,OUTPUT);
  
  pinMode(acpin1,OUTPUT);
  
  pinMode(temppin1,INPUT);
 
  pinMode(ldrpin1,INPUT);
  
  lcd.print("No:");
  lcd.setCursor(4,0);
  lcd.print(count);
  lcd.setCursor(7,0);
  lcd.print("TEMP1:");
  lcd.setCursor(7,1);
  lcd.print("LIGHT:");
  irrecv.enableIRIn(); 
}
void loop()
{
  
  if(count>=0)
  {
    
      if(irrecv.decode(&results))//irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
      {
    	unsigned int value = results.value; //Get the value of results as an unsigned int, so we can use switch case
    	//Serial.println(value);
    	irrecv.resume(); // Receive the next value
        
        
        ldrstatus1=analogRead(ldrpin1);
       
        	if(ldrstatus1<=307)
        	{
          		analogWrite(ledpin1,255 - (ldrstatus1)/4);
          		Serial.println(ldrstatus1/4);
        	}
        	else
        	{
          		digitalWrite(ledpin1,LOW);
        	}
        	val1=analogRead(temppin1);
        	temp1=val1/4;
        	Serial.println(temp1);
        	if(temp1<5)
        	{
          	digitalWrite(acpin1,LOW);
          	digitalWrite(relay1,LOW);
        	}
        	else if(temp1<29)
        	{
          		digitalWrite(acpin1,LOW);
          		digitalWrite(relay1,HIGH);
        	}
        	else if(temp1>=30)
        	{
          	digitalWrite(acpin1,HIGH);
          	digitalWrite(relay1,HIGH);
        	}
        
      }
       
    }
    else
    {
      digitalWrite(ledpin1,LOW);
      
      digitalWrite(acpin1,LOW);
     
      digitalWrite(relay1,HIGH);
      
      temp1=0;
      
    }
    
     lcd.setCursor(13,0);
     lcd.print(temp1);
     lcd.setCursor(13,1);
     lcd.print((ldrstatus1/4));
  }

