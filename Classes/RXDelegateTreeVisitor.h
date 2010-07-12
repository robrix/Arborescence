// RXDelegateTreeVisitor.h
// Created by Rob Rix on 2010-07-12
// Copyright 2010 Monochrome Industries

#ifndef RX_DELEGATE_TREE_VISITOR
#define RX_DELEGATE_TREE_VISITOR

#import "RXTreeNode.h"

/*
	In addition to the optional methods listed below, the visitor will also call -visitor:visit<Name>Node:, -visitor:leave<Name>Node:, -visitor:leave<Name>Node:withVisitedChildNode:, and -visitor:leave<Name>Node:withVisitedChildNodes: when these methods are available.
*/

@protocol RXDelegateTreeVisitorDelegate <NSObject>
@optional
-(BOOL)visitor:(RXTreeVisitorRef)visitor visitNode:(RXTreeNodeRef)node;
-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node;
-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node withVisitedChild:(id)childNode;
-(id)visitor:(RXTreeVisitorRef)visitor leaveNode:(RXTreeNodeRef)node withVisitedChildren:(NSArray *)childNodes;
@end

typedef struct RXDelegateTreeVisitor * RXDelegateTreeVisitorRef;

RXDelegateTreeVisitorRef RXDelegateTreeVisitorCreate(id<RXDelegateTreeVisitorDelegate> delegate);

#endif // RX_DELEGATE_TREE_VISITOR
