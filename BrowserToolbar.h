//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BROWSER_TOOLBAR_H
#define BROWSER_TOOLBAR_H

#include <View.h>

#include <BitmapButton.h>
#include <TextControl.h>

class BrowserToolbar : public BView {
	public:
		BrowserToolbar();
		virtual ~BrowserToolbar();

		void ChangeGoStopButton(bool loading);

	private:
		void _DrawViews();

		BitmapButton *fGoStopButton;
		BTextControl *fLocationBar;
};

#endif // BROWSER_TOOLBAR_H
