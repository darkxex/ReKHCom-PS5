/*
 * ReKHCoM - PS5 platform types
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Shared types for the frontend. Everything here is plain C11 so the same
 * sources build for the PS5 (no full libc++) and for the desktop test build.
 */
#ifndef ReKHCoM_H
#define ReKHCoM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SS_OPT_COUNT 1 /* core options: none in this build */

#define ReKHCoM_NAME "ReKHCoM"           /* identifiers: the User-Agent of network requests, the Vulkan application name */
#define ReKHCoM_TITLE "ReKHCoM" /* what is shown on screen */
#define ReKHCoM_TITLE_ID "PPSA98511"
#define ReKHCoM_VERSION "1.0.6" /* project release version; contentVersion follows it */
#define ReKHCoM_PATH_MAX 512

/* Pad bits use RetroPad numbering so the host can hand the mask to the core
 * unchanged. PlayStation names: Cross = B, Circle = A, Square = Y, Triangle = X. */
enum
{
    BTN_CROSS = 0,
    BTN_SQUARE = 1,
    BTN_SELECT = 2,
    BTN_START = 3,
    BTN_UP = 4,
    BTN_DOWN = 5,
    BTN_LEFT = 6,
    BTN_RIGHT = 7,
    BTN_CIRCLE = 8,
    BTN_TRIANGLE = 9,
    BTN_L1 = 10,
    BTN_R1 = 11,
    BTN_L2 = 12,
    BTN_R2 = 13,
    BTN_L3 = 14,
    BTN_R3 = 15,
    BTN_MENU = 16, /* touchpad click: opens the ReKHCoM in-game menu */
};
#define BIT(b) (1u << (b))
#define ReKHCoM_MAX_PADS 4 /* 3 and 4 play through a multitap */

typedef struct
{
    bool connected;
    uint32_t buttons;
    int16_t lx, ly, rx, ry;
    uint8_t l2, r2;    /* how far the triggers are pressed, 0..255 */
    bool motion;       /* quat holds the controller's orientation */
    float quat[4];     /* x, y, z, w */
    /* the light gun (filled in by ReKHCoM): -32767..32767 across the picture */
    int16_t gun_x, gun_y;
    bool gun_offscreen;
    /* the touchpad (one finger) and, for mouse games, the pointer's move this frame */
    bool touching;
    uint16_t touch_x, touch_y; /* 0..1919, 0..1079 */
    int16_t mouse_dx, mouse_dy;
} PadState;

enum UpscaleFilter
{
    UPSCALE_SHARP = 0, /* nearest-neighbour prescale: crisp pixels */
    UPSCALE_SMOOTH_PIXELS, /* Scale2x/Scale3x edge smoothing */
    UPSCALE_XBR,           /* xBR: edge-directed, smoothest (2x passes) */
    UPSCALE_FILTER_COUNT
};

enum RegionMode
{
    REGION_AUTO = 0,
    REGION_NTSC_J, /* the core's order: Auto, NTSC-J, NTSC-U, PAL */
    REGION_NTSC,
    REGION_PAL,
    REGION_COUNT
};

