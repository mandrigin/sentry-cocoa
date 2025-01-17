#import <Foundation/Foundation.h>

#import "SentryDefines.h"

@protocol SentrySpan;

@class SentryHub, SentryOptions, SentryEvent, SentryBreadcrumb, SentryScope, SentryUser, SentryId,
    SentryUserFeedback, SentryTransactionContext;

NS_ASSUME_NONNULL_BEGIN

/**
 * The main entry point for the SentrySDK.
 *
 * We recommend using `[Sentry startWithConfigureOptions]` to initialize Sentry.
 */
@interface SentrySDK : NSObject
SENTRY_NO_INIT

/**
 * Inits and configures Sentry (SentryHub, SentryClient) and sets up all integrations.
 */
+ (void)startWithOptions:(NSDictionary<NSString *, id> *)optionsDict NS_SWIFT_NAME(start(options:));

/**
 * Inits and configures Sentry (SentryHub, SentryClient) and sets up all integrations.
 */
+ (void)startWithOptionsObject:(SentryOptions *)options NS_SWIFT_NAME(start(options:));

/**
 * Inits and configures Sentry (SentryHub, SentryClient) and sets up all integrations. Make sure to
 * set a valid DSN.
 */
+ (void)startWithConfigureOptions:(void (^)(SentryOptions *options))configureOptions
    NS_SWIFT_NAME(start(configureOptions:));

/**
 * Captures a manually created event and sends it to Sentry.
 *
 * @param event The event to send to Sentry.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureEvent:(SentryEvent *)event NS_SWIFT_NAME(capture(event:));

/**
 * Captures a manually created event and sends it to Sentry. Only the data in this scope object will
 * be added to the event. The global scope will be ignored.
 *
 * @param event The event to send to Sentry.
 * @param scope The scope containing event metadata.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureEvent:(SentryEvent *)event
                 withScope:(SentryScope *)scope NS_SWIFT_NAME(capture(event:scope:));

/**
 * Captures a manually created event and sends it to Sentry. Maintains the global scope but mutates
 * scope data for only this call.
 *
 * @param event The event to send to Sentry.
 * @param block The block mutating the scope only for this call.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureEvent:(SentryEvent *)event
            withScopeBlock:(void (^)(SentryScope *scope))block NS_SWIFT_NAME(capture(event:block:));

/**
 * Creates a transaction, bound it to the hub and returns the instance.
 *
 * @param name The transaction name.
 * @param operation Short code identifying the type of operation the span is measuring.
 *
 * @return The created transaction.
 */
+ (id<SentrySpan>)startTransactionWithName:(NSString *)name
                                 operation:(NSString *)operation
    NS_SWIFT_NAME(startTransaction(name:operation:));

/**
 * Creates a transaction, bound it to the hub and returns the instance.
 *
 * @param name The transaction name.
 * @param operation Short code identifying the type of operation the span is measuring.
 * @param bindToScope Indicates whether the new transaction should be bind to the scope.
 *
 * @return The created transaction.
 */
+ (id<SentrySpan>)startTransactionWithName:(NSString *)name
                                 operation:(NSString *)operation
                               bindToScope:(BOOL)bindToScope
    NS_SWIFT_NAME(startTransaction(name:operation:bindToScope:));

/**
 * Creates a transaction, bound it to the hub and returns the instance.
 *
 * @param transactionContext The transaction context.
 *
 * @return The created transaction.
 */
+ (id<SentrySpan>)startTransactionWithContext:(SentryTransactionContext *)transactionContext
    NS_SWIFT_NAME(startTransaction(transactionContext:));

/**
 * Creates a transaction, bound it to the hub and returns the instance.
 *
 * @param transactionContext The transaction context.
 * @param bindToScope Indicates whether the new transaction should be bind to the scope.
 *
 * @return The created transaction.
 */
+ (id<SentrySpan>)startTransactionWithContext:(SentryTransactionContext *)transactionContext
                                  bindToScope:(BOOL)bindToScope
    NS_SWIFT_NAME(startTransaction(transactionContext:bindToScope:));

/**
 * Creates a transaction, bound it to the hub and returns the instance.
 *
 * @param transactionContext The transaction context.
 * @param bindToScope Indicates whether the new transaction should be bind to the scope.
 * @param customSamplingContext Additional information about the sampling context.
 *
 * @return The created transaction.
 */
+ (id<SentrySpan>)startTransactionWithContext:(SentryTransactionContext *)transactionContext
                                  bindToScope:(BOOL)bindToScope
                        customSamplingContext:
                            (nullable NSDictionary<NSString *, id> *)customSamplingContext
    NS_SWIFT_NAME(startTransaction(transactionContext:bindToScope:customSamplingContext:));

/**
 * Creates a transaction, bound it to the hub and returns the instance.
 *
 * @param transactionContext The transaction context.
 * @param customSamplingContext Additional information about the sampling context.
 *
 * @return The created transaction.
 */
