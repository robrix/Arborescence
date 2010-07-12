// RXBranchNode.h
// Created by Rob Rix on 2010-07-11
// Copyright 2010 Monochrome Industries

#ifndef RX_BRANCH_NODE
#define RX_BRANCH_NODE

#include "RXTreeNode.h"

typedef struct RXBranchNode * RXBranchNodeRef;

__strong RXBranchNodeRef RXBranchNodeCreate(RXTreeNodeClassRef nodeClass, CFArrayRef childNodes);

__strong CFArrayRef RXBranchNodeGetChildNodes(RXBranchNodeRef self);

#endif // RX_BRANCH_NODE