typedef struct
{
    bool integer_scale; /* whole-number scale factors only */
    bool smooth;      /* bilinear for the final scale to the screen */
    int renderer;     /* 0 Vulkan (the GPU), 1 Software (the CPU) */
    int internal_res; /* the core's scale, 1..16 (1 native) */
    int upscale;      /* 1..4: prescale before the final scale */
    int upscale_filter; /* enum UpscaleFilter */
    bool show_fps;
    int region;       /* enum RegionMode */
    bool dithering;
    int cd_speed;     /* CD read speed-up, 1..10 (1 off): shorter loads, rare glitches */
    bool analog;      /* DualShock instead of digital pad */
    int state_slot;   /* 0..9 */
    int last_game;    /* library cursor */
    int cover_style;  /* enum CoverStyle */
    bool cover_download; /* fetch missing covers over the network */
    int ui_sound;     /* SFX_STYLE_* in ui/sfx.h; SFX_STYLE_OFF mutes */
    int ui_volume;    /* 0..3 = 25/50/75/100 % */
    int stick_dpad;   /* enum StickDpad */
    int language;     /* enum Lang in i18n.h */
    int vibration;        /* controller vibration: 0 off, 1..4 = 25/50/75/100 % */
    /* Button mapping: for each controller button (BTN_CROSS..BTN_R3), the PS1
     * button it presses (BTN_*), or -1 for nothing. */
    int8_t button_map[16];
    int sort_mode;        /* shelf order, enum SortMode in ui/coverflow.h */
    int shelf_category;   /* shelf filter, enum ShelfCategory in ui/coverflow.h */
    int background;       /* 0 dark, 1 the selected cover's colour */
    bool widescreen;      /* turn on the game's widescreen code, show 16:9 */
    bool multitap;        /* 4 players through a multitap in port 1 */
    bool rewind;          /* keep the last seconds for rewinding */
    bool quick_resume;    /* save on quitting, offer Continue on the shelf */
    int crt;              /* scanlines: 0 off, 1 light, 2 strong */
    int border;           /* around the picture: 0 black, 1 glow, 2 TV frame */
    bool remote;          /* settings page for phones on the local network */
    bool update_check;    /* look for new ReKHCoM releases at start */
    bool pgxp;            /* precise geometry, no wobbling polygons */
    int shader;           /* 0 off, 1 LCD3x, 2 CRT Royale, 3 CRT, 4 sharp bilinear */
    bool hd_textures;     /* use a texture pack beside the game when there is one */
    int theme;            /* enum ThemeId in ui/theme.h */
    int crop_edges;       /* 0 off, 1: 8 lines top and bottom, 2: 16 (the black a CRT hid) */
    bool manual_crop;     /* the core's crop mode is ignored (drawn as None) and the picture's area is set by hand (mc_*) */
    int mc_w, mc_h;       /* manual crop: the picture's width and height as a percentage of its normal size (25..150) */
    int mc_x, mc_y;       /* manual crop: how far the picture is moved, in thousandths of the screen (-500..500) */
    bool ra_popups;       /* achievement unlock banners while playing */
    bool ra_tracker;      /* the progress card when a counted achievement moves */
    int ra_popup_style;   /* 0 banner, 1 compact, 2 big trophy */
    int bios_start;       /* Start BIOS boots this region's BIOS: 0 NTSC-U (default), 1 NTSC-J, 2 PAL; not saved */
    int lightbar;         /* 0 left to the system, 1 player colours, 2 the game's cover colour, 3 red in analog mode / off in digital */
    int stick_deadzone;   /* 0 off, 1..4: 5, 10, 15, 20 % of the stick's travel ignored */
    int stick_response;   /* 0 normal, 1 precise (slow near the centre), 2 quick */
    int trigger_effects;  /* DualSense triggers: 0 off, 1 automatic (pedal / gun click), then one feel for every game: click, light click, firm, buzz */
    bool racing_triggers; /* R2 and Cross swap places, and L2 and Square (off by default) */
    int rumble_feel;      /* 0 classic, 1 soft, 2 punchy, 3 punchy and in the triggers */
    int lightgun;         /* 0 automatic (known gun games), 1 off, 2 on */
    int overclock;        /* 0 off, 1 a little, 2 a lot */
    int brightness;       /* 0 darker, 1 normal, 2 brighter, 3 brightest */
    int colour;           /* 0 natural, 1 vivid, 2 soft, 3 warm, 4 cool, 5 black and white */
    int autosave;         /* 0 off, else every 5, 10 or 15 minutes into the auto slots */
    bool bezel;           /* the game's artwork around a 4:3 picture, when downloaded */
    int msaa;             /* anti-aliasing 0 off, 1..4 = 2x, 4x, 8x, 16x */
    int texture_filter;   /* 0 off, 1 bilinear, 2 xBR, 3 SABR, 4 JINC2, 5 3-point */
    bool filter_2d;       /* filter 2D sprites and menus too (off keeps them sharp) */
    bool supersampling;   /* render at the internal resolution, then scale down */
    int deinterlace;      /* 0 weave, 1 bob, 2 motion-adaptive */
    bool pal60;           /* European games at 60 Hz */
    bool game_fixes;      /* turn off what the game database says a game breaks with */
    bool fmv_smooth;      /* smooth the colour blocks of FMVs (MDEC chroma filter) */
    bool true_colour;     /* 32-bit colour, no dithering */
    bool boot_intro;      /* the PS1's startup logo and sound before the game (a real BIOS) */
    int sharpen;          /* 0 off, 1 light, 2 strong (AMD FidelityFX CAS) */
    bool disc_animation;  /* the disc slides out of its case when a game starts */
    bool disc_install_only; /* a disc put in is installed but its game is not started (the disc daemon does not open the app) */
    bool case_lighting;   /* the cover in the jewel case gets light: its shading and the glare over the lid; off: the picture as it is */
    bool jewel_cases;     /* the shelf shows 3D jewel cases; off: the flat covers with a reflection, as in 1.1.8 */
    bool negcon;          /* racing games that take a NeGcon: analog gas and brake on R2 / L2 */
    bool touch_mouse;     /* mouse games: the touchpad moves the pointer */
    int run_ahead;        /* 0 off, 1 to 10 frames less input lag */
    bool fast_effects;    /* screen effects on the GPU, without the software copy */
    bool fsr;             /* FSR 1 scales the picture before the shader */
    char usb_folder[48];  /* a folder name looked for on USB drives: /mnt/usb0/<name> and /mnt/usb1/<name> (empty: none) */
    char nfs_shares[512]; /* nfs:// addresses of the servers that hold games, ';' between them (empty: none); src/nfs/nfs.h */
    bool frame_pacing;    /* Video sync: one game frame per screen refresh, the sound stretched by a hair to keep up; off: synchronised to the sound */
    int video_out;        /* picture output to the TV: 0 60 Hz, 1 120 Hz (from the next start) */
    int framegen;         /* generated frames: 0 off, 1 one between two of the game's (x2), 2 three (x4, a 30 fps game on a 120 Hz screen) */
    int aspect_before_wide; /* the aspect ratio (index) the widescreen hack replaced with 16:9, or -1; saved by value */
    int ss_opt[SS_OPT_COUNT]; /* unused here */
} Settings;

