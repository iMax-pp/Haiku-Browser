//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef TRANQUILITY_H
#define TRANQUILITY_H


#include <Application.h>

// #include <stdio.h>

#include "BrowserWindow.h"


class Tranquility : public BApplication {
	public:
		Tranquility();
		~Tranquility();

		void AboutRequested();
		void MessageReceived(BMessage *message);
		void ReadyToRun();
		bool QuitRequested();

		BList *ChannelList();

  private:
		BrowserWindow *fBrowserWindow;
		BList *fChannelList;
};


#define my_app dynamic_cast<Tranquility*>(be_app)


#endif	// TRANQUILITY_H

