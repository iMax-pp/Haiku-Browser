//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ToolbarView.h"

#include <ControlLook.h>


ToolbarView::ToolbarView()
	: BGroupView(B_HORIZONTAL, 5)
{
	SetFlags(Flags() | B_WILL_DRAW);
	SetViewColor(ui_color(B_MENU_BACKGROUND_COLOR));
}


ToolbarView::~ToolbarView()
{
}


void
ToolbarView::Draw(BRect updateRect)
{
	BRect rect = Bounds();

	be_control_look->DrawBorder(this, rect, updateRect,
		ui_color(B_MENU_BACKGROUND_COLOR), B_PLAIN_BORDER, 0,
		BControlLook::B_BOTTOM_BORDER);

	be_control_look->DrawMenuBarBackground(this, rect, updateRect,
		ui_color(B_MENU_BACKGROUND_COLOR));
}
