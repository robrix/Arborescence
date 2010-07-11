// RXBlockTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"
#import "RXCoreFoundationIntegration.h"
#import "RXBlockTreeVisitor.h"

@interface RXBlockTreeVisitorTests : RXTreeVisitorTests
@end

@implementation RXBlockTreeVisitorTests

-(RXTreeVisitorRef)createVisitor {
	return (RXTreeVisitorRef)RXBlockTreeVisitorCreate(NULL, RXDictionary(
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef childNodes) {
			return @"leaf";
		}, @"leaf",
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef childNodes) {
			return [NSString stringWithFormat: @"branch(%@)", [(NSArray *)childNodes componentsJoinedByString: @", "]];
		}, @"branch",
		^void *(RXTreeVisitorRef visitor, RXTreeNodeRef node, CFArrayRef childNodes) {
			return @"(whatever)";
		}, kRXTreeVisitorGenericCallBackKey,
	NULL));
}

@end