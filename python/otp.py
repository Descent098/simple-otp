"""This file contains a simple implementation of the one-time pad.

It is NOT intended for production usage and has not been extensively verified for it.
This file is simply an educational tool for AN implementation that works. """

from secrets import choice   # Used to produce reliably random hex values
from string import printable # A list of printable characters to validate against


def generate_pad(length:int) -> str:
    """Generates a pad of random printable ASCII characters
    
    Parameters
    ----------
    length : int
        The length of the pad you want to generate
    
    Returns
    -------
    str
        The generated one time page
    """
    pad = ""
    for index in range(length):
        # Choose a random printable character
        pad_letter =  choice(printable)
        pad += (pad_letter)

    save(pad, "pad.txt")
    return pad

def encrypt(text:str, pad:str) -> str:
    """Encrypts the input text and returns the pad and ciphertext
    
    Parameters
    ----------
    text : str
        The plaintext to generate a ciphertext
    pad : str
        The one-time pad to use for generating a chiphertext
    
    Returns
    -------
    str
        The ciphertext
    
    Raises
    ------
    ValueError
        Raised when one of the characters is not printable ASCII
    """

    # String variable that will contain all the shifted values
    ciphertext = ""

    for text_character, pad_number in zip(text, pad):
        if text_character not in printable:
            raise ValueError(f"Text value: {text_character} provided is not printable ascii")

        # Completed the XOR of the characters ordinance (integer representation)
        xored_value = ord(text_character) ^ ord(pad_number)

        # Takes resulting integer from XOR operation and converts it to a character
        ciphertext_character = chr(xored_value)

        # Add the generated character to the ciphertext
        ciphertext += (ciphertext_character)

    save(ciphertext, "ciphertext.txt")

    return ciphertext

def decrypt(pad:str, ciphertext:str) -> str:
    """Decrypts the ciphertext using the provided pad
    
    Parameters
    ----------
    pad : str
        The pad used to encrypt the one time pad
    ciphertext : str
        The ciphertext to decrypt
    
    Returns
    -------
    str
        The decrypted plaintext
    """
    plaintext = ""

    for pad_number, ciphertext_number in zip(pad, ciphertext):
        plaintext += chr( ord(pad_number) ^ ord(ciphertext_number))

    save(plaintext, "plaintext.txt")

    return plaintext


def save(text:str, path:str):
    """Takes in text and saves it to the provided path
    
    Parameters
    ----------
    text : str
        The text to save to a file
    path : str
        The path to save it to
    """
    with open(path, "w+") as output_file:
        output_file.write(text)


if __name__ == "__main__":
    # The text to encrypt
    text = '''Do not go gentle into that good night,
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
Rage, rage against the dying of the light.'''

    # Generate a pad the same length as the text
    pad = generate_pad(len(text))
    print(f"The pad is: {pad}")

    # Generate a ciphertext from the pad and plaintext
    ciphertext = encrypt(text, pad)
    print(f"\nThe ciphertext is: {ciphertext}")

    # Decrypt and return result
    plaintext = decrypt(pad, ciphertext)
    print(f"\nThe calculated plaintext is: {plaintext}")
