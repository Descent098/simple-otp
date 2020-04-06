/** This file contains a simple implementation of the one-time pad.

It is NOT intended for production usage and has not been extensively verified for it.
This file is simply an educational tool for AN implementation that works. */


import java.io.*;
import java.util.Random;

class OTP {
public static void main(String[] args) {

    // The text to encrypt
    String text = 
    "Do not go gentle into that good night,\n"
    +"Old age should burn and rave at close of day;\n"
    +"Rage, rage against the dying of the light.\n"
    +"Though wise men at their end know dark is right,\n"
    +"Because their words had forked no lightning they\n"
    +"Do not go gentle into that good night.\n"
    +"Good men, the last wave by, crying how bright\n"
    +"Their frail deeds might have danced in a green bay,\n"
    +"Rage, rage against the dying of the light.\n"
    +"Wild men who caught and sang the sun in flight,\n"
    +"And learn, too late, they grieved it on its way,\n"
    +"Do not go gentle into that good night.\n"
    +"Grave men, near death, who see with blinding sight\n"
    +"Blind eyes could blaze like meteors and be gay,\n"
    +"Rage, rage against the dying of the light.\n"
    +"And you, my father, there on the sad height,\n"
    +"Curse, bless, me now with your fierce tears, I pray.\n"
    +"Do not go gentle into that good night.\n"
    +"Rage, rage against the dying of the light.";


    String pad = generate_pad(text.length());
    System.out.println(System.out.format("The pad is: %s", pad));

    String ciphertext = encrypt(text, pad);
    System.out.println(System.out.format("\nThe ciphertext is: %s", ciphertext));

    String plaintext = decrypt(pad, ciphertext);
    System.out.println(System.out.format("\nThe decrypted plaintext is: %s", plaintext));

    }

/** Generates a pad of random characters */
public static String generate_pad(int length){
    String pad = "";
    char randomCharacter; // Used to hold the current randomly generated character each iteration
    Random r = new Random();

    for( int i = 0; i < length; i++ ){
        randomCharacter = (char) r.nextInt(256);
        pad += randomCharacter;
        }
    
    // Serialize data to file called pad.txt in cwd
    try{
        save(pad, "pad.txt");
        }
    catch (IOException e){
        System.out.println("Can't save file");
        }

    return pad;
    }

/** Encrypts the input text and returns the pad and ciphertext */
public static String encrypt(String text, String pad){

    String ciphertext = "";
    char xoredValue;
    for( int i = 0; i < text.length(); i++ ){
        // XOR the int representation of the current text and pad characters
        xoredValue = (char) (text.charAt(i) ^ pad.charAt(i));
        ciphertext += xoredValue;
        }

    // Serialize data to file called ciphertext.txt in cwd
    try{
        save(ciphertext, "ciphertext.txt");
        }
    catch (IOException e){
        System.out.println("Can't save file");
        }

    return ciphertext;
    }

/** Decrypts the ciphertext using the provided pad */
public static String decrypt( String pad, String ciphertext){
    String plaintext = "";
    char xoredValue;

    for( int i = 0; i < pad.length(); i++ ){
        // XOR the int representation of the current ciphertext and pad characters
        xoredValue = (char) (ciphertext.charAt(i) ^ pad.charAt(i));

        plaintext += xoredValue;
        }

    // Serialize data to file called ciphertext.txt in cwd
    try{
        save(plaintext, "plaintext.txt");
        }
    catch (IOException e){
        System.out.println("Can't save file");
        }

    return plaintext;
    }

/** Takes in text and saves it to the provided path */
public static void save(String text, String path) throws IOException{
    BufferedWriter writer = new BufferedWriter(new FileWriter(path));
    try {
        writer.write(text);
        }
    finally {
        writer.close();
        }
    }

}
