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
	: BWindow(BRect(100, 100, 600, 600), "Tranquility", B_DOCUMENT_WINDOW, 0)
{
	fToolbar = new BrowserToolbar();
	fProxyView = new ProxyView(Bounds(), "Proxy");

	// Set the layout
	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(BGroupLayoutBuilder(B_VERTICAL, 10)
		.Add(fToolbar)
		.Add(fProxyView)
	);

	AddShortcut('N', B_COMMAND_KEY, new BMessage(kMsgNewTab), this);
	AddShortcut('W', B_COMMAND_KEY, new BMessage(kMsgCloseTab), this);
	AddShortcut('Q', B_COMMAND_KEY, new BMessage(B_QUIT_REQUESTED), this);

	fProxyView->StartRenderBoy();
}


BrowserWindow::~BrowserWindow()
{
}


void
BrowserWindow::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kMsgNewTab: {
			fProxyView->StartRenderBoy();
			break;
		}

		case kMsgCloseTab:
			fProxyView->StopRenderBoy();
			break;

		default:
			BWindow::MessageReceived(message);
			break;
	}
}


bool
BrowserWindow::QuitRequested()
{
	fProxyView->StopRenderBoy();
	be_app->PostMessage(B_QUIT_REQUESTED);

	return true;
}

