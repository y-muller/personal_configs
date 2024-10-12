// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include "y-muller.h"

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);
void send_device_suspend_state(bool status);

