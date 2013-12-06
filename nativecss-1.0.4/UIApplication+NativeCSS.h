/*
 File: UIApplication+NativeCSS.h
 
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
#import <QuartzCore/QuartzCore.h>

/**
 nativeCSS styles your app and manages your style content, by downloading and caching remote assets such as images and fonts.
 
*Applying the CSS*
 
 Styling is applied to your application using styleWithCSSString: we recommend calling this when your application becomes active.
    - (void)applicationDidBecomeActive:(UIApplication *)application{

        [UIApplication styleWithCSSString:@"label{background-color:red}"];
 
 *Using remote CSS*
 
 Styling can be applied from a remote CSS file and nativeCSS handles all the caching for you.
 For most users we recommend our simple call to load a remote URL, update periodically and have an initial CSS file included in your app for the first startup. 
 
    - (void)applicationDidBecomeActive:(UIApplication *)application{
 
        NSURL *cssURL = [NSURL URLWithString:@"http://localhost:8000/styles.css"];
 
        [UIApplication styleWithCSSFile:@"initial.css"
                                 updateFromURL:cssURL
                                 refreshPeriod:NCRemoteContentRefreshEverySecond];
 
 More advanced options for managing CSS content are also provided.
 
 *Managing the CSS content manually*
 
 There are many ways to download and cache your CSS content. nativeCSS provides helper functions to simplify this. These helper functions are useful at different time of the project lifecycle.
 
 *For development:* we recommend regularly refreshing the CSS content with updateCSSFromURL:repeatInterval:completionBlock:
     - (void)applicationDidBecomeActive:(UIApplication *)application{
 
        [UIApplication updateCSSFromURL: yourCSSURL] repeatInterval:1.0
                       completionBlock:^(BOOL success,  BOOL cssIsDifferent, NSString *cssContent) {
            if(success && cssIsDifferent)
                [UIApplication styleWithCSSString:cssContent];
    }];
 
  *For release:* we recommend using a bundled CSS file and updating your CSS with fetchMissingCSSAndAssetsFromURL:completionBlock:. This can be safely called multiple times, and will always return cached versions.
    - (void)applicationDidBecomeActive:(UIApplication *)application{
 
        NSString *initialCSSPath = [[NSBundle mainBundle] pathForResource:@"initial.css" ofType:nil];
        NSString *initialCSS = [NSString stringWithContentsOfFile:initialCSSPath encoding:NSASCIIStringEncoding error:nil];
        [UIApplication styleWithCSSString:initialCSS]; // apply initial css
 
        // obtain new CSS and all remote assets:
        [UIApplication fetchMissingCSSAndAssetsFromURL: yourCSSURL 
                       completionBlock:^(BOOL success, BOOL cssIsDifferent, NSString* cssContent, NSArray *unavailableAssets) {
            if(success && cssIsDifferent){
                [self showLoadingScreen]; // implement this yourself
                [UIApplication styleWithCSSString:cssContent];
                [self hideLoadingScreen]; // implement this yourself
        }];
 

 *Important:* fetchMissingCSSAndAssetsFromURL:completionBlock: will never update its cached content.
 
 To update a file regularly we recommend either updateCSSFromURL:completionBlock: or updatedCSSAndAssetsFromURL:completionBlock:, obviously reloading the assets will take alot more time and bandwidth. It's up to you how frequently to call this method. Presumably updating every day or  week will be sufficient for most applications.
 
    [UIApplication updateCSSAndAssetsFromURL: yourCSSURL 
                   completionBlock:^(BOOL success,  BOOL cssIsDifferent, NSString* cssContent, NSArray *unavailableAssets) {
        if(success && cssIsDifferent){
            [self showWaitView]; // implement this yourself
            [UIApplication styleWithCSSString:cssContent];
            [self hideWaitView]; // implement this yourself
        }
    }];
 
 We use a standard cache implementation https://github.com/rs/SDWebImage, but there will be no conflicts if you have this already installed, as we've renamed the relevant files.
 */

@interface UIApplication (NativeCSS)


