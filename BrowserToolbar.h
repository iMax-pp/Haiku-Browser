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

#include <TextControl.h>

class BrowserToolbar : public BView {
	public:
		BrowserToolbar();
		virtual ~BrowserToolbar();

	private:
		void _DrawViews();

		BTextControl *fLocationBar;
};

#endif // BROWSER_TOOLBAR_H
