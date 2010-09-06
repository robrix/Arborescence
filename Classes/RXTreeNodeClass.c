// RXTreeNodeClass.m
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#include "RXTreeNode+Protected.h"
#include "RXTreeNodeClass+Protected.h"

typedef struct RXTreeNodeClass {
	RX_FIELDS_FROM(RXObject, RXObjectType);
	
	__strong CFStringRef name;
	RXIndex dataSize;
	RXArity minimumArity, maximumArity;
} RXTreeNodeClass;

struct RXObjectType RXTreeNodeClassType;


RXTreeNodeClassRef RXTreeNodeClassCreateLeaf(CFStringRef name, RXIndex dataSize) {
	return RXTreeNodeClassCreate(name, dataSize, 0, 0);
}

RXTreeNodeClassRef RXTreeNodeClassCreateBranch(CFStringRef name) {
	return RXTreeNodeClassCreate(name, 0, 0, RXUnboundedArity);
}

RXTreeNodeClassRef RXTreeNodeClassCreate(CFStringRef name, RXIndex dataSize, RXArity minimumArity, RXArity maximumArity) {
	RXTreeNodeClassRef self = RXCreate(sizeof(RXTreeNodeClass), &RXTreeNodeClassType);
	self->name = CFStringCreateCopy(NULL, name);
	self->dataSize = dataSize;
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


bool RXTreeNodeClassDataIsObject(RXTreeNodeClassRef self) {
	return self->dataSize == RXObjectReferenceSize;
}


RXIndex RXTreeNodeClassInstanceDataSize(RXTreeNodeClassRef self) {
	return RXTreeNodeClassDataIsObject(self)
	?	sizeof(void *)
	:	self->dataSize;
}

RXIndex RXTreeNodeClassInstanceChildrenSize(RXTreeNodeClassRef self) {
	return sizeof(CFArrayRef);
}

RXIndex RXTreeNodeClassInstanceSize(RXTreeNodeClassRef self) {
	return sizeof(struct RXTreeNodeBase) + RXTreeNodeClassInstanceDataSize(self) + RXTreeNodeClassInstanceChildrenSize(self);
}


RXIndex RXTreeNodeClassInstanceDataOffset(RXTreeNodeClassRef self) {
	return sizeof(struct RXTreeNodeBase);
}

RXIndex RXTreeNodeClassInstanceChildrenOffset(RXTreeNodeClassRef self) {
	return RXTreeNodeClassInstanceDataOffset(self) + RXTreeNodeClassInstanceDataSize(self);
}


RXTreeNodeRef RXTreeNodeClassInstantiate(RXTreeNodeClassRef self, __strong void * data, CFArrayRef children) {
	RXTreeNodeRef node = RXCreate(RXTreeNodeClassInstanceSize(self), &RXTreeNodeType);
	// fixme: assert the existence of self
	node->nodeClass = RXRetain(self);
	if(RXTreeNodeClassDataIsObject(self)) {
		// assert that data is non-null
		RXTreeNodeSetData(node, data);
	} else {
		RXIndex size = RXTreeNodeClassInstanceDataSize(self);
		if(size > 0) {
			// assert that data is non-null
			if(data)
				memcpy(((uint8_t *)node) + RXTreeNodeClassInstanceDataOffset(self), data, size);
		}
	}
	// assert that children is non-null if the node class is not nullary
	CFArrayRef *nodeChildren = (CFArrayRef *)(((uint8_t *)node) + RXTreeNodeClassInstanceChildrenOffset(self));
	*nodeChildren = children ? CFArrayCreateCopy(NULL, children) : NULL;
	// fixme: enforce the arity of the children array
	CFIndex count = children ? CFArrayGetCount(children) : 0;
	for(CFIndex i = 0; i < count; i++) {
		RXTreeNodeSetParent((RXTreeNodeRef)CFArrayGetValueAtIndex(children, i), node);
	}
	return node;
}

RXTreeNodeRef RXTreeNodeClassInstantiateBranch(RXTreeNodeClassRef self, CFArrayRef children) {
	return RXTreeNodeClassInstantiate(self, NULL, children);
}

RXTreeNodeRef RXTreeNodeClassInstantiateLeaf(RXTreeNodeClassRef self, __strong void * data) {
	return RXTreeNodeClassInstantiate(self, data, NULL);
}


struct RXObjectType RXTreeNodeClassType = {
	.name = "RXTreeNodeClass",
	
	.deallocate = (RXDeallocateMethod)RXTreeNodeClassDeallocate,
	.isEqual = (RXIsEqualMethod)RXTreeNodeClassIsEqual,
};