/**
Refresh period for styleWithCSSFromURL:refreshPeriod:initialCSSFilename:
*/
typedef enum NCRemoteContentRefreshPeriod : NSUInteger {

NCRemoteContentRefreshNever = 0,
NCRemoteContentRefreshEverySecond= 1,
NCRemoteContentRefreshEveryFiveSeconds= 5,
NCRemoteContentRefreshEveryTenSeconds= 10,
NCRemoteContentRefreshEveryMinute = 60,
NCRemoteContentRefreshEveryHour= (60*60),
NCRemoteContentRefreshEveryDay = (60*60*24),
NCRemoteContentRefreshEveryWeek =(60*60*24*7)

} NCRemoteContentRefreshPeriod;




#pragma mark Download & Style

/** @name Download & Style */

/**
 Style application and any new views with CSS from a remote URL. 
 On the first load the initial CSS file will be used, whilst the remote CSS and its assets are downloaded.
 
@param remoteCSSURL the remote CSS to download and apply.
@param refreshPeriod  the time before the CSS is automatically updated.
@param filename an initial CSS file to apply before remote CSS is downloaded.
 */
+(void) styleWithCSSFile:(NSString*) filename updateFromURL:(NSURL*) remoteCSSURL refreshPeriod:(NCRemoteContentRefreshPeriod) refreshPeriod;
    
/** @name Styling */

#pragma mark CSS
/**
 Style application and any new views with CSS.
 
 @param cssContent CSS styles to be applied
 
 @warning Views can be presented whilst assets are loading, as remote assets will be downloaded on demand. For a smooth page style use fetchMissingCSSAndAssetsFromURL:completionBlock:
 @warning Remote assets are only downloaded once, to update any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) styleWithCSSString:(NSString*) cssContent;

/**
 Style application with CSS using images with remote relative paths.
 
 Any image url beginning with a '/' will be appended to the supplied remote host. Note any existing path on the remote host will be ignored, so http://nativecss.com/styles/ will be read as http://nativecss.com/
 
 For example, a remote host of http://nativecss.com/ and css
 
    background-image: url('/path/img.png/')
 
 will be rendered using the image url('http://nativecss.com/path/img.png/')
 
 @param cssContent CSS styles to be applied
 @param remoteHost remote host to prepend relative image urls with.
 
 @warning Views can be presented whilst assets are loading, as remote assets will be downloaded on demand. For a smooth page style use fetchMissingCSSAndAssetsFromURL:completionBlock:
 @warning Remote assets are only downloaded once, to update any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) styleWithCSSString:(NSString*) cssContent withRemoteHost:(NSURL*) remoteHost;
    
/**
 Style application and any new views with CSS.
 
 
 @param cssContent CSS styles to be applied
 @param debugLogging if true library will output log messages.

 */
+(void) styleWithCSSString:(NSString*) cssContent debugLogging:(BOOL) debugLogging;
    
#pragma mark CSS from File
    /**
     Style application and any new views with a named CSS file.
     
     
     @param filename CSS styles to be applied
     */
+(void) styleWithCSSFile:(NSString*) filename;
    
    /**
     Style application and any new views with named CSS file.
     
     
     
     @param filename CSS stylesheet to be applied
     @param debugLogging if true library will output log messages.
     */
+(void) styleWithCSSFile:(NSString*) filename debugLogging:(BOOL) debugLogging;
    
    /**
     Style application with CSS file using images with remote relative paths.
     
     Any image url beginning with a '/' will be appended to the supplied remote host. Note any existing path on the remote host will be ignored, so http://nativecss.com/styles/ will be read as http://nativecss.com/
     
     For example, a remote host of http://nativecss.com/ and css
     
     background-image: url('/path/img.png/')
     
     will be rendered using the image url('http://nativecss.com/path/img.png/')
     
     @param filename CSS stylesheet to be applied
     @param remoteHost remote host to prepend relative image urls with.
     */
+(void) styleWithCSSFile:(NSString*) filename withRemoteHost:(NSURL*) remoteHost;
  
#pragma mark LESS
    
