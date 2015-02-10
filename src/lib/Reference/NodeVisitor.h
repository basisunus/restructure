#ifndef FL_NODEVISITOR
#define FL_NODEVISITOR 1

#include "Node.h"

class NodeVisitor : public virtual Referenced
{
public:

	NodeVisitor();

	virtual ~NodeVisitor();

	virtual const char* className() const { return "NodeVisitor"; }

	inline void traverse(Node& node)
	{
		node.traverse(*this);
	}

	virtual void apply(Node& node);
};

#endif