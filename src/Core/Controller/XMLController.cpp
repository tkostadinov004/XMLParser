#include "XMLController.h"
#include "..\..\Utils\Exceptions\FileError.h"
#include "..\XML\Exceptions\XMLException.h"
#include "..\XPath\ResultSerializers\XPathQueryResultSerializer.h"

void XMLController::openFile(const MyString& path)
{
	if (_repository.isOpen())
	{
		throw FileError(OutputMessageBuilder::FILE_ALREADY_OPENED(_currentFileName, path.split('\\').back_or_default()));
	}

	_repository.open(path);
	_currentFilePath = path;
	_currentFileName = path.split('\\').back_or_default();
	std::cout << OutputMessageBuilder::SUCCESSFULLY_OPENED_FILE(path) << std::endl;
}

void XMLController::closeFile()
{
	if (!_repository.isOpen())
	{
		throw FileError(OutputMessageBuilder::FILE_NOT_OPENED(_currentFileName));
	}

	_repository.close();
	_currentFilePath.clear();
	_currentFileName.clear();
	std::cout << OutputMessageBuilder::SUCCESSFULLY_CLOSED_FILE(_currentFileName) << std::endl;
}

void XMLController::save()
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}
	_repository.saveAs(_currentFilePath);

	std::cout << OutputMessageBuilder::SUCCESSFULLY_SAVED_FILE(_currentFileName) << std::endl;
}

void XMLController::saveAs(const MyString& path)
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}
	_repository.saveAs(path);

	std::cout << OutputMessageBuilder::SUCCESSFULLY_SAVED_FILE(path.split('\\').back_or_default()) << std::endl;
}

void XMLController::help() const
{
	std::cout << "The following commands are supported:\n";
	std::cout << "open <file>\t\t\t\topens <file>\n";
	std::cout << "close\t\t\t\tcloses currently opened file\n";
	std::cout << "save\t\t\t\tsaves the currently open file\n";
	std::cout << "saveas <file>\t\t\t\tsaves the currently open file in <file>\n";
	std::cout << "help\t\t\t\tprints this information menu\n";
	std::cout << "exit\t\t\t\texists the program\n";
	std::cout << "print\t\t\t\t prints the deserialized data from a file that you've opened\n";
	std::cout << "select \"id\" \"attributeName\"\t\t\t\t prints the value of an attribute by a given id of a node and an attribute name\n";
	std::cout << "set \"id\" \"attributeName\" \"newValue\"\t\t\t\t changes the value of an attribute of a given node\n";
	std::cout << "children \"id\"\t\t\t\t prints a list of the children of a given node\n";
	std::cout << "child \"id\" \"n\" \t\t\t\t prints the n-th child of a given node\n";
	std::cout << "text \"id\" \t\t\t\t prints the inner text of a given node\n";
	std::cout << "delete \"id\" \"attributeName\"\t\t\t\t deletes an attribute of a given node\n";
	std::cout << "newChild \"id\" \"tagName\"\t\t\t\t adds a new child node to a given node\n";
	std::cout << "xpath \"query\" \t\t\t\t performs simple XPath queries\n";
}

void XMLController::print() const
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}
	std::cout << _repository.getContents() << std::endl;
}

void XMLController::selectAttribute(const MyString& nodeId, const MyString& attributeName) const
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}

	const XMLAttribute* attribute = selectedNode->attributes()[attributeName];
	if (!attribute)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_ATTRIBUTE_IN_NODE(attributeName, nodeId));
	}

	std::cout << attribute->getValue() << std::endl;
}

void XMLController::changeAttributeValue(const MyString& nodeId, const MyString& attributeName, const MyString& newValue)
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}

	const XMLAttribute* attribute = selectedNode->attributes()[attributeName];
	if (!attribute)
	{
		selectedNode->addAttribute(XMLAttribute(attributeName, newValue));
	}
	else
	{
		selectedNode->changeAttribute(attributeName, newValue);
		if (attributeName == "id")
		{
			selectedNode->setId(newValue);
			_repository.resolveIdConflicts();
		}
	}

	std::cout << OutputMessageBuilder::SUCCESSFULLY_CHANGED_ATTRIBUTE(attributeName, newValue);
}

