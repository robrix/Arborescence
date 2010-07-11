// RXTreeNode.h
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE
#define RX_TREE_NODE

#include "RXObject.h"

typedef struct RXTreeNode * RXTreeNodeRef;

#define RX_FIELDS_FROM_RXTreeNode(_type) \
	RX_FIELDS_FROM_RXObject(_type)\
	const char *name;

typedef struct RXTreeNodeType {
	RX_METHODS_FROM(RXObjectType);
} *RXTreeNodeTypeRef;

__strong RXTreeNodeRef RXTreeNodeRetain(RXTreeNodeRef self);
void RXTreeNodeRelease(RXTreeNodeRef self);

__strong const char *RXTreeNodeGetName(RXTreeNodeRef self);

#endif // RX_TREE_NODE
