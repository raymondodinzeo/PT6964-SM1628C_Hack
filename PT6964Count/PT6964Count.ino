//Binary count using PT6964 or SM1628C
//By Ray Houghton

//Connections to PT6964
//Pin 3 - CLK
//Pin 2 - DI/O - dataPin
//Pin 28 - GND
//Pin 7 - +5V
//Pin 4 - STB
 
  //Commands from Datasheet necessary to operate PT6964
  //command1 - 00000000 = 0 Display mode 4 dig 13 seg
  //command2 - 01000000 = 64 //Data setting, Write, increment address after write
  //command3 - 11000000 = 192 //Address setting 00 start
  //command4 - 10001000 = 136 Display ON minimum brightness
  //command4 - 10000000 = 121 Display OFF

//0 = 11010111 = 215   //the mapping of segments on my display PCB, others may differ 
//1 = 00010100 = 20    +32 to add decimal point
//2 = 11001101 = 205   
//3 = 01011101 = 93
//4 = 00011110 = 30
//5 = 01011011 = 91
//6 = 11011011 = 219 
//7 = 00010101 = 21
//8 = 11011111 = 223
//9 = 01011111 = 95

//1111 //bit No, 1 is LSB
//2  3 
//2  3
//4444
//8  5
//8  5
//7777  6 

int digits[8]; //Contains data to be written to display memory
int clockPin = 2; 
int dataPin = 3;
int STB = 4;
int i, j, k, l, m;

void setup()
 {
   pinMode(clockPin, OUTPUT); //serial display interface, STB is !Write enable
   pinMode(dataPin, OUTPUT);
   pinMode(STB, OUTPUT);
   
  delay(250); //start up delay
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 64); // Command 2: Data setting 'Write', increment address
  //after write
  digitalWrite(STB, HIGH);
  delayMicroseconds(1); // delay between data writes
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 192); //Command 3: Address set, 00 as start address
  delayMicroseconds(1);
  for(i = 0; i < 8; i++) //clear display memory
  {
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    delayMicroseconds(1);
    
  }
 digitalWrite(STB, HIGH);
 delayMicroseconds(1);
 
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0);//Command 1: Display mode 4 dig 13 seg
  digitalWrite(STB, HIGH);
  delayMicroseconds(1);
 
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 121); //Command 4: Display control - display off
  digitalWrite(STB, HIGH);
  delayMicroseconds(1);

 }

void loop()
 { // Digital count to give outputs for 1000s, 100s, 10s, units,
  for(j = 1; j < 11; j++) //count for thousands
  {
  for(k = 1; k < 11; k++) //count for hundreds
    {
    for(l = 1; l < 11; l++) //count for tens
      {
      for(m = 1; m < 11; m++) //count for units
        {
//assigns symbols to display IC addresses
digits[7] = 0;
digits[6] = symbols(j);
digits[5] = 0;  
digits[4] = symbols(k);
digits[3] = 0;  
digits[2] = symbols(l);
digits[1] = 0;
digits[0] = symbols(m);
       
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 64);// Command 2: Data setting 'Write', increment address
  //after write
  delayMicroseconds(1);
 for(i = 0; i < 8; i++) // write symbols stored in 'digits[]' array into display memory 
     {
      shiftOut(dataPin, clockPin, LSBFIRST, digits[i]);
      delayMicroseconds(1);
     }
  digitalWrite(STB, HIGH);
  delayMicroseconds(1);
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 192); //Address setting 00 start
  digitalWrite(STB, HIGH);
  delayMicroseconds(1);
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0); //command 1 Display mode 4 dig 13 seg
  digitalWrite(STB, HIGH);
  delayMicroseconds(1);
  digitalWrite(STB, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 136); // command 4 Display on
  digitalWrite(STB, HIGH);
  delay(100); //delay governs speed of count
        }
      }
    }
 }
 }

 int symbols(int symbolNum) //function to assign display segments to numbers
  {
//0 = 11010111 = 215    
//1 = 00010100 = 20    +32 to add decimal point
//2 = 11001101 = 205   
//3 = 01011101 = 93
//4 = 00011110 = 30
//5 = 01011011 = 91
//6 = 11011011 = 219 
//7 = 00010101 = 21
//8 = 11011111 = 223
//9 = 01011111 = 95


switch (symbolNum) {
    case 1: //zero
    return 215;
    break;
    
    case 2: // 1
    return 20;
    break;
    
    case 3: // 2
    return 205;
    break;
    
    case 4: // 3
    return 93;;
    break;

    case 5: // 4
    return 30;
    break;

    case 6: // 5
    return 91;
    break;

    case 7: // 6
    return 219;
    break;

    case 8: // 7
    return 21;
    break;

    case 9: // 8
    return 223;
    break;

    case 10: // 9
    return 95;
    break;

    default: // turn off digit
    return 0;
    break;
   
    break;
    }
  }
