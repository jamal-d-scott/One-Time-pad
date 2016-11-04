/*Corby Rider
*Jamal Scott
*Project 2 section B
*/

#include <stdio.h>

//Creates a variable to be used for all functions which serves as the max input size.
#define LIMIT 2048

//Protoypes for functions after the main.
int readMessage(char message[LIMIT]);
int readKey(char key[LIMIT]);
unsigned char rotate(unsigned char character, int count);
int bits(unsigned char character);
void chain(char key[LIMIT], int length);

int main()
{
	//Creates character arrays to store information.
	char message[LIMIT], key[LIMIT];

	//Variables which the key and message lengths are stored in.
	int messageLength = readMessage(message);
	int keyLength = readKey(key);

	//sets the keylength to the message length if the key is too long.
	if(keyLength >= messageLength)
		keyLength = messageLength;
	else
	{	//Otherwise,Tiles the key if the key is too short. 
		int i;
		for(i = 0; keyLength < messageLength; ++i)
			key[keyLength++] = key[i];
	}

	chain(key, keyLength);
	int i;

	//XORs each element in the key character array with that of the message char array.
	for(i = 0; i < messageLength; ++i)
		putchar(key[i] ^ message[i]);

}
//Function for geting the length of the actual message.
int readMessage(char message[LIMIT])
{
	int c, messageLength = 0;
	
	//Loops which will read up until the delimiter.
	while((c = getchar()) != 255)
		//Stores no more than 2048 characters.
		if(messageLength < LIMIT)
			message[messageLength++] = c;
	return messageLength;
}

//Function for geting the length of the key.
int readKey(char key[LIMIT])
{
	int c, keyLength = 0;
	//Counts until the limit or the end of the file is reached.
	while((c = getchar()) != EOF && keyLength < LIMIT)
		key[keyLength++] = c;
	return keyLength;
}

//Function for rotating the least significant bits.
unsigned char rotate(unsigned char character, int count)
{
	return (character >> count | character << 7 - count) & 0x7F;
}

//Function that counts the number of 1 bits.
int bits(unsigned char character)
{
	int bitCount = 0;
	while(character)
	{
		bitCount += character & 1;
		character >>= 1;
	}
	return bitCount;
}

//Function for chaining.
void chain(char key[LIMIT], int length)
{
	int i;
	char prev = key[length - 1];
	int sum = prev % length;
	for(i = 0; i < length; ++i)
	{
		//Chains the key.
		key[i] = rotate(key[i] ^ key[sum], bits(prev));	

		//Keeps the running sum of character values.
		sum = (sum + key[i]) % length;
		prev = key[i];
	}
}
