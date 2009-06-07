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


int32
ProxyViewManager::AddProxyView(ProxyView *proxyView)
{
	fCurrentProxyID++;
	fProxyViewList[fCurrentProxyID] = proxyView;
	proxyView->SetID(fCurrentProxyID);

	return fCurrentProxyID;
}


void
ProxyViewManager::RemoveProxyView(int32 proxyID)
{
	fProxyViewList.erase(proxyID);
}


ProxyView*
ProxyViewManager::GetProxyFromID(int32 proxyID)
{
	return fProxyViewList[proxyID];
}
