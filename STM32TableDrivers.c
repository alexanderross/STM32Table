/**
  ******************************************************************************
  * @file    table.c
  * @author  OneSeventyFour
  * @version V1. 2. 0
  * @date    08-August-2011
  * @brief   Main table drivers
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
 int primaryAll[16][4];
 int primaryActual[8][8];
 int primaryRed[8][8];
 int primaryGrn[8][8];
 int primaryBlu[8][8];
   int redRows[8];
  int greenRows[8];
  int blueRows[8];

 int mode;
 uint16_t redSerial = GPIO_Pin_3;
 uint16_t greenSerial = GPIO_Pin_2;
 uint16_t blueSerial = GPIO_Pin_1;
 uint16_t gndSerial = GPIO_Pin_5;
 uint16_t rgbClock = GPIO_Pin_7;
 uint16_t gndClock = GPIO_Pin_8;
 uint16_t rgbLatch = GPIO_Pin_6;
 uint16_t gndLatch = GPIO_Pin_0;
 uint16_t outEnable = GPIO_Pin_4;


void initialize(){

            
     
        primaryAll[0][0]=0;
        primaryAll[1][0]=1UL;
        primaryAll[2][0]=7UL;
        primaryAll[3][0]=7UL;
        primaryAll[4][0]=7UL;
        primaryAll[5][0]=7UL;
        primaryAll[6][0]=7UL;
        primaryAll[7][0]=7UL;
        primaryAll[8][0]=7UL;
        primaryAll[9][0]=7UL;
        primaryAll[10][0]=7UL;
        primaryAll[11][0]=7UL;
        primaryAll[12][0]=7UL;
        primaryAll[13][0]=7UL;
        primaryAll[14][0]=7UL;
        primaryAll[15][0]=0;

           primaryAll[0][1]=0;
        primaryAll[1][1]=1UL;
        primaryAll[2][1]=7UL;
        primaryAll[3][1]=7UL;
        primaryAll[4][1]=7UL;
        primaryAll[5][1]=7UL;
        primaryAll[6][1]=7UL;
        primaryAll[7][1]=7UL;
        primaryAll[8][1]=7UL;
        primaryAll[9][1]=7UL;
        primaryAll[10][1]=7UL;
        primaryAll[11][1]=7UL;
        primaryAll[12][1]=7UL;
        primaryAll[13][1]=7UL;
        primaryAll[14][1]=7UL;
        primaryAll[15][1]=0;  

          primaryAll[0][2]=0;
        primaryAll[1][2]=1UL;
        primaryAll[2][2]=7UL;
        primaryAll[3][2]=7UL;
        primaryAll[4][2]=7UL;
        primaryAll[5][2]=7UL;
        primaryAll[6][2]=7UL;
        primaryAll[7][2]=7UL;
        primaryAll[8][2]=7UL;
        primaryAll[9][2]=7UL;
        primaryAll[10][2]=7UL;
        primaryAll[11][2]=7UL;
        primaryAll[12][2]=7UL;
        primaryAll[13][2]=7UL;
        primaryAll[14][2]=7UL;
        primaryAll[15][2]=0;

         primaryAll[0][3]=0;
        primaryAll[1][3]=1UL;
        primaryAll[2][3]=7UL;
        primaryAll[3][3]=7UL;
        primaryAll[4][3]=7UL;
        primaryAll[5][3]=7UL;
        primaryAll[6][3]=7UL;
        primaryAll[7][3]=7UL;
        primaryAll[8][3]=7UL;
        primaryAll[9][3]=7UL;
        primaryAll[10][3]=7UL;
        primaryAll[11][3]=7UL;
        primaryAll[12][3]=7UL;
        primaryAll[13][3]=7UL;
        primaryAll[14][3]=7UL;
        primaryAll[15][3]=0;

		redRows[0] = 255UL;
		redRows[1] = 245UL;
		redRows[2] = 215UL;
		redRows[3] = 1UL;
		redRows[4] = 232UL;
		redRows[5] = 12UL;
		redRows[6] = 242UL;
		redRows[7] = 112UL;

		blueRows[0] = 163UL;
		blueRows[1] = 124UL;
		blueRows[2] = 25UL;
		blueRows[3] = 1UL;
		blueRows[4] = 26UL;
		blueRows[5] = 35UL;
		blueRows[6] = 66UL;
		blueRows[7] = 255UL;

		greenRows[0] = 125UL;
		greenRows[1] = 135UL;
		greenRows[2] = 145UL;
		greenRows[3] = 1UL;
		greenRows[4] = 255UL;
		greenRows[5] = 255UL;
		greenRows[6] = 255UL;
		greenRows[7] = 255UL;

}
/*
 Split Colors takes the 16x4 composite matrix and decodes the color digit.
 We can use logical OR with the whole binary thing to eliminate the need for an intense switch/ifelse statement. 
 While populating the 8x8 "actual" (By actual i mean how it will actually be fed into the shift registers) color arrays, we
 will also populate the primaryActual array, which is used later to determine whether to trigger the grounding register for a row sweep. 


*/
void splitColors(){
int i=0;
int t=0;
int currentActual=0;// Synthetic for referencing a 16x4 as an 8x8.. mainly to chop the 16 in half. Only changed on even increments... duh. 
//SIGNAL BITS
// 000
// RGB
//0-OFF 1-B; 2-G; 3-GB; 4-R;5-RB; 6-RG; 7-RGB
     for(i=0;i<16;i++){
         for(t=0;t<4;t++){
           if(primaryAll[i][t] & 4 == 4){
                if(i%2==0){
                    currentActual=i/2;
                       primaryRed[currentActual][t*2]=1;
                    primaryActual[currentActual][t*2]= primaryAll[i][t];
                }else{
                    primaryRed[currentActual][(t*2)+1]=1;
                    primaryActual[currentActual][(t*2)+1]= primaryAll[i][t];
                }
           }
           if(primaryAll[i][t] & 2 == 2){
                    if(i%2==0){
                    currentActual=i/2;
                       primaryGrn[currentActual][t*2]=1;
                    primaryActual[currentActual][t*2]= primaryAll[i][t];
                }else{
                    primaryGrn[currentActual][(t*2)+1]=1;
                    primaryActual[currentActual][(t*2)+1]= primaryAll[i][t];
                }
           }
           if(primaryAll[i][t] & 1 == 1){
                if(i%2==0){
                    currentActual=i/2;
                       primaryBlu[currentActual][t*2]=1;
                    primaryActual[currentActual][t*2]= primaryAll[i][t];

                }else{
                    primaryBlu[currentActual][(t*2)+1]=1;
                    primaryActual[currentActual][(t*2)+1]= primaryAll[i][t];
                }
           }
        }
     }
}

