// RXTreeNode.m
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#include "RXTreeNode+Protected.h"
#include "RXTreeNodeClass+Protected.h"

void RXTreeNodeDeallocate(RXTreeNodeRef self) {
	if(RXTreeNodeGetChildren(self)) CFRelease(RXTreeNodeGetChildren(self));
	if(RXTreeNodeClassDataIsObject(self->nodeClass)) {
		RXRelease(self->data);
	}
	RXRelease(self->nodeClass);
}


bool RXTreeNodeIsEqual(RXTreeNodeRef self, RXTreeNodeRef other) {
	return
		RXGetType(self) == RXGetType(other)
	&&	RXEquals(self->nodeClass, other->nodeClass)
	&&	((self->data == other->data) || CFEqual(self->data, other->data))
	&&	((self->children == other->children) || CFEqual(self->children, other->children));
}

__strong CFStringRef RXTreeNodeCopyDescription(RXTreeNodeRef self) {
	CFArrayRef children = RXTreeNodeGetChildren(self);
	return CFStringCreateWithFormat(NULL, NULL, CFSTR("<RXTreeNode:%@(%u)>"), RXTreeNodeClassGetName(self->nodeClass), children ? CFArrayGetCount(children) : 0);
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


void RXTreeNodeSetParent(RXTreeNodeRef self, RXTreeNodeRef parent) {
	self->parent = parent;
}

__strong void *RXTreeNodeGetParent(RXTreeNodeRef self) {
	return self->parent;
}


__strong void RXTreeNodeSetData(RXTreeNodeRef self, __strong void * data) {
	if(RXTreeNodeClassDataIsObject(self->nodeClass)) {
		self->data = data;
	} else {
		memcpy(((uint8_t *)self) + RXTreeNodeClassInstanceDataOffset(self->nodeClass), data, RXTreeNodeClassInstanceDataSize(self->nodeClass));
	}
}

__strong void *RXTreeNodeGetData(RXTreeNodeRef self) {
	void *data = NULL;
	if(RXTreeNodeClassDataIsObject(self->nodeClass)) {
		data = self->data;
	} else {
		data = ((uint8_t *)self) + RXTreeNodeClassInstanceDataOffset(self->nodeClass);
	}
	return data;
}

__strong CFArrayRef RXTreeNodeGetChildren(RXTreeNodeRef self) {
	return *(CFArrayRef *)(((uint8_t *)self) + RXTreeNodeClassInstanceChildrenOffset(self->nodeClass));
}

__strong RXTreeNodeRef RXTreeNodeGetChild(RXTreeNodeRef self, RXIndex i) {
	return (RXTreeNodeRef)CFArrayGetValueAtIndex(RXTreeNodeGetChildren(self), i);
}


struct RXObjectType RXTreeNodeType = {
	.name = "RXTreeNode",
	
	.deallocate = (RXDeallocateMethod)RXTreeNodeDeallocate,
	.isEqual = (RXIsEqualMethod)RXTreeNodeIsEqual,
	.copyDescription = (RXCopyDescriptionMethod)RXTreeNodeCopyDescription,
};
