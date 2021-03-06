//
//  TSIntent.h
//  Tetris
//
//  Created by Junren Wong on 2018/9/30.
//

#import <Foundation/Foundation.h>
#import "TSTree.h"
#import "TSRouterProtocols.h"
#import "TSIntentDisplayerProtocol.h"
#import "TSStream.h"
#import "TSResult.h"
#import "TSIntercepter.h"
#import "TSIntentableBuilder.h"
#import "TSUtils.h"

NS_ASSUME_NONNULL_BEGIN




NS_SWIFT_NAME(Intent)
@interface TSIntent : NSObject <NSCopying>

typedef void (^TSIntentableDidCreateBlock)(id<TSIntentable> intentable);

@property (nonatomic, strong, nullable) Class<TSIntentable> intentClass;

@property (nonatomic, copy  , nullable) NSString *urlString;

@property (nonatomic, assign) BOOL skip; // skip the intercepters or not

@property (nonatomic, strong, nullable) TSIntentableBuilder *builder;
@property (nonatomic, copy  , nullable) TSIntentableFactoryBlock factory;

@property (nonatomic, strong, nullable) TSTreeUrlComponent *urlComponent;

@property (nonatomic, strong, readonly) NSMutableDictionary<NSString *, id> *extraParameters;

@property (nonatomic, strong, nullable) id<TSIntentDisplayerProtocol> displayer;

@property (nonatomic, copy  , nullable) TSIntentableDidCreateBlock didCreate;


- (BOOL)isCreatable;

/**
 designated initializer
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// subscript
- (id)objectForKeyedSubscript:(id)key;
/// subscript
- (void)setObject:(id)obj forKeyedSubscript:(id<NSCopying>)key;

/**
 get string parameter
 */
- (nullable NSString *)getString:(NSString *)key;

/**
 get number parameter
 */
- (nullable NSNumber *)getNumber:(NSString *)key;


- (void)addParam:(id)object forKey:(NSString *)key;
- (void)addParameters:(nullable NSDictionary *)parameters;


- (TSStream<TSResult *> *)resultWithKey:(NSString *)key;
- (void)sendResult:(id)result source:(nullable id)source for:(NSString *)key;


@end

#pragma mark - Creations

@interface TSIntent (Creations)

- (instancetype)initWithUrl:(NSString *)urlString;
- (instancetype)initWithClass:(Class<TSIntentable>)aClass;
- (instancetype)initWithDisplayer:(id<TSIntentDisplayerProtocol>)displayer;
- (instancetype)initWithFactory:(TSIntentableFactoryBlock)factory;
- (instancetype)initWithBuilder:(TSIntentableBuilder *)builder;

- (instancetype)initWithUrl:(nullable NSString *)urlString
                intentClass:(nullable Class<TSIntentable>)intentClass
                  displayer:(nullable id<TSIntentDisplayerProtocol>)displayer
                    builder:(nullable TSIntentableBuilder *)builder;


+ (instancetype)intentWithUrl:(nullable NSString *)urlString
                  intentClass:(nullable Class<TSIntentable>)intentClass
                    displayer:(nullable id<TSIntentDisplayerProtocol>)displayer
                      builder:(nullable TSIntentableBuilder *)builder;

+ (instancetype)intentWithUrl:(NSString *)urlString;
+ (instancetype)intentWithClass:(Class<TSIntentable>)aClass;
+ (instancetype)intentWithDisplayer:(id<TSIntentDisplayerProtocol>)displayer;
+ (instancetype)intentWithFactory:(TSIntentableFactoryBlock)factory;

@end

#pragma mark - Result

@interface TSIntent (TSResult)

@property (readonly) TSStream<TSResult *> *onDestroy;

- (void)sendNumber:(NSNumber *)number source:(id)sender;
@property (readonly) TSStream<TSResult<NSNumber *> *> *onNumber;

- (void)sendString:(NSString *)string source:(id)sender;
@property (readonly) TSStream<TSResult<NSString *> *> *onString;

- (void)sendDict:(NSDictionary *)dict source:(id)sender;
@property (readonly) TSStream<TSResult<NSDictionary *> *> *onDict;

- (void)sendSuccessWithSource:(id)sender;
@property (readonly) TSStream<TSResult *> *onSuccess;

- (void)sendCancelWithSource:(id)sender;
@property (readonly) TSStream<TSResult *> *onCancel;

@end

#pragma mark - TSSpecIntent

NS_SWIFT_NAME(IntentSerializable)
@protocol TSIntentSerializable
- (NSDictionary<NSString *, id> *)ts_toDict;
- (instancetype)initFromDict:(NSDictionary<NSString *, id> *)dict;
@end

NS_SWIFT_NAME(SpecIntent)
@interface TSSpecIntent<Parameter: id<TSIntentSerializable>, Spec: id<TSIntentSerializable>> : TSIntent

@property (nonatomic, strong) Class<TSIntentSerializable> specType;

- (void)input:(Parameter)value;

- (void)sendSpec:(Spec)value source:(id)sender;

@property (readonly) TSStream<TSResult<Spec> *> *onSpec;

- (instancetype)initWithSpecType:(Class<TSIntentSerializable>)aClass NS_DESIGNATED_INITIALIZER;

@end

@interface NSDictionary (TSIntentSerializable) <TSIntentSerializable>

@end

NS_ASSUME_NONNULL_END
