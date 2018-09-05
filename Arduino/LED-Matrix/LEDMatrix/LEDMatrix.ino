//#define DEBUG_MODE

#define OFFSET_X_H_LOW 2
#define OFFSET_X_H_HIGH 0
#define OFFSET_X_MIN_LOW 12
#define OFFSET_X_MIN_HIGH 8
#define BOX_WIDTH 15

char printStringX = 0; //offset of panelarray window
char mode = 'T'; //current mode(display time or text)
char status = 'Y'; //current status (on or off)

char command, modeRead;
char timestamp_array[32];
char string_array[30];
char panel_array[8][30 * 4];
unsigned long timestamp = 0;
int hours = 0;
int minutes = 0;

//arduino gpio connected with SH_CP of 74HC595
int shiftPin1 = 5;
int shiftPin2 = 6;
int shiftPin3 = 7;
int shiftPin4 = 37;
int shiftPin5 = 3;
int shiftPin6 = 4;
int shiftPin7 = 41;
int shiftPin8 = 39;
int shiftPin9 = 35;
int shiftPin10 = 43;
int shiftPin11 = 47;
int shiftPin12 = 45;
int shiftPin13 = 53;
int shiftPin14 = 51;
int shiftPin15 = 49;

//arduino gpio connected with ST_CP of 74HC595
int storePin = 12;

//arduino gpio connected with DS of 74HC595
int dataPin1 = 22;
int dataPin2 = 24;
int dataPin3 = 26;
int dataPin4 = 50;
int dataPin5 = 48;
int dataPin6 = 46;
int dataPin7 = 44;
int dataPin8 = 42;
int dataPin9 = 40;
int dataPin10 = 38;
int dataPin11 = 36;
int dataPin12 = 34;
int dataPin13 = 32;
int dataPin14 = 30;
int dataPin15 = 28;

char panel[8][15] = { // (Y,X)
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  pinMode(storePin, OUTPUT);

  pinMode(shiftPin1, OUTPUT);
  pinMode(shiftPin2, OUTPUT);
  pinMode(shiftPin3, OUTPUT);
  pinMode(shiftPin4, OUTPUT);
  pinMode(shiftPin5, OUTPUT);
  pinMode(shiftPin6, OUTPUT);
  pinMode(shiftPin7, OUTPUT);
  pinMode(shiftPin8, OUTPUT);
  pinMode(shiftPin9, OUTPUT);
  pinMode(shiftPin10, OUTPUT);
  pinMode(shiftPin11, OUTPUT);
  pinMode(shiftPin12, OUTPUT);
  pinMode(shiftPin13, OUTPUT);
  pinMode(shiftPin14, OUTPUT);
  pinMode(shiftPin15, OUTPUT);

  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(dataPin4, OUTPUT);
  pinMode(dataPin5, OUTPUT);
  pinMode(dataPin6, OUTPUT);
  pinMode(dataPin7, OUTPUT);
  pinMode(dataPin8, OUTPUT);
  pinMode(dataPin9, OUTPUT);
  pinMode(dataPin10, OUTPUT);
  pinMode(dataPin11, OUTPUT);
  pinMode(dataPin12, OUTPUT);
  pinMode(dataPin13, OUTPUT);
  pinMode(dataPin14, OUTPUT);
  pinMode(dataPin15, OUTPUT);

#ifdef DEBUG_MODE
  Serial.println("Finished setup!");
#endif

  printPanel();
}

void calcTime(long timestamp) {
  int tmp_hours, tmp_minutes;
  tmp_hours = (timestamp  % 86400L) / 3600;
  tmp_minutes = (timestamp  % 3600) / 60;

  if (tmp_hours != 12) {
    tmp_hours = tmp_hours % 12;
    if (hours == tmp_hours || (hours + 1) == tmp_hours && tmp_minutes == 0 && minutes == 59 || hours == 0) { // time cant decrease if its not 12o´clock
      hours = tmp_hours;
      minutes = tmp_minutes;
    }
  }
#ifdef DEBUG_MODE
  Serial.println(hours);
  Serial.println(minutes);
#endif
}


void printDisplay() {
  if (status == 'Y') { //on
    if (mode == 'T') {
      printTime();
#ifdef DEBUG_MODE
      Serial.println("Going to print the time!");
#endif
    } else if (mode == 'S') {
      printString();
#ifdef DEBUG_MODE
      Serial.println("Going to print the String!");
#endif
    } else {
#ifdef DEBUG_MODE
      Serial.println("No valid mode - display time!");
#endif
    }
  } else { // off
    //clear panel
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 15; x++) {
        panel[y][x] = 0;
      }
    }
    printPanel();
  }
#ifdef DEBUG_MODE
  Serial.println("");
#endif
}

void loop() {
  int count = Serial1.available(); //serial with wemos d1

  if (count) {
#ifdef DEBUG_MODE
    Serial.print("In mode: ");
    Serial.println(mode);
#endif

    command = Serial1.read();

#ifdef DEBUG_MODE
    Serial.print("New Command: ");
    Serial.println(command);
#endif

    switch (command) {
      case 'T':
        for (int i = count - 2; i >= 0; i--) {
          timestamp_array[i] = Serial1.read();
#ifdef DEBUG_MODE
          Serial.print(timestamp_array[i]);
#endif
        }

        timestamp = 0;

        for (int i = 0; i < 32; i++) {
          timestamp = (long)timestamp + (long)((long)timestamp_array[i] << i);
        }

        calcTime(timestamp);

        break;

      case 'M':
        modeRead = Serial1.read();
        switch (modeRead) {
          case  'T':
            mode = 'T';
            break;
          case  'S':
            mode = 'S';
            break;
          case  'X':
            status = 'X';
            break;
          case  'Y':
            status = 'Y';
            break;
        }

#ifdef DEBUG_MODE
        Serial.print("Read new Mode :");
        Serial.println(mode);
        Serial.print("Status :");
        Serial.println(status);
#endif

        break;

      case 'S':
#ifdef DEBUG_MODE
        Serial.println("Got a new String!");
#endif

        //clear old string
        for (int i = 0; i < 30; i++) {
          string_array[i] = '*';
        }

        int char_amount = 0;

        //get new string
        for (int i = count - 2; i >= 0; i--) {
          string_array[i] = Serial1.read();
          char_amount++;
        }

        //reverse the mirroring effect of sending
        char string_array_tmp[30];
        for (int x = 0 - 1; x < 30; x++) {
          string_array_tmp[x] = '*';
        }

        int invert = 0;
        for (int x = char_amount - 1; x >= 0; x--) {
          string_array_tmp[invert] = string_array[x];
          invert++;
        }

        for (int x = 0; x < 30; x++) {
          string_array[x] = string_array_tmp[x];
        }

        break;
    }
    printDisplay();
  }
  delay(500);
}
