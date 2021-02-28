// engine
#include "AndroidApplication.hpp"
#include <core/Log.hpp>

// stl
#include <functional>

//
// Main Thread Functions
//

AndroidApplication::AndroidApplication(ANativeActivity* activity,
    void* savedState,
    size_t savedStateSize)
    : m_activity(activity)
    , m_activityState(InitializationActivityState)
    , m_mutex()
    , m_conditionVariable()
    , m_isRunning(false)
    , m_isDestroyed(false)
    , m_isDestroyRequested(false)
    , m_configuration(activity->assetManager)
    , m_looper()
    , mWindow()
    , m_events()
{
    UNUSED(savedState); // we don't save and load state for now
    UNUSED(savedStateSize); // --/--
    UNUSED(m_activity); // this variable also don't used now

    activity->callbacks->onDestroy = &AndroidApplication::onDestroy;
    activity->callbacks->onStart = &AndroidApplication::onStart;
    activity->callbacks->onResume = &AndroidApplication::onResume;
    activity->callbacks->onSaveInstanceState = &AndroidApplication::onSaveInstanceState;
    activity->callbacks->onPause = &AndroidApplication::onPause;
    activity->callbacks->onStop = &AndroidApplication::onStop;
    activity->callbacks->onConfigurationChanged = &AndroidApplication::onConfigurationChanged;
    activity->callbacks->onLowMemory = &AndroidApplication::onLowMemory;
    activity->callbacks->onWindowFocusChanged = &AndroidApplication::onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = &AndroidApplication::onNativeWindowCreated;
    activity->callbacks->onNativeWindowResized = &AndroidApplication::onNativeWindowResized;
    activity->callbacks->onNativeWindowRedrawNeeded = &AndroidApplication::onNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowDestroyed = &AndroidApplication::onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = &AndroidApplication::onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = &AndroidApplication::onInputQueueDestroyed;
    activity->callbacks->onContentRectChanged = &AndroidApplication::onContentRectChanged;

    CAUTION("Memory allocated before constructor so we can assign 'this' here, but if you"
            "want to move this code from constructor and assign to pointer of class that extends"
            "AndroidApplication, you must cast to AndroidApplication, because callbacks would"
            "downcast from 'void*' and you would get problems under virtual inheritance."
            "You would get wrong address, so do this please:"
            "activity->instance = static_cast<AndroidApplication*>(derivedPointer)");
    activity->instance = this;
}

AndroidApplication::~AndroidApplication()
{
    // this destructor intentionally left blank and moved to '.cpp' file
    Log::i(TAG, "Deleted! \n"); // delete this line when app is done
}

