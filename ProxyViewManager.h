//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef PROXY_VIEW_MANAGER_H
#define PROXY_VIEW_MANAGER_H

#include "ProxyView.h"

#include <ext/hash_map>

using __gnu_cxx::hash;

typedef __gnu_cxx::hash_map< int32, ProxyView*, hash<int32> > MapIntPtr;

class ProxyViewManager {
	public:
		ProxyViewManager();
		virtual ~ProxyViewManager();

		void AddProxyView(ProxyView *proxyView);
		void RemoveProxyView(ProxyView *proxyView);

		ProxyView* GetProxyFromID(int32 proxyID);
		int32 GetIDFromProxy(ProxyView *proxyView);

		int32 GetID();

	private:
		MapIntPtr fProxyViewList;
		int32 fCurrentProxyID;
};

#endif // PROXY_VIEW_MANAGER_H
