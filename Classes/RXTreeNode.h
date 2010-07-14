// RXTreeNode.h
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE
#define RX_TREE_NODE

#include "RXObject.h"

typedef struct RXTreeNode * RXTreeNodeRef;

#include "RXTreeNodeClass.h"
#include "RXTreeVisitor.h"

RXTreeNodeRef RXTreeNodeCreateLeaf(RXTreeNodeClassRef nodeClass, RXObjectRef data);
RXTreeNodeRef RXTreeNodeCreateBranch(RXTreeNodeClassRef nodeClass, CFArrayRef children);
RXTreeNodeRef RXTreeNodeCreate(RXTreeNodeClassRef nodeClass, RXObjectRef data, CFArrayRef children);

typedef void *(*RXTreeNodeAcceptVisitorMethod)(RXTreeNodeRef self, RXTreeVisitorRef visitor);

void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor);

RXTreeNodeClassRef RXTreeNodeGetNodeClass(RXTreeNodeRef self);

__strong void *RXTreeNodeGetData(RXTreeNodeRef self);
__strong CFArrayRef RXTreeNodeGetChildren(RXTreeNodeRef self);

#endif // RX_TREE_NODE