void AndroidApplication::onDestroy(ANativeActivity* activity)
{

    Log::i(TAG, "Destroy: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->waitForDestruction();

    delete application;
}

// callbacks

void AndroidApplication::onStart(ANativeActivity* activity)
{

    Log::i(TAG, "Start: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeActivityStateTo(StartActivityState);
}

void AndroidApplication::onResume(ANativeActivity* activity)
{

    Log::i(TAG, "Resume: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeActivityStateTo(ResumeActivityState);
}

void* AndroidApplication::onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{

    Log::i(TAG, "SaveInstanceState: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    UNUSED(application); // TODO: add game state saving to prevent visual glitches

    *outLen = 0;
    return nullptr;
}

void AndroidApplication::onPause(ANativeActivity* activity)
{

    Log::i(TAG, "Pause: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeActivityStateTo(PauseActivityState);
}

void AndroidApplication::onStop(ANativeActivity* activity)
{

    Log::i(TAG, "Stop: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeActivityStateTo(StopActivityState);
}

void AndroidApplication::onConfigurationChanged(ANativeActivity* activity)
{

    Log::i(TAG, "ConfigurationChanged: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->reloadConfiguration();
}

void AndroidApplication::onLowMemory(ANativeActivity* activity)
{

    Log::i(TAG, "LowMemory: %p\n", activity);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    UNUSED(application); // TODO: clean up any unused data in game or log low memory warning
}

void AndroidApplication::onWindowFocusChanged(ANativeActivity* activity, int hasFocus)
{

    Log::i(TAG, "WindowFocusChanged: %p -- %d\n", activity, hasFocus);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeFocus(hasFocus ? GainFocus : LostFocus);
}

void AndroidApplication::onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{

    Log::i(TAG, "NativeWindowCreated: %p -- %p\n", activity, window);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeNativeWindow(window);
}

void AndroidApplication::onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
    Log::i(TAG, "NativeWindowResized: %p -- %p\n", activity, window);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeNativeWindowSize();
}

void AndroidApplication::onNativeWindowRedrawNeeded(ANativeActivity* activity,
    ANativeWindow* window)
{

    Log::i(TAG, "NativeWindowRedrawNeeded: %p -- %p\n", activity, window);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    UNUSED(application); // To avoid transient artifacts during screen changes (such resizing after rotation),
        // applications should not return from this function until they have finished
        // drawing their window in its current state.
}

void AndroidApplication::onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{

    Log::i(TAG, "NativeWindowDestroyed: %p -- %p\n", activity, window);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeNativeWindow(nullptr);
}

void AndroidApplication::onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{

    Log::i(TAG, "InputQueueCreated: %p -- %p\n", activity, queue);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeInputQueue(queue);
}

void AndroidApplication::onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{

    Log::i(TAG, "InputQueueDestroyed: %p -- %p\n", activity, queue);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeInputQueue(nullptr);
}

void AndroidApplication::onContentRectChanged(ANativeActivity* activity, const ARect* rect)
{

    Log::i(TAG, "ContentRectChanged: %p -- %d %d %d %d\n", activity,
        rect->left, rect->top, rect->right, rect->bottom);

    AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
    application->changeNativeWindowSize();
}

void AndroidApplication::waitForStarted()
{

    std::unique_lock<std::mutex> lock(m_mutex);
    m_conditionVariable.wait(lock, std::bind(&AndroidApplication::isRunning, std::ref(*this)));
    m_mutex.unlock();
}

void AndroidApplication::waitForDestruction()
{

    std::unique_lock<std::mutex> lock(m_mutex);

    m_isDestroyRequested = true;

    m_conditionVariable.wait(lock, std::bind(&AndroidApplication::isDestroyed, std::ref(*this)));
    m_mutex.unlock();
}

void AndroidApplication::changeActivityStateTo(AndroidApplication::ActivityState activityState)
{

    using EventType = AndroidEvent::EventType;

    AndroidEvent event;
    switch (activityState) {
    case StartActivityState:
        event.setEventType(EventType::ActivityStartEventType);
        break;
    case ResumeActivityState:
        event.setEventType(EventType::ActivityResumeEventType);
        break;
    case PauseActivityState:
        event.setEventType(EventType::ActivityPauseEventType);
        break;
    case StopActivityState:
        event.setEventType(EventType::ActivityStopEventType);
        break;
    default:
        break;
    }

    auto isInState = [&activityState, this]() -> bool {
        return this->activityState() == activityState;
    };

    // wait for state to change
    std::unique_lock<std::mutex> lock(m_mutex);

    this->postEvent(event);

    m_conditionVariable.wait(lock, isInState);
    m_mutex.unlock();
}

void AndroidApplication::changeNativeWindow(ANativeWindow* window)
{

    if (window == nullptr) {

        AndroidEvent event { AndroidEvent::EventType::EventLoopEventType };
        event.setEventLoopEventData(false);

        auto isUserEventLoopFinished = [this]() -> bool {
            return !this->mWindow.isReady();
        };

        // wait for finish of user event loop
        std::unique_lock<std::mutex> lock(m_mutex);

        this->postEvent(event);

        m_conditionVariable.wait(lock, isUserEventLoopFinished);
        m_mutex.unlock();
    }

    AndroidEvent event(window ? AndroidEvent::EventType::NativeWindowCreatedEventType
                              : AndroidEvent::EventType::NativeWindowDestroyedEventType);

    event.setNativeWindowEventData(window);

    auto isWindowChanged = [&window, this]() -> bool {
        return this->mWindow.nativeWindow() == window;
    };

    // wait window to change
    std::unique_lock<std::mutex> lock(m_mutex);

    this->postEvent(event);

    m_conditionVariable.wait(lock, isWindowChanged);
    m_mutex.unlock();
}

void AndroidApplication::changeInputQueue(AInputQueue* queue)
{

    AndroidEvent event(queue ? AndroidEvent::EventType::InputQueueCreatedEventType
                             : AndroidEvent::EventType::InputQueueDestroyedEventType);

    event.setInputQueueEventData(queue);

    auto isQueueChanged = [&queue, this]() -> bool {
        return this->m_looper.inputQueue() == queue;
    };

    std::unique_lock<std::mutex> lock(m_mutex);

    this->postEvent(event);

    m_conditionVariable.wait(lock, isQueueChanged);
    m_mutex.unlock();
}

void AndroidApplication::changeNativeWindowSize()
{

    using EventType = AndroidEvent::EventType;

    AndroidEvent event(EventType::ResizedEventType);

    std::lock_guard<std::mutex> lock(m_mutex);

    event.setResizeEventData(window().requestWidth(), window().requestHeight());
    this->postEvent(event);

    m_conditionVariable.notify_all();
}

void AndroidApplication::changeFocus(AndroidApplication::Focus focus)
{

    using EventType = AndroidEvent::EventType;

    AndroidEvent event;
    switch (focus) {
    case GainFocus:
        event.setEventType(EventType::GainFocusEventType);
        break;
    case LostFocus:
        event.setEventType(EventType::LostFocusEventType);
        break;
    default:
        break;
    }

    std::lock_guard<std::mutex> lock(m_mutex);

    this->postEvent(event);

    m_conditionVariable.notify_all();
}

void AndroidApplication::reloadConfiguration()
{

    std::lock_guard<std::mutex> lock(m_mutex);

    m_configuration.reload();
    Log::i(TAG, m_configuration.toString());

    m_conditionVariable.notify_all();
}

//
// Game Thread Functions
//

bool AndroidApplication::isRunning() const
{

    return m_isRunning;
}

bool AndroidApplication::isDestroyed() const
{

    return m_isDestroyed;
}

bool AndroidApplication::isDestroyRequested() const
{

    return m_isDestroyRequested;
}

AndroidApplication::ActivityState AndroidApplication::activityState() const
{

    return m_activityState;
}

void AndroidApplication::exec()
{

    initialize();

    // application is initialized now
    {

        std::lock_guard<std::mutex> lock(m_mutex);
        m_isRunning = true;
        m_conditionVariable.notify_all();
    }

    // start 'system event loop'

    // if native window is not ready wait for appropriate event
    // then enter user 'main', if window is not ready again fall back to
    // system event loop and wait for appropriate event again

    while (!isDestroyRequested()) {

        AndroidEvent event;
        pollEvent(event); // we call 'pollEvent' to run 'processEvent' function

        if (mWindow.isReady()) {

            // start 'user event loop'
            main();
        }
    }

    // clean up after event loop
    terminate();
}

bool AndroidApplication::pollEvent(AndroidEvent& event)
{

    // looper event
    {

        AndroidEvent looperEvent;
        bool hasEventsInLooper = m_looper.pollEvent(looperEvent);

        if (hasEventsInLooper) {
            postEvent(looperEvent);
        }
    }

    if (!m_events.empty()) {

        event = m_events.front();
        m_events.pop();

        processEvent(event);

        return true;
    }

    return false;
}

void AndroidApplication::postEvent(const AndroidEvent& event)
{

    m_events.push(event);
}

const AndroidWindow& AndroidApplication::window() const
{

    return mWindow;
}

AndroidWindow& AndroidApplication::window()
{

    return mWindow;
}

void AndroidApplication::initialize()
{

    // load configuration
    m_configuration.reload();
    Log::i(TAG, m_configuration.toString());

    // prepare looper for this thread to read events
    m_looper.prepare();
}

void AndroidApplication::terminate()
{

    Log::i(TAG, "android_app_destroy!");

    std::lock_guard<std::mutex> lock(m_mutex);

    m_configuration.reset();

    m_isDestroyed = true;

    m_conditionVariable.notify_all();

    CAUTION("If you 'unlock' mutex, you can't touch 'this' object");
}

// from event handler thread

void AndroidApplication::processEvent(const AndroidEvent& event)
{

    CAUTION("Don't forget to lock mutex when you add new processing parts here"
            "If you touch class members of course");

    using EventType = AndroidEvent::EventType;

    switch (event.type()) {

    case EventType::ActivityStartEventType:
        setActivityState(StartActivityState);
        break;
    case EventType::ActivityResumeEventType:
        setActivityState(ResumeActivityState);
        break;
    case EventType::ActivityPauseEventType:
        setActivityState(PauseActivityState);
        break;
    case EventType::ActivityStopEventType:
        setActivityState(StopActivityState);
        break;

    case EventType::NativeWindowCreatedEventType:
        initializeNativeWindow(event);
        break;
    case EventType::NativeWindowDestroyedEventType:
        terminateNativeWindow(event);
        break;

    case EventType::InputQueueCreatedEventType:
        setInputQueue(event);
        break;
    case EventType::InputQueueDestroyedEventType:
        setInputQueue(event);
        break;

    case EventType::ResizedEventType:
        resizeNativeWindow(event);
        break;

    case EventType::EventLoopEventType:
        setEventLoopState(event);
        break;

    case EventType::EmptyEventType:
        break;

    default:
        break;
    }
}

void AndroidApplication::setActivityState(AndroidApplication::ActivityState activityState)
{

    Log::i(TAG, "Set activityState = %d\n", activityState);

    std::lock_guard<std::mutex> lock(m_mutex);

    m_activityState = activityState;

    m_conditionVariable.notify_all();
}

void AndroidApplication::initializeNativeWindow(const AndroidEvent& event)
{

    Log::i(TAG, "Initialize native window\n");

    std::lock_guard<std::mutex> lock(m_mutex);

    mWindow.setNativeWindow(event.nativeWindowEvent().pendingWindow);

    mWindow.initialize();

    m_conditionVariable.notify_all();
}

void AndroidApplication::terminateNativeWindow(const AndroidEvent& event)
{

    Log::i(TAG, "Terminate native window\n");

    std::lock_guard<std::mutex> lock(m_mutex);

    mWindow.terminate();

    mWindow.setNativeWindow(event.nativeWindowEvent().pendingWindow);

    m_conditionVariable.notify_all();
}

void AndroidApplication::resizeNativeWindow(const AndroidEvent& event)
{

    std::lock_guard<std::mutex> lock(m_mutex);

    mWindow.resize(event.resizeEvent().width, event.resizeEvent().height);

    m_conditionVariable.notify_all();
}

void AndroidApplication::setInputQueue(const AndroidEvent& event)
{

    std::lock_guard<std::mutex> lock(m_mutex);

    m_looper.setInputQueue(event.inputQueueEvent().pendingQueue);

    m_conditionVariable.notify_all();
}

void AndroidApplication::setEventLoopState(const AndroidEvent& event)
{

    std::lock_guard<std::mutex> lock(m_mutex);

    window().setReady(event.eventLoopEvent().windowReady);

    m_conditionVariable.notify_all();
}
