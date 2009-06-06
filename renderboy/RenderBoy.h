//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef RENDER_BOY_H
#define RENDER_BOY_H


#include <Application.h>
#include <Bitmap.h>
#include <Messenger.h>
#include <Rect.h>
#include <Window.h>
#include <View.h>

#include <ext/hash_set>

#include "RenderView.h"

using __gnu_cxx::hash;

typedef __gnu_cxx::hash_set< int32, hash<int32> > ProxyViewSet;

class RenderBoy : public BApplication {
	public:
		RenderBoy();
		~RenderBoy();

		void ReadyToRun();
		void MessageReceived(BMessage *message);
		void Pulse();
		bool QuitRequested();
  private:
		bool _PrepareRenderMessage(BMessage *message, int32 proxyID);

		bool fStartMsgReceived;
		BMessenger *fMessenger;
		BRect fRenderFrame;
		BBitmap *fRenderBitmap;
		RenderView *fRenderView;
		ProxyViewSet fProxyViewSet;

		BWindow *fDebugWindow;
		BView *fDebugView;
};


#endif	// RENDER_BOY_H

