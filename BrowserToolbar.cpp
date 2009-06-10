//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "BrowserToolbar.h"
#include "BitmapHelper.h"
#include "BrowserIcons.h"
#include "Constants.h"

#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>

#include <string.h>


BrowserToolbar::BrowserToolbar()
	: BView("main toolbar", B_WILL_DRAW)
{
	_DrawViews();
}


BrowserToolbar::~BrowserToolbar()
{
}


void
BrowserToolbar::ChangeGoStopButton(bool loading)
{
	if (loading && strcmp(fGoStopButton->Name(), "Go") == 0) {
		BRect iconRect(0, 0, 28, 28);
		fGoStopButton->SetName("Stop");
		fGoStopButton->SetBitmaps(RetrieveBitmap(kStopIconUp, iconRect),
									RetrieveBitmap(kStopIconDown, iconRect));
		fGoStopButton->SetMessage(new BMessage(kMsgNavStop));
	} else if (!loading && strcmp(fGoStopButton->Name(), "Stop") == 0) {
		BRect iconRect(0, 0, 28, 28);
		fGoStopButton->SetName("Go");
		fGoStopButton->SetBitmaps(RetrieveBitmap(kGoIconUp, iconRect),
									RetrieveBitmap(kGoIconDown, iconRect));
		fGoStopButton->SetMessage(new BMessage(kMsgNavGoURL));
	}
}


void
BrowserToolbar::_DrawViews()
{
	SetViewColor(233, 233, 233);

	BRect iconRect(0, 0, 28, 28);

	BBitmap *iconUp = RetrieveBitmap(kBackIconUp, iconRect);
	BBitmap *iconDown = RetrieveBitmap(kBackIconDown, iconRect);
	BitmapButton *back = new BitmapButton(BRect(0, 0, 1, 1), "Back",
		iconUp, iconDown, new BMessage(kMsgNavBack));

	iconUp  = RetrieveBitmap(kForwardIconUp, iconRect);
	iconDown = RetrieveBitmap(kForwardIconDown, iconRect);
	BitmapButton *forward = new BitmapButton(BRect(0, 0, 1, 1), "Forward",
		iconUp, iconDown, new BMessage(kMsgNavForward));

	iconUp = RetrieveBitmap(kReloadIconUp, iconRect);
	iconDown = RetrieveBitmap(kReloadIconDown, iconRect);
	BitmapButton *reload = new BitmapButton(BRect(0, 0, 1, 1), "Reload",
		iconUp, iconDown, new BMessage(kMsgNavReload));

	fLocationBar = new BTextControl("location bar", NULL, "about:blank", new BMessage(kMsgNavGoURL));

	iconUp = RetrieveBitmap(kGoIconUp, iconRect);
	iconDown = RetrieveBitmap(kGoIconDown, iconRect);
	fGoStopButton = new BitmapButton(BRect(0, 0, 1, 1), "Go", iconUp, iconDown, new BMessage(kMsgNavGoURL));

	// Set the layout
	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(back);
	AddChild(forward);
	AddChild(reload);
	AddChild(fLocationBar);
	AddChild(fGoStopButton);
}
