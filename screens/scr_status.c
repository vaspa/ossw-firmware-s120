#include <string.h>
#include <stdio.h>
#include "scr_status.h"
#include "../scr_mngr.h"
#include "../mlcd_draw.h"
#include "../mlcd.h"
#include "../i18n/i18n.h"
#include "../battery.h"
#include "../scr_controls.h"
#include "../ossw.h"

static NUMBER_CONTROL_DATA battery_level_ctrl_data;
static uint8_t mode = 0;

static const SCR_CONTROL_PROGRESS_BAR_CONFIG battery_level_config = {
	  35,
		50,
	  74,
	  32,
	  100,
		2<<16,
	  battery_get_level,
	  0,
    &battery_level_ctrl_data
};

static const SCR_CONTROL_DEFINITION controls[] = {
		{SCR_CONTROL_PROGRESS_BAR, (void*)&battery_level_config}
};

static const SCR_CONTROLS_DEFINITION controls_definition = {
	  sizeof(controls)/sizeof(SCR_CONTROL_DEFINITION),
	  (SCR_CONTROL_DEFINITION*)controls
};

static void scr_status_handle_button_pressed(uint32_t button_id) {
	  switch (button_id) {
			  case SCR_EVENT_PARAM_BUTTON_BACK:
					  scr_mngr_show_screen(SCR_WATCHFACE);
				    break;
		}
}

static void scr_status_draw_battery_status() {
	
		mlcd_clear_rect(0, 25, MLCD_XRES, 20);
		if (mode == 1) {
				mlcd_draw_text("charging", 0, 25, MLCD_XRES, 20, FONT_OPTION_NORMAL, HORIZONTAL_ALIGN_CENTER);
		} else if (mode == 2) {
				mlcd_draw_text("full", 0, 25, MLCD_XRES, 20, FONT_OPTION_NORMAL, HORIZONTAL_ALIGN_CENTER);
		} else {
				mlcd_draw_text("battery", 0, 25, MLCD_XRES, 20, FONT_OPTION_NORMAL, HORIZONTAL_ALIGN_CENTER);
		}
}

static void scr_status_refresh_screen() {
	  scr_controls_redraw(&controls_definition);
	
		uint8_t curr_mode = battery_is_charging()? (battery_is_full() ? 2 : 1) : 0;
		if (curr_mode != mode) {
				mode = curr_mode;
				scr_status_draw_battery_status();
		}
}

static void scr_status_draw_screen() {
	
		mlcd_draw_rect(109, 60, 6, 12);
		mode = battery_is_charging()? (battery_is_full() ? 2 : 1) : 0;
		scr_status_draw_battery_status();
	
  	mlcd_draw_text(ossw_mac_address(), 0, 135, MLCD_XRES, NULL, FONT_NORMAL_BOLD, HORIZONTAL_ALIGN_CENTER);
	
	  scr_controls_draw(&controls_definition);
}

void scr_status_handle_event(uint32_t event_type, uint32_t event_param) {
	  switch(event_type) {
        case SCR_EVENT_DRAW_SCREEN:
            scr_status_draw_screen();
            break;
        case SCR_EVENT_REFRESH_SCREEN:
            scr_status_refresh_screen();
            break;
			  case SCR_EVENT_BUTTON_PRESSED:
				    scr_status_handle_button_pressed(event_param);
				    break;
		}
}
