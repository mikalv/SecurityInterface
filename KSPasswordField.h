//
//  KSPasswordField.h
//  Sandvox
//
//  Created by Mike Abdullah on 28/04/2012.
//  Copyright (c) 2012-2014 Karelia Software. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Cocoa/Cocoa.h>

typedef NS_ENUM(NSInteger, KSPasswordFieldMatching) {
    KSPasswordFieldMatchingHideMatch = 0,
    KSPasswordFieldMatchingDoesntMatch,
    KSPasswordFieldMatchingPartialMatch,
    KSPasswordFieldMatchingFullMatch
};

typedef NS_ENUM(NSInteger, KSPasswordFieldMeter) {
    KSPasswordFieldMeterEmpty = 0,     // Disallow, very short; don't show strength yet
    KSPasswordFieldMeterCommon,        // Disallow, too common
    KSPasswordFieldMeterShort,         // Disallow, too short
    KSPasswordFieldMeterInsecure,      // Allow, but warn it's insecure (a.k.a. very weak)
    KSPasswordFieldMeterWeak,          // Allow, but weak
    KSPasswordFieldMeterFair,
    KSPasswordFieldMeterStrong
};

extern NSString *KSPasswordFieldDidBecomeFirstResponderNotification;

@interface KSPasswordField : NSSecureTextField

@property (nonatomic) IBInspectable BOOL showStrength;
@property (nonatomic) IBInspectable BOOL showMatchIndicator;
@property (nonatomic) IBInspectable BOOL useSmartPaste;
@property (nonatomic) KSPasswordFieldMeter passwordMeter;

/**
 Whether to display the password as plain text or not.
 */
@property (nonatomic) IBInspectable BOOL showsText;

@property (nonatomic, assign) float strength;
@property (nonatomic, assign) NSUInteger length;
@property (nonatomic, assign) KSPasswordFieldMatching matching;
@property (nonatomic, copy) NSString *descriptionOfStrength;

/**
 Whether the receiver becomes first responder whenever `.showsText` changes.
 
 The default is `YES`, which means that whenever the password is shown or hidden,
 the field will try to become the first responder, ready for the user to type
 into it. Set to `NO` if you want to perform your own management of the first
 responder instead.
 */
@property (nonatomic) BOOL becomesFirstResponderWhenToggled;

/**
 Sets `.showsText` to `YES`.
 
 Convenient for connecting up a "Show Password" button.
 */
- (IBAction)showText:(id)sender;

/**
 Sets `.showsText` to `NO`.
 
 Convenient for connecting up a "Hide Password" button.
 */
- (IBAction)secureText:(id)sender;

/**
 Toggles the value of `.showsText`.
 
 Generally connected up as the action of a "Show Password" checkbox, or some
 kind of toggle button.
 */
- (IBAction)toggleTextShown:(id)sender;

/**
 Performs cleanup of a potential password by limiting to a single line, and trimming whitespace.
 
 Called by `KSPasswordField` when the user pastes or drags in a string.
 
 @param string The password string to be cleaned up.
 */
- (NSString *)cleanedPasswordForString:(NSString *)string;


- (void)setStrength:(float)strength length:(NSUInteger)length;

- (BOOL)strongEnough;

@end


@interface KSPasswordTextFieldCell : NSTextFieldCell
@end

@interface KSPasswordSecureTextFieldCell : NSSecureTextFieldCell
@end
