// RXTreeNodeTests.m
// Created by Rob Rix on 2010-07-10
// Copyright 2010 Monochrome Industries

#import "RXTreeNode.h"
#import "RXTreeNodeTests.h"
#import "RXLeafNode.h"

@implementation RXTreeNodeTests

-(RXTreeNodeRef)createNode {
	return NULL;
}

-(CFStringRef)expectedNodeName {
	return CFSTR("");
}


-(void)setUp {
	node = RXRetain([self createNode]);
}

-(void)tearDown {
	RXRelease(node); node = NULL;
}


-(void)testHasANodeNamePointer {
	if(node) {
		RXAssertEquals(RXTreeNodeGetName(node), self.expectedNodeName);
	}
}


-(void)testAcceptsVisitors {
	if(node) {
		// write a logging visitor
		// call accept visitor on the node with the logging visitor
		// compare its output to the expected manifest
	}
}

// test visiting skips branches when requested

@end
