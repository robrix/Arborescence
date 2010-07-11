// RXTreeVisitor.h
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_VISITOR
#define RX_TREE_VISITOR

#ifndef RX_TREE_NODE
#error Include RXTreeNode.h instead of RXTreeVisitor.h
#endif // RX_TREE_NODE

typedef struct RXTreeVisitor * RXTreeVisitorRef;

bool RXTreeVisitorVisitNode(RXTreeVisitorRef self, RXTreeNodeRef node);
void *RXTreeVisitorLeaveNode(RXTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef childNodes); // childNodes will be NULL for leaf nodes

#endif // RX_TREE_VISITOR
