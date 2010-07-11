// RXTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXBranchNode.h"
#import "RXLeafNode.h"
#import "RXCoreFoundationIntegration.h"

@implementation RXTreeVisitorTests

-(RXTreeVisitorRef)createVisitor {
	return NULL;
}


-(void)setUp {
	visitor = RXRetain([self createVisitor]);
}

-(void)tearDown {
	RXRelease(visitor); visitor = NULL;
}


-(void)testVisitsNodes {
	if(visitor) {
		RXTreeNodeRef node = (RXTreeNodeRef)RXBranchNodeCreate(CFSTR("branch"), RXArray(
			RXLeafNodeCreate(CFSTR("leaf"), NULL, (RXLeafNodeCallBacks){0}),
			RXBranchNodeCreate(CFSTR("branch"), RXArray(
				RXLeafNodeCreate(CFSTR("leaf"), NULL, (RXLeafNodeCallBacks){0}),
				RXBranchNodeCreate(CFSTR("foo"), (CFArrayRef)[NSArray array]),
			NULL)),
			RXLeafNodeCreate(CFSTR("bar"), NULL, (RXLeafNodeCallBacks){0}),
		NULL));
		NSString *expected = @"branch(leaf, branch(leaf, (whatever)), (whatever))";
		NSString *actual = RXTreeNodeAcceptVisitor(node, visitor);
		RXAssertEquals(actual, expected);
	}
}

@end