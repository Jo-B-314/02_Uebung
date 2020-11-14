#ifndef BIOINFOI_INVALID_CHARACTER_H
#define BIOINFOI_INVALID_CHARACTER_H

#include <exception>
#include <string>

class InvalidCharacter : public std::exception
{
  public:
	InvalidCharacter(char c);
	const char* what() const noexcept override;

  private:
	std::string msg_;
};

#endif //BIOINFOI_INVALID_CHARACTER_H

