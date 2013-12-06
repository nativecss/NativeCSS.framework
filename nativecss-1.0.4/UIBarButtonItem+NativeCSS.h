/*
 File: UIBarButtonItem+NativeCSS.h
 
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


#import <UIKit/UIKit.h>

/**
 nativeCSS applies its styling based on notifications from iOS, using UIAppearance.
 
 However, there are cases where UIAppearance is not called on a new or altered view.
 
 We know this occurs for UIBarButtonItems.
 
 In cases like this we suggest adding a call to refreshCSSStylingInsideToolbar: method in your button's target method:
 
- (IBAction) buttonPressed:(id)sender {
 [self refreshCSSStylingInsideToolbar:toolbar];
}
 
 */
@interface UIBarButtonItem (NativeCSS)
/**
 Triggers nativeCSS to apply the styling for this view.
 */
- (void)refreshCSSStylingInsideToolbar:(UIToolbar*) toolbar;

@end
