// RXTreeVisitorTests.m
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#import "RXTreeVisitorTests.h"

@implementation RXTreeVisitorTests

-(RXTreeVisitorRef)createVisitor {
	return NULL;
}


-(void)setUp {
	visitor = RXRetain([self createVisitor]);
}

-(void)tearDown {
	RXRelease(visitor); visitor = NULL;
}


-(void)testVisitsNodes {
	if(visitor) {
		
	}
}

@end