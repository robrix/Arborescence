// RXDelegateTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXDelegateTreeVisitor.h"

@interface RXDelegateTreeVisitorTestsDelegate : NSObject <RXDelegateTreeVisitorDelegate>
@end

@implementation RXDelegateTreeVisitorTestsDelegate

-(id)visitor:(RXTreeVisitorRef)visitor leaveLeafNode:(RXTreeNodeRef)node withVisitedChildNodes:(NSArray *)childNodes {
	return @"leaf";
}

-(id)visitor:(RXTreeVisitorRef)visitor leaveBranchNode:(RXTreeNodeRef)node withVisitedChildNodes:(NSArray *)childNodes {
	return [NSString stringWithFormat: @"branch(%@)", [(NSArray *)childNodes componentsJoinedByString: @", "]];
}

-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node withVisitedChildNodes:(NSArray *)childNodes {
	return @"(whatever)";
}

@end


@interface RXDelegateTreeVisitorTestsFilteringDelegate : NSObject <RXDelegateTreeVisitorDelegate>
@end

@implementation RXDelegateTreeVisitorTestsFilteringDelegate

-(BOOL)visitor:(RXTreeVisitorRef)visitor visitLeafNode:(RXTreeNodeRef)node {
	return NO;
}

-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node withVisitedChildNodes:(NSArray *)childNodes {
	return [NSString stringWithFormat: @"%@(%@)", RXTreeNodeGetName(node), childNodes ? [(NSArray *)childNodes componentsJoinedByString: @", "] : @""];
}

@end


@interface RXDelegateTreeVisitorTests : RXTreeVisitorTests
@end

@implementation RXDelegateTreeVisitorTests

-(RXTreeVisitorRef)visitor {
	return (RXTreeVisitorRef)RXDelegateTreeVisitorCreate([[[RXDelegateTreeVisitorTestsDelegate alloc] init] autorelease]);
}

-(RXTreeVisitorRef)filteringVisitor {
	return (RXTreeVisitorRef)RXDelegateTreeVisitorCreate([[[RXDelegateTreeVisitorTestsFilteringDelegate alloc] init] autorelease]);
}

@end
