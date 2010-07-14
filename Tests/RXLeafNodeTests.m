// RXLeafNodeTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNodeTests.h"

@interface RXLeafNodeTests : RXTreeNodeTests
@end

@implementation RXLeafNodeTests

-(RXTreeNodeRef)createNode {
	return RXTreeNodeCreateLeaf(nodeClass, self);
}

-(RXTreeNodeClassRef)nodeClass {
	return RXTreeNodeClassCreateLeaf(self.expectedNodeName);
}

-(CFStringRef)expectedNodeName {
	return CFSTR("leaf");
}

-(NSString *)expectedManifest {
	return @"leaf()";
}


-(void)testHasDataPointer {
	RXAssertEquals(RXTreeNodeGetData(node), self);
}

@end