void shiftMap(int type){
}


void fillRegisters(){
int i,t=0;
int focus=1;
     for(i=0;i<8;i++){//Sweeping gnd channels 
		 t=0;
         for(t=0;t<8;t++){ // Sweeping RGB channels. For each sweep activation, also sweep the gnd while RGN is active
              GPIO_ResetBits(GPIOA,rgbClock|rgbLatch);//Clock Low
             if(redRows[i] & 1<<t){
                GPIO_SetBits(GPIOA,redSerial);
                 }else{
                GPIO_ResetBits(GPIOA,redSerial);
                 }
            if((greenRows[i] & 1UL<<t)){
                GPIO_SetBits(GPIOA,greenSerial);
                 }else{
                GPIO_ResetBits(GPIOA,greenSerial);
                 }
            if((blueRows[i] & 1UL<<t)){
                GPIO_SetBits(GPIOA,blueSerial);
                 }else{
                GPIO_ResetBits(GPIOA,blueSerial);
                 }            
            }
            GPIO_SetBits(GPIOA,rgbClock |rgbLatch);    //Clock High
     }                                                     
}

void createRows(){
  int i,t=0;
   for(i=0;i<8;i++){
           for(t=0;t<8;t++){
             //
             redRows[i] |= primaryRed[i][t]<<t;
             greenRows[i] |= primaryGrn[i][t]<<t;
             blueRows[i] |= primaryBlu[i][t]<<t;
        }
   }
}

/*
 *
 *   STANDALONE PATTERN FX
 *
 *
 */

