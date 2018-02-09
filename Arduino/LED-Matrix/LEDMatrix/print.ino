void printPanel(){
    int column1[8] = {panel[0][0],panel[1][0],panel[2][0],panel[3][0],panel[4][0],panel[5][0],panel[6][0],panel[7][0]};
    int column2[8] = {panel[0][1],panel[1][1],panel[2][1],panel[3][1],panel[4][1],panel[5][1],panel[6][1],panel[7][1]};
    int column3[8] = {panel[0][2],panel[1][2],panel[2][2],panel[3][2],panel[4][2],panel[5][2],panel[6][2],panel[7][2]};
    int column4[8] = {panel[0][3],panel[1][3],panel[2][3],panel[3][3],panel[4][3],panel[5][3],panel[6][3],panel[7][3]};
    int column5[8] = {panel[0][4],panel[1][4],panel[2][4],panel[3][4],panel[4][4],panel[5][4],panel[6][4],panel[7][4]};
    int column6[8] = {panel[0][5],panel[1][5],panel[2][5],panel[3][5],panel[4][5],panel[5][5],panel[6][5],panel[7][5]};
    int column7[8] = {panel[0][6],panel[1][6],panel[2][6],panel[3][6],panel[4][6],panel[5][6],panel[6][6],panel[7][6]};
    int column8[8] = {panel[0][7],panel[1][7],panel[2][7],panel[3][7],panel[4][7],panel[5][7],panel[6][7],panel[7][7]};
    int column9[8] = {panel[0][8],panel[1][8],panel[2][8],panel[3][8],panel[4][8],panel[5][8],panel[6][8],panel[7][8]};
    int column10[8] = {panel[0][9],panel[1][9],panel[2][9],panel[3][9],panel[4][9],panel[5][9],panel[6][9],panel[7][9]};
    int column11[8] = {panel[0][10],panel[1][10],panel[2][10],panel[3][10],panel[4][10],panel[5][10],panel[6][10],panel[7][10]};
    int column12[8] = {panel[0][11],panel[1][11],panel[2][11],panel[3][11],panel[4][11],panel[5][11],panel[6][11],panel[7][11]};
    int column13[8] = {panel[0][12],panel[1][12],panel[2][12],panel[3][12],panel[4][12],panel[5][12],panel[6][12],panel[7][12]};
    int column14[8] = {panel[0][13],panel[1][13],panel[2][13],panel[3][13],panel[4][13],panel[5][13],panel[6][13],panel[7][13]};
    int column15[8] = {panel[0][14],panel[1][14],panel[2][14],panel[3][14],panel[4][14],panel[5][14],panel[6][14],panel[7][14]};
    
   digitalWrite(storePin, LOW);

   for (int i=7; i>=0; i--){
    digitalWrite(shiftPin1, LOW);
    digitalWrite(shiftPin2, LOW);
    digitalWrite(shiftPin3, LOW);
    digitalWrite(shiftPin4, LOW);
    digitalWrite(shiftPin5, LOW);
    digitalWrite(shiftPin6, LOW);
    digitalWrite(shiftPin7, LOW);
    digitalWrite(shiftPin8, LOW);
    digitalWrite(shiftPin9, LOW);
    digitalWrite(shiftPin10, LOW);
    digitalWrite(shiftPin11, LOW);
    digitalWrite(shiftPin12, LOW);
    digitalWrite(shiftPin13, LOW);
    digitalWrite(shiftPin14, LOW);
    digitalWrite(shiftPin15, LOW);
    
    digitalWrite(dataPin1, column1[i]);
    digitalWrite(dataPin2, column2[i]);
    digitalWrite(dataPin3, column3[i]);
    digitalWrite(dataPin4, column4[i]);
    digitalWrite(dataPin5, column5[i]);
    digitalWrite(dataPin6, column6[i]);
    digitalWrite(dataPin7, column7[i]);
    digitalWrite(dataPin8, column8[i]);
    digitalWrite(dataPin9, column9[i]);
    digitalWrite(dataPin10, column10[i]);
    digitalWrite(dataPin11, column11[i]);
    digitalWrite(dataPin12, column12[i]);
    digitalWrite(dataPin13, column13[i]);
    digitalWrite(dataPin14, column14[i]);
    digitalWrite(dataPin15, column15[i]);
                
    digitalWrite(shiftPin1, HIGH);
    digitalWrite(shiftPin2, HIGH);
    digitalWrite(shiftPin3, HIGH);
    digitalWrite(shiftPin4, HIGH);
    digitalWrite(shiftPin5, HIGH);
    digitalWrite(shiftPin6, HIGH);
    digitalWrite(shiftPin7, HIGH);
    digitalWrite(shiftPin8, HIGH);
    digitalWrite(shiftPin9, HIGH);
    digitalWrite(shiftPin10, HIGH);
    digitalWrite(shiftPin11, HIGH);
    digitalWrite(shiftPin12, HIGH);
    digitalWrite(shiftPin13, HIGH);
    digitalWrite(shiftPin14, HIGH);
    digitalWrite(shiftPin15, HIGH);
   }
   
   digitalWrite(storePin, HIGH);
}

