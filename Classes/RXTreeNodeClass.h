// RXTreeNodeClass.h
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE_CLASS
#define RX_TREE_NODE_CLASS

#ifndef RX_TREE_NODE
#error Include RXTreeNode.h instead of RXTreeNodeClass.h
#endif // RX_TREE_NODE

#import <CoreFoundation/CoreFoundation.h>
#import "RXObject.h"

typedef struct RXTreeNodeClass * RXTreeNodeClassRef;

typedef RXIndex RXArity;
#define RXUnboundedArity RXIndexMax

#define RXObjectReferenceSize RXIndexMax

RXTreeNodeClassRef RXTreeNodeClassCreateLeaf(CFStringRef name, RXIndex dataSize);
RXTreeNodeClassRef RXTreeNodeClassCreateBranch(CFStringRef name);
RXTreeNodeClassRef RXTreeNodeClassCreate(CFStringRef name, RXIndex dataSize, RXArity minimumArity, RXArity maximumArity);

__strong CFStringRef RXTreeNodeClassGetName(RXTreeNodeClassRef self);

bool RXTreeNodeClassIsNullary(RXTreeNodeClassRef self);
bool RXTreeNodeClassIsUnary(RXTreeNodeClassRef self);

bool RXTreeNodeClassDataIsObject(RXTreeNodeClassRef self);

RXTreeNodeRef RXTreeNodeClassInstantiate(RXTreeNodeClassRef self, void * data, CFArrayRef children);
RXTreeNodeRef RXTreeNodeClassInstantiateBranch(RXTreeNodeClassRef self, CFArrayRef children);
RXTreeNodeRef RXTreeNodeClassInstantiateLeaf(RXTreeNodeClassRef self, void * data);

#endif // RX_TREE_NODE_CLASS
