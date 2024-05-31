#include "XMLTextNodeBuilder.h"

XMLTextNodeBuilder::XMLTextNodeBuilder(DataReader& reader) : XMLBuilder(reader)
{
    _node = MySharedPtr<XMLTextNode>(new XMLTextNode());
}

void XMLTextNodeBuilder::buildContent()
{
    MyString content = _reader.readPlainText();
    _node->setTextContent(content);
}

MySharedPtr<XMLTextNode> XMLTextNodeBuilder::flush(MyWeakPtr<XMLElementNode> parent)
{
    _node->setParent(parent);
    parent->addChild(_node);

    MySharedPtr<XMLTextNode> result = _node;
    _node = MySharedPtr<XMLTextNode>(new XMLTextNode());
    return result;
}
