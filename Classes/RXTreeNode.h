// RXTreeNode.h
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE
#define RX_TREE_NODE

#include "RXObject.h"

typedef struct RXTreeNode * RXTreeNodeRef;

#include "RXTreeNodeClass.h"
#include "RXTreeVisitor.h"

typedef void *(*RXTreeNodeAcceptVisitorMethod)(RXTreeNodeRef self, RXTreeVisitorRef visitor);

void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor);

RXTreeNodeClassRef RXTreeNodeGetNodeClass(RXTreeNodeRef self);

__strong void *RXTreeNodeGetParent(RXTreeNodeRef self);

__strong void RXTreeNodeSetData(RXTreeNodeRef self, __strong void * data);
__strong void *RXTreeNodeGetData(RXTreeNodeRef self);
__strong CFArrayRef RXTreeNodeGetChildren(RXTreeNodeRef self);
__strong RXTreeNodeRef RXTreeNodeGetChild(RXTreeNodeRef self, RXIndex i);

#endif // RX_TREE_NODE
