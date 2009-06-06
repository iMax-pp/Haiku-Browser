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


class ProxyView : public BView {
	public:
		ProxyView(BRect frame, const char *name);
		~ProxyView();

		void Draw(BRect updateRect);
		void FrameResized(float width, float height);
		void MouseDown(BPoint point);
		void MouseMoved(BPoint point, uint32 transit, const BMessage* message);

		void GetRenderBoy();

		void DrawSadTab(const char *error);

		int32 ID();
		void SetID(int32 id);

	private:
		void _ForwardCurrentMessage();

		int32 fID;
};

#endif	// PROXY_VIEW_H

