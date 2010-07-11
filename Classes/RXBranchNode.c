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


__strong CFArrayRef RXBranchNodeGetChildNodes(RXBranchNodeRef self) {
	return self->childNodes;
}


struct RXTreeNodeType RXBranchNodeType = {
	.name = "RXBranchNode",
	
	.deallocate = (RXDeallocateMethod)RXBranchNodeDeallocate,
	.isEqual = (RXIsEqualMethod)RXBranchNodeIsEqual,
};
