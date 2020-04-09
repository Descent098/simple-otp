# Simple otp (One Time Pad)

**NONE of the implementations are intended for production usage**. They have not been extensively validated for it. These files are simply an **educational tool** for looking at **AN implementation** that works to help people understand it.

There is an accompanying video that walks-through the python implementation that I will post a link to once I complete it. Additionally you can find an in-depth explanation below of the protocol and how to use the implementations (again not in production applications).

## Table of contents
- [Usage](#usage)    
- [Glossary](#glossary)        
   - [Variables](#variables)        
   - [Functions](#functions)    
- [Theory](#theory)        
   - [1. Background](#1-background)        
   - [2. ASCII Conversion](#2-ascii-conversion)       
   - [3. Pad Generation](#3-pad-generation)       
   - [4. Generating a ciphertext](#4-generating-a-ciphertext)      
   - [5. Decrypting to plaintext](#5-decrypting-to-plaintext)            
- [ASCII table](#ascii-table-provided-by-the-built-in-one-on-bing)


## Usage
Each folder contains a language implementation with details on how to setup a runtime environment and run the corresponding file. The most polished implementation is python since that's my preferred language. When you run the file it will generate three files ```pad.txt```, ```ciphertext.txt``` and ```plaintext.txt``` these each correspond to the variables generated based on the terms below.



## Glossary

Throughout the files I use a set of standardized terms to refer to variables and functions to make the implementations understandable:



### Variables

***text***: The text that you want to encrypt, in all files this is hardcoded and I am using [Do not go gentle into that good night by Dylan Thomas](https://poets.org/poem/do-not-go-gentle-good-night).



***pad***: The one time pad that is used to encrypt the text



***ciphertext***: The text generated through the iterative XORing of the text and pad



***plaintext***: The decrypted value generated through the XORing of the pad and ciphertext (should match the text variable if the implementation is correct)



### Functions

*Note the names change to suit whatever is the preferred language style so I have opted to just use names with uppercase first letters and spaces in between instead of either snake_case or camelCase.*



***Generate pad***: Used to generate the one-time pad. Will take in an integer for the length of pad it needs to generate and return whatever type is most appropriate for the language (either a string or char array). This is completed during step 3 of the theory section.



***Encrypt***: Generates the ciphertext using the pad and text, then return it as whatever type is most appropriate for the language (either a string or char array). This is completed during step 4 of the theory section.



***Decrypt***: Takes in the ciphertext and pad, generates the plaintext and return it as whatever type is most appropriate for the language (either a string or char array). This is completed during step 5 of the theory section.



***Save***: Takes in either a string or char array based on which language it is, and a file path then serializes the string/char array to the path provided.


## Theory

*This explanation is meant to be somewhat simplistic and skip over some of the detail about secrecy and **proofs** why the math works. This description is meant to be a laymen's terms, step-by-step walkthrough of how the one-time pad protocol works.*



### 1. Background

The one-time pad relies on a number of principles that aren't immediately obvious to everyone, two of the most basic are:

1. Any character can be represented as an integer

2. XORing 2 values, and then XORing the result of the values with one of the original values produces the other. So for example:
   ```
   a XOR b = c
   c XOR b = a
   c XOR a = b
   ```
   
   or

   ```
   text XOR pad = ciphertext
   ciphertext XOR pad = text
   ciphertext XOR text = pad
   ```




Additionally to maintain secrecy there are a few things that need to be done:

1. Each pad must be used **one time**, or else the ciphertexts are susceptible to cribdragging (a technique where you can use only resulting ciphertexts to determine the original pad).
2. The numbers generated must be **random** as flaws in the pseudorandom generation can be exploited.
3. The attacker must not have **any intuition** (be able to guess) as to what's inside the files.




### 2. ASCII Conversion
One way to do a conversion from string/chars to integers is to use an [ASCII table](#ascii-table-provided-by-the-built-in-one-on-bing), which allows you to have a 1-1 mapping of characters to an (at most) 2 byte integer. For example let's convert the string 'Hello' using the ASCII table below. The 'H' corresponds to 72 (0x48 in hex and 0b1001000 in binary) using the chart so that would be our first integer. The whole sequence would then be (72, 101, 108, 108, 111).



### 3. Pad Generation
From there we would use a random number generator to generate a pad of random 2 byte integers that is the same length as the input text (in this case 5 characters) lets say they are (11, 212, 8, 224, 122) which corresponds to ("VT", "Ô", "BS", "à", "z" ) . Notice that not all of these are printable characters (any with two letters) and so the resulting text file may end up looking weird.



### 4. Generating a ciphertext

The ciphertext can now be generated by iterating over the integer representations of the pad and original text ("Hello") and XORing them together. To XOR two numbers take the integers and convert them to binary, from there line up each binary number into columns and on columns where one of the bits is  a 1 and the other is a 0 the result is 1, any other combination is a 0.



For example for the first character of our pad and original text "VT" (11) and "H"(72) would be:



```
0000 1011 ("VT" or 11)
0100 1000 ("H" or 72)
----------
0100 0011 ("C" or 67)
```



The whole sequence would be:

```
Characters: ("H", "e", "l", "l", "o") XOR ("VT", "Ô", "BS", "à", "z" ) = ("C", "±", "d", "Œ", "NAK")

Decimal: (72, 101, 108, 108, 111) XOR (11, 212, 8, 224, 122) = (67, 177, 100, 140, 21)
```



Now that we have the pad and ciphertext, you can give someone the ciphertext over a public channel and it can only be decrypted if they also have the pad (which should be sent through a secured channel).



### 5. Decrypting to plaintext

Now to decrypt we do the same thing we did to generate the ciphertext, but with the ciphertext and pad characters to reverse it to the plaintext (remember ``` ciphertext XOR pad = text```). So in this case:

```
Characters: ("VT", "Ô", "BS", "à", "z" ) XOR ("C", "±", "d", "Œ", "NAK") = ("H", "e", "l", "l", "o")

Decimal: (11, 212, 8, 224, 122) XOR (67, 177, 100, 140, 21) = (72, 101, 108, 108, 111)
```



#### ASCII table (provided by the built in one on bing)

| DECIMAL | HEX  | CHAR | NAME (if not printable) |
| :--- | :--- | :--- | :--------------- |
| 0    | 00   | NUL  | Null             |
| 1    | 01   | SOH  | Start of heading |
| 2    | 02   | STX  | Start of text    |
| 3    | 03   | ETX  | End of text      |
| 4    | 04   | EOT  | End of trans.    |
| 5    | 05   | ENQ  | Enquiry          |
| 6    | 06   | ACK  | Ack.             |
| 7    | 07   | BEL  | Bell             |
| 8    | 08   | BS   | Back space       |
| 9    | 09   | HT   | Horizontal tab   |
| 10   | 0A   | LF   | Line feed        |
| 11   | 0B   | VT   | Vertical tab     |
| 12   | 0C   | FF   | Form feed        |
| 13   | 0D   | CR   | Carriage return  |
| 14   | 0E   | SO   | Shift out        |
| 15   | 0F   | SI   | Shift in         |
| 16   | 10   | DLE  | Data line escape |
| 17   | 11   | DC1  | Device control 1 |
| 18   | 12   | DC2  | Device control 2 |
| 19   | 13   | DC3  | Device control 3 |
| 20   | 14   | DC4  | Device control 4 |
| 21   | 15   | NAK  | Negative ack.    |
| 22   | 16   | SYN  | Synchronous idle |
| 23   | 17   | ETB  | End of block     |
| 24   | 18   | CAN  | Cancel           |
| 25   | 19   | EM   | End of medium    |
| 26   | 1A   | SUB  | Substitute       |
| 27   | 1B   | ESC  | Escape           |
| 28   | 1C   | FS   | File separator   |
| 29   | 1D   | GS   | Group separator  |
| 30   | 1E   | RS   | Record separator |
| 31   | 1F   | US   | Unit separator   |
| 32   | 20   |      | Space            |
| 33   | 21   | !    |                  |
| 34   | 22   | "    | &quot;           |
| 35   | 23   | #    |                  |
| 36   | 24   | $    |                  |
| 37   | 25   | %    |                  |
| 38   | 26   | &    | &amp;            |
| 39   | 27   | '    |                  |
| 40   | 28   | (    |                  |
| 41   | 29   | )    |                  |
| 42   | 2A   | *    |                  |
| 43   | 2B   | +    |                  |
| 44   | 2C   | ,    |                  |
| 45   | 2D   | -    |                  |
| 46   | 2E   | .    |                  |
| 47   | 2F   | /    |                  |
| 48   | 30   | 0    |                  |
| 49   | 31   | 1    |                  |
| 50   | 32   | 2    |                  |
| 51   | 33   | 3    |                  |
| 52   | 34   | 4    |                  |
| 53   | 35   | 5    |                  |
| 54   | 36   | 6    |                  |
| 55   | 37   | 7    |                  |
| 56   | 38   | 8    |                  |
| 57   | 39   | 9    |                  |
| 58   | 3A   | :    |                  |
| 59   | 3B   | ;    |                  |
| 60   | 3C   | <    | &lt;             |
| 61   | 3D   | =    |                  |
| 62   | 3E   | >    | &gt;             |
| 63   | 3F   | ?    |                  |
| 64   | 40   | @    |                  |
| 65   | 41   | A    |                  |
| 66   | 42   | B    |                  |
| 67   | 43   | C    |                  |
| 68   | 44   | D    |                  |
| 69   | 45   | E    |                  |
| 70   | 46   | F    |                  |
| 71   | 47   | G    |                  |
| 72   | 48   | H    |                  |
| 73   | 49   | I    |                  |
| 74   | 4A   | J    |                  |
| 75   | 4B   | K    |                  |
| 76   | 4C   | L    |                  |
| 77   | 4D   | M    |                  |
| 78   | 4E   | N    |                  |
| 79   | 4F   | O    |                  |
| 80   | 50   | P    |                  |
| 81   | 51   | Q    |                  |
| 82   | 52   | R    |                  |
| 83   | 53   | S    |                  |
| 84   | 54   | T    |                  |
| 85   | 55   | U    |                  |
| 86   | 56   | V    |                  |
| 87   | 57   | W    |                  |
| 88   | 58   | X    |                  |
| 89   | 59   | Y    |                  |
| 90   | 5A   | Z    |                  |
| 91   | 5B   | [    |                  |
| 92   | 5C   | \    |                  |
| 93   | 5D   | ]    |                  |
| 94   | 5E   | ^    |                  |
| 95   | 5F   | _    |                  |
| 96   | 60   | `    |                  |
| 97   | 61   | a    |                  |
| 98   | 62   | b    |                  |
| 99   | 63   | c    |                  |
| 100  | 64   | d    |                  |
| 101  | 65   | e    |                  |
| 102  | 66   | f    |                  |
| 103  | 67   | g    |                  |
| 104  | 68   | h    |                  |
| 105  | 69   | i    |                  |
| 106  | 6A   | j    |                  |
| 107  | 6B   | k    |                  |
| 108  | 6C   | l    |                  |
| 109  | 6D   | m    |                  |
| 110  | 6E   | n    |                  |
| 111  | 6F   | o    |                  |
| 112  | 70   | p    |                  |
| 113  | 71   | q    |                  |
| 114  | 72   | r    |                  |
| 115  | 73   | s    |                  |
| 116  | 74   | t    |                  |
| 117  | 75   | u    |                  |
| 118  | 76   | v    |                  |
| 119  | 77   | w    |                  |
| 120  | 78   | x    |                  |
| 121  | 79   | y    |                  |
| 122  | 7A   | z    |                  |
| 123  | 7B   | {    |                  |
| 124  | 7C   | \|   |                  |
| 125  | 7D   | }    |                  |
| 126  | 7E   | ~    |                  |
| 127  | 7F   |      | Delete           |
| 128  | 80   | €    | &euro;   |
| 129  | 81   |      |          |
| 130  | 82   | ‚    | &sbquo;  |
| 131  | 83   | ƒ    | &fnof;   |
| 132  | 84   | „    | &bdquo;  |
| 133  | 85   | …    | &hellip; |
| 134  | 86   | †    | &dagger; |
| 135  | 87   | ‡    | &Dagger; |
| 136  | 88   | ˆ    | &circ;   |
| 137  | 89   | ‰    | &permil; |
| 138  | 8A   | Š    | &Scaron; |
| 139  | 8B   | ‹    | &lsaquo; |
| 140  | 8C   | Œ    | &OElig;  |
| 141  | 8D   |      |          |
| 142  | 8E   | Ž    |          |
| 143  | 8F   |      |          |
| 144  | 90   |      |          |
| 145  | 91   | ‘    | &lsquo;  |
| 146  | 92   | ’    | &rsquo;  |
| 147  | 93   | “    | &ldquo;  |
| 148  | 94   | ”    | &rdquo;  |
| 149  | 95   | •    | &bull;   |
| 150  | 96   | –    | &ndash;  |
| 151  | 97   | —    | &mdash;  |
| 152  | 98   | ˜    | &tilde;  |
| 153  | 99   | ™    | &trade;  |
| 154  | 9A   | š    | &scaron; |
| 155  | 9B   | ›    | &rsaquo; |
| 156  | 9C   | œ    | &oelig;  |
| 157  | 9D   |      |          |
| 158  | 9E   | ž    |          |
| 159  | 9F   | ÿ    | &yuml;   |
| 160  | A0   |      | &nbsp;   |
| 161  | A1   | ¡    | &iexcl;  |
| 162  | A2   | ¢    | &cent;   |
| 163  | A3   | £    | &pound;  |
| 164  | A4   | ¤    | &curren; |
| 165  | A5   | ¥    | &yen;    |
| 166  | A6   | ¦    | &brvbar; |
| 167  | A7   | §    | &sect;   |
| 168  | A8   | ¨    | &uml;    |
| 169  | A9   | ©    | &copy;   |
| 170  | AA   | ª    | &ordf;   |
| 171  | AB   | «    | &laquo;  |
| 172  | AC   | ¬    | &not;    |
| 173  | AD   | ­    | &shy;    |
| 174  | AE   | ®    | &reg;    |
| 175  | AF   | ¯    | &macr;   |
| 176  | B0   | °    | &deg;    |
| 177  | B1   | ±    | &plusmn; |
| 178  | B2   | ²    | &sup2;   |
| 179  | B3   | ³    | &sup3;   |
| 180  | B4   | ´    | &acute;  |
| 181  | B5   | µ    | &micro;  |
| 182  | B6   | ¶    | &para;   |
| 183  | B7   | ·    | &middot; |
| 184  | B8   | ¸    | &cedil;  |
| 185  | B9   | ¹    | &sup1;   |
| 186  | BA   | º    | &ordm;   |
| 187  | BB   | »    | &raquo;  |
| 188  | BC   | ¼    | &frac14; |
| 189  | BD   | ½    | &frac12; |
| 190  | BE   | ¾    | &frac34; |
| 191  | BF   | ¿    | &iquest; |
| 192  | C0   | À    | &Agrave; |
| 193  | C1   | Á    | &Aacute; |
| 194  | C2   | Â    | &Acirc;  |
| 195  | C3   | Ã    | &Atilde; |
| 196  | C4   | Ä    | &Auml;   |
| 197  | C5   | Å    | &Aring;  |
| 198  | C6   | Æ    | &AElig;  |
| 199  | C7   | Ç    | &Ccedil; |
| 200  | C8   | È    | &Egrave; |
| 201  | C9   | É    | &Eacute; |
| 202  | CA   | Ê    | &Ecirc;  |
| 203  | CB   | Ë    | &Euml;   |
| 204  | CC   | Ì    | &Igrave; |
| 205  | CD   | Í    | &Iacute; |
| 206  | CE   | Î    | &Icirc;  |
| 207  | CF   | Ï    | &Iuml;   |
| 208  | D0   | Ð    | &ETH;    |
| 209  | D1   | Ñ    | &Ntilde; |
| 210  | D2   | Ò    | &Ograve; |
| 211  | D3   | Ó    | &Oacute; |
| 212  | D4   | Ô    | &Ocirc;  |
| 213  | D5   | Õ    | &Otilde; |
| 214  | D6   | Ö    | &Ouml;   |
| 215  | D7   | ×    | &times;  |
| 216  | D8   | Ø    | &Oslash; |
| 217  | D9   | Ù    | &Ugrave; |
| 218  | DA   | Ú    | &Uacute; |
| 219  | DB   | Û    | &Ucirc;  |
| 220  | DC   | Ü    | &Uuml;   |
| 221  | DD   | Ý    | &Yacute; |
| 222  | DE   | Þ    | &THORN;  |
| 223  | DF   | ß    | &szlig;  |
| 224  | E0   | à    | &agrave; |
| 225  | E1   | á    | &aacute; |
| 226  | E2   | â    | &acirc;  |
| 227  | E3   | ã    | &atilde; |
| 228  | E4   | ä    | &auml;   |
| 229  | E5   | å    | &aring;  |
| 230  | E6   | æ    | &aelig;  |
| 231  | E7   | ç    | &ccedil; |
| 232  | E8   | è    | &egrave; |
| 233  | E9   | é    | &eacute; |
| 234  | EA   | ê    | &ecirc;  |
| 235  | EB   | ë    | &euml;   |
| 236  | EC   | ì    | &igrave; |
| 237  | ED   | í    | &iacute; |
| 238  | EE   | î    | &icirc;  |
| 239  | EF   | ï    | &iuml;   |
| 240  | F0   | ð    | &eth;    |
| 241  | F1   | ñ    | &ntilde; |
| 242  | F2   | ò    | &ograve; |
| 243  | F3   | ó    | &oacute; |
| 244  | F4   | ô    | &ocirc;  |
| 245  | F5   | õ    | &otilde; |
| 246  | F6   | ö    | &ouml;   |
| 247  | F7   | ÷    | &divide; |
| 248  | F8   | ø    | &oslash; |
| 249  | F9   | ù    | &ugrave; |
| 250  | FA   | ú    | &uacute; |
| 251  | FB   | û    | &ucirc;  |
| 252  | FC   | ü    | &uuml;   |
| 253  | FD   | ý    | &yacute; |
| 254  | FE   | þ    | &thorn;  |
| 255  | FF   | ÿ    | &yuml;   |