#include <stdio.h>                                              // a poorly-written C program to do a Matrix screen
#include <stdlib.h>                                             // on the Z80-MBC2 by Sarah Libman
#include <stdbool.h>

#define A_ESC           27                                      // escape character for control codes
#define NUMBER_LINES    79                                      // number of lines (1 in column 1, 3, 5, ... 77, 79 on 80 column screen)
#define NUMBER_ROW      42                                      // number of rows on screen
#define MIN_LENGTH      6                                       // minimum length of line (>= maxBright)
#define MORE_LENGTH     30                                      // makes line longer than minimum length (can be longer than screen to give pauses between lines)
#define MORE_BRIGHT     3                                       // makes bright portion of line longer than 1 
#define START_CHAR      33                                      // value of first random character code
#define NUMBER_CHAR     222                                     // number of random characters starting at START_CHAR

int main()
{
    int length[NUMBER_LINES];                                   // how long is the line
    int bright[NUMBER_LINES];                                   // how long is the bright component of the line
    int start[NUMBER_LINES];                                    // where is the top of the line
    int end[NUMBER_LINES];                                      // where is the bottom of the line
    int line = 0;                                               // which line are we processing
    int screenLine = 0;                                         // which line is that on the screen
    int keyStatus = 0;                                          // user key status
    
    for (line = 0; line < NUMBER_LINES; line++)                 // prep everything
    {
        length[line] = MIN_LENGTH + (rand() % MORE_LENGTH);
        bright[line] = 1 + (rand() % MORE_BRIGHT);
        start[line] = 1;
        end[line] = 1;
    }

    printf("%c[2J%c[%d;%dH", A_ESC, A_ESC, 1, 1);               // clear screen and put cursor at top left
	
    while (true)
    {
        line = rand() % NUMBER_LINES;                           // select line: random number between 0 and NUMBER_LINES - 1
        screenLine =  line + 1;                            // the actual column number on the screen
        
        for (int i = 0; i < 4; i++)                             // add 4 characters to the line (because fewer characters doesn't give sense of downward motion)
        {
            if (end[line] <= NUMBER_ROW)                        // if the bottom of the line is on the screen then print a bright character (otherwise don't)
            {
                printf("%c[%dm%c[%d;%dH%c[1m%c%c[m", A_ESC, 32, A_ESC, end[line], screenLine, A_ESC, START_CHAR + (rand() % NUMBER_CHAR), A_ESC);
            }
            
            if (end[line] - bright[line] <= NUMBER_ROW && end[line] - bright[line] >= 1)    // if the uppermost bright character is on the screen
            {                                                                               // put cursor on it and print a random (non-bright) character
                printf("%c[%d;%dH%c", A_ESC, end[line] - bright[line], screenLine, START_CHAR + (rand() % NUMBER_CHAR));  
            }

            if (end[line] - length[line] <= NUMBER_ROW  && end[line] - length[line] >= 1)   // if the start of line is on screen
            {
                printf("%c[%d;%dH ", A_ESC, end[line] - length[line], screenLine);          // put the cursor on it and print space
            }

            if (end[line] > NUMBER_ROW + length[line])          // if the whole line is now off screen then reset the line
            {
                length[line] = MIN_LENGTH + (rand() % MORE_LENGTH);
                bright[line] = 1 + (rand() % MORE_BRIGHT);
                start[line] = 1;
                end[line] = 1;
            }
            else                                                // otherwise increase the position of the bottom of the line
            {
                end[line]++;
            }

            outp(1,128);                                        // opcode to read User Key
            keyStatus = inp(0);
            if (keyStatus != 0) {
				printf("%c[2J%c[%d;%dH", A_ESC, A_ESC, 1, 1);   // clear screen and put cursor at top left
				return 0;										// and break to CP/M is pressed
			}
        }

    }
    return 0;
}