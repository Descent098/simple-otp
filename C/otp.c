// File is in a questionable state rn so i'm commenting out the code until it's more stable


/**
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void save(char *text, char *path){
  FILE *f = fopen(path, "w");
  if (f == NULL) {
      printf("Error opening file!\n");
      exit(1);
    }
  fprintf(f, "%s\n", text);
}

char* generate_pad(int length){
    srand(time(NULL));   // Initialization, of random library
    char pad[length]; 

    int random_number;

    for( int i = 0 ; i < length ; i++ ) {
        // Generate number between 0 and 255
        random_number = rand() % 255;
        pad[i] = (char) random_number;
    }

    return pad;
}

char * encrypt(char *text, char *pad){
  char ciphertext[strlen(text)];
  int xoredValue;

  for( int i = 0 ; i < strlen(text) ; i++ ) {
        xoredValue = text[i] ^ pad[i];
        ciphertext[i] = (char) xoredValue;
    }

    return ciphertext;
}

char * decrypt(char *pad, char *ciphertext){

    
  char plaintext[strlen(pad)];
  int xoredValue;

  for( int i = 0 ; i < strlen(pad) ; i++ ) {
        xoredValue = ciphertext[i] ^ pad[i];
        plaintext[i] = (char) xoredValue;
    }

    save(plaintext, "plaintext.txt");
    return plaintext;
}

int main(void) {
  const char *text = "\
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

  char* pad = generate_pad(strlen(text));
  printf("The pad is: %s", pad);

  char* ciphertext = encrypt(text, pad);
  printf("\n\nThe ciphertext is: %s", ciphertext);

  char* plaintext = decrypt(pad, ciphertext);
  printf("\n\nThe plaintext is: %s", plaintext);



return 0;
}

*/