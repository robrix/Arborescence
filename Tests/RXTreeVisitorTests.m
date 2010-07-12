// RXTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXBranchNode.h"
#import "RXLeafNode.h"
#import "RXCoreFoundationIntegration.h"

@implementation RXTreeVisitorTests

-(RXTreeVisitorRef)visitor {
	return NULL;
}

-(RXTreeVisitorRef)filteringVisitor {
	return NULL;
}


-(RXTreeNodeRef)tree {
	return (RXTreeNodeRef)RXBranchNodeCreate(CFSTR("branch"), RXArray(
		RXLeafNodeCreate(CFSTR("leaf"), NULL, (RXLeafNodeCallBacks){0}),
		RXBranchNodeCreate(CFSTR("branch"), RXArray(
			RXLeafNodeCreate(CFSTR("leaf"), NULL, (RXLeafNodeCallBacks){0}),
			RXBranchNodeCreate(CFSTR("foo"), (CFArrayRef)[NSArray array]),
		NULL)),
		RXLeafNodeCreate(CFSTR("bar"), NULL, (RXLeafNodeCallBacks){0}),
	NULL));
}


-(void)testVisitsNodes {
	RXTreeVisitorRef visitor = self.visitor;
	if(visitor) {
		NSString *expected = @"branch(leaf, branch(leaf, (whatever)), (whatever))";
		NSString *actual = RXTreeNodeAcceptVisitor(self.tree, visitor);
		RXAssertEquals(actual, expected);
	}
}

-(void)testCanSkipHierarchies {
	RXTreeVisitorRef visitor = self.filteringVisitor;
	if(visitor) {
		NSString *expected = @"branch(branch(foo()), bar())";
		NSString *actual = RXTreeNodeAcceptVisitor(self.tree, visitor);
		RXAssertEquals(actual, expected);
	}
}

@end