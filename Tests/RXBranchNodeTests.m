// RXBranchNodeTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNodeTests.h"
#import "RXCoreFoundationIntegration.h"

@interface RXBranchNodeTests : RXTreeNodeTests
@end

@implementation RXBranchNodeTests

-(CFArrayRef)children {
	return RXArray(RXTreeNodeClassInstantiateLeaf(RXTreeNodeClassCreateLeaf(CFSTR("leaf1"), RXObjectReferenceSize), self), RXTreeNodeClassInstantiateLeaf(RXTreeNodeClassCreateLeaf(CFSTR("leaf2"), sizeof(void *)), self), NULL);
}

-(RXTreeNodeRef)createNode {
	return (RXTreeNodeRef)RXTreeNodeClassInstantiateBranch(nodeClass, self.children);
}

-(RXTreeNodeClassRef)nodeClass {
	return RXTreeNodeClassCreateBranch(self.expectedNodeName);
}

-(CFStringRef)expectedNodeName {
	return CFSTR("branch");
}

-(NSString *)expectedManifest {
	return @"branch(leaf1(), leaf2())";
}


-(void)testHasChildren {
	RXAssertEquals(RXTreeNodeGetChildren(node), self.children);
}

@end