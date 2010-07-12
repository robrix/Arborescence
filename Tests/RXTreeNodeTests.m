// RXTreeNodeTests.m
// Created by Rob Rix on 2010-07-10
// Copyright 2010 Monochrome Industries

#import "RXBlockTreeVisitor.h"
#import "RXTreeNode.h"
#import "RXTreeNodeTests.h"
#import "RXLeafNode.h"
#import "RXCoreFoundationIntegration.h"

@implementation RXTreeNodeTests

-(RXTreeNodeRef)createNode {
	return NULL;
}

-(CFStringRef)expectedNodeName {
	return CFSTR("");
}

-(NSString *)expectedManifest {
	return nil;
}


-(RXTreeVisitorRef)loggingVisitor {
	return (RXTreeVisitorRef)RXBlockTreeVisitorCreate(NULL, RXDictionary(
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef visitedNode, CFArrayRef childNodes) {
			return [NSString stringWithFormat: @"%@(%@)", RXTreeNodeGetName(visitedNode), childNodes ? [(NSArray *)childNodes componentsJoinedByString: @", "] : @""];
		}, kRXTreeVisitorGenericCallBackKey,
	NULL));
}


-(void)setUp {
	node = RXRetain([self createNode]);
}

-(void)tearDown {
	RXRelease(node); node = NULL;
}


-(void)testHasANodeNamePointer {
	if(node) {
		RXAssertEquals(RXTreeNodeGetName(node), self.expectedNodeName);
	}
}


-(void)testAcceptsVisitors {
	if(node) {
		NSString *result = RXTreeNodeAcceptVisitor(node, self.loggingVisitor);
		RXAssertEquals(result, self.expectedManifest);
	}
}

// test visiting skips branches when requested

@end
