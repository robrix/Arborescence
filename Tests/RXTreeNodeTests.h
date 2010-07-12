// RXTreeNodeTests.h
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeNode.h"

@interface RXTreeNodeTests : SenTestCase {
	RXTreeNodeRef node;
	RXTreeNodeClassRef nodeClass;
}

-(RXTreeNodeRef)createNode;

@property (nonatomic, readonly) RXTreeNodeClassRef nodeClass;

@property (nonatomic, readonly) CFStringRef expectedNodeName;
@property (nonatomic, readonly) NSString *expectedManifest;

@end
