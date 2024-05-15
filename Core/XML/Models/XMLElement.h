#pragma once
#include <ostream>
#include "../../../Utils/MyString/MyString.h"
class XMLElement
{
	MyString _textContent;
protected:
	virtual std::ostream& print(std::ostream& os) const;
public:
	XMLElement() = default;
	explicit XMLElement(const MyString& textContent);

	const MyString& textContent() const;
	void setTextContent(const MyString& textContent);
	friend std::ostream& operator<<(std::ostream& os, const XMLElement& element);
};