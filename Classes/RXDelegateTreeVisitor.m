// RXDelegateTreeVisitor.m
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#import "RXDelegateTreeVisitor.h"
#import <objc/message.h>

typedef struct RXDelegateTreeVisitor {
	RX_FIELDS_FROM(RXTreeVisitor, RXTreeVisitorType);
	
	__strong id<RXDelegateTreeVisitorDelegate> delegate;
} RXDelegateTreeVisitor;

struct RXTreeVisitorType RXDelegateTreeVisitorType;


RXDelegateTreeVisitorRef RXDelegateTreeVisitorCreate(id<RXDelegateTreeVisitorDelegate> delegate) {
	RXDelegateTreeVisitorRef self = RXCreate(sizeof(RXDelegateTreeVisitor), &RXDelegateTreeVisitorType);
	self->delegate = [delegate retain];
	return self;
}

void RXDelegateTreeVisitorDeallocate(RXDelegateTreeVisitorRef self) {
	[self->delegate release];
}


NSString *RXDelegateTreeVisitorNameForNode(RXTreeNodeRef node) {
	NSRange first = NSMakeRange(0, 1);
	return [(NSString *)RXTreeNodeGetName(node) stringByReplacingCharactersInRange: first withString: [[(NSString *)RXTreeNodeGetName(node) substringWithRange: first] uppercaseString]];
}


bool RXDelegateTreeVisitorVisit(RXDelegateTreeVisitorRef self, RXTreeNodeRef node) {
	id<RXDelegateTreeVisitorDelegate> delegate = self->delegate;
	SEL selector = NSSelectorFromString([NSString stringWithFormat: @"visitor:visit%@Node:", RXDelegateTreeVisitorNameForNode(node)]);
	return [delegate respondsToSelector: selector]
	?	(bool)[delegate performSelector: selector withObject: (id)self withObject: (id)node]
	:	([delegate respondsToSelector: @selector(visitor:visitNode:)]
		?	[delegate visitor: (RXTreeVisitorRef)self visitNode: node]
		:	1
	);
}

void *RXDelegateTreeVisitorLeave(RXDelegateTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef children) {
	id<RXDelegateTreeVisitorDelegate> delegate = self->delegate;
	id child = (id)(children && (CFArrayGetCount(children) > 0)) ? CFArrayGetValueAtIndex(children, 0) : NULL;
	SEL
		specific = NSSelectorFromString([NSString stringWithFormat: RXTreeNodeIsNullary(node) ? @"visitor:leave%@Node:" : (RXTreeNodeIsUnary(node) ? @"visitor:leave%@Node:withVisitedChild:" : @"visitor:leave%@Node:withVisitedChildren:"), RXDelegateTreeVisitorNameForNode(node)]),
		generic = RXTreeNodeIsNullary(node) ? @selector(visitor:leaveNode:) : (RXTreeNodeIsUnary(node) ? @selector(visitor:leaveNode:withVisitedChild:) : @selector(visitor:leaveNode:withVisitedChildren:));
	return [delegate respondsToSelector: specific]
	?	objc_msgSend(delegate, specific, self, node, RXTreeNodeIsUnary(node) ? child : (id)children)
	:	([delegate respondsToSelector: generic]
		?	objc_msgSend(delegate, generic, self, node, RXTreeNodeIsUnary(node) ? child : (id)children)
		:	([delegate respondsToSelector: @selector(visitor:leaveNode:withVisitedChildren:)]
			?	objc_msgSend(delegate, @selector(visitor:leaveNode:withVisitedChildren:), self, node, children)
			:	NULL
		)
	);
}


struct RXTreeVisitorType RXDelegateTreeVisitorType = {
	.name = "RXDelegateTreeVisitor",
	
	.deallocate = (RXDeallocateMethod)RXDelegateTreeVisitorDeallocate,
	
	.visit = (RXTreeVisitorVisitMethod)RXDelegateTreeVisitorVisit,
	.leave = (RXTreeVisitorLeaveMethod)RXDelegateTreeVisitorLeave,
};
