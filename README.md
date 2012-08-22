This file is a sample of using general GPIO function of a Cortex-3 ARM MCU, namely an STM32-F103****. 

In this example, a table with a 8x8 array of RGB LED's was used. Using a shift register also for ground allowed a grounding column to be assigned to a color row. This combined with many cycles a second allows the table to light
any color on the board at any time, independent of all other lights. Using a java program to create arrays that the MCU can recieve and use, a user can create text on the table, draw pictures, or do other creative stuff like that :)