// RXCallbackTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXCallbackTreeVisitor.h"
#import "RXCoreFoundationIntegration.h"

void *RXCallbackTreeVisitorTestsLeaveLeaf(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef childNodes) {
	return @"leaf";
}

void *RXCallbackTreeVisitorTestsLeaveBranch(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef childNodes) {
	return [NSString stringWithFormat: @"branch(%@)", [(NSArray *)childNodes componentsJoinedByString: @", "]];
}

void *RXCallbackTreeVisitorTestsLeaveGeneric(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef childNodes) {
	return @"(whatever)";
}


bool RXCallbackTreeVisitorTestsFilterLeaf(RXTreeVisitorRef visitor, RXTreeNodeRef visitedNode) {
	return 0;
}

void *RXCallbackTreeVisitorTestsLeaveUnfilteredGeneric(RXTreeVisitorRef visitor, RXTreeNodeRef visitedNode, CFArrayRef childNodes) {
	return [NSString stringWithFormat: @"%@(%@)", RXTreeNodeGetName(visitedNode), childNodes ? [(NSArray *)childNodes componentsJoinedByString: @", "] : @""];
}


typedef void *(^RXWithCFObjectBlock)(CFTypeRef object);
void *RXWithCFObject(CFTypeRef object, RXWithCFObjectBlock block) {
	void *result = block(object);
	CFRelease(object);
	return result;
}


@interface RXCallbackTreeVisitorTests : RXTreeVisitorTests
@end

@implementation RXCallbackTreeVisitorTests

-(RXTreeVisitorRef)visitor {
	return RXWithCFObject(RXCallbackDictionaryCreate(
		RXCallbackTreeVisitorTestsLeaveLeaf, @"leaf",
		RXCallbackTreeVisitorTestsLeaveBranch, @"branch",
		RXCallbackTreeVisitorTestsLeaveGeneric, kRXTreeVisitorGenericCallBackKey,
	NULL), (RXWithCFObjectBlock)^(CFDictionaryRef callbacks) {
		return RXCallbackTreeVisitorCreate(NULL, callbacks);
	});
}

-(RXTreeVisitorRef)filteringVisitor {
	return RXWithCFObject(RXCallbackDictionaryCreate(RXCallbackTreeVisitorTestsFilterLeaf, @"leaf", NULL), (RXWithCFObjectBlock)^(CFDictionaryRef visitCallbacks) {
		return RXWithCFObject(RXCallbackDictionaryCreate(RXCallbackTreeVisitorTestsLeaveUnfilteredGeneric, kRXTreeVisitorGenericCallBackKey, NULL), (RXWithCFObjectBlock)^(CFDictionaryRef leaveCallbacks) {
			return RXCallbackTreeVisitorCreate(visitCallbacks, leaveCallbacks);
		});
	});
}

@end
