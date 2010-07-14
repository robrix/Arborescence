// RXBlockTreeVisitor.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#include "RXBlockTreeVisitor.h"

typedef struct RXBlockTreeVisitor {
	RX_FIELDS_FROM(RXTreeVisitor, RXTreeVisitorType);
	
	__strong CFDictionaryRef visitBlocks;
	__strong CFDictionaryRef leaveBlocks;
} RXBlockTreeVisitor;

struct RXTreeVisitorType RXBlockTreeVisitorType;


RXBlockTreeVisitorRef RXBlockTreeVisitorCreate(CFDictionaryRef visitBlocks, CFDictionaryRef leaveBlocks) {
	RXBlockTreeVisitorRef self = RXCreate(sizeof(RXBlockTreeVisitor), &RXBlockTreeVisitorType);
	self->visitBlocks = visitBlocks ? CFDictionaryCreateCopy(NULL, visitBlocks) : NULL;
	self->leaveBlocks = leaveBlocks ? CFDictionaryCreateCopy(NULL, leaveBlocks) : NULL;
	return self;
}

void RXBlockTreeVisitorDeallocate(RXBlockTreeVisitorRef self) {
	if(self->visitBlocks) CFRelease(self->visitBlocks);
	if(self->leaveBlocks) CFRelease(self->leaveBlocks);
}


bool RXBlockTreeVisitorVisit(RXBlockTreeVisitorRef self, RXTreeNodeRef node) {
	RXBlockTreeVisitorVisitBlock block = self->visitBlocks ? (CFDictionaryGetValue(self->visitBlocks, RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(node))) ?: CFDictionaryGetValue(self->visitBlocks, kRXTreeVisitorGenericCallBackKey)) : NULL;
	return block
	?	block(self, node)
	:	1;
}

void *RXBlockTreeVisitorLeave(RXBlockTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef children) {
	RXBlockTreeVisitorLeaveBlock block = self->leaveBlocks ? (CFDictionaryGetValue(self->leaveBlocks, RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(node))) ?: CFDictionaryGetValue(self->leaveBlocks, kRXTreeVisitorGenericCallBackKey)) : NULL;
	return block
	?	block(self, node, children)
	:	NULL;
}


struct RXTreeVisitorType RXBlockTreeVisitorType = {
	.name = "RXBlockTreeVisitor",
	
	.deallocate = (RXDeallocateMethod)RXBlockTreeVisitorDeallocate,
	
	.visit = (RXTreeVisitorVisitMethod)RXBlockTreeVisitorVisit,
	.leave = (RXTreeVisitorLeaveMethod)RXBlockTreeVisitorLeave,
};
