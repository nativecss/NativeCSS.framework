//
//  UITableViewCell+NativeCSS.h
//  NativeCSSLibrary
//
//  Created by Peter Nash on 06/06/2013.
//  Copyright (c) 2013 Peter Nash. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UITableViewCell (NativeCSS)

-(void) refreshCSSStylingWithTableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

@end
