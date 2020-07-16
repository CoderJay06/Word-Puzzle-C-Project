/**************************************
Name: Jay J. Cruz
Date: 06/19/2020
Description: Word Puzzle Program
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define NUMBER_OF_WORDS 16
#define MAX_STRING_SIZE 10
#define GRID_SIZE 20
#define LB 0 // Lower Bound for random direction
#define UB 8 // Upper Bound for random direction
#define FLUSH while(getchar() != '\n');
// Function to print elements in an array. Marcus Long (temporary)
void outputArray(char arr[NUMBER_OF_WORDS][MAX_STRING_SIZE]);
// Function to sort the words in an alphabetical order & to print 4*4 grid. Marcus Long
void sortArray(char arr[NUMBER_OF_WORDS][MAX_STRING_SIZE]);
// functions for filling grid and getting user input(Jay Cruz)
void fillGridDots(char grid[][GRID_SIZE], char gridTitle[]);
void getWordsInput(char *word);
// functions for inserting words in all directions(Jay Cruz)
void insertDiagRdown(char *word, char grid[][GRID_SIZE]);
void insertUp(char *word, char grid[][GRID_SIZE]);
void insertDown(char *word, char grid[][GRID_SIZE]);
void insertAcrossRight(char *word, char grid[][GRID_SIZE]);
void insertAcrossLeft(char *word, char grid[][GRID_SIZE]);
void insertDiagLdown(char *word, char grid[][GRID_SIZE]);
void insertDiagRup(char *word, char grid[][GRID_SIZE]);
void insertDiagLUp(char *word, char grid[][GRID_SIZE]);
// for placing words in random locations(Jay Cruz)
int placeRandom();
// for outputting wordpuzzle and filling with random characters(Jay Cruz)
void printGrid(char grid[][GRID_SIZE], char gridTitle[]);
void fillGridRandomCharacters(char grid[][GRID_SIZE]);
// for checking allocated memory and printing puzzle to txt file(Jay Cruz)
void checkMemory(char *word, int *direction);
void sendToTextFile(char grid[][GRID_SIZE]);
int askToRepeat(char userChoice, int wordPlay);
char getRepeatChoice(char userChoice);

int main() {
   // Marcus Long
   // temporary fill the array with words so we don't have to type them everytime
   // char words[NUMBER_OF_WORDS][MAX_STRING_SIZE] = { "basketball","football","cricket","wrestling","fencing","rowing","volleyball","baseball",
   // "hockey","racing","running","bobsleigh","curling","dancing","bowling","tennis"};
   // declare word puzzle grid and title (Jay Cruz)
   char grid[GRID_SIZE][GRID_SIZE] = {' '};
   char gridTitle[] = "WORD BUILDER";
   int i = 0, j = 0, wordPlay = 0;
   int *direction = (int*) malloc(UB * sizeof(int)+1); // allocate memory for word direction (Jay Cruz)
   char *word = (char *) malloc(MAX_STRING_SIZE * sizeof(char)+1); // allocate memory for word input (Jay Cruz)
   char userChoice, repeatPuzzle;
   
   // check if memory was allocated
   checkMemory(word, direction);

   // seed random 
   srand((unsigned)time(NULL));

   fillGridDots(grid, gridTitle);
   // get user input and randomly insert 16 words (Jay Cruz)
   do {
      *direction = placeRandom();
      printf("\nPlease enter 16 words with 10 or fewer letters.\n");
      getWordsInput(word);
      switch (*direction) {
         case 0:
            insertDown(word, grid);
            break;
         case 1:
            insertUp(word, grid);
            break;
         case 2: 
            insertAcrossRight(word, grid); 
            break; 
         case 3: 
            insertAcrossLeft(word, grid);
            break;
         case 4: 
            insertDiagLdown(word, grid);
            break; 
         case 5: 
            insertDiagRdown(word, grid);
            break;
         case 6: 
            insertDiagLUp(word, grid);
            break;
         case 7: 
            insertDiagRup(word, grid);
            break;
         default: 
            break;
      }
      wordPlay++;

      // repeat program if user chooses to
      if (wordPlay == NUMBER_OF_WORDS) {
         wordPlay = askToRepeat(userChoice, wordPlay);
      }
      
   } while (wordPlay < NUMBER_OF_WORDS);

   fillGridRandomCharacters(grid);
   printGrid(grid, gridTitle);
   sendToTextFile(grid);

   // deallocate memory after use 
   free(word);
   free(direction);

   return 0;
}; // End of Main

void sendToTextFile(char grid[][GRID_SIZE]) {
   // set pointer for writing to file
   FILE* writePtr;
   writePtr = fopen("word_puzzle.txt", "w");

   // check if can write to file 
   if (writePtr == NULL) {
      printf("Sorry, cannot be written to..\n");
      system("pause");
      exit(-1); // HARD EXIT
   }
   // write word puzzle to txt file 
   for (int i = 0; i < GRID_SIZE; i++) {
      fprintf(writePtr, "\n%2d | ", i + 1);
      for (int j = 0; j < GRID_SIZE; j++) {
         fprintf(writePtr, "%3c ", grid[i][j]);
      }
      fprintf(writePtr, " %c", '|');
   }
   fclose(writePtr);
} // end sendToTextFile 

void checkMemory(char *word, int *direction) {
    if (word == NULL || direction == NULL) {
      printf("Failed to allocate memory..\n");
      exit(-1);
   }
   else {
      return;
   }
} // end checkMemory 

// function to place words in random places 
int placeRandom() {
   return LB + rand() % (UB - LB);
} // end placeRandom 

// Function to print elements in an array. Marcus Long
void outputArray(char arr[NUMBER_OF_WORDS][MAX_STRING_SIZE]) {
   for(int i = 0; i < NUMBER_OF_WORDS; i++) {
      printf("%s \n", arr[i]);
   }
} // end outputArray 

// Function to sort the words in an alphabetical order & to print 4*4 grid. Marcus Long
void sortArray(char arr[NUMBER_OF_WORDS][MAX_STRING_SIZE]) {
   char temp[MAX_STRING_SIZE];
   int i, j;
   for (i = 0; i < NUMBER_OF_WORDS - 1 ; i++) {
      for (j = i + 1; j < MAX_STRING_SIZE; j++) {
         if (strcmp(arr[i], arr[j]) > 0) {
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
         }  
      }
   } 
   printf("--------------------------------------------------------------------------------------\n");
   for (i = 0; i < 4; i++) {
      for (j = i; j < NUMBER_OF_WORDS; j = j + 4) {
         printf("%11s \t", arr[j]);
      }
      printf("\n");
   }
   printf("--------------------------------------------------------------------------------------\n\n");
} // end sortArray

void getWordsInput(char *word) {
   int i = 0, wordLength = 0;
   
   // get words input from the user 
   printf("Enter a word(1 - 10 characters): ");
   scanf("%s", word); FLUSH;
   wordLength = strlen(word);
   if (wordLength > 10 || wordLength <= 0) {
      printf("\nInvalid, Please enter (1 - 10) characters.\n");
      getWordsInput(word);
   }
   
} // end getWordsInput

void insertUp(char *word, char grid[][GRID_SIZE]) { 
   int length, i,j,x = 0;
   length = strlen(word);
   
    while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         for (j = 0; j < GRID_SIZE; j++) {
            if (*word != '\0' && grid[i][j] == '.') 
               grid[i--][j--] = putchar(toupper(*word++));
         }
      }
      x++;
   }
} // end insertUp

void insertAcrossRight(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         for (j = 0; j < GRID_SIZE; j++) {
            if (*word != '\0' && grid[i][j] == '.') {
               grid[i][j] = putchar(toupper(*word++));
            }
         }
      }
      x++;
   }
} // end insertAcrossRight

void insertAcrossLeft(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         if (*word != '\0' && grid[i][j] == '.') 
            grid[--i][--j] = putchar(toupper(*word++));
      x++;
      }
   }
} // end insertAcrossLeft

void insertDiagLdown(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         if (*word != '\0' && grid[i][j] == '.') 
            grid[i++][j--] = putchar(toupper(*word++));
      x++;
      }
   } 

} // end insertDiagLeftdown

void insertDiagRdown(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         for (j = 0; j < GRID_SIZE; j++) {
            if (*word != '\0' && grid[i][j] == '.')
               grid[i++][j++] = putchar(toupper(*word++));   
         }
      }
      x++;
   }
} // end insertDiagRdown

void insertDiagRup(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         for (j = 0; j < GRID_SIZE; j++) {
            if (*word != '\0' && grid[i][j] == '.') {
               grid[i--][j] = putchar(toupper(*word++));
            }
         }
      }
      x++;
   }
} // end insertDiagRup

void insertDiagLUp(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         for (j = 0; j < GRID_SIZE; j++) {
            if (*word != '\0' && grid[i][j] == '.') {
               grid[i--][j] = putchar(toupper(*word++));
            }
         }
      }
      x++;
   }
} // end insertDiagLup

void insertDown(char *word, char grid[][GRID_SIZE]) {
   int length, i,j,x = 0;
   length = strlen(word);

   while (x < length-1) {
      for (i = 0; i < GRID_SIZE; i++) {
         for (j = 0; j < GRID_SIZE; j++) {
            if (*word != '\0' && grid[i][j] == '.')
               grid[i++][j--] = putchar(toupper(*word++));
         }
      }
      x++;
   }
} // end insertDown
 
void fillGridDots(char grid[GRID_SIZE][GRID_SIZE], char gridTitle[]) {
   // set rows and cols iterators
   int i;
   int j;

   // Increment over grid rows and cols, fill with dot
   printf("\t============================%s===================================", gridTitle);
   for (i = 0; i < GRID_SIZE; i++) {
      printf("\n%2d | ", i + 1);
      for (j = 0; j < GRID_SIZE; j++) {
         grid[i][j] = '.';
         printf("%3c ", *(&(grid[i][j])));
      }
      printf(" |");
   }
} // end fillGridDots 

void fillGridRandomCharacters(char grid[][GRID_SIZE]) {
   int row, col;
   // fill grid with random letters A-Z
   for (row = 0; row < GRID_SIZE; row++) {
      for (col = 0; col < GRID_SIZE; col++) {
         if (grid[row][col] == '.')
            grid[row][col] = (rand() % 26) + 'A';
      }
   }
} // end fillGridRandomCharacters 

void printGrid(char grid[][GRID_SIZE], char gridTitle[]) { 
   int i;

   int j;

   // print grid (Marcus Long)
   printf("\n ================================%s=========================================", gridTitle);
   printf("\n     ");
   for (i = 0; i < GRID_SIZE; i++) {
      printf(" %2d ", i + 1);
   }
   printf("\n--------------------------------------------------------------------------------------\n");
   for (i = 0; i < GRID_SIZE; i++) {
      printf("\n%2d | ", i + 1);
      for (j = 0; j < GRID_SIZE; j++) {
         printf("%3c ", *(&(grid[i][j])));
      }
      //printf(" |");
   }
   printf("\n--------------------------------------------------------------------------------------\n\n");
} // end printGrid

int askToRepeat(char choice, int wordPlay) {

   if (getRepeatChoice(choice) == 'Y') {
      wordPlay = 0;
   }
   else {
      wordPlay = NUMBER_OF_WORDS;
   }
   return wordPlay;
} // end askToRepeat

char getRepeatChoice(char choice) {
   printf("\nDo you want to repeat? Y/N: ");
   scanf("%c", &choice); FLUSH;
   return toupper(choice);
} // end getRepeatChoice