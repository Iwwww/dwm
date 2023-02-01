/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define BROWSER "qutebrowser"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
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
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_r,      reorganizetags, {0} },
	{ MODKEY,                       XK_x,      transfer,       {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY|ShiftMask,             XK_q,      try_quit,       {0} },
	// { MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },

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
	{ MODKEY,		XK_w,		spawn,		SHCMD(BROWSER) },
	{ MODKEY|ShiftMask,	XK_w,		spawn,		SHCMD("networkmanager_dmenu") },
	{ MODKEY|ShiftMask,	XK_b,		spawn,		SHCMD("dmenu-bluetooth -l 30") },
	{ MODKEY|ControlMask,	XK_w,		spawn,		SHCMD("firefox") },
	{ MODKEY|ControlMask,	XK_o,           spawn,		SHCMD("dm-browser") },
	{ MODKEY|ControlMask,	XK_e,           spawn,		SHCMD("dm-unicode") },
	{ MODKEY|ShiftMask,	XK_l,		spawn,		SHCMD("dm-power") },
	{ MODKEY,		XK_c,		spawn,		SHCMD("dmenu-translate") },
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

	{ 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -37 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("if [ $(pamixer --get-mute) == 'true' ]; then pamixer --unmute; fi; if [ $(pamixer --get-volume) -le 159 ]; then pamixer --allow-boost -i 5; kill -37 $(pidof dwmblocks); fi") },
	{ 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("pamixer --allow-boost -d 5; kill -37 $(pidof dwmblocks)") },
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
	{ 0, XF86XK_MonBrightnessDown,		spawn,		SHCMD("brightnessctl  set 10%-") },
        { 0, XF86XK_TouchpadToggle,		spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,		spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,			spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_ScreenSaver,		spawn,		SHCMD("i3lock -c 000000 & sleep 1 && xset dpms force off; mpc pause; pauseallmpv") },

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
static const int EMPTY_WINDOW_COUNT = 2;
