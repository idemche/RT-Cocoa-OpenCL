//
//  DHCircularProgressView.h
//  RT
//
//  Created by Igor Demchenko on 10/12/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface DHCircularProgressView : NSView

- (void)incrementBy:(double)value;
- (void)setMaxValue:(double)maxValue;
- (void)setCurrentValue:(double)currentValue;
- (void)setIncrementalSteps:(NSArray *)incrementalSteps;

- (double)currentValue;
- (double)maxValue;

@end
