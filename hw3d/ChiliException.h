#pragma once
#include <exception>
#include <string>

class ChiliException: public std::exception
{
public:
	ChiliException(int line, const char* file) noexcept;
	//will print out type,line no and file of exception
	const char* what() const noexcept override;
	//will give type name of exception
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;;
	const std::string& GetFile() const noexcept;
	//formats the line and file in one string
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};

