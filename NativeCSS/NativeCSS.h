/*
 File: NativeCSS.h
 
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
 Refresh period for styleWithCSSFile:updateFromURL:refreshPeriod:andCSSFromStudioAppId:
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


/**
 nativeCSS styles your app and enables dynamic app editing with nativeCSS studio ( http://nativecss.com/studio ) nativeCSS studio enables runtime CSS changes to be applied during development or after the app is released.
 
 nativeCSS also manages your style content, by downloading and caching remote assets such as images and fonts.
 
 *Styling with CSS & NativeCSS Studio*
 
Our recommended setup is loading an initial CSS file and developing your CSS with nativeCSS studio. During development NativeCSS studio will update your app at runtime, but in production it will only update the CSS on app opening.
 
    - (void)applicationDidBecomeActive:(UIApplication *)application{
 
    [NativeCSS styleWithCSSFile:filename andCSSFromStudioAppId:@"YOUR APP ID"];
 
  ( see styleWithCSSFile:andCSSFromStudioAppId: )
 
 *Styling with CSS Strings & NativeCSS Studio*
 
 
 Alternatively, you can style your app with CSS strings and CSS content from nativeCSS studio. During development NativeCSS studio will update your app at runtime, but in production it will only update the CSS on app opening.
 
    - (void)applicationDidBecomeActive:(UIApplication *)application{
 
    [NativeCSS setStudioAppId:@"YOUR APP ID"];
    [NativeCSS styleWithCSSString:@"label{background-color:red}"];
 
 ( see setStudioAppId: and styleWithCSSString: )
 
 *Styling with custom remote CSS & NativeCSS Studio*
 
 Styling can be applied from a remote CSS file and nativeCSS handles all the caching for you.
 For most users we recommend our simple call to load a remote URL, update periodically and have an initial CSS file included in your app for the first startup. Any custom initial content or remote content will be overridden by your changes on nativeCSS Studio.
 
     - (void)applicationDidBecomeActive:(UIApplication *)application{
     
     NSURL *cssURL = [NSURL URLWithString:@"http://localhost:8000/styles.css"];
 
     [NativeCSS styleWithCSSFile:@"initial.css" andCSSFromStudioAppId:(NSString*) appId
                                                updateFromURL:cssURL
                                                refreshPeriod:NCRemoteContentRefreshEverySecond];
 
 ( see styleWithCSSFile:andCSSFromStudioAppId:updateFromURL:refreshPeriod: )
 
 More advanced options for managing CSS content are also provided.
 
 *Managing the CSS content manually*
 
 There are many ways to download and cache your CSS content. nativeCSS provides several helper functions to simplify this.
 
    - (void)applicationDidBecomeActive:(UIApplication *)application{
 
        [NativeCSS styleWithCSSFile:@"initial.css" andCSSFromStudioAppId:@"YOUR APP ID"];
 
        NSURL *cssURL = [NSURL URLWithString:@"http://localhost:8000/styles-with-assets.css"];
        // obtain new CSS and all remote assets:
 
        [NativeCSS updateCSSAndAssetsFromURL: yourCSSURL
                       completionBlock:^(BOOL success,  
                                         BOOL cssIsDifferent,
                                         NSString *cssContent,
                                         NSArray *unavailableAssets) {
            if(success && cssIsDifferent){
                [self showWaitView]; // implement this yourself
                [NativeCSS styleWithCSSString:cssContent];
                [self hideWaitView]; // implement this yourself
            }
        }];

 ( see updateCSSAndAssetsFromURL:completionBlock: )
 
 The completion block returns CSS from both your target URL and NativeCSS studio. The developer is responsible for calling styleWithCSSString: to apply this CSS to the application. The content from NativeCSS studio is appended to your target CSS content and can edited before being passed to nativeCSS.
 
  *Debugging*
 
 You can inspect / modify all your CSS:
 
    - (void)applicationDidBecomeActive:(UIApplication *)application{
 
        // inspect CSS for your app
        [NativeCSS setCSSStylingPreprocessBlock:^NSMutableArray *(NSMutableArray *allStylingRules) {
            NSLog(@"%@",allStylingRules);
            return allStylingRules;
        }];
 
 ( see setCSSStylingPreprocessBlock: )
 
 or CSS just for a particular view
 
         // inspect / modify CSS for your views:
        [view setCSSStylingPreprocessBlock:^NSMutableDictionary* (NSMutableDictionary *matchingStyle){
            NSLog(@"%@",matchingStyle);
            return matchingStyle;
        }];
 
 ( see [UIView(NativeCSS) setCSSStylingPreprocessBlock:] )
 
  *Cache library*
 
 We use a standard cache implementation https://github.com/rs/SDWebImage.
 */
