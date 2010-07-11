// RXTreeVisitor.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#include "RXTreeNode.h"
#include "RXTreeVisitor.h"

typedef struct RXTreeVisitor {
	RX_FIELDS_FROM(RXTreeVisitor, RXTreeVisitorType);
} RXTreeVisitor;


bool RXTreeVisitorVisitNode(RXTreeVisitorRef self, RXTreeNodeRef node) {
	return self->type->visit
	?	self->type->visit(self, node)
	:	1;
}

void *RXTreeVisitorLeaveNode(RXTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef childNodes) {
	return self->type->leave
	?	self->type->leave(self, node, childNodes)
	:	NULL;
}
