// RXBlockTreeVisitor.h
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#ifndef RX_BLOCK_TREE_VISITOR
#define RX_BLOCK_TREE_VISITOR

#include "RXTreeNode.h"

typedef struct RXBlockTreeVisitor * RXBlockTreeVisitorRef;

typedef bool (^RXBlockTreeVisitorVisitBlock)(RXBlockTreeVisitorRef self, RXTreeNodeRef node);
typedef void *(^RXBlockTreeVisitorLeaveBlock)(RXBlockTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef childNodes);

RXBlockTreeVisitorRef RXBlockTreeVisitorCreate(CFDictionaryRef visitBlocks, CFDictionaryRef leaveBlocks);

#endif // RX_BLOCK_TREE_VISITOR
