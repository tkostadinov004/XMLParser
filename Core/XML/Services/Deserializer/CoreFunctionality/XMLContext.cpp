#include "XMLContext.h"

XMLDocument XMLContext::finish() const
{
	if (!_tags.empty())
	{
		MyString unclosedTags = join(_tags.convertTo<MyString>([](const MyString& tag) {return tag;}), ", ");
		throw std::exception(MyString("Opening tags for: " + unclosedTags + " are not defined!").c_str());
	}
    return XMLDocument(_resultRoot);
}

XMLContext::XMLContext(DataReader& reader) : _elementNodeBuilder(reader), _textNodeBuilder(reader)
{
}

void XMLContext::createTag()
{
	_elementNodeBuilder.buildTagName();
	if (_elementNodeBuilder.getTagStatus() == TagStatus::Open)
	{
		_tags.push(_elementNodeBuilder.getFullTagName());
	}
}

void XMLContext::createAttributes()
{
	_elementNodeBuilder.buildAttributes();
	if (_elementNodeBuilder.getTagStatus() == TagStatus::SelfClosing)
	{
		_tags.pop();
	}
}

void XMLContext::flushElementNode()
{
	TagStatus tagStatus = _elementNodeBuilder.getTagStatus();
	MySharedPtr<XMLElementNode> flushedNode = _elementNodeBuilder.flush(_previousParent);
	if (!_resultRoot)
	{
		_previousParent = _resultRoot = flushedNode;
	}
	else if(tagStatus == TagStatus::Open)
	{
		_previousParent = flushedNode;
	}
}

void XMLContext::flushTextNode()
{
	_textNodeBuilder.flush(_previousParent);
}

void XMLContext::closeTag()
{
	MyString closingTag = _elementNodeBuilder.getClosingTagForValidation();
	if (closingTag != _tags.peek())
	{
		MyString peek = _tags.peek();
		throw std::logic_error("Opening tag missing!");
	}
	_tags.pop();
	_previousParent = _previousParent->parent();
}

void XMLContext::createPlainText()
{
	_textNodeBuilder.buildContent();
}

