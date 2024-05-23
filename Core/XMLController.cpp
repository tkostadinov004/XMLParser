#include "XMLController.h"

void XMLController::openFile(const MyString& path)
{
	if (!_currentFileName.empty())
	{
		std::cout << OutputMessageBuilder::FILE_ALREADY_OPENED(_currentFileName, path.split('\\').back_or_default()) << std::endl;
	}

	_repository.open(path);
	_currentFilePath = path;
	_currentFileName = path.split('\\').back_or_default();
	std::cout << OutputMessageBuilder::SUCCESSFULLY_OPENED_FILE(path) << std::endl;
}

void XMLController::closeFile()
{
	if (_currentFilePath.empty())
	{
		std::cout << OutputMessageBuilder::FILE_NOT_OPENED(_currentFileName) << std::endl;
	}

	_repository.close();
	_currentFilePath.clear();
	_currentFileName.clear();
	std::cout << OutputMessageBuilder::SUCCESSFULLY_CLOSED_FILE(_currentFileName) << std::endl;
}

void XMLController::save()
{
	if (_currentFilePath.empty())
	{
		std::cout << OutputMessageBuilder::NO_FILE_OPENED_FOR_SAVING() << std::endl;
	}
	_repository.saveAs(_currentFilePath);

	std::cout << OutputMessageBuilder::SUCCESSFULLY_SAVED_FILE(_currentFileName) << std::endl;
}

void XMLController::saveAs(const MyString& path)
{
	_repository.saveAs(path);

	std::cout << OutputMessageBuilder::SUCCESSFULLY_SAVED_FILE(path.split('\\').back_or_default()) << std::endl;
}

void XMLController::help() const
{
	std::cout << "The following commands are supported:\nopen <file>\t\topens <file>\nclose\t\tcloses currently opened file\nsave\t\tsaves the currently open file\nsaveas <file>\t\tsaves the currently open file in <file>\nhelp\t\tprints this information\nexit\t\texists the program";
}

void XMLController::print() const
{
	std::cout << _repository.getContents() << std::endl;
}

void XMLController::selectAttribute(const MyString& nodeId, const MyString& attributeName) const
{
	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const XMLElementNodeWithID* node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId);
		return;
	}

	const XMLAttribute* attribute = selectedNode->attributes()[attributeName];
	if (!attribute)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_ATTRIBUTE_IN_NODE(attributeName, nodeId);
		return;
	}

	std::cout << attribute->getValue() << std::endl;
}

void XMLController::changeAttributeValue(const MyString& nodeId, const MyString& attributeName, const MyString& newValue)
{
	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const XMLElementNodeWithID* node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId);
		return;
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
}

void XMLController::printChildrenOfNode(const MyString& nodeId) const
{
	const MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const XMLElementNodeWithID* node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId);
		return;
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

void XMLController::printInnerText(const MyString& nodeId) const
{
	const MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const XMLElementNodeWithID* node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId);
		return;
	}

	std::cout << "Text of node with id: " << nodeId << std::endl;
	MyStack<MySharedPtr<XMLNode>> stack;

	stack.push(selectedNode);
	while (!stack.empty())
	{
		MySharedPtr<XMLNode> current = stack.pop();
		if (const MySharedPtr<XMLElementNodeWithID> nodeWithChildren = current)
		{
			for (int i = nodeWithChildren->children().size() - 1; i >= 0; i--)
			{
				stack.push(nodeWithChildren->children()[i].get());
			}
		}
		else if(current)
		{
			current->print(std::cout);
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void XMLController::deleteAttribute(const MyString& nodeId, const MyString& attributeName)
{
	if (attributeName == "id")
	{
		std::cout << "You cannot delete the id of an element!" << std::endl;
		return;
	}

	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const XMLElementNodeWithID* node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId);
		return;
	}

	bool isDeleted = selectedNode->deleteAttribute(attributeName);
	if (isDeleted)
	{
		std::cout << "Successfully deleted attribute with name \"" + attributeName + "\" from node with id \"" + nodeId + "\"" << std::endl;
	}
	else
	{
		std::cout << "Attribute with name \"" + attributeName + "\" as not found in the node with id \"" + nodeId + "\"" << std::endl;
	}
}

void XMLController::addChild(const MyString& nodeId)
{
	MySharedPtr<XMLElementNodeWithID> selectedNode = _repository.find([nodeId](const XMLElementNodeWithID* node) {return node->getId() == nodeId;});
	if (!selectedNode)
	{
		std::cout << ErrorMessageBuilder::UNABLE_TO_FIND_NODE(nodeId);
		return;
	}

	selectedNode->addChild(XMLElementNodeWithID());
	_repository.resolveIdConflicts();
}

void XMLController::handleXPath(const MyString& query) const
{
	std::cout << "[" << join(_repository.handleXPath(query), ", ") << "]" << std::endl;
}
