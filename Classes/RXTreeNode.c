// RXTreeNode.m
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#include "RXTreeNode.h"

typedef struct RXTreeNode {
	RX_FIELDS_FROM(RXTreeNode, RXTreeNodeType);
} RXTreeNode;


__strong CFStringRef RXTreeNodeGetName(RXTreeNodeRef self) {
	return self->name;
}


void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor) {
	return self->type->acceptVisitor(self, visitor);
}


RXTreeNodeArity RXTreeNodeGetMinimumArity(RXTreeNodeRef self) {
	return self->minimumArity;
}

RXTreeNodeArity RXTreeNodeGetMaximumArity(RXTreeNodeRef self) {
	return self->maximumArity;
}

bool RXTreeNodeIsNullary(RXTreeNodeRef self) {
	return (self->minimumArity == 0) && (self->maximumArity == 0);
}

bool RXTreeNodeIsUnary(RXTreeNodeRef self) {
	return (self->minimumArity == 1) && (self->maximumArity == 1);
}

