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

const XMLElementNodeWithID* XMLRepository::find(std::function<bool(const XMLElementNodeWithID*)> pred) const
{
    MyStack<const XMLNode*> stack;

    stack.push(_xmlDocument.root());
    while (!stack.empty())
    {
        const XMLNode* current = stack.pop();
        if (const XMLElementNodeWithID* nodeWithChildren = dynamic_cast<const XMLElementNodeWithID*>(current))
        {
            if (pred(nodeWithChildren))
            {
                return nodeWithChildren;
            }

            for (int i = nodeWithChildren->children().size() - 1; i >= 0; i--)
            {
                stack.push(nodeWithChildren->children()[i].get());
            }
        }
    }
    return nullptr;
}

XMLElementNodeWithID* XMLRepository::find(std::function<bool(const XMLElementNodeWithID*)> pred)
{
    MyStack<XMLNode*> stack;

    stack.push(_xmlDocument.root());
    while (!stack.empty())
    {
        XMLNode* current = stack.pop();
        if (XMLElementNodeWithID* nodeWithChildren = dynamic_cast<XMLElementNodeWithID*>(current))
        {
            if (pred(nodeWithChildren))
            {
                return nodeWithChildren;
            }

            for (int i = nodeWithChildren->children().size() - 1; i >= 0; i--)
            {
                stack.push(nodeWithChildren->children()[i].get());
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
