//
//  UICollectionView+NativeCSS.h
//  Artlyst
//
//  Created by Peter Nash on 03/06/2013.
//  Copyright (c) 2013 Peter Nash. All rights reserved.
//

#import <UIKit/UIKit.h>



@interface UIView (NativeCSSCollectionView)

-(void) refreshCSSStylingWithCollectionView:(UIView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@end


