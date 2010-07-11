// RXTreeNode.m
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#include "RXTreeNode.h"

// extern struct RXTreeNodeType RXTreeNodeType;

typedef struct RXTreeNode {
	RX_FIELDS_FROM(RXTreeNode, RXTreeNodeType);
} RXTreeNode;


__strong RXTreeNodeRef RXTreeNodeRetain(RXTreeNodeRef self) {
	return RXRetain(self);
}

void RXTreeNodeRelease(RXTreeNodeRef self) {
	RXRelease(self);
}


__strong CFStringRef RXTreeNodeGetName(RXTreeNodeRef self) {
	return self->name;
}
