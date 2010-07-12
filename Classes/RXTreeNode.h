// RXTreeNode.h
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE
#define RX_TREE_NODE

#include "RXObject.h"

typedef struct RXTreeNode * RXTreeNodeRef;

#include "RXTreeNodeClass.h"
#include "RXTreeVisitor.h"

#define RX_FIELDS_FROM_RXTreeNode(_type) \
	RX_FIELDS_FROM_RXObject(_type)\
	__strong RXTreeNodeClassRef nodeClass;

typedef void *(*RXTreeNodeAcceptVisitorMethod)(RXTreeNodeRef self, RXTreeVisitorRef visitor);

typedef struct RXTreeNodeType {
	RX_METHODS_FROM(RXObjectType);
	
	RXTreeNodeAcceptVisitorMethod acceptVisitor;
} *RXTreeNodeTypeRef;



void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor);

RXTreeNodeClassRef RXTreeNodeGetNodeClass(RXTreeNodeRef self);

#endif // RX_TREE_NODE
