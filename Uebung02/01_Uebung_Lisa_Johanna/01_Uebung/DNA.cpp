#include "DNA.h"

#include "InvalidCharacter.h"
#include "ParsingException.h"

#include <cassert>

namespace Alphabet
{

DNA::Characters DNA::toCharacter(char c)
{
	/*
	 * I'm sorry using switch case I know it's not a good programming style
	 * but I don't see any better way
	 */
	switch (c) {
		case 'a': return DNA::Characters::a;
		case 'A': return DNA::Characters::A;
		case 'g': return DNA::Characters::g;
		case 'G': return DNA::Characters::G;
		case 'c': return DNA::Characters::c;
		case 'C': return DNA::Characters::C;
		case 't': return DNA::Characters::t;
		case 'T': return DNA::Characters::T;
		case 'n':
		case 'N': return DNA::Characters::N;
		default: throw InvalidCharacter(c);
	}
}

char DNA::toChar(Characters c)
{
	switch (c) {
		case DNA::Characters::A: return 'A';
		case DNA::Characters::a: return 'a';
		case DNA::Characters::G: return 'G';
		case DNA::Characters::g: return 'g';
		case DNA::Characters::C: return 'C';
		case DNA::Characters::c: return 'c';
		case DNA::Characters::T: return 'T';
		case DNA::Characters::t: return 't';
		case DNA::Characters::N: return 'N';
	}
}

DNA::Characters DNA::canonicalize(Characters c)
{
	switch (c) {
        case DNA::Characters::a: return DNA::Characters::A;
        case DNA::Characters::g: return DNA::Characters::G;
		case DNA::Characters::c: return DNA::Characters::C;
		case DNA::Characters::t: return DNA::Characters::T;
		default: return c;
        }
}

std::string DNA::to2Bit(Characters c)
{
	switch (c) {
		case DNA::Characters::N:
		case DNA::Characters::g:
		case DNA::Characters::G: return "00";
		case DNA::Characters::a:
		case DNA::Characters::A: return "01";
		case DNA::Characters::t:
		case DNA::Characters::T: return "10";
		case DNA::Characters::c:
		case DNA::Characters::C: return "11";
	}
}

std::string DNA::to2BitMask(Characters c)
{
	switch (c) {
		case DNA::Characters::G:
		case DNA::Characters::A:
		case DNA::Characters::C:
		case DNA::Characters::T: return "00";
		case DNA::Characters::N: return "10";
		default: return "01";
	}
}

DNA::Characters DNA::from2Bit(const std::string str) 
{
	//str.compare() returns 0 if the strings are equal
	if (!str.compare("00")) return DNA::Characters::G; 
	if (!str.compare("01")) return DNA::Characters::A;
	if (!str.compare("10")) return DNA::Characters::T;
	if (!str.compare("11")) return DNA::Characters::C;
	throw ParsingException("not a 2bit Sequence");
}

DNA::Characters DNA::intron(Characters c) 
{
	switch (c) {
		case DNA::Characters::G: return DNA::Characters::g;
		case DNA::Characters::C: return DNA::Characters::c;
		case DNA::Characters::T: return DNA::Characters::t;
		case DNA::Characters::A: return DNA::Characters::a;
		default: return c;
	}
}

DNA::Characters DNA::from2BitMask(const std::string str, Characters c)
{
	//string.compare returns 0 if the strings are equal
	if (!str.compare("00")) return canonicalize(c);
	if (!str.compare("10")) return DNA::Characters::N;
	if (!str.compare("01")) return intron(c);
	throw ParsingException("not a 2bit mask");
}
}
