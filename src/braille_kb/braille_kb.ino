#include "LiquidCrystal595.h"

// LCD
int latch = 9;
int data = 8;
int clock = 10;
LiquidCrystal595 lcd(data, latch, clock);

// MUX 151
int a=2; // select a pin
int b=3; // select b pin
int c=4; // select c pin
int input = 5; // read pin
// to store the values from mux
int val[] = {0,0,0,0,0,0};
int valsStored[] = {0,0,0,0,0,0};

bool pressed = false; // indicates a button is pressed


char alpha[16]; //array that will hold alphabetical characters to be printed on screen
char alpha2[16]; //array to store characters on line 2

int caseIndex = 0; //variable to keep track of the current case. 0 - lowercase, 1 - uppercase, 2 - numbers

int numOfChars = 0;  //keep track of number of alphabetical characters currently being displayed

char characters[3][64];  //2d array to store characters.
                         //[0][64] will contain lowercase letters
                         //[1][64] will contain uppercase letters
                         //[2][64] will contain numbers
						 

// digital values to control 8 inputs
int c_bin[]={LOW,LOW,LOW,HIGH,HIGH,HIGH};
int b_bin[]={LOW,LOW,HIGH,HIGH,LOW,LOW};
int a_bin[]={LOW,HIGH,LOW,LOW,HIGH,LOW};

//aux
int counter = 0;
int a_val = 0;
int b_val = 0;
int c_val = 0;

