/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 7;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;        /* vert inner gap between windows */
static const unsigned int gappoh    = 7;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 7;        /* vert outer gap between windows and screen edge */
static const int smartgaps_fact     = 1;        /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "JetBrainsMono NFP,JetBrainsMono NFP SemiBold:style=SemiBold,Regular" };
static const char dmenufont[]       = "JetBrainsMono NFP,JetBrainsMono NFP SemiBold:style=SemiBold,Regular";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#ed8836";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	// { "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Telegram",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Spotify",  NULL,       NULL,       1 << 7,       0,           -1 },
	{ "ripdrag",  NULL,       NULL,       1 << 9,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */

#include "vanitygaps.c"
// #include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "[]U",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_r,      reorganizetags, {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_z,      incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },
	{ MODKEY,                       XK_a,      togglegaps,     {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },  // tile
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} },  // bstack
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[1]} },  // monocle
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },  // spiral
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },  // dwindle
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },  // dwindle
	{ MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY|ShiftMask,             XK_q,      try_quit,       {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,           XK_l,      viewnext,       {0} },
	{ MODKEY|ControlMask,           XK_h,      viewprev,       {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_l,      tagtonext,      {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_h,      tagtoprev,      {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,		XK_minus,	spawn,		SHCMD("pamixer --allow-boost -d 5; kill -37 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_minus,	spawn,		SHCMD("pamixer --allow-boost -d 15; kill -37 $(pidof dwmblocks)") },
	{ MODKEY,		XK_equal,	spawn,		SHCMD("if [ $(pamixer --get-mute) == 'true' ]; then pamixer --unmute; fi; if [ $(pamixer --get-volume) -le 159 ]; then pamixer --allow-boost -i 5; kill -37 $(pidof dwmblocks); fi") },
	{ MODKEY|ShiftMask,	XK_equal,	spawn,		SHCMD("if [ $(pamixer --get-mute) == 'true' ]; then pamixer --unmute; fi; if [ $(pamixer --get-volume) -le 159 ]; then pamixer --allow-boost -i 15; kill -37 $(pidof dwmblocks); fi") },
	// { MODKEY,		XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -37 $(pidof dwmblocks)") },
	// { MODKEY|ShiftMask,	XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -37 $(pidof dwmblocks)") },
	// { MODKEY,		XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -37 $(pidof dwmblocks)") },
	// { MODKEY|ShiftMask,	XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -37 $(pidof dwmblocks)") },
	{ MODKEY,		XK_w,		spawn,		SHCMD(BROWSER) },
	{ MODKEY|ShiftMask,	XK_w,		spawn,		SHCMD("networkmanager_dmenu -l 30 -i") },
	{ MODKEY|ShiftMask,	XK_b,		spawn,		SHCMD("dmenu-bluetooth -l 30") },
	{ MODKEY|ControlMask,	XK_w,		spawn,		SHCMD("firefox") },
	{ MODKEY|ControlMask,	XK_o,           spawn,		SHCMD("dm-browser") },
	{ MODKEY|ControlMask,	XK_e,           spawn,		SHCMD("dm-unicode") },
	{ MODKEY|ShiftMask,	XK_l,		spawn,		SHCMD("dm-power") },
	{ MODKEY,		XK_c,		spawn,		SHCMD("dmenu-translate-run.sh") },
	{ MODKEY,		XK_r,		spawn,		SHCMD("rofi-run") },
	{ MODKEY|ShiftMask,	XK_s,           spawn,		SHCMD("screenshot-part") },
	{ MODKEY|ControlMask,	XK_t,		spawn,		SHCMD("telegram-desktop") },
	{ MODKEY,		XK_m,		spawn,		SHCMD("mount_device") },
	{ 0,			XK_Print,	spawn,		SHCMD("screenshot") },
	{ Mod1Mask,		XK_Shift_L,	spawn,		SHCMD("kill -40 ($pidof dwmblocks)") },
	{ Mod1Mask,		XK_Shift_R,	spawn,		SHCMD("kill -40 ($pidof dwmblocks)") },
	{ MODKEY,		XK_p,		spawn,		SHCMD("mpc toggle") },
	{ MODKEY|ShiftMask,	XK_p,		spawn,		SHCMD("mpc pause ; pauseallmpv") },
	{ MODKEY,		XK_bracketleft,	spawn,		SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,	XK_bracketleft,	spawn,		SHCMD("mpc seek -60") },
	{ MODKEY,		XK_bracketright,spawn,		SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,	XK_bracketright,spawn,		SHCMD("mpc seek +60") },
	{ MODKEY,		XK_comma,	spawn,		SHCMD("mpc prev") },
	{ MODKEY|ShiftMask,	XK_comma,	spawn,		SHCMD("mpc seek 0%") },
	{ MODKEY,		XK_period,	spawn,		SHCMD("mpc next") },
	{ MODKEY|ShiftMask,	XK_period,	spawn,		SHCMD("mpc repeat") },
	{ MODKEY, 		XK_slash,	spawn,		SHCMD(TERMINAL " -e ncmpcpp") },

	// { 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -37 $(pidof dwmblocks)") },
	// { 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("if [ $(pamixer --get-mute) == 'true' ]; then pamixer --unmute; fi; if [ $(pamixer --get-volume) -le 159 ]; then pamixer --allow-boost -i 5; kill -37 $(pidof dwmblocks); fi") },
	// { 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("pamixer --allow-boost -d 5; kill -37 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer --toggle-mute") },
	{ 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("pamixer --allow-boost -i 5") },
	{ 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("pamixer --allow-boost -d 5") },
	// { 0, XF86XK_AudioMute,			spawn,		SHCMD("wpctl set-mute  @DEFAULT_AUDIO_SINK@ toggle") },
	// { 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -37 $(pidof dwmblocks)") },
	// { 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -37 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,			spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,			spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,			spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,			spawn,		SHCMD("mpc toggle") },
	{ 0, XF86XK_AudioStop,			spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,		spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,		spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,			spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,		spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_Calculator,			spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,			spawn,		SHCMD("dm-power") },
	{ 0, XF86XK_MonBrightnessUp,		spawn,		SHCMD("brightnessctl  set +10%") },
	{ 0, XF86XK_MonBrightnessUp|ControlMask,		spawn,		SHCMD("brightnessctl  set 100%") },
	{ 0, XF86XK_MonBrightnessDown,		spawn,		SHCMD("brightnessctl  set 10%-") },
	{ 0, XF86XK_MonBrightnessDown|ControlMask,		spawn,		SHCMD("brightnessctl  set 0%") },
        { 0, XF86XK_TouchpadToggle,		spawn,		SHCMD("touchpad_toggle") },
	{ MODKEY|Mod1Mask,		XK_t, 	spawn,		SHCMD("touchpad_toggle") },
	{ 0, XF86XK_TouchpadOff,		spawn,		SHCMD("touchpad_off") },
	{ 0, XF86XK_TouchpadOn,			spawn,		SHCMD("touchpad_on") },
	{ 0, XF86XK_ScreenSaver,		spawn,		SHCMD("dm-power screen_off") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* how many windows should be open when quitting? */
/* on a stock dwm install, this seems to be two; however, you'll have to
 * change it depending on how many invisible X windows exist */
/* you can get a list with `xwininfo -tree -root`. */
static const int EMPTY_WINDOW_COUNT = 5;
