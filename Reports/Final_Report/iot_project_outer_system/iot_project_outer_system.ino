	#include <LiquidCrystal.h>
	#include <IRremote.h>
    #include <Keypad.h>
    #include <Servo.h>
	
	int RECV_PIN = 10;
	IRrecv irrecv(RECV_PIN);
	decode_results results;

	const int rs=A0,en=A1,d4=A2,d5=A3,d6=A4,d7=A5;
    LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

    Servo servo_Motor; 
	unsigned int count;
    char* password = "852"; 
    int position = 0; 
    const byte ROWS = 4;
    const byte COLS = 4;
    char keys[ROWS][COLS] = { 
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
    };

    byte rowPins[ROWS] = { 9, 8, 7, 6 }; 
    byte colPins[COLS] = { 5, 4, 3, 2 }; 
    Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

    const int red = 12; 
    const int green = 13;

    void setup(){
      pinMode(red, OUTPUT); 
      pinMode(green, OUTPUT); 
	  Serial.begin(9600);
      servo_Motor.attach(11); 
      setLocked(true); 
      irrecv.enableIRIn(); 
      lcd.print("No Of Person:");
      lcd.setCursor(13,0);
  	   lcd.print(count);
    }
    void loop(){
      char key = keypad.getKey();
      if (key == '*' || key == '#') { 
          position = 0; 
          setLocked(true); 
    }
    if (key == password[position]){ 
          position ++;
    }
    if (position == 4){ 
          setLocked(false); 
    }
    delay(100);
    }
    void setLocked(int locked){
    if (locked){ 
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        servo_Motor.write(0);
    }
    else{ 
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        servo_Motor.write(90); 
    }
    
     if (irrecv.decode(&results)) //irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
     {
    	unsigned int value = results.value; //Get the value of results as an unsigned int, so we can use switch case
        irrecv.resume(); // Receive the next value
        switch (value) 
        {
      		case 12495: 
      				count++;
      				break;
          case 2295: 
      				count++;
      				break;
          case 34935: 
      				count++;
      				break;
          case 18615: 
      				count++;
      				break;
          case 10455: 
      				count++;
      				break;
          case 43095: 
      				count++;
      				break;
          case 26775: 
      				count++;
      				break;
          case 3675: 
      				count++;
      				break;
          case 39015: 
      				count++;
      				break;
          case 22695: 
      				count++;
      				break;
      
      
    }
       switch (value) 
        {
      		case 255: 
      				count--;
      				break;
          case 32855: 
      				count--;
      				break;
          case 36975: 
      				count--;
      				break;
          case 16575: 
      				count--;
      				break;
          case 41055: 
      				count--;
      				break;
          case 8415: 
      				count--;
      				break;
          case 24735: 
      				count--;
      				break;
          case 4325: 
      				count--;
      				break;
          case 20655: 
      				count--;
      				break;
          case 45135: 
      				count--;
      				break;
         case 28815: 
      				count--;
      				break;
      
      
      
    }
       
  	   lcd.setCursor(13,0);
  	   lcd.print(count);
       Serial.print("No of Persons:");
       Serial.println(count);
     }
    }