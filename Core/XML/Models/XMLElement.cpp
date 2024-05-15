#include "XMLElement.h"

std::ostream& XMLElement::print(std::ostream& os) const
{
    return os << _textContent;
}

XMLElement::XMLElement(const MyString& textContent)
{
    setTextContent(textContent);
}

const MyString& XMLElement::textContent() const
{
    return _textContent;
}

void XMLElement::setTextContent(const MyString& textContent)
{
    _textContent = textContent;
}

std::ostream& operator<<(std::ostream& os, const XMLElement& element)
{
    return element.print(os);
}
