// RXCallbackTreeVisitor.m
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#include "RXCallbackTreeVisitor.h"

typedef struct RXCallbackTreeVisitor {
	RX_FIELDS_FROM(RXTreeVisitor, RXTreeVisitorType);
	
	__strong CFDictionaryRef visitCallbacks;
	__strong CFDictionaryRef leaveCallbacks;
} RXCallbackTreeVisitor;

struct RXTreeVisitorType RXCallbackTreeVisitorType;


CFDictionaryRef RXCallbackDictionaryCreate(void *callback, ...) {
	CFDictionaryValueCallBacks valueFunctions = {0};
	CFMutableDictionaryRef callbacks = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &valueFunctions);
	va_list args;
	va_start(args, callback);
	do {
		CFStringRef key = va_arg(args, CFStringRef);
		CFDictionaryAddValue(callbacks, key, callback);
	} while((callback = va_arg(args, void *(*)())) != NULL);
	va_end(args);
	
	CFDictionaryRef result = CFDictionaryCreateCopy(NULL, callbacks);
	CFRelease(callbacks);
	return result;
}


RXCallbackTreeVisitorRef RXCallbackTreeVisitorCreate(CFDictionaryRef visitCallbacks, CFDictionaryRef leaveCallbacks) {
	RXCallbackTreeVisitorRef self = RXCreate(sizeof(RXCallbackTreeVisitor), &RXCallbackTreeVisitorType);
	self->visitCallbacks = visitCallbacks ? CFDictionaryCreateCopy(NULL, visitCallbacks) : NULL;
	self->leaveCallbacks = leaveCallbacks ? CFDictionaryCreateCopy(NULL, leaveCallbacks) : NULL;
	return self;
}

void RXCallbackTreeVisitorDeallocate(RXCallbackTreeVisitorRef self) {
	if(self->visitCallbacks) CFRelease(self->visitCallbacks);
	if(self->leaveCallbacks) CFRelease(self->leaveCallbacks);
}


bool RXCallbackTreeVisitorVisit(RXCallbackTreeVisitorRef self, RXTreeNodeRef node) {
	RXCallbackTreeVisitorVisitFunction function = self->visitCallbacks ? (CFDictionaryGetValue(self->visitCallbacks, RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(node))) ?: CFDictionaryGetValue(self->visitCallbacks, kRXTreeVisitorGenericCallBackKey)) : NULL;
	return function
	?	function(self, node)
	:	1;
}

void *RXCallbackTreeVisitorLeave(RXCallbackTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef childNodes) {
	RXCallbackTreeVisitorLeaveFunction function = self->leaveCallbacks ? (CFDictionaryGetValue(self->leaveCallbacks, RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(node))) ?: CFDictionaryGetValue(self->leaveCallbacks, kRXTreeVisitorGenericCallBackKey)) : NULL;
	return function
	?	function(self, node, childNodes)
	:	NULL;
}


struct RXTreeVisitorType RXCallbackTreeVisitorType = {
	.name = "RXCallbackTreeVisitor",
	
	.deallocate = (RXDeallocateMethod)RXCallbackTreeVisitorDeallocate,
	
	.visit = (RXTreeVisitorVisitMethod)RXCallbackTreeVisitorVisit,
	.leave = (RXTreeVisitorLeaveMethod)RXCallbackTreeVisitorLeave,
};
