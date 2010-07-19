// RXStructLeafNodeTests.m
// Created by Rob Rix on 2010-07-19
// Copyright 2010 Monochrome Industries

#import "RXTreeNodeTests.h"

@interface RXStructLeafNodeTests : RXTreeNodeTests
@end

@implementation RXStructLeafNodeTests

-(NSPoint)point {
	return NSMakePoint(3.0, 13.0);
}

-(RXTreeNodeRef)createNode {
	NSPoint point = self.point;
	return RXTreeNodeClassInstantiateLeaf(nodeClass, &point);
}

-(RXTreeNodeClassRef)nodeClass {
	return RXTreeNodeClassCreateLeaf(self.expectedNodeName, sizeof(NSPoint));
}

-(CFStringRef)expectedNodeName {
	return CFSTR("struct-leaf");
}

-(NSString *)expectedManifest {
	return @"struct-leaf()";
}


-(void)testHasData {
	NSPoint point = *(NSPoint *)RXTreeNodeGetData(node);
	RXAssertEquals(point, self.point);
}

@end