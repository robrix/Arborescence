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

__strong RXLeafNodeRef RXLeafNodeCreate(const char *name, void *data, RXLeafNodeCallBacks callbacks) {
	RXLeafNodeRef self = RXCreate(sizeof(RXLeafNode), &RXLeafNodeType);
	self->name = name;
	self->callbacks = callbacks;
	RXLeafNodeSetData(self, data);
	return self;
}

void RXLeafNodeDeallocate(RXLeafNodeRef self) {
	if(self->callbacks.release) {
		self->callbacks.release(self->data);
	}
}


__strong void *RXLeafNodeGetData(RXLeafNodeRef self) {
	return self->data;
}


struct RXTreeNodeType RXLeafNodeType = {
	.name = "RXLeafNode",
	
	.deallocate = (RXDeallocateMethod)RXLeafNodeDeallocate,
	
};
