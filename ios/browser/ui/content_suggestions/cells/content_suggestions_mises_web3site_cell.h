// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_UI_CONTENT_SUGGESTIONS_CELLS_CONTENT_SUGGESTIONS_MISES_WEB3SITE_CELL_H_
#define IOS_CHROME_BROWSER_UI_CONTENT_SUGGESTIONS_CELLS_CONTENT_SUGGESTIONS_MISES_WEB3SITE_CELL_H_

#import <MaterialComponents/MDCCollectionViewCell.h>

@class FaviconView;

// Associated cell to display a Most Visited tile based on the suggestion.
// It displays the favicon for this Most Visited suggestion and its title.
@interface ContentSuggestionsMisesWeb3siteCell : MDCCollectionViewCell

// FaviconView displaying the favicon.
@property(nonatomic, strong, readonly, nonnull) FaviconView* faviconView;

// Title of the Most Visited.
@property(nonatomic, strong, readonly, nonnull) UILabel* titleLabel;

// Size for a Most Visited tile.
+ (CGSize)defaultSize;

@end

#endif  // IOS_CHROME_BROWSER_UI_CONTENT_SUGGESTIONS_CELLS_CONTENT_SUGGESTIONS_MISES_WEB3SITE_CELL_H_
