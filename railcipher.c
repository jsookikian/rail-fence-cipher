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

// Print the contents of the input file. 

void printContents(char options[][BUFSIZE], int numItems) {
    int i;
    for (i = 0; i < numItems; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }
}

void initializeRails(char ***rails, int depth, int msglen) {
    int i;
    *rails = calloc(depth, sizeof (char *) );
    char **temp = *rails;
    for (i = 0.; i < depth; i++) {
        *temp++ = calloc (msglen,  sizeof (char) );
    }
}


char *encryptMsg(char **rails, int depth, char *msg) {
    int rows, cols, strNdx = 0, movingUp = 0;
    char *ciphertext = calloc (strlen(msg), sizeof(char)); 

    for (cols = 0, rows = 0; cols < strlen(msg); cols++) {
        rails[rows][cols] = msg[cols];

        // If we reach the bottom of the rail, we need to reverse directions
        if (rows == depth - 1) {
            movingUp = 1;
        }
        // If we reach the top of the rail, we need to reverse directions
        else if (rows == 0) {
            movingUp = 0;
        }

        if (movingUp) {
            rows--;
        }
        else if (!movingUp) {
            rows++;
        }
    }
   

  // loop through all rows and columns. 
  // if a valid char is found, append it to ciphertext string
    for (rows = 0; rows < depth; rows++) {
        for (cols = 0; cols < strlen(msg); cols += 1) {
            if (rails[rows][cols] != '\0') {
            ciphertext[strNdx++] = rails[rows][cols];
            }
        }
    }
   

   ciphertext[strNdx] = '\0';
   return ciphertext;
}

int main(int argc, char *argv[]) {
    FILE *inFile;
    char plaintext[BUFSIZE][BUFSIZE], **rails, *ciphertext;
    int numOptions, numRails, choice;

   if (argc < 2) {
      perror("usage: <railcipher> <input_file>\n");
      exit(EXIT_FAILURE);
   }

   inFile = fopen(argv[1], "r");
   numOptions = readFile(inFile, plaintext);
   printContents(plaintext, numOptions);
    while (1) {
        printf("Which line would you like to encrypt? (-1 to quit)\n");
        scanf(" %d", &choice);

        if (choice == -1) {
         printf("Goodbye!\n");
         exit(EXIT_SUCCESS);
        }
        printf("How many rails would you like to use?\n");
        scanf(" %d", &numRails);

        initializeRails(&rails, numRails, strlen(plaintext[choice - 1]));
        ciphertext = encryptMsg(rails, numRails, plaintext[choice - 1]);
        printf("%s\n", ciphertext);
    }

}
