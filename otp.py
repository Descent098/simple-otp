from secrets import choice   # Used to produce reliably random hex values
from string import printable


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
        pad_letter =  choice(printable)
        pad += (pad_letter)
    return pad

def encrypt(text:str) -> tuple:
    """Encrypts the input text and returns the pad and ciphertext
    
    Parameters
    ----------
    text : str
        The text to generate a ciphertext and one time pad for
    
    Returns
    -------
    Tuple[str, str]
        Returns both the pad and ciphertext (in that order)
    
    Raises
    ------
    ValueError
        Raised when one of the characters is not printable ASCII
    """
    pad = generate_pad(len(text))
    print(f"The pad is: {pad}")
    ciphertext = ""

    for text_character, pad_number in zip(text, pad):
        if text_character not in printable:
            raise ValueError(f"Text value: {text_character} provided is not printable ascii")
        shifted_value = ord(text_character) ^ ord(pad_number)
        ciphertext_character = chr(shifted_value)
        ciphertext += (ciphertext_character)

    return pad, ciphertext

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
        The plaintext
    """
    plaintext = ""

    for pad_number, ciphertext_number in zip(pad, ciphertext):
        plaintext += chr( ord(pad_number) ^ ord(ciphertext_number))

    return plaintext


def save(text:str, path:str) -> bool:
    with open(path, "w+") as output_file:
        output_file.write(text)


if __name__ == "__main__":
    plaintext = '''Do not go gentle into that good night,
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
    pad, ciphertext = encrypt(plaintext)
    print(f"Pad is {pad}\nciphertext is {ciphertext}")

    # Write the results to files
    save(pad, "pad.txt")
    save(ciphertext, "ciphertext.txt")
    save(plaintext, "plaintext.txt")
