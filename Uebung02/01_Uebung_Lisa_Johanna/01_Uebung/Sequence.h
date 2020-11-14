#ifndef BIOINFOI_SEQUENCE_H
#define BIOINFOI_SEQUENCE_H

#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <istream>
#include <ostream>

/**
 * Generic implementation of a sequence class.
 *
 * This class takes an Alphabet as type parameter.
 * The Alphabet defines which characters are representable
 * by the sequence. To do so, the Alphabet class must
 * define a "Characters" enum, which defines the characters
 * stored in the sequence.
 *
 * Additionally, it is assumed to offer the static
 * toChar and toCharacter methods for conversion between
 * chars and the internal representation.
 */
template <typename Alpha> class Sequence
{
  public:
	/**
	 * Some defines that can be used throughout the program.
	 */
	using Alphabet = Alpha;
	using Characters = typename Alphabet::Characters;

	/**
	 * Defines how the data is stored internally.
	 *
	 * Can be changed if desired.
	 */
	using Container = std::vector<Characters>;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;

	/**
	 * Converts the given string to a sequence.
	 *
	 * @throw InvalidCharacter if a character in seq
	 *        is not valid.
	 */
	static Sequence fromString(const std::string& seq) {
		Sequence sequence;
		std::string::const_iterator iter;
		for (iter = seq.begin(); iter != seq.end(); iter++) {
			sequence.push_back(Alphabet::toCharacter(*iter));
		}
		return sequence;
	}

	/**
	 * Default constructor.
	 */
	Sequence<Alphabet>(): storage_(), comment_() {}

	/**
	 * Returns a string representing the sequence.
	 */
	std::string toString() const {
		std::string rep = "";
		for(unsigned int iter = 0; iter < size(); iter++) {
			Characters character = storage_[iter];
			char chars = Alphabet::toChar(character);
			rep.push_back(chars);
		}
		return rep;
	}
	
	std::string to2Bit() const {
		std::string binary;
		std::string mask;
		const_iterator iter;
		for (iter = begin(); iter != end(); iter++) {
			binary += Alphabet::to2Bit(*iter);
			mask += Alphabet::to2BitMask(*iter);
		}
		//we have to add 00 until we can divide by 4
		unsigned int seq_size = size();
		while(seq_size % 4) {
			seq_size++;
			binary += "00";
			mask += "00";
		}
		return binary + mask;	
	}

	/// Mutable iterator pointing to the begin of the sequence.
	iterator begin() {
		return storage_.begin();
	}

	/// Mutable iterator pointing 'past-the-end' of the sequence.
	iterator end() {
		return storage_.end();
	}

	/// Constant iterator pointing to the begin of the sequence.
	const_iterator begin() const {
		const_iterator iter =  storage_.begin();
		return iter; 
	}

	/// Constant iterator pointing 'past-the-end' of the sequence.
	const_iterator end() const {
		const_iterator iter = storage_.end();
		return iter;
	}

	/// Constant iterator pointing to the begin of the sequence.
	const_iterator cbegin() const {
		return storage_.cbegin();
	}

	/// Constant iterator pointing 'past-the-end' of the sequence.
	const_iterator cend() const {
		return storage_.cend();
	}

	/**
	 * Returns the length of the sequence
	 */
	size_t size() const {
		return storage_.size();
	}

	/**
	 * Removes all entries from the sequence
	 */
	void clear() {
		Container helper;
		storage_ = helper;
	}

	/**
	 * Make the sequence larger or smaller.
	 *
	 * If the sequence is made larger, new Characters are appended
	 * to the existing sequence, while the old Characters are left intact.
	 * Which Characters are added is undefined.
	 *
	 * Otherwise, only as many characters as needed are removed,
	 * the remaining Characters are again left intact.
	 */
	void resize(size_t i) {
		storage_.resize(i);
	}

	/**
	 * This method ensures, that there are at least i bytes of
	 * internal storage for adding new Characters.
	 */
	void reserve(size_t i) {
		storage_.reserve(i);
	}

	/**
	 * Append a single character at the end of the sequence, resulting
	 * in a sequence of size() + 1
	 */
	void push_back(Characters c) {
		storage_.push_back(c);
	}

	/**
	 * Get the comment of the sequence.
	 */
	const std::string& getComment() const {
		return comment_ ;
	}

	/**
	 * Set the comment of the sequence.
	 */
	void setComment(const std::string& comment) {
		comment_ = comment;
	}

	/**
	 * Compares two sequences with offset i.
	 *
	 * @param seq The second sequence with which to compare
	 * @param i   The offset in the first sequence.
	 *
	 * @return true if the first sequence starting at i is
	 *         equal to the second sequence.
	 */
	//compares seq's content with storage_'s contet from index i+j to index i+seq.size
	bool compare(const Sequence& seq, size_t i) const {
		bool b = true;
		if ((storage_.size() - i) != seq.size()) {
			return false;
		}
		for (unsigned int j = 0; j < seq.size(); j++) {
			if (storage_[i + j] != seq[j]) {
				b = false;
				break;
			} else {
				continue;
			}
		}
		return b;
	}

	/**
	 * Compute the maximum overlap between the end
	 * of this sequence with the beginning of seq.
	 */
	size_t overlap(const Sequence& seq) const {
		size_t overlap_size = 0;
		size_t max = size();
		if (seq.size() < max) {
			max = seq.size();
		}
		/*
		 * we use our compare method to compute the overlap
		 * but to do so we need just a piece of the sequence	
		 */
		for (unsigned int i =  0; i <= max; i++) {
			Sequence helper = seq;
			if (helper.size() > i) {
				helper.resize(i);
			}		
			if (compare(helper, size() - i)) {
				overlap_size = i;
			}
		}
		return overlap_size;
	}

	/**
	 * Return a map that contains for each character
	 * how often it is present in the sequence.
	 *
	 * Characters that are not present in the sequence
	 * should not have an entry in the returned map.
	 */
	std::map<Characters, size_t> statistics() const {
		const_iterator iter;
		std::map<Characters, size_t> map;
		for (iter = cbegin(); iter != cend(); iter++) {
			Characters character = Alphabet::canonicalize(*iter);
			typename std::map<Characters, size_t>::iterator mapIter = map.find(character);
			if (mapIter != map.end()) {
				//element found
				map[character]++;
			} else {
				map.insert(std::pair<Characters, size_t>(character, 1));
			}
		}
		return map;
	}

	// Operators

	/**
	 * Return the i-th character of the sequence.
	 */
	Characters& operator[](size_t i) {
		return storage_[i];
	}

	/**
	 * Return the i-th character of the sequence.
	 */
	Characters operator[](size_t i) const {
		return storage_[i];
	}

	/**
	 * Equality operator.
	 */
	bool operator==(const Sequence& seq) const {
		return compare(seq, 0);
	}

	/**
	 * Inequality operator.
	 */
	bool operator!=(const Sequence& seq) const {
		return !compare(seq,0);
	}

	/**
	 * Global output operator
	 */
	template <typename A>
	friend std::ostream& operator<<(std::ostream& os, const Sequence<A>& seq);

	/**
	 * Global input operator
	 */
	template <typename A>
	friend std::istream& operator>>(std::istream& in, Sequence<A>& sequence);
		

  protected:
	/**
	 * The internal storage of the sequence
	 */
	Container storage_;

	/**
	 * An additional string that can be used to store the name of the sequence.
	 */
	std::string comment_;
};

template <typename A>
std::ostream& operator<<(std::ostream& os, const Sequence<A>& seq) {
        os << seq.toString();
        return os;
}

template <typename A>
std::istream& operator>>(std::istream& in, Sequence<A>& sequence) {
        std::string seq;
        in >> seq;
        std::string::iterator iter;
        for (iter  = seq.begin(); iter != seq.end(); iter++) {
              	sequence.push_back(A::toCharacter(*iter));
      	}
	return in;
}



#endif // BIOINFOI_SEQUENCE_H
