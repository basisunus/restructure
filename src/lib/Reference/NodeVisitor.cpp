#include "NodeVisitor.h"

NodeVisitor::NodeVisitor()
{
}

NodeVisitor::~NodeVisitor()
{
}

void NodeVisitor::apply(Node& node)
{
	traverse(node);
}