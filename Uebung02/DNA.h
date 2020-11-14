#include<string>

#ifndef BIOINFOI_DNA_H
#define BIOINFOI_DNA_H

namespace Alphabet
{

/**
 * Class implementing the conversion and validation
 * of string charactes to sequence characters
 */
class DNA
{
  public:
	/// The characters available for DNA
	enum class Characters {
		a, // Adenine intron
		A, // Adenine exon
		c, // Cytosine intron
		C, // Cytosine exon
		t, // Thymine intron
		T, // Thymine exon
		g, // Guanine intron
		G, // Guanine exon
		N  // Unknown. Valid characters are 'N' and 'n'.
	};

	/**
	 * Converts a char to a Character. The conversion is case insensitive.
	 * Throws an InvalidCharacter exception if the passed char is invalid.
	 */
	static Characters toCharacter(char c);

	/**
	 * Converts a Character to an upper-case char.
	 */
	static char toChar(Characters c);

	static Characters canonicalize(Characters c);
	
	/**
	 * Converts a Character to a 2Bit String
	 */
	static std::string to2Bit(Characters c);

	/**
	 * returns the mask for the given Character
	 */
	static std::string to2BitMask(Characters c);

	/**
	 * returns the Character for the given 2Bit which are stored in a string
	 */
	static Characters from2Bit(const std::string str);

	/**
	 * computes the Character from a 2BitMask with the mask and the Character from the sequence
	 */
	static Characters from2BitMask(const std::string str, Characters c);

	/**
	 * returns an intron Character
	 */
	static Characters intron(Characters c);
};
}

#endif // BIOINFOI_DNA_H
