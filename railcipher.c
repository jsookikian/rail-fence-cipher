#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024



// Read the specified file and output all of the proper messages within the file.
int readFile(FILE *file, char plaintext[][BUFSIZE]) {
    char buf[BUFSIZE];
    int ndx = 0;

    while (fgets(buf, BUFSIZE, file)) {
         strncpy(plaintext[ndx++], buf, BUFSIZE); 
    }
    return ndx;
}

int main(int argc, char *argv[]) {
   FILE *inFile;
   char plaintext[BUFSIZE][BUFSIZE];
   int numOptions;

   if (argc < 2) {
      perror("usage: <railcipher> <input_file>\n");
      exit(EXIT_FAILURE);
   }


   inFile = fopen(argv[1], "r");
   numOptions = readFile(inFile, plaintext);



}
