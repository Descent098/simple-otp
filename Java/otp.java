/**

Keep in mind this is just using the standard random library so it is NOT random enough for a real implementation of the one time pad.
*/


import java.util.Random;

class Main {
public static void main(String[] args) {

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

    String ciphertext = encrypt(text, pad);

    System.out.println(decrypt(pad, ciphertext));

    }

/** ...
*/
public static String generate_pad(int length){
    String pad = "";
    char randomCharacter;
    Random r = new Random();
    for( int i = 0; i < length; i++ ){
        randomCharacter = (char) r.nextInt(256);
        pad += randomCharacter;
        }

    return pad;
    }

/** ...
*/
public static String encrypt(String text, String pad){

    String ciphertext = "";
    char xoredValue;
    for( int i = 0; i < text.length(); i++ ){
        xoredValue = (char) (text.charAt(i) ^ pad.charAt(i));
        ciphertext += xoredValue;
        }
    return ciphertext;
    }

/** ...
*/
public static String decrypt( String pad, String ciphertext){
    String plaintext = "";
    char xoredValue;

    for( int i = 0; i < pad.length(); i++ ){
        xoredValue = (char) (ciphertext.charAt(i) ^ pad.charAt(i));

        plaintext += xoredValue;
        }

    return plaintext;
    }

/** ...
*/
public static boolean save(String text, String path){

    return false;

    }

}