void setup() {

  Serial.begin(9600);
  pinMode(input, INPUT);    
  pinMode(c, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  
  lcd.setLED2Pin(HIGH);
  lcd.begin(16,2);  //set up lcd with 16 columns and 2 rows
  
  for(int i = 0; i < 16;i++)  //initialize character array to all spaces(blank)
  {
    alpha[i] = ' ';
    alpha2[i] = ' ';
  }
  
  //Set up blank arrays
  for(int i = 0; i < 3; i++)
  {
     for(int j = 0; j < 64; j++)
     {
       characters[i][j] = NULL;
     }
  }
  //set up lowercase characters
  characters[0][1] = 'a';
  characters[0][3] = 'b';
  characters[0][9] = 'c';
  characters[0][25] = 'd';
  characters[0][17] = 'e';
  characters[0][11] = 'f';
  characters[0][27] = 'g';
  characters[0][19] = 'h';
  characters[0][10] = 'i';
  characters[0][26] = 'j';
  characters[0][5] = 'k';
  characters[0][7] = 'l';
  characters[0][13] = 'm';
  characters[0][29] = 'n';
  characters[0][21] = 'o';
  characters[0][15] = 'p';
  characters[0][31] = 'q';
  characters[0][23] = 'r';
  characters[0][14] = 's';
  characters[0][30] = 't';
  characters[0][37] = 'u';
  characters[0][39] = 'v';
  characters[0][58] = 'w';
  characters[0][45] = 'x';
  characters[0][61] = 'y';
  characters[0][53] = 'z';

  //set up uppercase characters
  characters[1][1] = 'A';
  characters[1][3] = 'B';
  characters[1][9] = 'C';
  characters[1][25] = 'D';
  characters[1][17] = 'E';
  characters[1][11] = 'F';
  characters[1][27] = 'G';
  characters[1][19] = 'H';
  characters[1][10] = 'I';
  characters[1][26] = 'J';
  characters[1][5] = 'K';
  characters[1][7] = 'L';
  characters[1][13] = 'M';
  characters[1][29] = 'N';
  characters[1][21] = 'O';
  characters[1][15] = 'P';
  characters[1][31] = 'Q';
  characters[1][23] = 'R';
  characters[1][14] = 'S';
  characters[1][30] = 'T';
  characters[1][37] = 'U';
  characters[1][39] = 'V';
  characters[1][58] = 'W';
  characters[1][45] = 'X';
  characters[1][61] = 'Y';
  characters[1][53] = 'Z';
  
  //set up numbers
  characters[2][1] = '1';
  characters[2][3] = '2';
  characters[2][9] = '3';
  characters[2][25] = '4';
  characters[2][17] = '5';
  characters[2][11] = '6';
  characters[2][27] = '7';
  characters[2][19] = '8';
  characters[2][10] = '9';
  characters[2][26] = '0';
  
  //set up punctuation characters
  characters[0][2] = ',';
  characters[1][2] = ',';
  characters[2][2] = ',';
  characters[0][6] = ';';
  characters[1][6] = ';';
  characters[2][6] = ';';
  characters[0][18] = ':';
  characters[1][18] = ':';
  characters[2][18] = ':';
  characters[0][50] = '.';
  characters[1][50] = '.';
  characters[2][50] = '.';
  characters[0][22] = '!';
  characters[1][22] = '!';
  characters[2][22] = '!';
  characters[0][2] = ',';
  characters[1][2] = ',';
  characters[2][2] = ',';
  
  characters[0][38] = '?';
  characters[1][38] = '?';
  characters[2][38] = '?';
  characters[0][20] = '*';
  characters[1][20] = '*';
  characters[2][20] = '*';
  characters[0][52] = '"';
  characters[1][52] = '"';
  characters[2][52] = '"';
  characters[0][4] = '\'';
  characters[1][4] = '\'';
  characters[2][4] = '\'';
  characters[0][36] = '-';
  characters[1][36] = '-';
  characters[2][36] = '-';
}

void readBraille() {
  for (int select = 0; select < 6; select++) {
    //select mux input
    a_val = a_bin[select];
    b_val = b_bin[select];
    c_val = c_bin[select];

    digitalWrite(a, a_val);
    digitalWrite(b, b_val);
    digitalWrite(c, c_val);
	
    val[select] = digitalRead(input);
    if(val[select] == 1){
      valsStored[select] = 1;
      pressed = true;
  }
	
  }
  /* DEBUG
  Serial.print("loop: ");
  delay(100);
  for(int i = 0; i < 6; i++) {
    Serial.print(val[i]);
  }
  Serial.println();
  */
}

void checkButtons() {
  pressed = false;
  for(int i = 0; i < 6; i++) {
    if(val[i] == 1) pressed = true;
  }
}

void getButton() {
  pressed = false;
  while(pressed == false) {
    readBraille();
  }
  while(pressed == true) {
    readBraille();
	checkButtons();
  }
}

void clearValsStored(){
  for(int i = 0; i < 6; i++)
    valsStored[i] = 0;
}

void loop() {
  // integer representation of a character
  int letter = 0;
  
  /***** input *****/
  getButton();

  /* DEBUG
  Serial.print("pressed: ");
  delay(50);
  for(int i = 0; i < 6; i++) {
    Serial.print(valsStored[i]);
  }
  Serial.println();
  */

  /***** decode *****/  
  letter = binToInt(valsStored);
  
  if(letter)
  {
  //check for case change
  if(letter == 48) // lowercase
    caseIndex = 0;
  else if(letter == 32) // uppercase
    caseIndex = 1;
  else if(letter == 60) // number
    caseIndex = 2;
     
    else  //not a case/number changer, then it is a character
    {
      if(characters[caseIndex][letter] != NULL)  //make sure it's a valid letter
      {
      if(numOfChars <= 15)  //less than 16 characters, print on first line
      {
        alpha[numOfChars] = characters[caseIndex][letter];
        numOfChars++;
      }
      else if(numOfChars >= 16 && numOfChars < 32)  //more than 16, but less than 32 characters, print on second line.
      {
        alpha2[numOfChars-16] = characters[caseIndex][letter];
        numOfChars++;
      }
      else  //else, 32 characters or more. have to shift all characters left before inserting at end.
      {
      shiftChars();  //shift all characters
      numOfChars = 32;
      alpha[numOfChars-1] = characters[caseIndex][letter];  //insert new character at end of second array.
      }
    }
    } 
  }
  /***** reset *****/
  lcd.setCursor(0,0);
  lcd.print(alpha);  // print first line
  
  lcd.setCursor(0,1);
  lcd.print(alpha2); //print second line
  
  clearValsStored(); // reset valsStored
  letter = 0; // reset letter  
}

int binToInt(int valStore[8])  //converts the 6 inputs from the mux into an integer
{
 int index = 0;
 int multiplier = 1;
 for(int i = 0; i < 8; i++)
 {
   if(valStore[i] == 1)
     index += multiplier;
   multiplier *= 2;
 }
 return index; 
}

//shifts all of the characters in both character arrays left once. only needs to be called when both lines are full and there's another character input.
void shiftChars()
{
  for(int i = 0; i < 15; i++)  //shift first row
  {
    alpha[i] = alpha[i+1];
  }
  alpha[15] = alpha2[0];
  for(int i = 0; i < 15; i++)
  {
   alpha2[i] = alpha2[i+1]; 
  }
}
