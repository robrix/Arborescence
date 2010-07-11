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
	node = RXTreeNodeRetain([self createNode]);
}

-(void)tearDown {
	RXTreeNodeRelease(node); node = NULL;
}


-(void)testHasANodeNamePointer {
	if(node) {
		RXAssertEquals(RXTreeNodeGetName(node), self.expectedNodeName);
	}
}

@end
