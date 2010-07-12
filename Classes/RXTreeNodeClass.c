// RXTreeNodeClass.m
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#include "RXTreeNodeClass.h"

typedef struct RXTreeNodeClass {
	RX_FIELDS_FROM(RXObject, RXObjectType);
	
	__strong CFStringRef name;
	RXArity minimumArity, maximumArity;
} RXTreeNodeClass;

struct RXObjectType RXTreeNodeClassType;


RXTreeNodeClassRef RXTreeNodeClassCreateLeaf(CFStringRef name) {
	return RXTreeNodeClassCreate(name, 0, 0);
}

RXTreeNodeClassRef RXTreeNodeClassCreateBranch(CFStringRef name) {
	return RXTreeNodeClassCreate(name, 0, RXUnboundedArity);
}

RXTreeNodeClassRef RXTreeNodeClassCreateFixed(CFStringRef name, RXArity arity) {
	return RXTreeNodeClassCreate(name, arity, arity);
}

RXTreeNodeClassRef RXTreeNodeClassCreate(CFStringRef name, RXArity minimumArity, RXArity maximumArity) {
	RXTreeNodeClassRef self = RXCreate(sizeof(RXTreeNodeClass), &RXTreeNodeClassType);
	self->name = CFStringCreateCopy(NULL, name);
	self->minimumArity = minimumArity;
	self->maximumArity = maximumArity;
	return self;
}


void RXTreeNodeClassDeallocate(RXTreeNodeClassRef self) {
	CFRelease(self->name); self->name = NULL;
}

bool RXTreeNodeClassIsEqual(RXTreeNodeClassRef self, RXTreeNodeClassRef other) {
	return
		self == other
	||	(RXGetType(self) == RXGetType(other)
	&&	CFEqual(self->name, other->name)
	&&	(self->minimumArity == other->minimumArity)
	&&	(self->maximumArity == other->maximumArity)
	);
}


__strong CFStringRef RXTreeNodeClassGetName(RXTreeNodeClassRef self) {
	return self->name;
}


bool RXTreeNodeClassIsNullary(RXTreeNodeClassRef self) {
	return (self->minimumArity == 0) && (self->maximumArity == 0);
}

bool RXTreeNodeClassIsUnary(RXTreeNodeClassRef self) {
	return (self->minimumArity == 1) && (self->maximumArity == 1);
}


struct RXObjectType RXTreeNodeClassType = {
	.name = "RXTreeNodeClass",
	
	.deallocate = (RXDeallocateMethod)RXTreeNodeClassDeallocate,
	.isEqual = (RXIsEqualMethod)RXTreeNodeClassIsEqual,
};