@interface NativeCSS :NSObject

#pragma mark Style
/** @name Style */

/**
 Style application with CSS file and from nativeCSS Studio ( http://nativecss.com/studio ).
 
 On the first load the initial CSS file will be used, before new CSS content is downloaded from nativeCSS Studio.
 Any CSS content for this app from nativeCSS Studio will be appended to your initial CSS file.
 
 @param filename an initial CSS file to apply before remote CSS is downloaded from nativeCSS studio.
 @param appId nativeCSS Studio app id ( see http://nativecss.com/studio )
 
 @warning Remote assets are downloaded on demand. To avoid this delay see updateCSSAndFetchMissingAssetsFromURL:completionBlock:
 @warning Remote assets are not re-downloaded, so any new versions of the asset will not be shown. To force redownloading of assets see updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) styleWithCSSFile:(NSString*) filename andCSSFromStudioAppId:(NSString*) appId;

/**
 Style application and any new views with a CSS string. This method requires a Studio App Id, by setStudioAppId: or any method taking an app Id.
 
    [NativeCSS setStudioAppId:@"YOUR APP ID"];
    [NativeCSS styleWithCSSString:@"label{background-color:red}"];

 @param cssContent CSS styles to be applied
 
 @warning Remote assets are downloaded on demand. To avoid this delay see updateCSSAndFetchMissingAssetsFromURL:completionBlock:
 @warning Remote assets are not re-downloaded, so any new versions of the asset will not be shown. To force redownloading of assets see updateCSSAndAssetsFromURL:completionBlock:
 */
+(void)  styleWithCSSString:(NSString*) cssContent;

#pragma mark Download & Style
/** @name Download & Style */

/**
 Style application and any new views with CSS from a remote URL.
 On the first load the initial CSS file will be used, whilst the remote CSS and its assets are downloaded.

 @param filename an initial CSS file to apply before remote CSS is downloaded.
 @param appId nativeCSS Studio app id ( see http://nativecss.com/studio )
 @param remoteCSSURL the remote CSS to download and apply.
 @param refreshPeriod  the time before the CSS is automatically updated.
 */
+(void) styleWithCSSFile:(NSString*) filename andCSSFromStudioAppId:(NSString*) appId updateFromURL:(NSURL*) remoteCSSURL refreshPeriod:(NCRemoteContentRefreshPeriod) refreshPeriod;


#pragma mark Download CSS and Assets
/** @name Downloading and Caching */

/**
 We recommend using this method for updating your CSS content from a URL.
 
 It re-downloads CSS from your remote URL and then downloads and caches any missing associated styling assets like fonts, images etc. When the completion block returns with success all referenced assets are available in the cache.
 
 To display a loading screen use this method with styleWithCSSString:
 
    [self showWaitView];
 
    [NativeCSS updateCSSAndFetchMissingAssetsFromURL:url
            completionBlock:^(BOOL success, BOOL cssIsDifferent, NSString* cssContent, NSArray *unavailableAssets) {
 
        [NativeCSS styleWithCSSString:cssContent];
        [self hideWaitView];
    }];
 
 @param url location of CSS file.
 @param completionBlock Callback block with success as true, if the CSS and all the assets were downloaded otherwise success as false with CSS content, if available, and a list of remote failed assets.
 
 @warning Remote assets are only downloaded once, to update any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) updateCSSAndFetchMissingAssetsFromURL:(NSURL*) url completionBlock:(void (^)(BOOL success, BOOL cssIsDifferent,NSString* cssContent,NSArray *unavailableAssets)) completionBlock;

/**
 Download and cache remote CSS file. After the CSS file is downloaded the completion block is called.
 
 @param url location of CSS file.
 @param completionBlock Callback block with success as true, if the CSS was downloaded otherwise success as false.
 
 @warning Remote assets are not pre-fetched with this method, and are downloaded ondemand. To pre-fetch any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) updateCSSFromURL:(NSURL*) url completionBlock:(void (^)(BOOL success, BOOL cssIsDifferent, NSString* cssContent)) completionBlock;

/**
 Download and cache remote CSS file and associated styling assets like fonts, images etc from your remote URL. After all assets are downloaded the completion block is called.
 
 @param url location of CSS file.
 @param completionBlock Callback block with success as true, if the CSS and all the assets were downloaded otherwise success as false with CSS content, if available, and a list of remote failed assets.
 
 */
