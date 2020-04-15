/// This file contains a simple implementation of the one-time pad.
/// It is NOT intended for production usage and has not been extensively verified for it.
/// This file is simply an educational tool for AN implementation that works.

extern crate rand;           // Used to generate random numbers

use std::fs::File;           // Used to open files
use std::io::Write;          // Uses to write text to files
use std::path::Path;         // Used to write files to paths
use rand::{thread_rng, Rng}; // Random number generation system

/// The primary entrypoint that's run when the file get's run
fn main() {
    let text = String::from("
    Do not go gentle into that good night,
    Old age should burn and rave at close of day;
    Rage, rage against the dying of the light.
    Though wise men at their end know dark is right,
    Because their words had forked no lightning they
    Do not go gentle into that good night.
    Good men, the last wave by, crying how bright
    Their frail deeds might have danced in a green bay,
    Rage, rage against the dying of the light.
    Wild men who caught and sang the sun in flight,
    And learn, too late, they grieved it on its way,
    Do not go gentle into that good night.
    Grave men, near death, who see with blinding sight
    Blind eyes could blaze like meteors and be gay,
    Rage, rage against the dying of the light.
    And you, my father, there on the sad height,
    Curse, bless, me now with your fierce tears, I pray.
    Do not go gentle into that good night.
    Rage, rage against the dying of the light.");

    // Pad Generation
    let pad = generate_pad(text.chars().count());
    println!("The pad is: {}", pad);

    // Generating a ciphertext
    let ciphertext = encrypt(&text, &pad);
    println!("\nThe ciphertext is: {}", ciphertext);

    // Decrypting to plaintext
    let plaintext = decrypt(&pad, &ciphertext);
    println!("\nThe decrypted plaintext is: {}", plaintext);
}

/// Generates a pad of random characters equal to the length argument
/// 
/// Parameters
/// ----------
/// length : usize
///     The length of the pad you want to generate
/// 
/// Example
/// -------
/// ```rust
/// let pad = generate_pad(25); // Generates a 25 character long pad
/// println!("The pad is: {}", pad);
/// ```
/// Returns
/// -------
/// String
///     The generated one time page
pub fn generate_pad(length:usize) -> String{
    
    let mut pad = String::new();

    // Random number generator
    let mut rng = thread_rng();
    let mut current_number: u32;
    
    let mut counter = 0;
    loop{
        // Grab random number between 0 and 255
        current_number = rng.gen_range(0, 255);

        // Create char option from random number
        let option = std::char::from_u32(current_number);

        // Push random character to the string
        pad.push(*option.as_ref().unwrap());
        
        // When pad is same length as original text, break the loop
        counter += 1;
        if counter == length{ 
            break; 
        }
    }
    let path = Path::new("pad.txt");
    save(&pad, path);
    return pad;
}

/// Encrypts the input text and returns the pad and ciphertext
/// 
/// Parameters
/// ----------
/// text : &String
///     The plaintext to generate a ciphertext
/// pad : &String
///     The one-time pad to use for generating a chiphertext
/// 
/// Example
/// -------
/// ```rust
/// let text = String::from("Secret data");
/// let pad = generate_pad(25); // Generates a 25 character long pad
/// let ciphertext = encrypt(text, pad);
/// println!("The ciphertext is: {}", ciphertext);
/// ```
///     
/// Returns
/// -------
/// String
///     The ciphertext
pub fn encrypt(text: &String, pad: &String) -> String{
    let mut ciphertext = String::new();

    // Generate vectors of characters to iterate over
    let text_characters: Vec<char> = text.chars().collect();
    let pad_characters: Vec<char> = pad.chars().collect();

    // Will store the xored value of the current pad and text character
    let mut xored_value: u32;

    for i in 0 .. pad.chars().count() {
        xored_value = u32::from(text_characters[i]) ^ u32::from(pad_characters[i]);

        // Create char option from the xored Value
        let option = std::char::from_u32(xored_value);
        ciphertext.push(*option.as_ref().unwrap());
    }

    let path = Path::new("ciphertext.txt");
    save(&ciphertext, path);
    return ciphertext;

}

/// Decrypts the ciphertext using the provided pad
/// 
/// Parameters
/// ----------
/// pad : &String
///     The pad used to encrypt the one time pad
/// ciphertext : &String
///     The ciphertext to decrypt
/// 
/// Example
/// -------
/// ```rust
/// let text = String::from("Secret data");
/// let pad = generate_pad(25); // Generates a 25 character long pad
/// let ciphertext = encrypt(text, pad);
/// let plaintext = decrypt(pad, ciphertext);
/// println!("The decrypted plaintext is: {}", plaintext); // Prints: Secret data
/// ```
///     
/// Returns
/// -------
/// String
///     The decrypted plaintext

pub fn decrypt(pad: &String, ciphertext: &String) -> String{
    let mut plaintext = String::new();

    // Generate vectors of characters to iterate over
    let ciphertext_characters: Vec<char> = ciphertext.chars().collect();
    let pad_characters: Vec<char> = pad.chars().collect();

    // Will store the xored value of the current pad and text character
    let mut xored_value: u32;

    for i in 0 .. pad.chars().count() {
        xored_value = u32::from(ciphertext_characters[i]) ^ u32::from(pad_characters[i]);

        // Create char option from the xored Value
        let option = std::char::from_u32(xored_value);
        plaintext.push(*option.as_ref().unwrap());
    }

    let path = Path::new("plaintext.txt");
    save(&plaintext, path);
    return plaintext;
}

/// Takes in a String and path and writes the String to the path
/// 
/// Parameters
/// ----------
/// text : &String
///     The text to save to a file
/// path : &Path
///     The path to save the text to
/// 
/// Example
/// -------
/// Save "Secret Data" to output.txt
/// ```rust
/// let text = String::from("Secret data");
/// let path = Path::new("output.txt");
/// save(text, path);
/// ```
pub fn save(text: &String, path: &Path){

    let mut file = File::create(path).expect("Error when creating file");

    file.write_all(text.as_bytes()).expect("Failed to write file");

}
