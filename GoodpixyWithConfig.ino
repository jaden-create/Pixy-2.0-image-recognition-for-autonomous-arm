
#include <Pixy2.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int column1 = 14;
int column2 = 58;
int column3 = 120;
int column4 = 188;
int column5 = 255;
int column6 = 301;

int rowDivide = 120; // where the row divides


int threshold = 50; // how much different from test points a ball can be, default 30


int reader = 0;
int p = 1;
// This is the main Pixy object
Pixy2 pixy;
int row1type[6] = {0, 0, 0, 0, 0, 0};
int row2type[6] = {0, 0, 0, 0, 0, 0};
String lcdRow1;
String lcdRow2;

void setup()
{


  Serial.begin(9600);

  pixy.init();

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2, 0);
  lcd.print("Hello");

  lcd.setCursor(2, 1);
  lcd.print("Initializing...");
}



void loop() {
  int i;

  if (Serial.available() > 1) {
    for (i = 0; i < 6; i++) {
      row1type[i] = 0;
      row2type[i] = 0;
    }



    pixy.ccc.getBlocks();

    if (pixy.ccc.numBlocks)
    {
      for (i = 0; i < pixy.ccc.numBlocks; i++)
      {
        point_assign(pixy.ccc.blocks[i].m_x, pixy.ccc.blocks[i].m_y, pixy.ccc.blocks[i].m_signature);




      }

    }
    printRows();
    reader = Serial.read();
    reader = Serial.read();
  }

}





void point_assign(int x, int y, int type) {
  if (y > rowDivide) { //if bottom row
    if ((x > (column1 - threshold)) && (x < (column1 + threshold))) { // if r2c1
      row2type[0] = type;
    }
    else if ((x > (column2 - threshold)) && (x < (column2 + threshold))) { // if r2c2
      row2type[1] = type;
    }
    else if ((x > (column3 - threshold)) && (x < (column3 + threshold))) { // if r2c3
      row2type[2] = type;
    }
    else if ((x > (column4 - threshold)) && (x < (column4 + threshold))) { // if r2c4
      row2type[3] = type;
    }
    else if ((x > (column5 - threshold)) && (x < (column5 + threshold))) { // if r2c5
      row2type[4] = type;
    }
    else if ((x > (column6 - threshold)) && (x < (column6 + threshold))) { // if r2c6
      row2type[5] = type;
    }
  }
  else if (y < rowDivide) { //if bottom row
    if ((x > (column1 - threshold)) && (x < (column1 + threshold))) { // if r1c1
      row1type[0] = type;
    }
    else if ((x > (column2 - threshold)) && (x < (column2 + threshold))) { // if r1c2
      row1type[1] = type;
    }
    else if ((x > (column3 - threshold)) && (x < (column3 + threshold))) { // if r1c3
      row1type[2] = type;
    }
    else if ((x > (column4 - threshold)) && (x < (column4 + threshold))) { // if r1c4
      row1type[3] = type;
    }
    else if ((x > (column5 - threshold)) && (x < (column5 + threshold))) { // if r1c5
      row1type[4] = type;
    }
    else if ((x > (column6 - threshold)) && (x < (column6 + threshold))) { // if r1c6
      row1type[5] = type;
    }
  }




}








String typetrans(int type) {
  if (type == 1) {
    return ("Y");
  }
  else if (type == 2 || type == 3) {
    return ("T");
  }
  else {
    return ("X");
  }
}

void printRows() {
  lcdRow1 = "";
  lcdRow2 = "";
  Serial.print("\n");
  Serial.print("Row 1 corresponding types");
  for (int i = 0; i < 6; i++) {
    Serial.print(" ");
    Serial.print(typetrans(row1type[i]));
    lcdRow1 += " ";
    lcdRow1 += typetrans(row1type[i]);
  }
  Serial.print("\n");
  Serial.print("Row 2 corresponding types");
  for (int i = 0; i < 6; i++) {
    Serial.print(" ");
    Serial.print(typetrans(row2type[i]));
    lcdRow2 += " ";
    lcdRow2 += typetrans(row2type[i]);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lcdRow1);

  lcd.setCursor(0, 1);
  lcd.print(lcdRow2);
}
