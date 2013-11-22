
//mux variables
int input = 5;   // digital input to arduino from mux
//int strobe=0;   //digital outputs to control mux  
int c=4;
int b=3;
int a=2;

int caseIndex = 0;            //variable to keep track of the current case. 0 - lowercase, 1 - uppercase, 2 - numbers

bool storingInput = false;

// to store the values from mux
int val[] = {0,0,0,0,0,0,0,0}; 
int valsStored[8] = {0,0,0,0,0,0,0,0}; 
char characters[3][64];  //2d array to store characters.
                         //[0][64] will contain lowercase letters
                         //[1][64] will contain uppercase letters
                         //[2][64] will contain numbers

// digital values to control 8 inputs
int c_bin[]={LOW,LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH};
int b_bin[]={LOW,LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH};
int a_bin[]={LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH};

//aux
int contador=0;
int entrada=0;
int a_val=0;
int b_val=0;
int c_val=0;

void setup() {

  Serial.begin(9600);
  pinMode(input, INPUT);    
  //pinMode(strobe, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);
  
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
  
  //todo: decide whether ( or ) is used.
  characters[0][54] = '(';
  characters[1][54] = '(';
  characters[2][54] = '(';
  
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

void loop() {
  bool allZero = true;
  int letter = 0;
  for(entrada=0;entrada<=5;entrada++) {

    //select mux input
    a_val=a_bin[entrada];
    b_val=b_bin[entrada];
    c_val=c_bin[entrada];

    digitalWrite(a,a_val);
    digitalWrite(b,b_val);
    digitalWrite(c,c_val);

    //strobe LOW to read
    //digitalWrite(strobe,LOW);

    //read value
    val[entrada] = digitalRead(input);  // read input value
    if(val[entrada] != 0)
    {
      storingInput = true;
      valsStored[entrada] = 1;
      allZero = false;
    }
    //strobe HIGH to avoid jitters
    //digitalWrite(strobe,HIGH);
  }
  
  if(allZero && storingInput)
  {    
      letter = binToInt(valsStored);
      
      //check for case change
      if(letter == 48)  //lowercase
        caseIndex = 0;
      else if(letter == 32)  //uppercase
        caseIndex = 1;
      else if(letter == 60)  //number
        caseIndex = 2;
        
      //now check for backspace or space
      //for now, assuming backspace is the 7th button and space is the 8th
      else if(letter == 64)
        Serial.print('\b');  //backspace override character, might have to change it to work with led screen library
      else if(letter == 128)
        Serial.print(' ');
      
     //******letters******
     if(valsStored[0] && !valsStored[1] && !valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('a');
     else if(valsStored[0] && valsStored[1] && !valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('b');
     else if(valsStored[0] && !valsStored[1] && !valsStored[2] && valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('c');
     else if(valsStored[0] && !valsStored[1] && !valsStored[2] && valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('d');
     else if(valsStored[0] && !valsStored[1] && !valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('e');
     else if(valsStored[0] && valsStored[1] && !valsStored[2] && valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('f');
     else if(valsStored[0] && valsStored[1] && !valsStored[2] && valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('g');
     else if(valsStored[0] && valsStored[1] && !valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('h');
     else if(!valsStored[0] && valsStored[1] && !valsStored[2] && valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('i');
     else if(!valsStored[0] && valsStored[1] && !valsStored[2] && valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('j');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('k');
     else if(valsStored[0] && valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('l');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('m');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('n');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('o');
     else if(valsStored[0] && valsStored[1] && valsStored[2] && valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('p');
     else if(valsStored[0] && valsStored[1] && valsStored[2] && valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('q');
     else if(valsStored[0] && valsStored[1] && valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('r');
     else if(!valsStored[0] && valsStored[1] && valsStored[2] && valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print('s');
     else if(!valsStored[0] && valsStored[1] && valsStored[2] && valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('t');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && valsStored[5])
       Serial.print('u');
     else if(valsStored[0] && valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && valsStored[5])
       Serial.print('v');
     else if(!valsStored[0] && valsStored[1] && !valsStored[2] && valsStored[3] && valsStored[4] && valsStored[5])
       Serial.print('w');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && valsStored[3] && !valsStored[4] && valsStored[5])
       Serial.print('x');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && valsStored[3] && valsStored[4] && valsStored[5])
       Serial.print('y');
     else if(valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && valsStored[4] && valsStored[5])
       Serial.print('z');
       
       
       
     //*****punctuation*****
     else if(!valsStored[0] && valsStored[1] && !valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print(',');
     else if(!valsStored[0] && valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print(';');
     else if(!valsStored[0] && valsStored[1] && !valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print(':');
     else if(!valsStored[0] && valsStored[1] && !valsStored[2] && !valsStored[3] && valsStored[4] && valsStored[5])
       Serial.print('.');
     else if(!valsStored[0] && valsStored[1] && valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('!');
     else if(!valsStored[0] && !valsStored[1] && !valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
     {
       //todo: choose to display "("or ")" depending on the last one displayed
       //if(something)
       //Serial.print('(');
       //else
       //Serial.print(')'); 
     }
     else if(!valsStored[0] && valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && valsStored[5])
       Serial.print('?');
     else if(!valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && valsStored[4] && !valsStored[5])
       Serial.print('*');
     else if(!valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && valsStored[4] && valsStored[5])
       Serial.print('"');
     else if(!valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && !valsStored[5])
       Serial.print("'");
     else if(!valsStored[0] && !valsStored[1] && valsStored[2] && !valsStored[3] && !valsStored[4] && valsStored[5])
       Serial.print('-');
     
     //*****No case has matched, assume invalid input and don't print anything.
       else 
       Serial.print("not a valid character/not implemented yet");
       
     Serial.println();
     //Reset stored buttons
     storingInput = false;
     for(int i = 0; i < 6; i++)
     {
       valsStored[i] = 0; 
     }
     letter = 0;  //reset letter
  }


  //serial printing
  Serial.print('A');
  delay(100);
  for(contador=0;contador<=7;contador++) {
    Serial.print(val[contador]);
    delay(100);
  }
  Serial.println();

}

int binToInt(int valStore[8])
{
 int index = 0;
 int multiplier = 1;
 for(int i = 0; i <= 5; i++)
 {
   if(valStore[i] == 1)
     index += multiplier;
   multiplier *= 2;
 }
 return index; 
}
