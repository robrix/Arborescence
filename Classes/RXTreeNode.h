// RXTreeNode.h
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE
#define RX_TREE_NODE

#include "RXObject.h"

typedef struct RXTreeNode * RXTreeNodeRef;
typedef RXIndex RXTreeNodeArity;

#define RXTreeNodeUnboundedArity RXIndexMax;

#include "RXTreeVisitor.h"

#define RX_FIELDS_FROM_RXTreeNode(_type) \
	RX_FIELDS_FROM_RXObject(_type)\
	__strong CFStringRef name;\
	RXTreeNodeArity minimumArity, maximumArity;

typedef void *(*RXTreeNodeAcceptVisitorMethod)(RXTreeNodeRef self, RXTreeVisitorRef visitor);

typedef struct RXTreeNodeType {
	RX_METHODS_FROM(RXObjectType);
	
	RXTreeNodeAcceptVisitorMethod acceptVisitor;
} *RXTreeNodeTypeRef;

__strong CFStringRef RXTreeNodeGetName(RXTreeNodeRef self);

void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor);

RXTreeNodeArity RXTreeNodeGetMinimumArity(RXTreeNodeRef self);
RXTreeNodeArity RXTreeNodeGetMaximumArity(RXTreeNodeRef self);
bool RXTreeNodeIsNullary(RXTreeNodeRef self);
bool RXTreeNodeIsUnary(RXTreeNodeRef self);

#endif // RX_TREE_NODE
