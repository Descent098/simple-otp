function generatePad(textLength) {
    var pad = "";

    for (var i = 0; i < textLength; i++){
      randomNumber = Math.floor(Math.random() * 256);  // returns a random integer from 0 to 256
        randomLetter = String.fromCharCode(randomNumber);
        pad += randomLetter;
    }

    return pad;
}

function encrypt(text, pad){
    ciphertext = "";

    var xoredValue;

    for (var i = 0; i < pad.length; i++){
        xoredValue = text.charCodeAt(i) ^ pad.charCodeAt(i);
        ciphertext += String.fromCharCode(xoredValue);
    }

    return ciphertext;
}

function decrypt(pad, ciphertext){
    plaintext = "";

    var xoredValue;

    for (var i = 0; i < pad.length; i++){
        xoredValue = ciphertext.charCodeAt(i) ^ pad.charCodeAt(i);
        plaintext += String.fromCharCode(xoredValue);
    }

    return plaintext;
}

text = `Do not go gentle into that good night,
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
Rage, rage against the dying of the light.`

var pad = generatePad(text.length);
console.log("Pad is: " + pad);
document.getElementById("pad").innerText = pad;

var ciphertext = encrypt(text, pad);
console.log("Ciphertext is: " + ciphertext);
document.getElementById("ciphertext").innerText = ciphertext;

var plaintext = decrypt(pad, ciphertext);
console.log("Plaintext is: " + plaintext);
document.getElementById("plaintext").innerText = plaintext;
