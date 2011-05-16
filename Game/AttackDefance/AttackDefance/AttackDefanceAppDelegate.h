//
//  AttackDefanceAppDelegate.h
//  AttackDefance
//
//  Created by Max Ford on 11. 3. 8..
//  Copyright 2011년 N/A. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AttackDefanceViewController;

@interface AttackDefanceAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet AttackDefanceViewController *viewController;

@end