+(void) updateCSSAndAssetsFromURL:(NSURL*) url completionBlock:(void (^)(BOOL success, BOOL cssIsDifferent, NSString* cssContent, NSArray *unavailableAssets)) completionBlock;

#pragma mark Development
/** @name Development */
/**
 Download and cache remote CSS file and repeat after the repeat interval. After the CSS file is downloaded the completion block is called every time.
 
 @param url location of CSS file.
 @param repeatInterval number of seconds between redownloading and caching remote CSS file and calling completion block.
 @param completionBlock Callback block with success as true, if the CSS was downloaded otherwise success is false.
 
 @warning This method is not recommended for released apps, as it can be data intensive. Consider calling updateCSSAndAssetsFromURL:completionBlock: when the application is activated.
 
 @warning Remote assets are not pre-fetched with this method, and are downloaded ondemand. To pre-fetch any remote assets call updateCSSAndAssetsFromURL:completionBlock:
 */
+(void) updateCSSFromURL:(NSURL*) url repeatInterval: (double) repeatInterval completionBlock:(void (^)(BOOL success,  BOOL cssIsDifferent, NSString* cssContent)) completionBlock;

#pragma mark Manage CSS and Assets
/** @name Managing Assets */

/**
 Downloads all image and font assets found in the CSS string.
 
 @param cssContent the CSS to scan for assets.
 @param remoteHost the remote host to reference for relative remote urls.
 @param redownloadIfCached if true, will redownload all assets. If false, will download only missing assets.
 @param completionBlock Callback block with success as true, if all assets were downloaded otherwise success is false.

 */
+(void) downloadAssetsFromCSSString:(NSString*) cssContent withRemoteHost:(NSURL*) remoteHost redownloadIfCached:(BOOL) redownloadIfCached  completionBlock:(void (^)(BOOL success, NSArray *unavailableAssets)) completionBlock;

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
 Sets a remote host for any remote image assets.
 
 Any image url beginning with a '/' will be prefixed by the remote host.
 
 For example, a remote host of http://nativecss.com/ and css
 
 background-image: url('/path/img.png/')
 
 will be rendered using the image url('http://nativecss.com/path/img.png/')
 
 Note any existing path on the remote host will be ignored, so http://nativecss.com/styles/ will be read as http://nativecss.com/
 
 @param remoteHost remote host to prefix relative image urls with.
 */
+(void) setRemoteHost:(NSURL*) remoteHost;

/**
 Sets the nativeCSS Studio app id.
 @param appId nativeCSS Studio app id ( see http://nativecss.com/studio )
 */
+(void) setStudioAppId:(NSString*) appId;

/**
 Disables NativeCSS studio, by default NativeCSS Studio is enabled.
 @param nativeCSSStudioEnabled set to false to disable nativeCSS.
 */
+(void) setNativeCSSStudioEnabled:(BOOL) nativeCSSStudioEnabled;

#pragma mark LESS
/** @name Less */

/**
 Styles your app with CSS content from a Less string, as well as from NativeCSS Studio.
 
 @param appId nativeCSS Studio app id ( see http://nativecss.com/studio )
 @param lessContent style native CSS with a LESS string.
 */
+(void) styleWithLESSString:(NSString*) lessContent andCSSFromStudioAppId:(NSString*) appId;

#pragma mark Debug

/**
 Inspect and modify styles to be applied to the app.
 
 @param processBlock accepts and returns an array of styles, developers can modify the styling in this dictionary, but this is unsupported. Set to nil to remove processing block.
 **/
+ (void) setCSSStylingPreprocessBlock:(NSMutableArray* (^)(NSMutableArray *allStylingRules)) processBlock;

/**
 Returns the current preprocess block for this app.
 */
+ (NSMutableArray* (^)(NSMutableArray *allStylingRules)) CSSStylingPreprocessBlock;


/** @name Debug */
/**
 Sets debug logging.
 @param debugLoggingEnabled set to true to enable debug logging.
 */
+(void) setCSSDebugLogging:(BOOL) debugLoggingEnabled;
@end
