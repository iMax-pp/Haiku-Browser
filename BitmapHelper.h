//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <Application.h>
#include <Bitmap.h>
#include <IconUtils.h>
#include <Resources.h>

static BBitmap*
RetrieveBitmap(int32 id, BRect rect = BRect(0, 0, 63, 63))
{
	BResources *resource = BApplication::AppResources();
	size_t size = 0;

	const void *data = resource->LoadResource('VICN', id, &size);
	if (!data)
		return NULL;

	BBitmap *bitmap = new BBitmap(rect, B_RGBA32);
	if (BIconUtils::GetVectorIcon((const uint8 *)data, size, bitmap) != B_OK)
		return NULL;

	return bitmap;
}
