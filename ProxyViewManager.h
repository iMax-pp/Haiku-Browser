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

#if __GNUC__ > 2
	#include <ext/hash_map>
	using __gnu_cxx::hash;
	typedef __gnu_cxx::hash_map< int32, ProxyView*, hash<int32> > MapIntPtr;
#else
	#include <hash_map>
	using std::hash;
	typedef hash_map< int32, ProxyView*, hash<int32> > MapIntPtr;
#endif

class ProxyViewManager {
	public:
		ProxyViewManager();
		~ProxyViewManager();

		int32 AddProxyView(ProxyView *proxyView);
		void RemoveProxyView(int32 proxyID);

		ProxyView* GetProxyFromID(int32 proxyID);

	private:
		MapIntPtr fProxyViewList;
		int32 fCurrentProxyID;
};

#endif // PROXY_VIEW_MANAGER_H
