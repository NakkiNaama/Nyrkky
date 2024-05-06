#pragma once
#include "Basics.h"

class DialogNode;


class Choice
{
public:
	std::string text;
	int nextNode;
};


class DialogNode
{
public:
	DialogNode(int pid, int pnextNodeID, std::string ptype, std::vector<std::string> plines);
	
	bool NextLine()
	{
		lineID++;
		if (lines.size() > lineID)
		{
			current = lines[lineID];
			return true;
		}
		return false;
	}

	void ResetNode()
	{
		lineID = 0;
		current = lines[0];
	}

	int id;
	int nextNodeID;
	int lineID = 0;

	std::string type;
	std::string current;
	std::vector<std::string> lines;
	std::vector<Choice> choices;

private:
};


class Story {
public:
	Story();
	void SetNode(int index)
	{
		currentNode = &nodes[index];
	}

	inline bool ProceedLine()
	{
		return currentNode->NextLine();
	}

	bool HasNextNode()
	{
		int id = currentNode->nextNodeID;
		return id >= 0;

	}

	void FinishChain()
	{
		currentNode->ResetNode();
	}

	void ChoiceSelected(int index)
	{
		if (currentNode->choices.size() > index)
		{
			DialogNode* node = &nodes[currentNode->choices[index].nextNode];
			if (node != nullptr)
			{
				currentNode->ResetNode();
				currentNode = node;
			}
			else
			{
				std::cout << "choice node was nullptr" << std::endl;
			}
		}
	}

	void NextNode()
	{
		int id = currentNode->nextNodeID;
		currentNode->ResetNode();

		if (nodes.size() > id)
		{
			currentNode = &nodes[id];
		}
	}

	DialogNode* rootNode;
	DialogNode* currentNode;
	std::vector<DialogNode> nodes;

};




