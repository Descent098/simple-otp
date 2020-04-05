#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char* generate_pad(int length){
    srand(time(NULL));   // Initialization, of random library
    int pad[length]; 

    int random_number;

    for( int i = 0 ; i < length ; i++ ) {
        random_number = rand() % 255;
        // Generate number between 0 and 255
        printf("%d\n", random_number);
    }

    return "pad";
}

char * encrypt(char *text){

    const char *pad = generate_pad(strlen(text));

    return "Encrypted String";
}

char * decrypt(char *pad, char *ciphertext){

    return "Decrypted String";
}

void save(){

}

int main(void) {
  const char *plaintext = "\
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

printf("%s", encrypt(plaintext));



return 0;
}
