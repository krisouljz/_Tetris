//
//  TSViewDisplayer.h
//  RouteIntent
//
//  Created by 王俊仁 on 2017/11/24.
//


#import "TSDisplayerAdapter.h"

NS_ASSUME_NONNULL_BEGIN

/// completion need null check
typedef void(^TSViewDisplayAction)(UIViewController *source, UIViewController *target, BOOL animated, void (^ _Nullable completion)(void));

typedef void(^TSViewFinishAction)(UIViewController *vc, BOOL animated, void (^ _Nullable completion)(void));

NS_SWIFT_NAME(ViewDisplayer)
@interface TSViewDisplayer : TSDisplayerAdapter

@property (nonatomic, copy) TSViewDisplayAction displayAction;

@property (nonatomic, copy) TSViewFinishAction finishAction;

+ (instancetype)displayerWith:(TSViewDisplayAction)display finish:(TSViewFinishAction)finish;

@end

NS_ASSUME_NONNULL_END
