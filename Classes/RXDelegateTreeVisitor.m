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

void *RXDelegateTreeVisitorLeave(RXDelegateTreeVisitorRef self, RXTreeNodeRef node, CFArrayRef childNodes) {
	id<RXDelegateTreeVisitorDelegate> delegate = self->delegate;
	id child = (id)(childNodes && (CFArrayGetCount(childNodes) > 0)) ? CFArrayGetValueAtIndex(childNodes, 0) : NULL;
	SEL
		nullary = NSSelectorFromString([NSString stringWithFormat: @"visitor:leave%@Node:", RXDelegateTreeVisitorNameForNode(node)]),
		unary = NSSelectorFromString([NSString stringWithFormat: @"visitor:leave%@Node:withVisitedChildNode:", RXDelegateTreeVisitorNameForNode(node)]),
		nary = NSSelectorFromString([NSString stringWithFormat: @"visitor:leave%@Node:withVisitedChildNodes:", RXDelegateTreeVisitorNameForNode(node)]),
		genericNullary = @selector(visitor:leaveNode:),
		genericUnary = @selector(visitor:leaveNode:withVisitedChildNode:),
		genericNary = @selector(visitor:leaveNode:withVisitedChildNodes:);
	return [delegate respondsToSelector: nullary]
	?	[delegate performSelector: nullary withObject: (id)self withObject: (id)node]
	:	([delegate respondsToSelector: unary]
		?	objc_msgSend(delegate, unary, self, node, child)
		:	([delegate respondsToSelector: nary]
			?	objc_msgSend(delegate, nary, self, node, childNodes)
			:	([delegate respondsToSelector: genericNullary]
				?	[delegate visitor: (RXTreeVisitorRef)self leaveNode: node]
				:	([delegate respondsToSelector: genericUnary]
					?	[delegate visitor: (RXTreeVisitorRef)self leaveNode: node withVisitedChildNode: child]
					:	([delegate respondsToSelector: genericNary]
						?	[delegate visitor: (RXTreeVisitorRef)self leaveNode: node withVisitedChildNodes: (NSArray *)childNodes]
						:	NULL
					)
				)
			)
		)
	);
}


struct RXTreeVisitorType RXDelegateTreeVisitorType = {
	.name = "RXDelegateTreeVisitor",
	
	.deallocate = (RXDeallocateMethod)RXDelegateTreeVisitorDeallocate,
	
	.visit = (RXTreeVisitorVisitMethod)RXDelegateTreeVisitorVisit,
	.leave = (RXTreeVisitorLeaveMethod)RXDelegateTreeVisitorLeave,
};
