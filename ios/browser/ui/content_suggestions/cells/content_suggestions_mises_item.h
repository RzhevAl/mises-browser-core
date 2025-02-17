// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_UI_CONTENT_SUGGESTIONS_CELLS_CONTENT_SUGGESTIONS_MISES_ITEM_H_
#define IOS_CHROME_BROWSER_UI_CONTENT_SUGGESTIONS_CELLS_CONTENT_SUGGESTIONS_MISES_ITEM_H_

//#import <MaterialComponents/MDCCollectionViewCell.h>

#import "ios/chrome/browser/ui/collection_view/cells/collection_view_item.h"
#import "ios/chrome/browser/ui/content_suggestions/cells/suggested_content.h"

#import <MaterialComponents/M3CButton.h>

// // Item to display what is new in the ContentSuggestions.
// @interface ContentSuggestionsMisesItem : CollectionViewItem<SuggestedContent>



// + (nonnull NSString*)accessibilityIdentifier;

// @end

// Associated cell, displaying what is new.
@interface ContentSuggestionsMisesCell : UIView

@property(nonatomic, strong, nonnull) M3CButton* enterButton;

// Returns the height needed by a cell contained in |width| containing |text|.
+ (CGFloat)heightForWidth:(CGFloat)width;

@end



#endif  // IOS_CHROME_BROWSER_UI_CONTENT_SUGGESTIONS_CELLS_CONTENT_SUGGESTIONS_WHATS_NEW_ITEM_H_