void printString(){

  //Clear panel
  for(int y=0; y<8;y++){
    for(int x=0;x<15;x++){
      panel[y][x]=0;
    }
  }
  
  //Clear panel_array
  for(int y=0; y<8;y++){
    for(int x=0;x<(30*4);x++){
      panel_array[y][x]=0;
    }
  }

  int char_amount = 0;
  
  //Count panel chars
  for(int x=0;x<29;x++){
    if(string_array[x] != '*'){ // * is the default char
       char_amount++; 
    }
  }

  Serial.print("Amount of chars: ");
  Serial.println(char_amount);

  Serial.print("String: ");  
  for(int x=0;x<29;x++){
    if(string_array[x] != '*'){ // * is the default char
       Serial.print(string_array[x]); 
    }
  }
  Serial.println("");

  // Fill Panel
  int offset_big_char = 0; 
  for(int y=0;y<char_amount;y++){

    int x = (y*4)+offset_big_char;
  
    if(x+5<(30*4)){ //Does the biggest char fit?
      switch(string_array[y]){
                  case 'a':
                  case 'A':
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
                        
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;  
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        
                        break;
                  case 'b':
                  case 'B':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
                        
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;  
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
  
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                        
                  case 'c':
                  case 'C': 
                        
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        
                        panel_array[1][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        
                        panel_array[0][x+1]=1;
                        panel_array[7][x+1]=1;
                        
                        break;
                        
                  case 'd':
                  case 'D':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
                        
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;  
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        
                        panel_array[0][x+1]=1;
                        panel_array[7][x+1]=1;
                        
                        break;
                        
                  case 'e':
                  case 'E': 
  
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
                        
                        panel_array[0][x+2]=1;  
                        panel_array[3][x+2]=1;  
                        panel_array[7][x+2]=1;  
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                        
                  case 'f':
                  case 'F':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
                        
                        panel_array[0][x+2]=1;  
                        panel_array[3][x+2]=1;  
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                       
                        break;
                        
                  case 'g':
                  case 'G': 
                  
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
  
                        panel_array[1][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
  
                        panel_array[0][x+1]=1;
                        panel_array[4][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                        
                  case 'h':
                  case 'H':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1; 
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[3][x+1]=1;
                        
                        break;
                  
                  case 'i':
                  case 'I': 
                        panel_array[0][x+1]=1; 
                        panel_array[1][x+1]=1;  
                        panel_array[2][x+1]=1;  
                        panel_array[3][x+1]=1;
                        panel_array[4][x+1]=1; 
                        panel_array[5][x+1]=1;  
                        panel_array[6][x+1]=1;  
                        panel_array[7][x+1]=1; 
                        break;
                        
                  case 'j':
                  case 'J':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[6][x]=1;  
  
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
  
                        panel_array[0][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                        
                  case 'k':
                  case 'K': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;  
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[3][x+1]=1;
                        break;
                  
                  case 'l':
                  case 'L':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
   
                        panel_array[7][x+2]=1;
  
                        panel_array[7][x+1]=1;
                        break;
                        
                  case 'm':
                  case 'M': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[1][x+1]=1;
                        panel_array[2][x+1]=1;
                        
                        break;
                  
                  case 'n':
                  case 'N':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+3]=1;
                        panel_array[1][x+3]=1;  
                        panel_array[2][x+3]=1;
                        panel_array[3][x+3]=1;
                        panel_array[4][x+3]=1; 
                        panel_array[5][x+3]=1;  
                        panel_array[6][x+3]=1;  
                        panel_array[7][x+3]=1;
  
                        panel_array[3][x+1]=1;
                        panel_array[4][x+2]=1;
                     
                        offset_big_char++;
                        
                        break;
                  
                  case 'o':
                  case 'O': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                  
                  case 'p':
                  case 'P':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[1][x+2]=1;
                        panel_array[2][x+2]=1;
  
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        break;                     
                  
                  case 'q':
                  case 'Q': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[7][x+1]=1;
                        
                        panel_array[7][x+3]=1;
                        offset_big_char++;
                        break;
                        
                  case 'r':
                  case 'R':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
                        
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                  
                        break;
                  
                  case 's':
                  case 'S': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
   
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
  
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                   
                   case 't':
                   case 'T':
                        panel_array[0][x]=1;
                        
                        panel_array[0][x+2]=1;
                        
                        panel_array[0][x+1]=1; 
                        panel_array[1][x+1]=1;  
                        panel_array[2][x+1]=1;  
                        panel_array[3][x+1]=1;
                        panel_array[4][x+1]=1; 
                        panel_array[5][x+1]=1;  
                        panel_array[6][x+1]=1;  
                        panel_array[7][x+1]=1; 
                        break;
                  
                  case 'u':
                  case 'U': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[7][x+1]=1;
                        break;
                  
                  case 'v':
                  case 'V':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        
  
                        panel_array[7][x+1]=1;
                        break;
                        
                  case 'w':
                  case 'W': 
                        panel_array[0][x]=1;
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;
                        panel_array[3][x]=1;
                        panel_array[4][x]=1;  
                        panel_array[5][x]=1;
                        panel_array[6][x]=1;  
                         
                        panel_array[7][x+1]=1;  

                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;    
                        panel_array[6][x+2]=1;    
                        
                        panel_array[7][x+3]=1;  
             
                        panel_array[0][x+4]=1;
                        panel_array[1][x+4]=1;  
                        panel_array[2][x+4]=1;
                        panel_array[3][x+4]=1;
                        panel_array[4][x+4]=1;
                        panel_array[5][x+4]=1;
                        panel_array[6][x+4]=1;
                          
                        offset_big_char =offset_big_char+2;
                        break;                      
                  
                  case 'x':
                  case 'X': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[3][x+1]=1;
                        break;
                  
                  case 'y':
                  case 'Y':
                        panel_array[0][x]=1;
                        panel_array[1][x]=1;
                        
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;
                         
                        panel_array[2][x+1]=1;  
                        panel_array[3][x+1]=1;
                        panel_array[4][x+1]=1; 
                        panel_array[5][x+1]=1;  
                        panel_array[6][x+1]=1;  
                        panel_array[7][x+1]=1;
                        break;
                  
                  case 'z':
                  case 'Z': 
                        panel_array[0][x]=1; 
                        panel_array[5][x]=1;
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1; 
  
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1; 
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[4][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                  
                  case '0': 
                      
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                      
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                     
                        panel_array[0][x+1]=1;
                        panel_array[7][x+1]=1;
                  
                        break;
                  case '1': 
                       
                        panel_array[2][x]=1;  
                        
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[1][x+1]=1;
  
                        break;
                        
                  case '2':
  
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;  
                        panel_array[3][x+2]=1;
                        panel_array[7][x+2]=1; 
  
                        panel_array[0][x]=1;
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                        panel_array[7][x]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[4][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                  case '3': 
                        panel_array[0][x]=1; 
                        panel_array[3][x]=1;
                        panel_array[7][x]=1; 
                        
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        
                        break;
                  case '4':
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                     
                        panel_array[0][x+2]=1;
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[3][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                        panel_array[7][x+2]=1;
  
                        panel_array[3][x+1]=1;
                        break;
                  case '5': 
                        panel_array[0][x]=1; 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[6][x]=1;  
  
                        panel_array[0][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
  
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                  case '6': 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[3][x]=1;
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                      
                        panel_array[1][x+2]=1;  
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                     
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;                      
                        panel_array[7][x+1]=1;
                        break;
                        
                  case '7': 
                        panel_array[0][x]=1;
                        panel_array[1][x]=1;
                        
                        panel_array[0][x+2]=1;
                        panel_array[4][x+2]=1;
                        panel_array[5][x+2]=1;
                        panel_array[6][x+2]=1;
                        panel_array[7][x+2]=1;
                         
                        panel_array[0][x+1]=1;  
                        panel_array[1][x+1]=1;
                        panel_array[2][x+1]=1; 
                        panel_array[3][x+1]=1;  
  
                        break; 
                  case '8':
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[4][x]=1; 
                        panel_array[5][x]=1;  
                        panel_array[6][x]=1;  
                      
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                     
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                  case '9': 
                        panel_array[1][x]=1;  
                        panel_array[2][x]=1;  
                        panel_array[6][x]=1;  
                      
                        panel_array[1][x+2]=1;  
                        panel_array[2][x+2]=1;
                        panel_array[4][x+2]=1; 
                        panel_array[5][x+2]=1;  
                        panel_array[6][x+2]=1;  
                     
                        panel_array[0][x+1]=1;
                        panel_array[3][x+1]=1;
                        panel_array[7][x+1]=1;
                        break;
                  case ' ': //nothing
  
                        break;
                  default: 
                        Serial.println("Char nicht erkannt!");
                        break;                       
       }
      }

     
    }
  //Fill Panel with current window
      
  for(int y=0; y<8;y++){
    for(int x=0;x<15;x++){
      panel[y][x]=panel_array[y][(x+printStringX)%((char_amount*4+(offset_big_char+4)))];;
    }
  }

  printStringX++; //Window will slide 

  if(printStringX>(30*4)){ // When end is reached, reset!
    printStringX =0;
  }

  //Print panel
  printPanel();
}

void printTime(){

  for(int y=0; y<8;y++){
    for(int x=0;x<15;x++){
      panel[y][x]=0;
    }
  }
  
  switch(hours){
    case 0: print0(OFFSET_X_H_LOW);     
            break;
        
    case 1: print1(OFFSET_X_H_LOW);   
            break;
           
    case 2: print2(OFFSET_X_H_LOW);
            break;
           
    case 3: print3(OFFSET_X_H_LOW);
            break;
           
    case 4: print4(OFFSET_X_H_LOW);
            break;
           
    case 5: print5(OFFSET_X_H_LOW);
            break;
           
    case 6: print6(OFFSET_X_H_LOW);
            break;
           
    case 7: print7(OFFSET_X_H_LOW);
            break;
           
    case 8: print8(OFFSET_X_H_LOW);
            break;
           
    case 9: print9(OFFSET_X_H_LOW);
            break;
           
    case 10: panel[0][OFFSET_X_H_HIGH] = 1;
             panel[1][OFFSET_X_H_HIGH] = 1;
             panel[2][OFFSET_X_H_HIGH] = 1;
             panel[3][OFFSET_X_H_HIGH] = 1;
             panel[4][OFFSET_X_H_HIGH] = 1;
             panel[5][OFFSET_X_H_HIGH] = 1;
             panel[6][OFFSET_X_H_HIGH] = 1;
             panel[7][OFFSET_X_H_HIGH] = 1;
             print0(OFFSET_X_H_LOW);
             break;
           
    case 11: panel[0][OFFSET_X_H_HIGH] = 1;
             panel[1][OFFSET_X_H_HIGH] = 1;
             panel[2][OFFSET_X_H_HIGH] = 1;
             panel[3][OFFSET_X_H_HIGH] = 1;
             panel[4][OFFSET_X_H_HIGH] = 1;
             panel[5][OFFSET_X_H_HIGH] = 1;
             panel[6][OFFSET_X_H_HIGH] = 1;
             panel[7][OFFSET_X_H_HIGH] = 1;
             
             panel[0][OFFSET_X_H_LOW+1] = 1;
             panel[1][OFFSET_X_H_LOW+1] = 1;
             panel[2][OFFSET_X_H_LOW+1] = 1;
             panel[3][OFFSET_X_H_LOW+1] = 1;
             panel[4][OFFSET_X_H_LOW+1] = 1;
             panel[5][OFFSET_X_H_LOW+1] = 1;
             panel[6][OFFSET_X_H_LOW+1] = 1;
             panel[7][OFFSET_X_H_LOW+1] = 1;
             break;
           
    case 12: panel[0][OFFSET_X_H_HIGH] = 1;
             panel[1][OFFSET_X_H_HIGH] = 1;
             panel[2][OFFSET_X_H_HIGH] = 1;
             panel[3][OFFSET_X_H_HIGH] = 1;
             panel[4][OFFSET_X_H_HIGH] = 1;
             panel[5][OFFSET_X_H_HIGH] = 1;
             panel[6][OFFSET_X_H_HIGH] = 1;
             panel[7][OFFSET_X_H_HIGH] = 1;
             print2(OFFSET_X_H_LOW);
             break;
  }

  // :
  panel[2][6]= 1;  
  panel[5][6]= 1;  

  switch(minutes/10){
    case 0: print0(OFFSET_X_MIN_HIGH);
            break;
            
    case 1: print1(OFFSET_X_MIN_HIGH);
            break;
           
    case 2: print2(OFFSET_X_MIN_HIGH);
            break;
           
    case 3: print3(OFFSET_X_MIN_HIGH);
            break;
           
    case 4: print4(OFFSET_X_MIN_HIGH);
            break;
           
    case 5: print5(OFFSET_X_MIN_HIGH);
            break;
  }

  switch(minutes%10){
    case 0: print0(OFFSET_X_MIN_LOW);
            break;
            
    case 1: print1(OFFSET_X_MIN_LOW);
            break;
           
    case 2: print2(OFFSET_X_MIN_LOW);
            break;
           
    case 3: print3(OFFSET_X_MIN_LOW);
            break;
           
    case 4: print4(OFFSET_X_MIN_LOW);
            break;
           
    case 5: print5(OFFSET_X_MIN_LOW);
            break;
                      
    case 6: print6(OFFSET_X_MIN_LOW);
            break;
                      
    case 7: print7(OFFSET_X_MIN_LOW);
            break;
                      
    case 8: print8(OFFSET_X_MIN_LOW);
            break;
                      
    case 9: print9(OFFSET_X_MIN_LOW);
            break;
  }
  printPanel();
}

void print0(int offset){
  panel[0][offset] = 1;
  panel[1][offset] = 1;
  panel[2][offset] = 1;
  panel[3][offset] = 1;
  panel[4][offset] = 1;
  panel[5][offset] = 1;
  panel[6][offset] = 1;
  panel[7][offset] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
  panel[0][offset+1] = 1;
  panel[7][offset+1] = 1;   
}

void print1(int offset){
  panel[2][offset] = 1;
  panel[1][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
}

void print2(int offset){
  panel[0][offset] = 1;
  panel[3][offset] = 1;
  panel[4][offset] = 1;
  panel[5][offset] = 1;
  panel[6][offset] = 1;
  panel[7][offset] = 1;
  panel[0][offset+1] = 1;
  panel[3][offset+1] = 1;
  panel[7][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[7][offset+2] = 1;

}

void print3(int offset){
  panel[0][offset] = 1;
  panel[3][offset] = 1;
  panel[7][offset] = 1;
  panel[0][offset+1] = 1;
  panel[3][offset+1] = 1;
  panel[7][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
}

void print4(int offset){
  panel[0][offset] = 1;
  panel[1][offset] = 1;
  panel[2][offset] = 1;
  panel[3][offset] = 1;
  panel[4][offset] = 1;
  panel[4][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
}

void print5(int offset){
  panel[0][offset] = 1;
  panel[1][offset] = 1;
  panel[2][offset] = 1;
  panel[3][offset] = 1;
  panel[7][offset] = 1;
  panel[0][offset+1] = 1;
  panel[3][offset+1] = 1;
  panel[7][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
}

void print6(int offset){
  panel[0][offset] = 1;
  panel[1][offset] = 1;
  panel[2][offset] = 1;
  panel[3][offset] = 1;
  panel[4][offset] = 1;
  panel[5][offset] = 1;
  panel[6][offset] = 1;
  panel[7][offset] = 1; 
  panel[0][offset+1] = 1;
  panel[4][offset+1] = 1;
  panel[7][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
}

void print7(int offset){
  panel[0][offset] = 1;
  panel[0][offset+1] = 1;
  panel[4][offset+1] = 1;
  panel[5][offset+1] = 1;
  panel[6][offset+1] = 1;
  panel[7][offset+1] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
}

void print8(int offset){
  panel[0][offset] = 1;
  panel[1][offset] = 1;
  panel[2][offset] = 1;
  panel[3][offset] = 1;
  panel[4][offset] = 1;
  panel[5][offset] = 1;
  panel[6][offset] = 1;
  panel[7][offset] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
  panel[0][offset+1] = 1;
  panel[3][offset+1] = 1; 
  panel[7][offset+1] = 1;   
}

void print9(int offset){
  panel[0][offset] = 1;
  panel[1][offset] = 1;
  panel[2][offset] = 1;
  panel[3][offset] = 1;
  panel[7][offset] = 1;
  panel[0][offset+2] = 1;
  panel[1][offset+2] = 1;
  panel[2][offset+2] = 1;
  panel[3][offset+2] = 1;
  panel[4][offset+2] = 1;
  panel[5][offset+2] = 1;
  panel[6][offset+2] = 1;
  panel[7][offset+2] = 1;
  panel[0][offset+1] = 1;
  panel[3][offset+1] = 1; 
  panel[7][offset+1] = 1;   
}
