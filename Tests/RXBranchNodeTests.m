// RXBranchNodeTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNodeTests.h"
#import "RXBranchNode.h"
#import "RXLeafNode.h"
#import "RXCoreFoundationIntegration.h"

@interface RXBranchNodeTests : RXTreeNodeTests
@end

@implementation RXBranchNodeTests

-(CFArrayRef)childNodes {
	return RXArray(RXLeafNodeCreate(RXTreeNodeClassCreateLeaf(CFSTR("leaf1")), self, kRXLeafNodeObjectCallBacks), RXLeafNodeCreate(RXTreeNodeClassCreateLeaf(CFSTR("leaf2")), self, kRXLeafNodeObjectCallBacks), NULL);
}

-(RXTreeNodeRef)createNode {
	return (RXTreeNodeRef)RXBranchNodeCreate(nodeClass, self.childNodes);
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


-(void)testHasChildNodes {
	RXAssertEquals(RXBranchNodeGetChildNodes((RXBranchNodeRef)node), self.childNodes);
}

@end