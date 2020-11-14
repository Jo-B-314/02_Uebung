#ifndef BIOINFOI_2BIT_H
#define BIOINFOI_2BIT_H

#include "Sequence.h"
#include "DNA.h"

#include <istream>
#include <ostream>

/**
 * A simple helper class used to signal
 * that we want to write a DNA sequence in 2Bit format.
 */
class Sequence2BitWriter
{
  public:
	Sequence2BitWriter(const Sequence<Alphabet::DNA>& seq);

	Sequence<Alphabet::DNA> getSequence() const {
		return seq_;
	}

	/// Global input operator
	friend std::ostream& operator<<(std::ostream& strm,
	                                const Sequence2BitWriter&);

  private:
	/// Stores a reference to the sequence to write.
	const Sequence<Alphabet::DNA>& seq_;
};

/**
 * A simple helper class used to signal
 * that we want to read a DNA sequence in 2Bit format.
 */
class Sequence2BitReader
{
  public:
	Sequence2BitReader(Sequence<Alphabet::DNA>& seq);

	Sequence<Alphabet::DNA>& getSequence() {
		return seq_;
	}

	/// Global input operator (Needs an rvalue reference to work with from2Bit...)
	friend std::istream& operator>>(std::istream& strm, Sequence2BitReader&&);

  private:
	/// Stores a reference to the sequence to read.
	Sequence<Alphabet::DNA>& seq_;
};

/// Helper function for creating a Sequence2BitWriter
Sequence2BitWriter to2Bit(const Sequence<Alphabet::DNA>&);

/// Helper function for creating a Sequence2BitReader
Sequence2BitReader from2Bit(Sequence<Alphabet::DNA>&);

#endif // BIOINFOI_2BIT_H