void XMLController::printChildrenOfNode(const MyString& nodeId) const
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}

	std::cout << selectedNode->children().size() << " children of node with id: " << nodeId << std::endl;
	std::cout << "{";
	if (!selectedNode->children().empty())
	{
		std::cout << std::endl;
	}

	for (size_t i = 0; i < selectedNode->children().size(); i++)
	{
		const XMLElementNodeWithID* childNode = dynamic_cast<const XMLElementNodeWithID*>(selectedNode->children()[i].get());
		std::cout << "\t";
		if (!childNode)
		{
			std::cout << "Text node with content: \"";
			selectedNode->children()[i]->print(std::cout);
			std::cout << "\"";
		}
		else
		{
			MyVector<MyString> attributes = childNode->attributes().convertTo<MyString>([](const XMLAttribute& attribute) {return attribute.toString();});
			std::cout << "Element node with attributes: {" << join(attributes, ", ") << "}";
		}
		std::cout << std::endl;
	}
	std::cout << "}" << std::endl;
}

void XMLController::printNthChild(const MyString& nodeId, int childIndex) const
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}

	if (childIndex < 0 || childIndex >= selectedNode->children().size())
	{
		throw XMLException(ErrorMessageBuilder::INVALID_INDEX());
	}
	selectedNode->children()[childIndex]->print(std::cout);
	std::cout << std::endl;
}

void XMLController::printInnerText(const MyString& nodeId) const
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	const MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}

	std::cout << "Text of node with id: " << nodeId << std::endl;
	MyStack<const XMLNode*> stack;

	stack.push(selectedNode.get());
	while (!stack.empty())
	{
		const XMLNode* current = stack.peek();
		stack.pop();
		if (const XMLElementNodeWithID* nodeWithChildren = dynamic_cast<const XMLElementNodeWithID*>(current))
		{
			for (int i = nodeWithChildren->children().size() - 1; i >= 0; i--)
			{
				stack.push(nodeWithChildren->children()[i].get());
			}
		}
		else if (current)
		{
			current->print(std::cout);
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void XMLController::deleteAttribute(const MyString& nodeId, const MyString& attributeName)
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	if (attributeName == "id")
	{
		throw XMLException("You cannot delete the id of an element!");
	}

	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}

	bool isDeleted = selectedNode->deleteAttribute(attributeName);
	if (!isDeleted)
	{
		throw XMLException(ErrorMessageBuilder::ATTRIBUTE_NOT_FOUND(attributeName, nodeId));
	}

	std::cout << OutputMessageBuilder::SUCCESSFULLY_DELETED_ATTRIBUTE(attributeName, nodeId);
}

void XMLController::addChild(const MyString& nodeId, const MyString& newChildName)
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED_FOR_SAVING());
	}

	MySharedPtr<XMLElementNode> selectedNode = _repository.find([nodeId](MySharedPtr<XMLElementNodeWithID> node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		throw XMLException(ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId));
	}
	MySharedPtr<XMLNode> conv = selectedNode;
	MyWeakPtr<XMLNode> parent = conv;
	XMLElementNodeWithID result;
	result.setParent(parent);

	int nsIndex = newChildName.find(":");
	if (nsIndex != -1)
	{
		result.assignNamespace(newChildName.substr(0, nsIndex));
		result.setTagName(newChildName.substr(nsIndex + 1));
	}
	else
	{
		result.setTagName(newChildName);
	}

	selectedNode->addChild(result);
	_repository.resolveIdConflicts();

	std::cout << OutputMessageBuilder::SUCCESSFULLY_ADDED_CHILD(newChildName, nodeId);
}

void XMLController::handleXPath(const MyString& query) const
{
	if (!_repository.isOpen())
	{
		throw FileError(ErrorMessageBuilder::NO_FILE_OPENED());
	}

	XPathQueryResultSerializer serializer;
	std::cout << serializer.serializeResult(_repository.handleXPath(query));
}
