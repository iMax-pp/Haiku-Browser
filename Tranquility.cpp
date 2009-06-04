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
#include "BrowserWindow.h"
#include "Constants.h"

#include <Alert.h>
#include <Roster.h>
#include <String.h>

#ifdef DEBUG
#include "LeakTracker.h"
#endif

Tranquility::Tranquility()
	: BApplication(kBrowserAppSignature),
	fChannelList(new BList())
{
}


Tranquility::~Tranquility()
{
	delete fChannelList;
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
		case kMsgBitmapData: {
			Channel *link;
			team_id renderTeam;
			renderTeam = message->ReturnAddress().Team();
			for (int32 i = 0; i < fChannelList->CountItems(); i++) {
				link = static_cast<Channel *>(fChannelList->ItemAt(i));
				if (link->renderBoy == renderTeam) {
					link->proxyViewManager->MessageReceived(message);
					break;
				}
			}
			break;
		}

		case B_SOME_APP_QUIT: {
			BString sig;
			if (message->FindString("be:signature", &sig) == B_OK) {
				if (sig.Compare(kRenderAppSignature) == 0) {
					Channel *link;
					team_id renderTeam;
					message->FindInt32("be:team", &renderTeam);
					for (int32 i = 0; i < fChannelList->CountItems(); i++) {
						link = static_cast<Channel *>(fChannelList->ItemAt(i));
						if (link->renderBoy == renderTeam) {
							link->proxyViewManager->MessageReceived(message);
							break;
						}
					}
				}
			}
			break;
		}

		default:
			BApplication::MessageReceived(message);
			break;
	}
}


bool
Tranquility::QuitRequested()
{
	be_roster->StopWatching(be_app_messenger);

	Channel *link;
	for (int32 i = 0; i < fChannelList->CountItems(); i++) {
		link = static_cast<Channel *>(fChannelList->ItemAt(i));
		link->renderBoy = -1;
		link->proxyViewManager->Quit();
		delete link->proxyViewManager;
	}

	return true;
}


BList*
Tranquility::ChannelList()
{
	return fChannelList;
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

