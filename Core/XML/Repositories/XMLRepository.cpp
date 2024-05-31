#include <sstream>
#include "XMLRepository.h"
#include "..\Services/Deserializer\XMLDeserializer.h"
#include "..\Services\XMLSerializer.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"
#include "..\..\XPath\Services\XPathQuery.h"

void XMLRepository::open(const MyString& path)
{
    XMLDeserializer deserializer(path);
    _xmlDocument = deserializer.deserialize();
}

void XMLRepository::close()
{
    _xmlDocument = XMLDocumentWithID();
}

void XMLRepository::saveAs(const MyString& path)
{
    XMLSerializer serializer(path);
    serializer.serializeToStream(_xmlDocument);
}

void XMLRepository::add(const XMLElementNodeWithID& item)
{
}

bool XMLRepository::remove(const XMLElementNodeWithID& item)
{
    return false;
}

bool XMLRepository::remove(const MyString& id)
{
    return false;
}

MyString XMLRepository::getContents() const
{
    std::stringstream ss;
    ss << _xmlDocument;
    return MyString(ss.str().c_str());
}

const MySharedPtr<XMLElementNodeWithID> XMLRepository::find(std::function<bool(const MySharedPtr<XMLElementNodeWithID>)> pred) const
{
    MyStack<MySharedPtr<XMLNode>> stack;

    stack.push(_xmlDocument.root());
    while (!stack.empty())
    {
        const MySharedPtr<XMLNode> current = stack.peek();
        if (XMLElementNodeWithID* currentChild = dynamic_cast<XMLElementNodeWithID*>(current.get()))
        {
            if (pred(current))
            {
                return current;
            }

            for (int i = currentChild->children().size() - 1; i >= 0; i--)
            {
                stack.push(currentChild->children()[i]);
            }
        }
        stack.pop();
    }
    return nullptr;
}

MySharedPtr<XMLElementNodeWithID> XMLRepository::find(std::function<bool(MySharedPtr<XMLElementNodeWithID>)> pred)
{
    MyStack<MySharedPtr<XMLNode>> stack;

    stack.push(_xmlDocument.root());
    while (!stack.empty())
    {
        MySharedPtr<XMLNode> current = stack.peek();
        if (XMLElementNodeWithID* currentChild = dynamic_cast<XMLElementNodeWithID*>(current.get()))
        {
            if (pred(current))
            {
                return current;
            }

            for (int i = currentChild->children().size() - 1; i >= 0; i--)
            {
                stack.push(currentChild->children()[i]);
            }
        }
        stack.pop();
    }
    return nullptr;
}

void XMLRepository::resolveIdConflicts()
{
    _xmlDocument.resolveIdConflicts();
}

MyVector<MyString> XMLRepository::handleXPath(const MyString& query) const
{
    XPathQuery xPath;
    return xPath.evaluate(_xmlDocument.root(), query);
}
