// RXTreeNodeClass.h
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_NODE_CLASS
#define RX_TREE_NODE_CLASS

#import <CoreFoundation/CoreFoundation.h>
#import "RXObject.h"

typedef struct RXTreeNodeClass * RXTreeNodeClassRef;

typedef RXIndex RXArity;
#define RXUnboundedArity RXIndexMax

RXTreeNodeClassRef RXTreeNodeClassCreateLeaf(CFStringRef name);
RXTreeNodeClassRef RXTreeNodeClassCreateBranch(CFStringRef name);
RXTreeNodeClassRef RXTreeNodeClassCreateFixed(CFStringRef name, RXArity arity);
RXTreeNodeClassRef RXTreeNodeClassCreate(CFStringRef name, RXArity minimumArity, RXArity maximumArity);

__strong CFStringRef RXTreeNodeClassGetName(RXTreeNodeClassRef self);

bool RXTreeNodeClassIsNullary(RXTreeNodeClassRef self);
bool RXTreeNodeClassIsUnary(RXTreeNodeClassRef self);
// RXTreeNodeRef RXTreeNodeClassInstantiate(RXTreeNodeClassRef self, void * data);

#endif // RX_TREE_NODE_CLASS
