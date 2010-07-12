// RXTreeNode.m
// Created by Rob Rix on 2010-07-07
// Copyright 2010 Monochrome Industries

#include "RXTreeNode.h"

typedef struct RXTreeNode {
	RX_FIELDS_FROM(RXTreeNode, RXTreeNodeType);
} RXTreeNode;


void *RXTreeNodeAcceptVisitor(RXTreeNodeRef self, RXTreeVisitorRef visitor) {
	return self->type->acceptVisitor(self, visitor);
}


RXTreeNodeClassRef RXTreeNodeGetNodeClass(RXTreeNodeRef self) {
	return self->nodeClass;
}
