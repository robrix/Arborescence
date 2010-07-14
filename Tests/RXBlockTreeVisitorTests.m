// RXBlockTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXCoreFoundationIntegration.h"
#import "RXBlockTreeVisitor.h"

@interface RXBlockTreeVisitorTests : RXTreeVisitorTests
@end

@implementation RXBlockTreeVisitorTests

-(RXTreeVisitorRef)visitor {
	return (RXTreeVisitorRef)RXBlockTreeVisitorCreate(NULL, RXDictionary(
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef children) {
			return @"leaf";
		}, @"leaf",
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef children) {
			return [NSString stringWithFormat: @"branch(%@)", [(NSArray *)children componentsJoinedByString: @", "]];
		}, @"branch",
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef children) {
			return @"(whatever)";
		}, kRXTreeVisitorGenericCallBackKey,
	NULL));
}

-(RXTreeVisitorRef)filteringVisitor {
	return (RXTreeVisitorRef)RXBlockTreeVisitorCreate(RXDictionary(
		^bool (RXTreeVisitorRef visitor, RXTreeNodeRef visitedNode) {
			return 0;
		}, @"leaf",
	NULL), RXDictionary(
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef visitedNode, CFArrayRef children) {
			return [NSString stringWithFormat: @"%@(%@)", RXTreeNodeClassGetName(RXTreeNodeGetNodeClass(visitedNode)), children ? [(NSArray *)children componentsJoinedByString: @", "] : @""];
		}, kRXTreeVisitorGenericCallBackKey,
	NULL));
}

@end