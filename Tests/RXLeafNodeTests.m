// RXLeafNodeTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNodeTests.h"
#import "RXLeafNode.h"

@interface RXLeafNodeTests : RXTreeNodeTests
@end

@implementation RXLeafNodeTests

-(RXTreeNodeRef)createNode {
	return (RXTreeNodeRef)RXLeafNodeCreate(self.expectedNodeName, self, kRXLeafNodeObjectCallBacks);
}

-(CFStringRef)expectedNodeName {
	return CFSTR("leaf");
}

-(NSString *)expectedManifest {
	return @"leaf()";
}


-(void)testHasDataPointer {
	RXAssertEquals(RXLeafNodeGetData((RXLeafNodeRef)node), self);
}

@end
