#include "XMLDocumentWithID.h"


void XMLDocumentWithID::resolveIdConflicts(XMLElementNode* root, GroupVector& groups)
{
	if (!root)
	{
		return;
	}

	//for (size_t i = 0; i < root->children().size(); i++)
	//{
	//	const MyString& id = root->children()[i]->getId();
	//	if (groups[id] > 1)
	//	{
	//		int count = groups[id];
	//		groups[id]++;
	//		//root->children()[i]->setId(id + "_" + std::to_string(count)); //!!!!!
	//	}
	//	else
	//	{
	//		groups.add(id);
	//	}

	//	resolveIdConflicts(root->children()[i], groups);
	//}
}

void XMLDocumentWithID::resolveIdConflicts()
{
	GroupVector groups;
	//resolveIdConflicts(_root, groups);
}
