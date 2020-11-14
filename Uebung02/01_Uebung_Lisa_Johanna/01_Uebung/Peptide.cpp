#include "Peptide.h"

#include "InvalidCharacter.h"

#include <cassert>

namespace Alphabet
{
Peptide::Characters Peptide::toCharacter(char c)
{
	/*
	 * toupper(char c) converts the char to its upper-case if exits
	 * -> so our function is case insensitive
	 */
	char newC = std::toupper(c);

	//used the code table from wikiedia
	switch (newC) {
		case 'A': return Peptide::Characters::Ala;
		case 'R': return Peptide::Characters::Arg;
		case 'N': return Peptide::Characters::Asn;
		case 'D': return Peptide::Characters::Asp;
		case 'C': return Peptide::Characters::Cys;
		case 'Q': return Peptide::Characters::Gln;
		case 'E': return Peptide::Characters::Glu;
		case 'G': return Peptide::Characters::Gly;
		case 'H': return Peptide::Characters::His;
		case 'I': return Peptide::Characters::Ile;
		case 'L': return Peptide::Characters::Leu;
		case 'K': return Peptide::Characters::Lys;
		case 'M': return Peptide::Characters::Met;
		case 'F': return Peptide::Characters::Phe;
		case 'P': return Peptide::Characters::Pro;
		case 'S': return Peptide::Characters::Ser;
		case 'T': return Peptide::Characters::Thr;
		case 'W': return Peptide::Characters::Trp;
		case 'Y': return Peptide::Characters::Tyr;
		case 'V': return Peptide::Characters::Val;
		default: throw InvalidCharacter(c);
	}

}

char Peptide::toChar(Peptide::Characters c)
{
	switch (c) {
		case Peptide::Characters::Ala: return 'A';
		case Peptide::Characters::Arg: return 'R';
		case Peptide::Characters::Asn: return 'N';
		case Peptide::Characters::Asp: return 'D';
		case Peptide::Characters::Cys: return 'C';
		case Peptide::Characters::Gln: return 'Q';
		case Peptide::Characters::Glu: return 'E';
		case Peptide::Characters::Gly: return 'G';
		case Peptide::Characters::His: return 'H';
		case Peptide::Characters::Ile: return 'I';
		case Peptide::Characters::Leu: return 'L';
		case Peptide::Characters::Lys: return 'K';
		case Peptide::Characters::Met: return 'M';
		case Peptide::Characters::Phe: return 'F';
		case Peptide::Characters::Pro: return 'P';
		case Peptide::Characters::Ser: return 'S';
		case Peptide::Characters::Thr: return 'T';
		case Peptide::Characters::Trp: return 'W';
		case Peptide::Characters::Tyr: return 'Y';
		case Peptide::Characters::Val: return 'V';
	}
}
}

