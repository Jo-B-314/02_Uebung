#include<string>

#ifndef BIOINFOI_PEPTIDE_H
#define BIOINFOI_PEPTIDE_H

namespace Alphabet
{

/**
 * Class implementing the conversion and validation
 * of string charactes to sequence characters
 */
class Peptide
{
  public:
	/// The characters available for a Peptide
	enum class Characters {
		Ala,
		Arg,
		Asn,
		Asp,
		Cys,
		Gln,
		Glu,
		Gly,
		His,
		Ile,
		Leu,
		Lys,
		Met,
		Phe,
		Pro,
		Ser,
		Thr,
		Trp,
		Tyr,
		Val
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

	static Characters canonicalize(Characters c) { return c;}

        /**
         * returns an empty string because toBit is just for DNA
         */
	static std::string to2Bit(Characters c) {
		return "";
	}

        /**
         * returns an empty string because toBit is just for DNA
         */
	static std::string to2BitMask(Characters c) {
		return "";
	}

};
}

#endif // BIOINFOI_Peptide_H
