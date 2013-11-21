
//mux variables
int input = 5;   // digital input to arduino from mux
//int strobe=0;   //digital outputs to control mux  
int c=4;
int b=3;
int a=2;

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
  for(int i = 0; i < 3; i++)
  {
     for(int j = 0; j < 64; j++)
     {
       characters[i][j] = NULL;
     }
  }
}

void loop() {
  bool allZero = true;
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
      //check for backspace or space signals first.
      
      
     //use values in valsPressed to get the character to display. 
     //int index = binToInt();       //convert six signals to an int to access arrays.
     
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
     
     //*****Case and number
     //uppercase
     //lowercase
     //numericals
       
     
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
