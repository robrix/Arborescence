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
	RXTreeNodeClassRef
		leafClass = RXTreeNodeClassCreateLeaf(CFSTR("leaf")),
		branchClass = RXTreeNodeClassCreateBranch(CFSTR("branch")),
		fooClass = RXTreeNodeClassCreateBranch(CFSTR("foo")),
		barClass = RXTreeNodeClassCreateLeaf(CFSTR("bar"));
	return (RXTreeNodeRef)RXBranchNodeCreate(branchClass, RXArray(
		RXLeafNodeCreate(leafClass, NULL, (RXLeafNodeCallBacks){0}),
		RXBranchNodeCreate(branchClass, RXArray(
			RXLeafNodeCreate(leafClass, NULL, (RXLeafNodeCallBacks){0}),
			RXBranchNodeCreate(fooClass, (CFArrayRef)[NSArray array]),
		NULL)),
		RXLeafNodeCreate(barClass, NULL, (RXLeafNodeCallBacks){0}),
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