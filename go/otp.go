// This file contains a simple implementation of the one-time pad.
// It is NOT intended for production usage and has not been extensively verified for it.
// This file is simply an educational tool for AN implementation that works.
package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"
)

// Initializing seed for random number generator
var seededRand *rand.Rand = rand.New(rand.NewSource(time.Now().UnixNano()))

func main() {

	text := `Do not go gentle into that good night,
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

	pad := generatePad(len(text))
	fmt.Printf("Pad is: %s", pad)

	ciphertext := encrypt(text, pad)
	fmt.Printf("\nCiphertext is: %s", ciphertext)

	plaintext := decrypt(pad, ciphertext)
	fmt.Printf("\nPlaintext is: %s", plaintext)
}

// Generates a pad of random characters
func generatePad(length int) string {
	var pad string

	// The random characters to be chosen from
	const characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

	// Add characters to the pad until it is the specified length

	for i := 0; i < length; i++ {
		pad += string(characters[seededRand.Intn(len(characters))])
	}

	save(pad, "pad.txt")
	return pad
}

// Encrypts the input text and returns the pad and ciphertext
func encrypt(text string, pad string) string {
	var ciphertext string

	// The result of the XORing of the current original text and pad characters in the iteration
	var xoredValue int

	for i := range pad {
		xoredValue = int(text[i]) ^ int(pad[i])

		// Store the character representation of xoredValue to the ciphertext string
		ciphertext += string(xoredValue)
	}

	save(ciphertext, "ciphertext.txt")
	return ciphertext
}

// Decrypts the ciphertext using the provided pad
func decrypt(pad string, ciphertext string) string {
	var plaintext string

	// The result of the XORing of the current pad and ciphertext characters in the iteration
	var xoredValue int

	for i := range pad {
		xoredValue = int(ciphertext[i]) ^ int(pad[i])

		// Store the character representation of xoredValue to the plaintext string
		plaintext += string(xoredValue)
	}

	save(plaintext, "plaintext.txt")
	return plaintext
}

// Takes in text and saves it to the provided path
func save(text string, path string) {
	file, err := os.Create(path)
	if err != nil {
		panic(err)
	}
	file.Write([]byte(text))
	defer file.Close()
}
