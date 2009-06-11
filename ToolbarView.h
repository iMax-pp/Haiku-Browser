//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef TOOLBAR_VIEW_H
#define TOOLBAR_VIEW_H

#include <GroupView.h>

class ToolbarView : public BGroupView {
	public:
		ToolbarView();
		virtual ~ToolbarView();

		void Draw(BRect updateRect);
};

#endif // TOOLBAR_VIEW_H
