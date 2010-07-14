// RXTreeNodeTests.m
// Created by Rob Rix on 2010-07-10
// Copyright 2010 Monochrome Industries

#import "RXBlockTreeVisitor.h"
#import "RXTreeNode.h"
#import "RXTreeNodeTests.h"
#import "RXCoreFoundationIntegration.h"

@implementation RXTreeNodeTests

-(RXTreeNodeRef)createNode {
	return NULL;
}

-(RXTreeNodeClassRef)nodeClass {
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
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef visitedNode, CFArrayRef children) {
			return [NSString stringWithFormat: @"%@(%@)", RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(visitedNode)), children ? [(NSArray *)children componentsJoinedByString: @", "] : @""];
		}, kRXTreeVisitorGenericCallBackKey,
	NULL));
}


-(void)setUp {
	nodeClass = RXRetain([self nodeClass]);
	node = RXRetain([self createNode]);
}

-(void)tearDown {
	RXRelease(node); node = NULL;
	RXRelease(nodeClass); nodeClass = NULL;
}


-(void)testAcceptsVisitors {
	if(node) {
		NSString *result = RXTreeNodeAcceptVisitor(node, self.loggingVisitor);
		RXAssertEquals(result, self.expectedManifest);
	}
}

@end
