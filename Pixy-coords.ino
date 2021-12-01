
#include <Pixy2.h>

int reader = 0;
int p = 1;
String row1[] = {"x","x","x","x","x","x"};
String row2[] = {"x","x","x","x","x","x"};
// This is the main Pixy object
Pixy2 pixy;

void setup()
{
  Serial.begin(9600);

  pixy.init();

}



void loop() {
  int i;


    if (Serial.available() > 1) {
      pixy.ccc.getBlocks();

      if (pixy.ccc.numBlocks)
      {
        for (i = 0; i < pixy.ccc.numBlocks; i++)
        {
          if (pixy.ccc.blocks[i].m_signature == 1) {
            //Serial.print("Yellow ");
          }
          Serial.print(pixy.ccc.blocks[i].m_x);
          Serial.print(" ");
          Serial.println(pixy.ccc.blocks[i].m_y);

        }

      }
      reader = Serial.read();
      reader = Serial.read();
    }

  }

void plot(int type, int x, int y){

  
  
  
  }
