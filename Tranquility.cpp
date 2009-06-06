//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Tranquility.h"
#include "AppSignatures.h"
#include "Constants.h"

#include <Alert.h>
#include <Roster.h>

#ifdef DEBUG
#include "LeakTracker.h"
#endif

Tranquility::Tranquility()
	: BApplication(kBrowserAppSignature),
	fRenderAppManager(new RenderAppManager())
{
}


Tranquility::~Tranquility()
{
	delete fRenderAppManager;
}


void
Tranquility::AboutRequested()
{
	BAlert* alert = new BAlert("About Tranquility",
		"Tranquility Web Browser\n\nby Ryan Leavengood", "Sweet!");
	alert->Go();
}


void
Tranquility::ReadyToRun()
{
	fBrowserWindow = new BrowserWindow();

	be_roster->StartWatching(be_app_messenger, B_REQUEST_QUIT);
	fBrowserWindow->Show();
}


void
Tranquility::MessageReceived(BMessage *message)
{
	switch(message->what) {
		case kMsgForward:
		case kMsgUpdate:
		case kMsgBitmapData:
		case B_SOME_APP_QUIT:
			fRenderAppManager->MessageReceived(message);
			break;

		default:
			BApplication::MessageReceived(message);
			break;
	}
}


bool
Tranquility::QuitRequested()
{
	be_roster->StopWatching(be_app_messenger);
	fRenderAppManager->Quit();

	return true;
}


RenderAppManager*
Tranquility::GetRenderAppManager()
{
	return fRenderAppManager;
}

//	#pragma mark -


int
main(int, char **)
{
	Tranquility *browser = new Tranquility();
	browser->Run();
	delete browser;

#ifdef DEBUG
	DumpUnfreed();
#endif

	return 0;
}

