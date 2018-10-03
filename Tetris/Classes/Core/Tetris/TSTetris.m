//
//  TSTetris.m
//  Tetris
//
//  Created by Junren Wong on 2018/9/28.
//

#import "TSTetris.h"

@implementation TSTetris

static TSTetris *__sharedInstance;
+ (instancetype)shared {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        __sharedInstance = [[TSTetris alloc] init];
    });
    return __sharedInstance;
}

- (instancetype)init {
    if (self = [super init]) {
        _server = [TSTetrisServer new];
        _moduler = [TSTetrisModuler new];
        _router = [TSRouter new];
    }
    return self;
}

- (void)tetrisStart {
    
}

#pragma mark - server methods

- (void)registerServiceByProtocol:(Protocol *)aProtocol class:(Class<TSServiceExportable>)aClass singleton:(BOOL)singleton {
    [_server bindServiceByProtocol:aProtocol class:aClass singleton:singleton];
    
}

#pragma mark - moduler methods

- (void)registerModuleByClass:(Class<TSTetrisModulable>)aClass priority:(TSModulePriority)priority {
    [_moduler registerModuleWithClass:aClass priority:TSModulePriorityNormal];
}

- (void)registerModuleByClass:(Class<TSTetrisModulable>)aClass {
    [_moduler registerModuleWithClass:aClass];
}

#pragma mark - router methods

- (void)bindUrl:(NSString *)url viewController:(Class<TSIntentable>)aClass {
    [_router bindUrl:url viewController:aClass];
}

@end
