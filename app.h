/*
 *  Application handing
 *  Copyright (C) 2007 Andreas �man
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef APP_H
#define APP_H

#include "hid/input.h"
#include "media.h"

/**
 * Application 
 */
typedef struct app {
  LIST_ENTRY(app) app_link;

  const char *app_name;
  const char *app_model;

  glw_t *app_icon_widget;

  void (*app_spawn)(struct appi *ai);

} app_t;

#define appi_menu_top(ai) ((ai)->ai_menu)


/**
 * Application instance
 */
typedef struct appi {
  glw_t *ai_widget;

  app_t *ai_app;

  glw_focus_stack_t ai_gfs;

  ic_t ai_ic;
  media_pipe_t ai_mp;
  
  AVFormatContext *ai_fctx;

  int ai_instance_index;
  struct config_head *ai_settings;

  enum {
    AI_FS_NONE,
    AI_FS_WITH_BG,
    AI_FS_BLANK,
  } ai_req_fullscreen;

  glw_t *ai_menu;               /* Top level menu */

  const char *ai_name;

  int ai_display_menu;

} appi_t;


#define appi_focused(ai) ((ai)->ai_gfs.gfs_active)

void apps_load(void);

void app_spawn(app_t *app, struct config_head *settings, int index);

void appi_destroy(appi_t *ai);

FILE *appi_setings_create(appi_t *ai);

appi_t *appi_create(const char *name);

#endif /* APP_H */
