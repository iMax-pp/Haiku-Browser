//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef PROXY_VIEW_H
#define PROXY_VIEW_H

#include <View.h>

#include "ProxyViewManager.h"


class ProxyView : public BView {
	public:
		ProxyView(BRect frame, const char *name);
		~ProxyView();

		void Draw(BRect updateRect);
		void FrameResized(float width, float height);
		void MouseDown(BPoint point);
		void MouseMoved(BPoint point, uint32 transit, const BMessage* message);

		void StartRenderBoy();
		void StopRenderBoy();

		void DrawSadTab(const char *error);

	private:
		void _ForwardCurrentMessage();

		ProxyViewManager *fProxyViewManager;
};

#endif	// PROXY_VIEW_H

