/*
 File: UIView+NativeCSS.h
 
 Disclaimer: IMPORTANT:  This Make Apps Better software is supplied to you by Make Apps Better
 LTD. ("Make Apps Better") in consideration of your agreement to the following
 terms, and your use, installation, modification or redistribution of
 this Make Apps Better software constitutes acceptance of these terms.  If you do
 not agree with these terms, please do not use or install this Make Apps Better software.
 
 In consideration of your agreement to abide by the following terms, and
 subject to these terms, Make Apps Better grants you a personal, non-exclusive
 license, under Make Apps Better's copyrights in this original Make Apps Better software (the
 "Make Apps Better Software"), to use the Make Apps Better
 Software, without modifications, in source and/or binary forms;
 provided you must retain this notice and the following
 text and disclaimers in all such redistributions of the Make Apps Better Software.
 Neither the name, trademarks, service marks or logos of Make Apps Better LTD. may
 be used to endorse or promote products derived from the Make Apps Better Software
 without specific prior written permission from Make Apps Better.  Except as
 expressly stated in this notice, no other rights or licenses, express or
 implied, are granted by Make Apps Better herein, including but not limited to any
 patent rights that may be infringed by your derivative works or by other
 works in which the Make Apps Better Software may be incorporated.
 
 The Software is provided by Make Apps Better on an "AS IS" basis.  Make Apps Better
 MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
 THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE, REGARDING THE Make Apps Better SOFTWARE OR ITS USE AND
 OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL MAKE APPS BETTER BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
 MODIFICATION AND/OR DISTRIBUTION OF THE MAKE APPS BETTER SOFTWARE, HOWEVER CAUSED
 AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
 STRICT LIABILITY OR OTHERWISE, EVEN IF MAKE APPS BETTER HAS BEEN ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 
 Copyright (C) 2013 Make Apps Better LTD. All Rights Reserved.
 
 */


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/**
 nativeCSS applies its styling based on notifications from iOS, using UIAppearance.
 
 However, there are cases where UIAppearance is not called on a new or altered view. 
 
 We know this occurs on the backgroundView for UITableViewCells. In short, the UITableView reuses the cell rather than creating a new one. This creates a problem for UIAppearance. 
 
 In cases like this we suggest refreshing the CSS styling for UITableViewCells and UICollectionViewCells in the delegate methods.
 */
@interface UIView (NativeCSS)
/**
 Restyle a view. This reapplies the CSS selectors and restyles the view.
 @see refreshCSSStylingAfterLayoutChange:
 */
-(void) refreshCSSStyling;

/**
 Restyle a view with an altered layout.
 @param layoutChange if true, nativeCSS will ignore the view's previous frame.
 */
-(void) refreshCSSStylingAfterLayoutChange:(BOOL) layoutChange;
/**
 Restyle a view but ignore subviews.
 @param ignoreSubviews if true, nativeCSS will only style the current view and no subviews.
 */
-(void) refreshCSSStylingAndIgnoreSubviews:(BOOL) ignoreSubviews;


/**
 Assigns a CSS class to a view.
 Any CSS Styling matching the passed class will be applied to this view.
 
 @param className the CSS class
 */
-(void) addCSSClass:(NSString*) className;


/**
 Removes a CSS class from a view.
 
 @param className the CSS class to remove
 */
-(void) removeCSSClass:(NSString*) className;


/**
 Returns all CSS classes associated with this view.
 */
-(NSArray*) CSSClasses;

/**
 Sets the CSS id for this view. This overrides the original ID set in code or Nib files.
 Any CSS Styling matching the passed id will be applied to this view. Set the id to null to remove all aliases.
 
 @param cssId the CSS id. Set to a new id or null to remove.
 */
-(void) setCSSId:(NSString*) cssId;

/**
 The CSS id for this view. If set, this overrides the original ID set in code or Nib files.
 */
-(NSString*) CSSId;



@end
