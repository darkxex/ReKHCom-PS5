/*
 * ReKHCoM for PS5 - updates from the project's GitHub releases.
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef REKHCOM_UPDATE_H
#define REKHCOM_UPDATE_H

enum UpdateState
{
    UPDATE_IDLE,
    UPDATE_CHECKING,
    UPDATE_NONE,      /* this is the newest version */
    UPDATE_AVAILABLE, /* update_version() is newer */
    UPDATE_INSTALLING,
    UPDATE_INSTALLED, /* restart the app to use it */
    UPDATE_FAILED,    /* update_message() says why */
};

/* PS5 releases are tagged ps5-vX.Y.Z and carry PPSA98511.zip (the app folder PPSA98511/ inside). */
#define UPDATE_REPO "darkxex/ReKHCom-PS5"
#define UPDATE_TAG_PREFIX "ps5-v"

/* log: where the messages go (printf-like), may be NULL. */
void update_init(void (*log)(const char *fmt, ...));
void update_check(void);   /* in the background */
void update_install(void); /* in the background; needs UPDATE_AVAILABLE */
int update_state(void);
const char *update_version(void);
const char *update_message(void);

#endif
