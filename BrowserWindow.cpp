//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "BrowserWindow.h"
#include "Constants.h"
#include "ProxyView.h"

#include <Application.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>


BrowserWindow::BrowserWindow()
	: BWindow(BRect(100, 100, 400, 400), "Tranquility", B_DOCUMENT_WINDOW, 0)
{
	fToolbar = new BrowserToolbar();
	fProxyView = new ProxyView(Bounds(), "Proxy");

	BGroupView *view = new BGroupView(B_VERTICAL, 10);
	view->SetViewColor(255, 255, 255);

	// Set the layout
	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(BGroupLayoutBuilder(view)
		.Add(fToolbar)
		.Add(fProxyView)
	);
	ResizeTo(500, 500);

	AddShortcut('N', B_COMMAND_KEY, new BMessage(kMsgNewTab), this);
	AddShortcut('W', B_COMMAND_KEY, new BMessage(kMsgCloseTab), this);
}


BrowserWindow::~BrowserWindow()
{
}


void
BrowserWindow::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kMsgNewTab:
			break;

		case kMsgCloseTab:
			break;

		case kMsgNavGoURL:
			fToolbar->ChangeReloadStopButton(true);
			break;

		case kMsgNavReload:
			fToolbar->ChangeReloadStopButton(true);
			break;

		case kMsgNavStop:
			fToolbar->ChangeReloadStopButton(false);
			break;

		default:
			BWindow::MessageReceived(message);
			break;
	}
}


bool
BrowserWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);

	return true;
}


void
BrowserWindow::FrameResized(float width, float height)
{
	BWindow::FrameResized(width, height);
	if (width < 300)
		ResizeTo(300, height);
}
