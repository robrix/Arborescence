// RXTreeNode+Protected.h
// Created by Rob Rix on 2010-07-19
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE_PROTECTED
#define RX_TREE_NODE_PROTECTED

#include "RXTreeNode.h"

struct RXTreeNodeBase {
	RX_FIELDS_FROM(RXObject, RXObjectType);
	
	__strong RXTreeNodeClassRef nodeClass;
	__strong RXTreeNodeRef parent;
};

typedef struct RXTreeNode {
	RX_FIELDS_FROM(RXObject, RXObjectType);
	
	__strong RXTreeNodeClassRef nodeClass;
	__strong RXTreeNodeRef parent;
	
	__strong RXObjectRef data;
	__strong CFArrayRef children;
} RXTreeNode;

struct RXObjectType RXTreeNodeType;

void RXTreeNodeSetParent(RXTreeNodeRef self, RXTreeNodeRef parent);

#endif // RX_TREE_NODE_PROTECTED
