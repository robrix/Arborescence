// RXDelegateTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXDelegateTreeVisitor.h"

@interface RXDelegateTreeVisitorTestsDelegate : NSObject <RXDelegateTreeVisitorDelegate>
@end

@implementation RXDelegateTreeVisitorTestsDelegate

-(id)visitor:(RXTreeVisitorRef)visitor leaveLeafNode:(RXTreeNodeRef)node {
	return @"leaf";
}

-(id)visitor:(RXTreeVisitorRef)visitor leaveBranchNode:(RXTreeNodeRef)node withVisitedChildren:(NSArray *)children {
	return [NSString stringWithFormat: @"branch(%@)", [(NSArray *)children componentsJoinedByString: @", "]];
}

-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node withVisitedChildren:(NSArray *)children {
	return @"(whatever)";
}

@end


@interface RXDelegateTreeVisitorTestsFilteringDelegate : NSObject <RXDelegateTreeVisitorDelegate>
@end

@implementation RXDelegateTreeVisitorTestsFilteringDelegate

-(BOOL)visitor:(RXTreeVisitorRef)visitor visitLeafNode:(RXTreeNodeRef)node {
	return NO;
}

-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node withVisitedChildren:(NSArray *)children {
	return [NSString stringWithFormat: @"%@(%@)", RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(node)), children ? [(NSArray *)children componentsJoinedByString: @", "] : @""];
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
