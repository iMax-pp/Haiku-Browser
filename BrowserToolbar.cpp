//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "BitmapHelper.h"
#include "BrowserToolbar.h"

#include <ToolbarButton.h>
#include <ToolbarSeparator.h>

#include "Constants.h"

BrowserToolbar::BrowserToolbar()
	: WToolbar(BRect(0, 0, 1, 1), "main toolbar")
{
	BBitmap *icon = RetrieveBitmap("back.png");
	WToolbarButton *button = new WToolbarButton("Back", "Back", icon, new BMessage(kMsgNavBack));
	AddItem(button, 0, W_TOOLBAR_LAST_POSITION);

	icon = RetrieveBitmap("forward.png");
	button = new WToolbarButton("Forward", "Forward", icon, new BMessage(kMsgNavForward));
	AddItem(button, 0, W_TOOLBAR_LAST_POSITION);

	icon = RetrieveBitmap("reload.png");
	button = new WToolbarButton("Reload", "Reload", icon, new BMessage(kMsgNavReload));
	AddItem(button, 0, W_TOOLBAR_LAST_POSITION);

	icon = RetrieveBitmap("home.png");
	button = new WToolbarButton("Home", "Home", icon, new BMessage(kMsgNavHome));
	AddItem(button, 0, W_TOOLBAR_LAST_POSITION);

	AddItem(new WToolbarSeparator(), 0, W_TOOLBAR_LAST_POSITION);

	icon = RetrieveBitmap("stop.png");
	button = new WToolbarButton("Stop", "Stop", icon, new BMessage(kMsgNavStop));
	AddItem(button, 0, W_TOOLBAR_LAST_POSITION);

	SetLabelPosition(W_TOOLBAR_LABEL_NONE);
}


BrowserToolbar::~BrowserToolbar()
{
}
