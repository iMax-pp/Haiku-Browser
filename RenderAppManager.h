//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef RENDER_APP_MANAGER_H
#define RENDER_APP_MANAGER_H

#include "ProxyViewManager.h"

#include <Handler.h>

#include <ext/hash_map>
#include <set>

using __gnu_cxx::hash;

typedef __gnu_cxx::hash_map< int32, int32, hash<int32> > MapIntInt;
typedef __gnu_cxx::hash_map< int32, std::set<int32>, hash<int32> > MapIntVecInt;

class RenderAppManager : public BHandler {
	public:
		RenderAppManager();
		~RenderAppManager();

		void MessageReceived(BMessage *message);
		void Quit();

		team_id StartRenderBoy(BMessage startMsg);
		void StopRenderBoy(team_id renderTeam);
		void RenderBoyRequest(ProxyView *proxyView);
		void LeaveRenderBoy(int32 proxyID);

	private:
		ProxyViewManager *fProxyViewManager;
		MapIntInt fMapProxyToRender;
		MapIntVecInt fMapRenderToProxy;

};

#endif // RENDER_APP_MANAGER_H
