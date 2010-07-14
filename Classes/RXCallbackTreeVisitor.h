// RXCallbackTreeVisitor.h
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#ifndef RX_CALLBACK_TREE_VISITOR
#define RX_CALLBACK_TREE_VISITOR

#include "RXTreeNode.h"
#include "RXCoreFoundationIntegration.h"

typedef struct RXCallbackTreeVisitor * RXCallbackTreeVisitorRef;

typedef bool (*RXCallbackTreeVisitorVisitFunction)(RXCallbackTreeVisitorRef self, RXTreeNodeRef node);
typedef void *(*RXCallbackTreeVisitorLeaveFunction)(RXCallbackTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef children);

CFDictionaryRef RXCallbackDictionaryCreate(void *function, ...) RX_REQUIRES_NULL_TERMINATION;

RXCallbackTreeVisitorRef RXCallbackTreeVisitorCreate(CFDictionaryRef visitBlocks, CFDictionaryRef leaveBlocks);

#endif // RX_CALLBACK_TREE_VISITOR
