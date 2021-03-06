// Copyright 2014 Toggl Desktop developers.

#ifndef SRC_UI_LINUX_TOGGLDESKTOP_TOGGL_H_
#define SRC_UI_LINUX_TOGGLDESKTOP_TOGGL_H_

#include <QObject>
#include <QUrl>
#include <QVector>

#include <stdint.h>

#include "./toggl_api.h"

class AutocompleteView;
class GenericView;
class SettingsView;
class TimeEntryView;

class TogglApi : public QObject {
    Q_OBJECT

 public:
    TogglApi(
        QObject *parent = 0,
        QString logPathOverride = "",
        QString dbPathOverride = "");
    ~TogglApi();

    static TogglApi *instance;

    static QString Project;
    static QString Duration;
    static QString Description;

    static bool notifyBugsnag(
        const QString errorClass,
        const QString message,
        const QString context);

    bool shutdown;

    bool startEvents();

    void clear();

    void setEnvironment(const QString environment);

    void login(const QString email, const QString password);

    void signup(const QString email, const QString password);

    void googleLogin(const QString accessToken);

    QString start(
        const QString description,
        const QString duration,
        const uint64_t task_id,
        const uint64_t project_id);

    bool stop();

    bool deleteTimeEntry(const QString guid);

    bool continueTimeEntry(const QString guid);

    bool continueLatestTimeEntry();

    void openInBrowser();

    void sync();

    bool clearCache();

    void getSupport();

    void logout();

    void editPreferences();

    void editTimeEntry(const QString guid,
                       const QString focusedFieldName);

    void editRunningTimeEntry(
        const QString focusedFieldName);

    void viewTimeEntryList();

    void setIdleSeconds(u_int64_t idleSeconds);

    bool setTimeEntryProject(
        const QString guid,
        const uint64_t task_id,
        const uint64_t project_id,
        const QString project_guid);

    bool setTimeEntryDescription(
        const QString guid,
        const QString value);

    bool setTimeEntryTags(
        const QString guid,
        const QString tags);

    bool setTimeEntryDuration(
        const QString guid,
        const QString value);

    bool setTimeEntryBillable(
        const QString guid,
        const bool billable);

    bool setTimeEntryDate(
        const QString guid,
        const int64_t unix_timestamp);

    bool setTimeEntryStart(
        const QString guid,
        const QString value);

    bool setTimeEntryStop(
        const QString guid,
        const QString value);

    bool addProject(
        const QString time_entry_guid,
        const uint64_t workspace_id,
        const uint64_t client_id,
        const QString project_name,
        const bool is_private);

    bool createClient(
        const uint64_t wid,
        const QString name);

    bool setProxySettings(
        const bool useProxy,
        const QString proxyHost,
        const uint64_t proxyPort,
        const QString proxyUsername,
        const QString proxyPassword);

    bool setSettingsUseIdleDetection(const bool useIdleDetection);
    bool setSettingsReminder(const bool reminder);
    bool setSettingsIdleMinutes(const uint64_t idle_minutes);
    bool setSettingsReminderMinutes(const uint64_t reminder_minutes);

    void toggleTimelineRecording(
        const bool recordTimeline);

    bool setUpdateChannel(const QString channel);
    QString updateChannel();

    bool sendFeedback(const QString topic,
                      const QString details,
                      const QString filename);

    bool discardTimeAt(const QString guid,
                       const uint64_t at,
                       const bool split_into_new_time_entry);

    bool runScriptFile(const QString filename);

    static const QString formatDurationInSecondsHHMMSS(
        const int64_t duration);

 signals:
    void displayApp(
        const bool open);

    void displayError(
        const QString errmsg,
        const bool user_error);

    void displayUpdate(
        const QString url);

    void displayOnlineState(
        int64_t state);

    void displayLogin(
        const bool open,
        const uint64_t user_id);

    void displayReminder(
        const QString title,
        const QString informative_text);

    void displayTimeEntryList(
        const bool open,
        QVector<TimeEntryView *> list);

    void displayTimeEntryEditor(
        const bool open,
        TimeEntryView *view,
        const QString focused_field_name);

    void displaySettings(
        const bool open,
        SettingsView *view);

    void displayStoppedTimerState();

    void displayRunningTimerState(
        TimeEntryView *view);

    void displayIdleNotification(
        const QString guid,
        const QString since,
        const QString duration,
        const uint64_t started,
        const QString description);

    void displayClientSelect(
        QVector<GenericView *> list);

    void displayTags(
        QVector<GenericView *> list);

    void displayTimeEntryAutocomplete(
        QVector<AutocompleteView *> list);

    void displayMinitimerAutocomplete(
        QVector<AutocompleteView *> list);

    void displayProjectAutocomplete(
        QVector<AutocompleteView *> list);

    void displayWorkspaceSelect(
        QVector<GenericView *> list);

 private:
    void *ctx;

    bool setTime(
        const QString guid,
        const QDate date,
        const QString time,
        const bool start);
};

// callbacks used internally by the app instance
void on_display_app(const _Bool open);
void on_display_error(
    const char *errmsg,
    const _Bool user_error);
void on_display_update(
    const char *url);
void on_display_online_state(
    const bool is_online,
    const char *reason);
void on_display_url(
    const char *url);
void on_display_login(
    const _Bool open,
    const uint64_t user_id);
void on_display_reminder(
    const char *title,
    const char *informative_text);
void on_display_time_entry_list(
    const _Bool open,
    TogglTimeEntryView *first);
void on_display_time_entry_autocomplete(
    TogglAutocompleteView *first);
void on_display_mini_timer_autocomplete(
    TogglAutocompleteView *first);
void on_display_project_autocomplete(
    TogglAutocompleteView *first);
void on_display_workspace_select(
    TogglGenericView *first);
void on_display_client_select(
    TogglGenericView *first);
void on_display_tags(
    TogglGenericView *first);
void on_display_time_entry_editor(
    const _Bool open,
    TogglTimeEntryView *te,
    const char *focused_field_name);
void on_display_settings(
    const _Bool open,
    TogglSettingsView *settings);
void on_display_timer_state(
    TogglTimeEntryView *te);
void on_display_idle_notification(
    const char *guid,
    const char *since,
    const char *duration,
    const uint64_t started);



#endif  // SRC_UI_LINUX_TOGGLDESKTOP_TOGGL_H_
