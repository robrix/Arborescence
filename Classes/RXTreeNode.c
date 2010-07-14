// RXTreeNode.m
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#include "RXTreeNode.h"

typedef struct RXTreeNode {
	RX_FIELDS_FROM(RXObject, RXObjectType);
	
	__strong RXTreeNodeClassRef nodeClass;
	__strong RXObjectRef data;
	__strong CFArrayRef children;
	__strong RXTreeNodeRef parent;
} RXTreeNode;

struct RXObjectType RXTreeNodeType;


RXTreeNodeRef RXTreeNodeCreateLeaf(RXTreeNodeClassRef nodeClass, RXObjectRef data) {
	return RXTreeNodeCreate(nodeClass, data, NULL);
}

RXTreeNodeRef RXTreeNodeCreateBranch(RXTreeNodeClassRef nodeClass, CFArrayRef children) {
	return RXTreeNodeCreate(nodeClass, NULL, children);
}

RXTreeNodeRef RXTreeNodeCreate(RXTreeNodeClassRef nodeClass, RXObjectRef data, CFArrayRef children) {
	RXTreeNodeRef self = RXCreate(sizeof(struct RXTreeNode), &RXTreeNodeType);
	// fixme: assert the existence of nodeClass
	self->nodeClass = RXRetain(nodeClass);
	// fixme: assert the existence of either data or children
	self->data = RXRetain(data);
	self->children = children ? CFArrayCreateCopy(NULL, children) : NULL;
	return self;
}


void RXTreeNodeDeallocate(RXTreeNodeRef self) {
	RXRelease(self->nodeClass);
	RXRelease(self->data);
	if(self->children) CFRelease(self->children);
}


bool RXTreeNodeIsEqual(RXTreeNodeRef self, RXTreeNodeRef other) {
	return
		RXGetType(self) == RXGetType(other)
	&&	RXEquals(self->nodeClass, other->nodeClass)
	&&	((self->data == other->data) || CFEqual(self->data, other->data))
	&&	((self->children == other->children) || CFEqual(self->children, other->children));
}


void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor) {
	void *result = NULL;
	if(RXTreeVisitorVisitNode(visitor, (RXTreeNodeRef)self)) {
		CFArrayRef children = RXTreeNodeGetChildren(self);
		CFIndex count = children ? CFArrayGetCount(children) : 0;
		CFMutableArrayRef visitedChildren = children ? CFArrayCreateMutable(NULL, count, &kCFTypeArrayCallBacks) : NULL;
		for(CFIndex i = 0; i < count; i++) {
			RXTreeNodeRef visitedChild = RXTreeNodeAcceptVisitor((RXTreeNodeRef)CFArrayGetValueAtIndex(children, i), visitor);
			if(visitedChild) {
				CFArrayAppendValue(visitedChildren, visitedChild);
			}
		}
		result = RXTreeVisitorLeaveNode(visitor, (RXTreeNodeRef)self, visitedChildren);
	}
	return result;
}


RXTreeNodeClassRef RXTreeNodeGetNodeClass(RXTreeNodeRef self) {
	return self->nodeClass;
}


__strong void *RXTreeNodeGetParent(RXTreeNodeRef self) {
	return self->parent;
}


__strong void *RXTreeNodeGetData(RXTreeNodeRef self) {
	return self->data;
}

__strong CFArrayRef RXTreeNodeGetChildren(RXTreeNodeRef self) {
	return self->children;
}


struct RXObjectType RXTreeNodeType = {
	.deallocate = (RXDeallocateMethod)RXTreeNodeDeallocate,
	.isEqual = (RXIsEqualMethod)RXTreeNodeIsEqual,
};