void renderPatternUnifiedTrigger(int clockRefreshRate = 10000){
	int gndCount=0,rgbCount=0;
	int clocks=0;
	GPIO_SetBits(GPIOA,rgbLatch | gndLatch ); // Hold open the latches for more duty cycle on the LEDS

	//Ground sweep, which is different from an iteration, mind you.
			/* For each ground sweep, we must go through all 8 of the available voltage suppliers
			 * for the R, G and B LED's. We will reference the current global row array, and if the
			 * active bit is set, then we light the voltage rail for that row. The important thing is that
			 * any particular forward voltage rail NEVER supplies over 40ma (lights 2 LED's at once). This is because
			 * the max current for the 74HC shift register is 40ma, and noone wants to order another one of those.. :(
			 */
	while(1){
		clocks++;

		if(clocks % clockRefreshRate == 0){
			clocks=0;

			GPIO_ResetBits(GPIOA,gndClock |gndSerial);//Here we go... If ground needs to be fired, it's already set.

			for(rgbCount=0;rgbCount<7;rgbCount++){
				GPIO_ResetBits(GPIOA,rgbClock|redSerial|blueSerial|greenSerial);//Reset everything.

				if(redRows[gndCount] & 1UL << rgbCount > 0){ // We shift our "mask" over the desired value, and if it's good, we set the bit!
					GPIO_SetBits(GPIOA,redSerial);
				}

				if(greenRows[gndCount] & 1UL << rgbCount > 0){ // We shift our "mask" over the desired value, and if it's good, we set the bit!
								GPIO_SetBits(GPIOA,greenSerial);
							}

				if(blueRows[gndCount] & 1UL << rgbCount > 0){ // We shift our "mask" over the desired value, and if it's good, we set the bit!
								GPIO_SetBits(GPIOA,blueSerial);
				}

				GPIO_SetBits(GPIOA,rgbClock);//Whatever we want lit is set, fire the clock to cycle them into their registers


			}



			gndCount++;
			if(gndCount >=8){ // This is the last sweep, we must reset the ground count to set a new ground rail next cycle
				gndCount=0;
				GPIO_SetBits(GPIOA,gndSerial);//Set serial high, will activate rail next time around.
			}
			GPIO_SetBits(GPIOA,gndClock);// Post-set clock to unify cycle
		}//IF for clock refresh rate
	}//While
}

