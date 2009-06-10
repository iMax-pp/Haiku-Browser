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
#include "Constants.h"

// #include <BitmapButton.h>
#include <Button.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>

BrowserToolbar::BrowserToolbar()
	: BView("main toolbar", B_WILL_DRAW)
{
	_DrawViews();
}


BrowserToolbar::~BrowserToolbar()
{
}


void
BrowserToolbar::_DrawViews()
{
	BButton *back = new BButton("back", "Back", new BMessage(kMsgNavBack));
	BButton *forward = new BButton("forward", "Forward", new BMessage(kMsgNavForward));
	BButton *reload = new BButton("reload", "Reload", new BMessage(kMsgNavReload));
	BButton *home = new BButton("home", "Home", new BMessage(kMsgNavHome));
	fLocationBar = new BTextControl("location bar", NULL, "about:blank", new BMessage(kMsgNavURL));
	BButton *stop = new BButton("stop", "Stop", new BMessage(kMsgNavStop));

	// Set the layout
	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(BGroupLayoutBuilder(B_HORIZONTAL, 1)
		.Add(back)
		.Add(forward)
		.Add(reload)
		.Add(home)
		.Add(fLocationBar)
		.Add(stop)
		.SetInsets(1, 1, 1, 0)
	);
}