+ (id<SentrySpan>)startTransactionWithContext:(SentryTransactionContext *)transactionContext
                        customSamplingContext:
                            (nullable NSDictionary<NSString *, id> *)customSamplingContext
    NS_SWIFT_NAME(startTransaction(transactionContext:customSamplingContext:));

/**
 * Captures an error event and sends it to Sentry.
 *
 * @param error The error to send to Sentry.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureError:(NSError *)error NS_SWIFT_NAME(capture(error:));

/**
 * Captures an error event and sends it to Sentry. Only the data in this scope object will be added
 * to the event. The global scope will be ignored.
 *
 * @param error The error to send to Sentry.
 * @param scope The scope containing event metadata.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureError:(NSError *)error
                 withScope:(SentryScope *)scope NS_SWIFT_NAME(capture(error:scope:));

/**
 * Captures an error event and sends it to Sentry. Maintains the global scope but mutates scope data
 * for only this call.
 *
 * @param error The error to send to Sentry.
 * @param block The block mutating the scope only for this call.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureError:(NSError *)error
            withScopeBlock:(void (^)(SentryScope *scope))block NS_SWIFT_NAME(capture(error:block:));

/**
 * Captures an exception event and sends it to Sentry.
 *
 * @param exception The exception to send to Sentry.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureException:(NSException *)exception NS_SWIFT_NAME(capture(exception:));

/**
 * Captures an exception event and sends it to Sentry. Only the data in this scope object will be
 * added to the event. The global scope will be ignored.
 *
 * @param exception The exception to send to Sentry.
 * @param scope The scope containing event metadata.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureException:(NSException *)exception
                     withScope:(SentryScope *)scope NS_SWIFT_NAME(capture(exception:scope:));

/**
 * Captures an exception event and sends it to Sentry. Maintains the global scope but mutates scope
 * data for only this call.
 *
 * @param exception The exception to send to Sentry.
 * @param block The block mutating the scope only for this call.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureException:(NSException *)exception
                withScopeBlock:(void (^)(SentryScope *scope))block
    NS_SWIFT_NAME(capture(exception:block:));

/**
 * Captures a message event and sends it to Sentry.
 *
 * @param message The message to send to Sentry.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureMessage:(NSString *)message NS_SWIFT_NAME(capture(message:));

/**
 * Captures a message event and sends it to Sentry. Only the data in this scope object will be added
 * to the event. The global scope will be ignored.
 *
 * @param message The message to send to Sentry.
 * @param scope The scope containing event metadata.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureMessage:(NSString *)message
                   withScope:(SentryScope *)scope NS_SWIFT_NAME(capture(message:scope:));

/**
 * Captures a message event and sends it to Sentry. Maintains the global scope but mutates scope
 * data for only this call.
 *
 * @param message The message to send to Sentry.
 * @param block The block mutating the scope only for this call.
 *
 * @return The SentryId of the event or SentryId.empty if the event is not sent.
 */
+ (SentryId *)captureMessage:(NSString *)message
              withScopeBlock:(void (^)(SentryScope *scope))block
    NS_SWIFT_NAME(capture(message:block:));

/**
 * Captures a manually created user feedback and sends it to Sentry.
 *
 * @param userFeedback The user feedback to send to Sentry.
 */
+ (void)captureUserFeedback:(SentryUserFeedback *)userFeedback
    NS_SWIFT_NAME(capture(userFeedback:));

/**
 * Adds a Breadcrumb to the current Scope of the current Hub. If the total number of breadcrumbs
 * exceeds the `SentryOptions.maxBreadcrumbs`, the SDK removes the oldest breadcrumb.
 *
 * @param crumb The Breadcrumb to add to the current Scope of the current Hub.
 */
+ (void)addBreadcrumb:(SentryBreadcrumb *)crumb NS_SWIFT_NAME(addBreadcrumb(crumb:));

/**
 * Use this method to modify the current Scope of the current Hub. The SDK uses the Scope to attach
 * contextual data to events.
 *
 * @param callback The callback for configuring the current Scope of the current Hub.
 */
+ (void)configureScope:(void (^)(SentryScope *scope))callback;

/**
 * Checks if the last program execution terminated with a crash.
 */
@property (nonatomic, class, readonly) BOOL crashedLastRun;

/**
 * Set user to the current Scope of the current Hub.
 *
 * @param user The user to set to the current Scope.
 */
+ (void)setUser:(SentryUser *_Nullable)user;

/**
 * Starts a new session. If there's a running session, it ends it before starting the new one.
 */
+ (void)startSession;

/**
 * Ends the current session.
 */
+ (void)endSession;

/**
 * This forces a crash, useful to test the SentryCrash integration
 */
+ (void)crash;

@end

NS_ASSUME_NONNULL_END
