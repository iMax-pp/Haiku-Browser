//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "RenderAppManager.h"
#include "AppSignatures.h"
#include "Constants.h"
#include "Tranquility.h"

#include <Bitmap.h>
#include <Messenger.h>
#include <OS.h>
#include <Roster.h>
#include <String.h>

#include <syslog.h>


RenderAppManager::RenderAppManager()
	: BHandler(),
	fProxyViewManager(new ProxyViewManager())
{
}


RenderAppManager::~RenderAppManager()
{
}


void
RenderAppManager::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kMsgForward:
		case kMsgUpdate:
		{
			int32 proxyID;
			message->FindInt32("proxyID", &proxyID);
			team_id renderTeam = fMapProxyToRender[proxyID];
			BMessenger(kRenderAppSignature, renderTeam).SendMessage(message);
			break;
		}

		case kMsgBitmapData:
		{
			int32 proxyID;
			message->FindInt32("proxyID", &proxyID);
			ProxyView *proxyView = fProxyViewManager->GetProxyFromID(proxyID);
			syslog(LOG_DEBUG, "RenderAppManager: received kMsgBitmapData message");
			BBitmap *bitmap = dynamic_cast<BBitmap*>(BBitmap::Instantiate(message));
			if (bitmap != NULL) {
				if (proxyView->Window()->Lock()) {
					proxyView->SetViewBitmap(bitmap);
					proxyView->Window()->Unlock();
				}
				delete bitmap;
			} else {
				syslog(LOG_DEBUG, "RenderAppManager: bitmap from message is not valid!");
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
			BString sig;
			if (message->FindString("be:signature", &sig) == B_OK) {
				if (sig.Compare(kRenderAppSignature) == 0) {
					team_id renderTeam;
					message->FindInt32("be:team", &renderTeam);
					std::set<int32> proxyList = fMapRenderToProxy[renderTeam];
					std::set<int32>::iterator id;
					for (id = proxyList.begin(); id != proxyList.end(); id++) {
						fProxyViewManager->GetProxyFromID(*id)->DrawSadTab("The render process has quit!");
						fMapProxyToRender.erase(*id);
					}
					fMapRenderToProxy.erase(renderTeam);
				}
			}
			break;
		}

		default:
		      BHandler::MessageReceived(message);
		      break;
	}
}


void
RenderAppManager::Quit()
{
	MapIntVecInt::iterator it;
	team_id renderTeam;

	for (it = fMapRenderToProxy.begin(); it != fMapRenderToProxy.end(); it++) {
		renderTeam = it->first;
		BMessenger(kRenderAppSignature, renderTeam).SendMessage(B_QUIT_REQUESTED);
	}
}


team_id
RenderAppManager::StartRenderBoy(BMessage startMsg)
{
	team_id renderTeam;
	if (be_roster->Launch(kRenderAppSignature, &startMsg, &renderTeam) != B_OK)
		syslog(LOG_DEBUG, "RenderAppManager: There was an error trying to launch the render process!");
	return renderTeam;
}


void
RenderAppManager::StopRenderBoy(team_id renderTeam)
{
	MapIntInt::iterator it;
	for (it = fMapProxyToRender.end(); it != fMapProxyToRender.begin(); ++it) {
		if (it->second == renderTeam)
			fMapProxyToRender.erase(it);
	}

	BMessenger(kRenderAppSignature, renderTeam).SendMessage(B_QUIT_REQUESTED);
}


void
RenderAppManager::RenderBoyRequest(ProxyView *proxyView)
{
	team_id renderTeam;
	fProxyViewManager->AddProxyView(proxyView);
	int32 proxyID = fProxyViewManager->GetIDFromProxy(proxyView);
		// Something may be done to avoid multiple RenderBoys per ProxyView

	if (true) {
		// For the moment each time a ProxyView needs a RenderBoy,
		// a RenderBoy is started. This isn't the expected behaviour.
		BMessage startMsg(kMsgStartRenderApp);
		startMsg.AddRect("renderFrame", proxyView->Bounds());
		startMsg.AddInt32("teamID", my_app->Team());
		startMsg.AddInt32("proxyID", proxyID);

		renderTeam = StartRenderBoy(startMsg);
	}

	fMapProxyToRender[proxyID] = renderTeam;
	fMapRenderToProxy[renderTeam].insert(proxyID);
}


void
RenderAppManager::LeaveRenderBoy(int32 proxyID)
{
	team_id renderTeam = fMapProxyToRender[proxyID];
	fMapProxyToRender.erase(proxyID);
	fMapRenderToProxy[renderTeam].erase(proxyID);

	BMessage leaveMsg(kMsgLeaveRenderApp);
	leaveMsg.AddInt32("proxyID", proxyID);
	BMessenger(kRenderAppSignature, renderTeam).SendMessage(&leaveMsg);

	if (fMapRenderToProxy[renderTeam].empty()) {
		StopRenderBoy(renderTeam);
		fMapRenderToProxy.erase(renderTeam);
	}
}
