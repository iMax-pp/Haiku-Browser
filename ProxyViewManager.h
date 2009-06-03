//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef PROXY_VIEW_MANAGER_H
#define PROXY_VIEW_MANAGER_H

#include <Handler.h>
#include <Messenger.h>


class ProxyViewManager;

typedef struct Channel {
	int32 renderBoy;
	ProxyViewManager *proxyViewManager;
} Channel;

class BrowserWindow;

class ProxyView;

class ProxyViewManager : public BHandler {
	public:
		ProxyViewManager(ProxyView *proxyView);
		~ProxyViewManager();

		void MessageReceived(BMessage *message);

		void Run(BrowserWindow *browserWindow);
		void Quit();

	private:
		BMessenger *fMessenger;
		ProxyView *fProxyView;
		BrowserWindow *fBrowserWindow;
		Channel fLink;
};

#endif // PROXY_VIEW_MANAGER_H
