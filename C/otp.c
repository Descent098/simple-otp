// Honestly this is in the git history for posterity, looks like theres some pointer garbage going on I can't debug so i'm getting rid of this version

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

const int text_length = 939; // How many characters are in the text variable


void save(char text[], char path[]){
  FILE *f = fopen(path, "w");
  if (f == NULL) {
      printf("Error opening file!\n");
      exit(1);
    }
  fprintf(f, "%s\n", text);
}

void generate_pad(int length, char* var){
    srand(time(NULL));   // Initialization, of random library
    char pad[length]; 

    int random_number;

    for( int i = 0 ; i < length ; i++ ) {
        // Generate number between 0 and 255
        random_number = rand() % 255;
        pad[i] = (char) random_number;
    }

    save(pad, "pad.txt");
    strcpy(var, pad);
}

void encrypt(char text[], char * pad, char* var){
  char ciphertext[strlen(text)];
  int xoredValue;

  for( int i = 0 ; i < strlen(text) ; i++ ) {
        xoredValue = text[i] ^ pad[i];
        ciphertext[i] = (char) xoredValue;
    }

    save(ciphertext, "ciphertext.txt");
    strcpy(var, ciphertext);
}

const char* decrypt(char* pad, char* ciphertext, char* var){

    
  char plaintext[text_length];
  int xoredValue;

  for( int i = 0 ; i < strlen(pad) ; i++ ) {
        xoredValue = ciphertext[i] ^ pad[i];
        plaintext[i] = (char) xoredValue;
    }

    save(plaintext, "plaintext.txt");
    strcpy(var, plaintext);
}

int main(void) {
  const char text[] = "\
    Do not go gentle into that good night,\n\
    Old age should burn and rave at close of day;\n\
    Rage, rage against the dying of the light.\n\
    Though wise men at their end know dark is right,\n\
    Because their words had forked no lightning they\n\
    Do not go gentle into that good night.\n\
    Good men, the last wave by, crying how bright\n\
    Their frail deeds might have danced in a green bay,\n\
    Rage, rage against the dying of the light.\n\
    Wild men who caught and sang the sun in flight,\n\
    And learn, too late, they grieved it on its way.\n\
    Do not go gentle into that good night.\n\
    Grave men, near death, who see with blinding sight\n\
    Blind eyes could blaze like meteors and be gay,\n\
    Rage, rage against the dying of the light.\n\
    And you, my father, there on the sad height,\n\
    Curse, bless, me now with your fierce tears, I pray.\n\
    Do not go gentle into that good night.\n\
    Rage, rage against the dying of the light.";



  char pad[text_length];
  generate_pad(text_length, pad);
  printf("The pad is: %s", pad);

  char ciphertext[text_length];
  encrypt(text, pad, ciphertext);
  printf("\n\nThe ciphertext is: %s", ciphertext);

  char plaintext[text_length];
  decrypt(pad, ciphertext, plaintext);
  printf("\n\nThe plaintext is: %s", plaintext);



return 0;
}
