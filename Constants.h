//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef CONSTANTS_H
#define CONSTANTS_H


// Message constants
const static uint32 kMsgStartRenderApp = 'strt';
	// Used as the message constant to a message sent when launching the render
	// process, so it can be differentiated from an accidental user launch.

const static uint32 kMsgUpdate = 'updt';
const static uint32 kMsgBitmapData = 'bmdt';
const static uint32 kMsgForward = 'frwd';
const static uint32 kMsgLeaveRenderApp = 'leav';

const static uint32 kMsgManageBookmarks = 'mgbk';
const static uint32 kMsgOpenBookmark = 'opbk';

const static uint32 kMsgNavBack = 'back';
const static uint32 kMsgNavForward = 'forw';
const static uint32 kMsgNavReload = 'relo';
const static uint32 kMsgNavHome = 'home';
const static uint32 kMsgNavStop = 'stop';

const static uint32 kMsgNewTab = 'open';
const static uint32 kMsgCloseTab = 'clos';

#endif	// CONSTANTS_H

