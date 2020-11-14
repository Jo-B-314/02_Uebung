#include "RNA.h"

#include "InvalidCharacter.h"

#include <cassert>

namespace Alphabet
{
RNA::Characters RNA::toCharacter(char c)
{
	switch(c) {
		case 'a':
		case 'A': return RNA::Characters::A;
		case 'g':
		case 'G': return RNA::Characters::G;
		case 'c':
		case 'C': return RNA::Characters::C;
		case 'u':
		case 'U': return RNA::Characters::U;
		default: throw InvalidCharacter(c);
	}
}

char RNA::toChar(RNA::Characters c)
{
	switch(c) {
		case RNA::Characters::A: return 'A';
		case RNA::Characters::C: return 'C';
		case RNA::Characters::G: return 'G';
		case RNA::Characters::U: return 'U';
	}
}
}
