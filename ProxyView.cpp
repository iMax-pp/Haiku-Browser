//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ProxyView.h"
#include "BitmapHelper.h"
#include "Constants.h"
#include "Tranquility.h"

#include <syslog.h>


ProxyView::ProxyView(BRect frame, const char *name)
	: BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW|B_FRAME_EVENTS)
{
}


ProxyView::~ProxyView()
{
}


void
ProxyView::Draw(BRect updateRect)
{
}


void
ProxyView::FrameResized(float width, float height)
{
}


void
ProxyView::MouseDown(BPoint point)
{
	syslog(LOG_DEBUG, "Tranquility, ProxyView: received mouse down message, forwarding it to be_app");
	_ForwardCurrentMessage();
}


void
ProxyView::MouseMoved(BPoint point, uint32 transit, const BMessage* message)
{
	syslog(LOG_DEBUG, "Tranquility, ProxyView: received mouse moved message, forwarding it to be_app");
	_ForwardCurrentMessage();
}


void
ProxyView::GetRenderBoy()
{
	my_app->GetRenderAppManager()->RenderBoyRequest(this);
}

void
ProxyView::DrawSadTab(const char *error)
{
	BBitmap *sadTab = RetrieveBitmap("sad_tab.png", BRect(0, 0, 255, 255));

	if (Window()->Lock()) {
		MovePenTo(Bounds().Width() / 2 - 127, Bounds().Height() / 2 - 177);
		DrawBitmap(sadTab);

		MovePenTo(Bounds().Width() / 2 - 45, Bounds().Height() / 2 + 55);
		BFont font;
		GetFont(&font);
		font.SetSize(18.0);
		font.SetFace(B_BOLD_FACE);
		SetFont(&font, B_FONT_SIZE | B_FONT_FACE);
		SetLowColor(0, 0, 0);
		SetHighColor(255, 255, 255);
		DrawString("Aw, Snap!");

		MovePenTo(Bounds().Width() / 2 - 90, Bounds().Height() / 2 + 70);
		font.SetSize(12.0);
		font.SetFace(B_REGULAR_FACE);
		SetFont(&font, B_FONT_SIZE | B_FONT_FACE);
		DrawString(error);

		Window()->Unlock();
	}
}


int32
ProxyView::ID()
{
	return fID;
}


void
ProxyView::SetID(int32 id)
{
	fID = id;
}


void
ProxyView::_ForwardCurrentMessage()
{
	BMessage forward(kMsgForward);
	forward.AddMessage("original", Window()->CurrentMessage());
	forward.AddInt32("proxyID", fID);
	be_app->PostMessage(&forward);
}
