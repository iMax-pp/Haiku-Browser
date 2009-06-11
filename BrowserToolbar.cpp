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
	: BView("main toolbar", B_WILL_DRAW),
	fIconSize(BRect(0, 0, 23, 23))
{
	_DrawViews();
}


BrowserToolbar::~BrowserToolbar()
{
}


void
BrowserToolbar::ChangeReloadStopButton(bool loading)
{
	if (loading && strcmp(fReloadStopButton->Name(), "Reload") == 0) {
		fReloadStopButton->SetName("Stop");
		fReloadStopButton->SetBitmaps(RetrieveBitmap(kStopIconUp, fIconSize),
									RetrieveBitmap(kStopIconDown, fIconSize));
		fReloadStopButton->SetMessage(new BMessage(kMsgNavStop));
	} else if (!loading && strcmp(fReloadStopButton->Name(), "Stop") == 0) {
		fReloadStopButton->SetName("Reload");
		fReloadStopButton->SetBitmaps(RetrieveBitmap(kReloadIconUp, fIconSize),
									RetrieveBitmap(kReloadIconDown, fIconSize));
		fReloadStopButton->SetMessage(new BMessage(kMsgNavReload));
	}
}


void
BrowserToolbar::_DrawViews()
{
	BBitmap *iconUp = RetrieveBitmap(kBackIconUp, fIconSize);
	BBitmap *iconDown = RetrieveBitmap(kBackIconDown, fIconSize);
	BitmapButton *back = new BitmapButton(BRect(0, 0, 1, 1), "Back",
		iconUp, iconDown, new BMessage(kMsgNavBack));
	back->SetExplicitMinSize(BSize(fIconSize.Width(), fIconSize.Height()));
	back->SetExplicitMaxSize(BSize(fIconSize.Width(), fIconSize.Height()));

	iconUp  = RetrieveBitmap(kForwardIconUp, fIconSize);
	iconDown = RetrieveBitmap(kForwardIconDown, fIconSize);
	BitmapButton *forward = new BitmapButton(BRect(0, 0, 1, 1), "Forward",
		iconUp, iconDown, new BMessage(kMsgNavForward));
	forward->SetExplicitMinSize(BSize(fIconSize.Width(), fIconSize.Height()));
	forward->SetExplicitMaxSize(BSize(fIconSize.Width(), fIconSize.Height()));

	iconUp = RetrieveBitmap(kReloadIconUp, fIconSize);
	iconDown = RetrieveBitmap(kReloadIconDown, fIconSize);
	fReloadStopButton = new BitmapButton(BRect(0, 0, 1, 1), "Reload",
		iconUp, iconDown, new BMessage(kMsgNavReload));
	fReloadStopButton->SetExplicitMinSize(BSize(fIconSize.Width(), fIconSize.Height()));
	fReloadStopButton->SetExplicitMaxSize(BSize(fIconSize.Width(), fIconSize.Height()));

	fLocationBar = new BTextControl("location bar", NULL, "about:blank", new BMessage(kMsgNavGoURL));

	font_height fontHeight;
	GetFontHeight(&fontHeight);
	float height = fontHeight.descent + fontHeight.ascent + fontHeight.leading;
	BSize locationBarSize;
	locationBarSize.SetHeight(height + 10);
	fLocationBar->SetExplicitMinSize(locationBarSize);
	fLocationBar->SetExplicitMaxSize(locationBarSize);

	iconUp = RetrieveBitmap(kGoIconUp, fIconSize);
	iconDown = RetrieveBitmap(kGoIconDown, fIconSize);
	BitmapButton *go = new BitmapButton(BRect(0, 0, 1, 1), "Go",
		iconUp, iconDown, new BMessage(kMsgNavGoURL));
	go->SetExplicitMinSize(BSize(fIconSize.Width(), fIconSize.Height()));
	go->SetExplicitMaxSize(BSize(fIconSize.Width(), fIconSize.Height()));

	// Set the layout
	SetLayout(new BGroupLayout(B_HORIZONTAL));
	AddChild(BGroupLayoutBuilder(B_HORIZONTAL, 5)
		.Add(back)
		.Add(forward)
		.Add(fReloadStopButton)
		.Add(fLocationBar, B_SIZE_UNLIMITED)
		.Add(go)
		.SetInsets(5, 5, 5, 5)
	);
}
