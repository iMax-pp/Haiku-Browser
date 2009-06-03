//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ProxyViewManager.h"
#include "AppSignatures.h"
#include "BrowserWindow.h"
#include "Constants.h"
#include "ProxyView.h"
#include "Tranquility.h"

#include <Alert.h>
#include <Bitmap.h>
#include <OS.h>
#include <Roster.h>

#include <syslog.h>


ProxyViewManager::ProxyViewManager(ProxyView *proxyView)
	: BHandler(),
	fMessenger(NULL),
	fProxyView(proxyView),
	fBrowserWindow(NULL)
{
}


ProxyViewManager::~ProxyViewManager()
{
	delete fMessenger;
}


void
ProxyViewManager::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kMsgForward:
		case kMsgUpdate:
		{
			if (fMessenger)
				fMessenger->SendMessage(message);
			break;
		}

		case kMsgBitmapData:
		{
			syslog(LOG_DEBUG, "ProxyViewManager: received kMsgBitmapData message");
			BBitmap *bitmap = dynamic_cast<BBitmap*>(BBitmap::Instantiate(message));
			if (bitmap != NULL) {
				if (fBrowserWindow->Lock()) {
					fProxyView->SetViewBitmap(bitmap);
					fBrowserWindow->Unlock();
				}
				delete bitmap;
			} else {
				syslog(LOG_DEBUG, "ProxyViewManager: bitmap from message is not valid!");
			}
			// Code to create the bitmap from raw data and a bytes per row (bpr) value
			/*int32 length = 0;
			const void *data;
			if (message->FindData("data", B_RAW_TYPE, &data, &length) == B_OK) {
				int32 bpr;
				if (message->FindInt32("bpr", &bpr) == B_OK) {
					syslog(LOG_DEBUG, "Tranquility: got bpr from kMsgBitmapData message");
					BBitmap bitmap(fBrowserWindow->Bounds(), B_RGB32);
					bitmap.ImportBits(data, length, bpr, 0, B_RGB32);
					fBrowserWindow->SetViewBitmap(&bitmap);
				}
			}*/
			break;
		}

		case B_SOME_APP_QUIT:
		{
			fProxyView->DrawSadTab("The render process has quit!");
			fMessenger = NULL;
			fLink.renderBoy = -1;
			my_app->ChannelList()->RemoveItem(&fLink);
			break;
		}

		default:
		      BHandler::MessageReceived(message);
		      break;
	}
}


void
ProxyViewManager::Run(BrowserWindow *browserWindow)
{
	fBrowserWindow = browserWindow;

	BMessage startMsg(kMsgStartRenderApp);
	startMsg.AddRect("renderFrame", fBrowserWindow->Bounds());
	startMsg.AddInt32("teamID", my_app->Team());

	team_id renderTeam;
	if (be_roster->Launch(kRenderAppSignature, &startMsg, &renderTeam) != B_OK)
		fProxyView->DrawSadTab("There was an error trying to launch the render process!");
	else {
		my_app->AddHandler(this);
		fMessenger = new BMessenger(kRenderAppSignature, renderTeam);

		fLink.renderBoy = renderTeam;
		fLink.proxyViewManager = this;

		my_app->ChannelList()->AddItem(&fLink);
	}
}


void
ProxyViewManager::Quit()
{
	if (fMessenger != NULL)
		fMessenger->SendMessage(B_QUIT_REQUESTED);

	if (fLink.renderBoy != -1)
		my_app->ChannelList()->RemoveItem(&fLink);

	if (my_app->Lock()) {
		my_app->RemoveHandler(this);
		my_app->Unlock();
	}
}

