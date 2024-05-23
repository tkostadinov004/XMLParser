#include <sstream>
#include "XMLRepository.h"
#include "..\Services\XMLDeserializer.h"
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

const MySharedPtr<XMLElementNodeWithID> XMLRepository::find(std::function<bool(const XMLElementNodeWithID*)> pred) const
{
    MyStack<MySharedPtr<XMLNode>> stack;

    stack.push(_xmlDocument.root().get());
    while (!stack.empty())
    {
        const MySharedPtr<XMLElementNodeWithID> current = dynamic_cast<XMLElementNodeWithID*>(stack.pop().get());
        if (current)
        {
            if (pred(current.get()))
            {
                return current;
            }

            for (int i = current->children().size() - 1; i >= 0; i--)
            {
                stack.push(current->children()[i]);
            }
        }
    }
    return nullptr;
}

MySharedPtr<XMLElementNodeWithID> XMLRepository::find(std::function<bool(const XMLElementNodeWithID*)> pred)
{
    MyStack<MySharedPtr<XMLNode>> stack;

    stack.push(_xmlDocument.root().get());
    while (!stack.empty())
    {
        MySharedPtr<XMLElementNodeWithID> current = dynamic_cast<XMLElementNodeWithID*>(stack.pop().get());
        if (current)
        {
            if (pred(current.get()))
            {
                return current;
            }

            for (int i = current->children().size() - 1; i >= 0; i--)
            {
                stack.push(current->children()[i]);
            }
        }
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