+(void) styleWithLESSString:(NSString*) cssContent;
+(void) styleWithLESSString:(NSString*) cssContent debugLogging:(BOOL) debugLogging;
    
    
/** @name Downloading and Caching */
#pragma mark Download CSS and Assets
/**
 Download and cache, if missing, remote CSS file and associated styling assets like fonts, images etc. After all assets are downloaded the completion block is called.
 
 This method should be used with styleWithCSSString: to display a loading screen:
 
    [self showWaitView];
    [UIApplication fetchMissingCSSAndAssetsFromURL:url 
                                     completionBlock:^(BOOL success, BOOL cssIsDifferent, NSString* cssContent, NSArray *unavailableAssets) {
        [UIApplication styleWithCSSString:cssContent];
        [self hideWaitView];
    }];
 
 @param url location of CSS file.
 @param completionBlock Callback block with success as true, if the CSS and all the assets were downloaded otherwise success as false with CSS content, if available, and a list of remote failed assets.
 
  @warning Remote assets are only downloaded once, to update any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) fetchMissingCSSAndAssetsFromURL:(NSURL*) url completionBlock:(void (^)(BOOL success, BOOL cssIsDifferent,NSString* cssContent,NSArray *unavailableAssets)) completionBlock;

/**
 Download and cache remote CSS file and associated styling assets like fonts, images etc. After all assets are downloaded the completion block is called.

 @param url location of CSS file.
 @param completionBlock Callback block with success as true, if the CSS and all the assets were downloaded otherwise success as false with CSS content, if available, and a list of remote failed assets.
 
 */
+(void) updateCSSAndAssetsFromURL:(NSURL*) url completionBlock:(void (^)(BOOL success, BOOL cssIsDifferent, NSString* cssContent, NSArray *unavailableAssets)) completionBlock;

/**
 Download and cache remote CSS file. After the CSS file is downloaded the completion block is called.
 
 @param url location of CSS file.
 @param completionBlock Callback block with success as true, if the CSS was downloaded otherwise success as false.
 
 @warning Remote assets are not downloaded with this method, to reload any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) updateCSSFromURL:(NSURL*) url completionBlock:(void (^)(BOOL success, BOOL cssIsDifferent, NSString* cssContent)) completionBlock;
/**
 Download and cache remote CSS file and repeat after the repeat interval. After the CSS file is downloaded the completion block is called every time.
 
 @param url location of CSS file.
 @param repeatInterval number of seconds between redownloading and caching remote CSS file and calling completion block.
 @param completionBlock Callback block with success as true, if the CSS was downloaded otherwise success as false.
 
 @warning This method is not recommended for released apps, as it can be data intensive. Consider calling updateCSSFromURL:completionBlock: when the application is activated.
 @warning Remote assets are not downloaded with this method, to reload any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) updateCSSFromURL:(NSURL*) url repeatInterval: (double) repeatInterval completionBlock:(void (^)(BOOL success,  BOOL cssIsDifferent, NSString* cssContent)) completionBlock;

#pragma mark Manage CSS and Assets
/**
 Tests if a CSS file or asset as been cached locally.
 @param url location of remote CSS or asset
 @return true if cached, otherwise false
 */
+(BOOL) isAssetCachedForURL:(NSURL*) url;

/**
 Returns the last modified date for asset url.
 
 @param url location of remote CSS or asset
 @return date of last download, otherwise nil
 */
+(NSDate *) lastModifiedDateForURL:(NSURL*) url;

/**
 Returns a file reference to a locally cached CSS file or asset.
 @param url location of remote CSS or asset
 @return File reference if cached, otherwise null
 */
+(id) cachedAssetForURL:(NSURL*) url;

/**
 Deletes the cached asset downloaded from the specified URL. The specified URL is expected to return an asset, such as an image.
 
 @param url location of a remote asset.
 */
+(void) deleteCachedAssetForURL:(NSURL*) url;


/**
 Deletes all the cached assets referenced by the CSS content at the specified URL.
 The specified URL is expected to return CSS content containing references to images or fonts.
 
 @param url location of CSS content, which references remote assets.
 */
+(void) deleteCachedAssetsFromURL:(NSURL*) url;

/**
 Extracts all image and font assets in the target CSS URL. The url is expected
 The specified URL is expected to return CSS content containing references to images or fonts.
 
 @param url location of the remote CSS
 */
+(NSArray*) assetURLsFromURL:(NSURL*) url;

/**
 Deletes all cached assets.
 */
+(void) clearCSSAssetCache;


    
/**
 Sets debug logging.
 */
+(void) setCSSDebugLogging:(BOOL) debugLoggingEnabled;
@end
