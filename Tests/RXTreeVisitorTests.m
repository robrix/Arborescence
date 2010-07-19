// RXTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNode.h"
#import "RXTreeVisitorTests.h"
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
		leafClass = RXTreeNodeClassCreateLeaf(CFSTR("leaf"), RXObjectReferenceSize),
		branchClass = RXTreeNodeClassCreateBranch(CFSTR("branch")),
		fooClass = RXTreeNodeClassCreateBranch(CFSTR("foo")),
		barClass = RXTreeNodeClassCreateLeaf(CFSTR("bar"), RXObjectReferenceSize);
	return (RXTreeNodeRef)RXTreeNodeClassInstantiateBranch(branchClass, RXArray(
		RXTreeNodeClassInstantiateLeaf(leafClass, NULL),
		RXTreeNodeClassInstantiateBranch(branchClass, RXArray(
			RXTreeNodeClassInstantiateLeaf(leafClass, NULL),
			RXTreeNodeClassInstantiateBranch(fooClass, (CFArrayRef)[NSArray array]),
		NULL)),
		RXTreeNodeClassInstantiateLeaf(barClass, NULL),
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