#include "Node.h"
#include "NodeVisitor.h"

Node::Node()
	:Object()
{
}

Node::Node(const Node& node)
	:Object(node)
{
}

Node::~Node()
{
}

void Node::accept(NodeVisitor& nv)
{
	nv.apply(*this);
}

void Node::traverse(NodeVisitor& nv)
{
	for (NodeList::iterator itr = _children.begin();
		itr != _children.end(); ++itr)
	{
		(*itr)->accept(nv);
	}
}

bool Node::addChild(Node* child)
{
	return insertChild(_children.size(), child);
}

bool Node::insertChild(unsigned int index, Node* child)
{
	if (!child)
		return false;
	else
	{
		return true;
	}
}

bool Node::removeChildren(unsigned int pos, unsigned int numChildrenToRemove)
{
	if (pos < _children.size() && numChildrenToRemove > 0)
	{
		return true;
	}
	else return false;
}

bool Node::replaceChild(Node *origChild, Node* newChild)
{
	if (origChild==NULL || origChild==newChild)
		return false;

	unsigned int pos = getChildIndex(origChild);
	if (pos<_children.size())
	{
		return setChild(pos, newChild);
	}
	return false;
}

bool Node::setChild(unsigned int i, Node* newChild)
{
	if (i<_children.size() && newChild)
	{
		return true;
	}
	else return false;
}