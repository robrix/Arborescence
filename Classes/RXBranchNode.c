// RXBranchNode.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#include "RXBranchNode.h"

typedef struct RXBranchNode {
	RX_FIELDS_FROM(RXTreeNode, RXTreeNodeType);
	
	__strong CFArrayRef childNodes;
} RXBranchNode;

struct RXTreeNodeType RXBranchNodeType;


__strong RXBranchNodeRef RXBranchNodeCreate(CFStringRef name, CFArrayRef childNodes) {
	RXBranchNodeRef self = RXCreate(sizeof(RXBranchNode), &RXBranchNodeType);
	self->name = CFRetain(name);
	self->minimumArity = 0;
	self->maximumArity = RXTreeNodeUnboundedArity;
	self->childNodes = CFRetain(childNodes);
	return self;
}

void RXBranchNodeDeallocate(RXBranchNodeRef self) {
	CFRelease(self->name);
	CFRelease(self->childNodes);
}

bool RXBranchNodeIsEqual(RXBranchNodeRef self, RXBranchNodeRef other) {
	return
		RXGetType(self) == RXGetType(other)
	&&	CFEqual(self->name, other->name)
	&&	CFEqual(self->childNodes, other->childNodes);
}


void *RXBranchNodeAcceptVisitor(RXBranchNodeRef self, RXTreeVisitorRef visitor) {
	void *result = NULL;
	if(RXTreeVisitorVisitNode(visitor, (RXTreeNodeRef)self)) {
		CFArrayRef childNodes = RXBranchNodeGetChildNodes(self);
		CFIndex count = CFArrayGetCount(childNodes);
		CFMutableArrayRef visitedChildNodes = CFArrayCreateMutable(NULL, count, &kCFTypeArrayCallBacks);
		for(CFIndex i = 0; i < count; i++) {
			RXTreeNodeRef visitedChildNode = RXTreeNodeAcceptVisitor((RXTreeNodeRef)CFArrayGetValueAtIndex(childNodes, i), visitor);
			if(visitedChildNode) {
				CFArrayAppendValue(visitedChildNodes, visitedChildNode);
			}
		}
		result = RXTreeVisitorLeaveNode(visitor, (RXTreeNodeRef)self, visitedChildNodes);
	}
	return result;
}


__strong CFArrayRef RXBranchNodeGetChildNodes(RXBranchNodeRef self) {
	return self->childNodes;
}


struct RXTreeNodeType RXBranchNodeType = {
	.name = "RXBranchNode",
	
	.deallocate = (RXDeallocateMethod)RXBranchNodeDeallocate,
	.isEqual = (RXIsEqualMethod)RXBranchNodeIsEqual,
	
	.acceptVisitor = (RXTreeNodeAcceptVisitorMethod)RXBranchNodeAcceptVisitor,
};
