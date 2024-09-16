//
//  main.m
//  test_usercmp
//
//  Created by Salavat Rakhmanov on 13/9/24.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import <Usercentrics/Usercentrics.h>


int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