enum StickDpad
{
    STICK_DPAD_AUTO = 0, /* left stick drives the D-pad while the game uses digital mode */
    STICK_DPAD_ALWAYS,
    STICK_DPAD_OFF,
    STICK_DPAD_COUNT
};

enum CoverStyle
{
    COVER_FLAT = 0, /* front art, shown in perspective by ReKHCoM */
    /* COVER_BOX3D,    pre-rendered 3D jewel case (no longer used) */
    COVER_STYLE_COUNT
};

/* Data layout below the ReKHCoM root (default /data/ReKHCom on PS5). */
typedef struct
{
    char root[ReKHCoM_PATH_MAX];
    char games[ReKHCoM_PATH_MAX];
    char bios[ReKHCoM_PATH_MAX];
    char saves[ReKHCoM_PATH_MAX];
    char states[ReKHCoM_PATH_MAX];
    char cheats[ReKHCoM_PATH_MAX];
    char covers[ReKHCoM_PATH_MAX]; /* covers/default/<serial>.jpg, covers/3d/<serial>.png */
    char logs[ReKHCoM_PATH_MAX];
    char cache[ReKHCoM_PATH_MAX];  /* downloads and the emulator's shader cache */
    char config[ReKHCoM_PATH_MAX];
    char user[ReKHCoM_PATH_MAX];   /* the profile's folder (saves, states, settings, stats): root for the main one */
} Paths;

void ReKHCoM_log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void ReKHCoM_log_open(const char *path);

/* Small string helpers shared by the frontend. */
void str_copy(char *dst, size_t size, const char *src);
void path_join(char *dst, size_t size, const char *a, const char *b);
bool path_exists(const char *path);
bool path_is_dir(const char *path);
bool make_dirs(const char *path);
bool file_copy(const char *from, const char *to); /* replaces `to` */
const char *path_ext(const char *path);  /* lower-case-insensitive extension without dot, "" if none */
int str_icmp(const char *a, const char *b);
/* localtime into *out (the PS5 libc has no localtime_r); false on failure */
struct tm;
bool local_time(long long when, struct tm *out);

#endif
