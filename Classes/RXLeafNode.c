// RXLeafNode.m
// Created by Rob Rix on 2010-07-10
// Copyright 2010 Monochrome Industries

#include "RXLeafNode.h"

const RXLeafNodeCallBacks kRXLeafNodeObjectCallBacks = {0, (RXLeafNodeRetainCallBack)RXRetain, (RXLeafNodeReleaseCallBack)RXRelease};
const RXLeafNodeCallBacks kRXLeafNodeFreeOnReleaseCallBacks = {0, NULL, NULL}; // fixme; should be 0, no-op, free

typedef struct RXLeafNode {
	RX_FIELDS_FROM(RXTreeNode, RXTreeNodeType);
	
	__strong void *data;
	RXLeafNodeCallBacks callbacks;
} RXLeafNode;

struct RXTreeNodeType RXLeafNodeType;


void RXLeafNodeSetData(RXLeafNodeRef self, void *data) {
	self->data = (self->callbacks.retain)
	?	self->callbacks.retain(data)
	:	data;
}


__strong RXLeafNodeRef RXLeafNodeCreate(CFStringRef name, void *data, RXLeafNodeCallBacks callbacks) {
	RXLeafNodeRef self = RXCreate(sizeof(RXLeafNode), &RXLeafNodeType);
	self->name = CFRetain(name);
	self->minimumArity = self->maximumArity = 0;
	self->callbacks = callbacks;
	RXLeafNodeSetData(self, data);
	return self;
}

void RXLeafNodeDeallocate(RXLeafNodeRef self) {
	if(self->callbacks.release) {
		self->callbacks.release(self->data);
	}
	CFRelease(self->name);
}

bool RXLeafNodeIsEqual(RXLeafNodeRef self, RXLeafNodeRef other) {
	return
		RXGetType(self) == RXGetType(other)
	&&	CFEqual(self->name, other->name)
	&&	(self->callbacks.isEqual
		?	self->callbacks.isEqual(self->data, other->data)
		:	(self->data == other->data)
	);
}


void *RXLeafNodeAcceptVisitor(RXLeafNodeRef self, RXTreeVisitorRef visitor) {
	return RXTreeVisitorVisitNode(visitor, (RXTreeNodeRef)self)
	?	RXTreeVisitorLeaveNode(visitor, (RXTreeNodeRef)self, NULL)
	:	NULL;
}


__strong void *RXLeafNodeGetData(RXLeafNodeRef self) {
	return self->data;
}


struct RXTreeNodeType RXLeafNodeType = {
	.name = "RXLeafNode",
	
	.deallocate = (RXDeallocateMethod)RXLeafNodeDeallocate,
	.isEqual = (RXIsEqualMethod)RXLeafNodeIsEqual,
	
	.acceptVisitor = (RXTreeNodeAcceptVisitorMethod)RXLeafNodeAcceptVisitor,
};
