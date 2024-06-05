#pragma once
#include "../XML/Repositories/XMLRepository.h"
#include "../../Utils/Messages/ErrorMessageBuilder.h"
#include "../../Utils/Messages/OutputMessageBuilder.h"

class XMLController
{
	XMLRepository _repository;
	MyString _currentFilePath;
	MyString _currentFileName;
public:
	void openFile(const MyString& path);
	void closeFile();
	void save();
	void saveAs(const MyString& path);
	void help() const;
	void print() const;
	void selectAttribute(const MyString& nodeId, const MyString& attributeName) const;
	void changeAttributeValue(const MyString& nodeId, const MyString& attributeName, const MyString& newValue);
	void printChildrenOfNode(const MyString& nodeId) const;
	void printNthChild(const MyString& nodeId, int childIndex) const;
	void printInnerText(const MyString& nodeId) const;
	void deleteAttribute(const MyString& nodeId, const MyString& attributeName);
	void addChild(const MyString& nodeId);
	void handleXPath(const MyString& query) const;
};