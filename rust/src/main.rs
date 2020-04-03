extern crate rand;

use rand::distributions::{Distribution, Uniform};

fn main() {
    println!("Hello, world!");
}

fn generate_pad(length:i64) -> Vec<i64>{
    let pad = vec![];
    let mut counter = 0;
    let mut rng = rand::thread_rng();
    
    loop{
        counter += 1;
        if counter == length{ 
            break; 
        }
    }
    return pad;
}

fn encrypt(text:&str) -> Vec<i16>{
    return vec![12];

}

fn decrypt(pad: &str, ciphertext: &str) -> String{
    let plaintext = String::from("");
    return plaintext;

}
