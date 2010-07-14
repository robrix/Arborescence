// RXTreeVisitor.h
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#ifndef RX_TREE_VISITOR
#define RX_TREE_VISITOR

#ifndef RX_TREE_NODE
#error Include RXTreeNode.h instead of RXTreeVisitor.h
#endif // RX_TREE_NODE

typedef struct RXTreeVisitor * RXTreeVisitorRef;

#define RX_FIELDS_FROM_RXTreeVisitor(_type) \
	RX_FIELDS_FROM_RXObject(_type);

typedef bool (*RXTreeVisitorVisitMethod)(RXTreeVisitorRef self, RXTreeNodeRef node);
typedef void *(*RXTreeVisitorLeaveMethod)(RXTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef children);

typedef struct RXTreeVisitorType {
	RX_METHODS_FROM(RXObjectType);
	
	RXTreeVisitorVisitMethod visit;
	RXTreeVisitorLeaveMethod leave;
} *RXTreeVisitorTypeRef;

bool RXTreeVisitorVisitNode(RXTreeVisitorRef self, RXTreeNodeRef node);
void *RXTreeVisitorLeaveNode(RXTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef children); // children will be NULL for leaf nodes

extern CFStringRef kRXTreeVisitorGenericCallBackKey;

#endif // RX_TREE_VISITOR
