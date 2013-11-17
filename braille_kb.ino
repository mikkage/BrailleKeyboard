
//mux variables
int input = 2;   // digital input to arduino from mux
int strobe=5;   //digital outputs to control mux  
int c=10;
int b=9;
int a=8;

bool storingInput = false;

// to store the values from mux
int val[] = {
  0,0,0,0,0,0,0,0}; 
int valsStored[] = {0,0,0,0,0,0,0,0}; 

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
  pinMode(strobe, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);
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
    digitalWrite(strobe,LOW);

    //read value
    val[entrada] = digitalRead(input);  // read input value
    if(val[entrada] != 0)
    {
      storingInput = true;
      valsStored[entrada] = 1;
      allZero = false;
    }
    //strobe HIGH to avoid jitters
    digitalWrite(strobe,HIGH);
  }
  if(allZero && storingInput)
  {
     //use values in valsPressed to get the character to display. 
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
       else Serial.print("type a letter, asshole");
       
     Serial.println();
     //Reset stored buttons
     storingInput = false;
     for(int i = 0; i < 6; i++)
     {
       valsStored[i] = 0; 
     }
  }

/*
  //serial printing
  Serial.print('A');
  delay(100);
  for(contador=0;contador<=7;contador++) {
    Serial.print(val[contador]);
    delay(100);
  }
  Serial.println();*/

}
