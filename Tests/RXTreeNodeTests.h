// RXTreeNodeTests.h
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNode.h"

@interface RXTreeNodeTests : SenTestCase {
	RXTreeNodeRef node;
}

-(RXTreeNodeRef)createNode;

@property (nonatomic, readonly) CFStringRef expectedNodeName;

@end