void renderPatternMixedTrigger(int clockRefreshRate = 10000){
	int gndCount=0,rgbCount=0;
	int clocks=0;
	GPIO_SetBits(GPIOA,rgbLatch | gndLatch ); // Hold open the latches for more duty cycle on the LEDS

	//Ground sweep, which is different from an iteration, mind you.
			/* For each ground sweep, we must go through all 8 of the available voltage suppliers
			 * for the R, G and B LED's. We will reference the current global row array, and if the
			 * active bit is set, then we light the voltage rail for that row. The important thing is that
			 * any particular forward voltage rail NEVER supplies over 40ma (lights 2 LED's at once). This is because
			 * the max current for the 74HC shift register is 40ma, and noone wants to order another one of those.. :(
			 */
	while(1){
		clocks++;

		if(clocks % clockRefreshRate == 0){
			clocks=0;

			GPIO_SetBits(GPIOA,gndClock);//Here we go... If ground needs to be fired, it's already set.

			for(rgbCount=0;rgbCount<7;rgbCount++){
				GPIO_ResetBits(GPIOA,rgbClock|redSerial|blueSerial|greenSerial);//Reset everything.

				if(redRows[gndCount] & 1UL << rgbCount > 0){ // We shift our "mask" over the desired value, and if it's good, we set the bit!
					GPIO_SetBits(GPIOA,redSerial);
				}

				if(greenRows[gndCount] & 1UL << rgbCount > 0){ // We shift our "mask" over the desired value, and if it's good, we set the bit!
								GPIO_SetBits(GPIOA,greenSerial);
							}

				if(blueRows[gndCount] & 1UL << rgbCount > 0){ // We shift our "mask" over the desired value, and if it's good, we set the bit!
								GPIO_SetBits(GPIOA,blueSerial);
				}

				GPIO_SetBits(GPIOA,rgbClock);//Whatever we want lit is set, fire the clock to cycle them into their registers


			}


			GPIO_ResetBits(GPIOA,gndClock | gndSerial); // Set clock low/serial low in anticipation of next GND clock
			gndCount++;
			if(gndCount >=8){ // This is the last sweep, we must reset the ground count to set a new ground rail next cycle
				gndCount=0;
				GPIO_SetBits(GPIOA,gndSerial);//Set serial high, will activate rail next time around.
			}
		}//IF for clock refresh rate
	}//While
}


 void rainPattern(int densitySeparator){
  			// PRE-PROGRAMMED RAIN PATTERN

	 GPIO_InitTypeDef GPIO_InitStructure;
	 	//RCC_ClocksTypeDef RCC_ClockFreq;

	 	int clocks=0;
	 	int ints=0;
	 	int clup=0;
	 	int fire=0;
	 	int color=1;
	 	int mode=1;
	 	  initialize();
	 	  //splitColors();
	 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	 	GPIO_InitStructure.GPIO_Pin = gndClock | blueSerial | greenSerial | redSerial | GPIO_Pin_4 | gndSerial | rgbLatch | rgbClock | gndLatch | GPIO_Pin_9;
	 	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	 	  GPIO_Init(GPIOA, &GPIO_InitStructure);



	 	   GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	 	   GPIO_SetBits(GPIOA,gndLatch | GPIO_Pin_9);
	 	   while(1){

				   clocks++;
				   if(clocks % 100000 == 0){
				   fire = rand() % (7+densitySeparator) + 1;
				   //-----------------------Clock strike
				   switch(fire){
					case 1:
					//fire=0;	//Lock
					 GPIO_SetBits(GPIOA,redSerial);
					   break;
					case 2:
					  GPIO_SetBits(GPIOA,greenSerial);
					   break;
					case 3:
					  GPIO_SetBits(GPIOA,blueSerial);
					   break;
					case 4:
					  GPIO_SetBits(GPIOA,greenSerial|blueSerial);
					   break;
					case 5:
					 GPIO_SetBits(GPIOA,greenSerial|redSerial);
					   break;
					case 6:
					  GPIO_SetBits(GPIOA,greenSerial|redSerial|blueSerial);
					   break;
					case 7:
					   GPIO_SetBits(GPIOA,blueSerial);
					   break;
					case 8:
					   GPIO_SetBits(GPIOA,blueSerial);
					   break;
					default:

					   break;
					}
					fire++ ;
					  if(clup==1){
					  // Clock active strike
						GPIO_SetBits(GPIOA,rgbLatch|rgbClock);
						clup=0;
					  }else{
						clup=1;
						GPIO_ResetBits(GPIOA,rgbLatch|rgbClock);
					  }// Clock active strike
					GPIO_ResetBits(GPIOA,blueSerial | greenSerial | redSerial);
					//-----------------------Clock strike
				   }

			   if(clocks % 1000 == 0){
			   //-----GNDCLOCK
					ints++;
					GPIO_SetBits(GPIOA,gndClock | gndLatch );
					if(ints == 7){
						  GPIO_SetBits(GPIOA,gndSerial);
						  ints=0;
					}else{
						GPIO_ResetBits(GPIOA,gndSerial);

					}
					GPIO_ResetBits(GPIOA,gndClock| gndLatch);
			   //-----GNDCLOCK
			   }
		 }//WHILE
 }

 /*
  *
  * END STANDALONE FX
  *
  */

 /*
  *
  * IO
  *
  */
 void readFile(){
	 FILE*fp;
	   long elapsed_seconds;
	   char line[80];

	      fp = fopen ( "PR1.C","r" ) ;
	       if( fp == NULL )
	         {
	               puts ( "cannot open file" ) ;
	               exit() ;
	         }else{
	        	 while(fgets(line, 80, fp) != NULL)
	        	    {
	        	 	 /* get a line, up to 80 chars from fr.  done if NULL */
	        	 	 sscanf (line, "%ld", &elapsed_seconds);
	        	 	 /* convert the string to a long int */
	        	 	 printf ("%ld\n", elapsed_seconds);
	        	    }
	         }
	 fclose ( fp ) ;
 }

int main(void)
{
	 int mode=0;


	 initialize();
		if(mode == 1){//Pattern rendering
			createRows();
		    renderPatternUnifiedTrigger();
		}else{//Standalone FX rain
			rainPattern();
		}

}
