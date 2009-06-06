//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ProxyViewManager.h"


ProxyViewManager::ProxyViewManager()
	: fCurrentProxyID(-1)
{
}


ProxyViewManager::~ProxyViewManager()
{
}


void
ProxyViewManager::AddProxyView(ProxyView *proxyView)
{
	fCurrentProxyID++;
	fProxyViewList[fCurrentProxyID] = proxyView;
	proxyView->SetID(fCurrentProxyID);
}


void
ProxyViewManager::RemoveProxyView(ProxyView *proxyView)
{
	fProxyViewList.erase(proxyView->ID());
}


ProxyView*
ProxyViewManager::GetProxyFromID(int32 proxyID)
{
	return fProxyViewList[proxyID];
}


int32
ProxyViewManager::GetIDFromProxy(ProxyView *proxyView)
{
	return proxyView->ID();
}
