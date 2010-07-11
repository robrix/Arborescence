// RXLeafNode.h
// Created by Rob Rix on 2010-07-10
// Copyright 2010 Monochrome Industries

#ifndef RX_LEAF_NODE
#define RX_LEAF_NODE

#include "RXTreeNode.h"

typedef struct RXLeafNode * RXLeafNodeRef;

typedef void *(*RXLeafNodeRetainCallBack)(void *value);
typedef void (*RXLeafNodeReleaseCallBack)(void *value);

typedef struct RXLeafNodeCallBacks {
	RXIndex version;
	RXLeafNodeRetainCallBack retain;
	RXLeafNodeReleaseCallBack release;
} RXLeafNodeCallBacks;

extern const RXLeafNodeCallBacks kRXLeafNodeObjectCallBacks;
extern const RXLeafNodeCallBacks kRXLeafNodeFreeOnReleaseCallBacks;

__strong RXLeafNodeRef RXLeafNodeCreate(CFStringRef name, void *data, RXLeafNodeCallBacks callbacks);

__strong void *RXLeafNodeGetData(RXLeafNodeRef self);

#endif
