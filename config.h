/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "st"
#define BROWSER "qutebrowser"

/* appearance */
static const unsigned int borderpx       = 3;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 7;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 7;  /* vert inner gap between windows */
static const unsigned int gappoh         = 7;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 7;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int focusonwheel            = 0;
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';

#define NAMETAG_FORMAT "%s"
/* The maximum amount of bytes reserved for each tag text. */
#define MAX_TAGLEN 16
/* The command to run (via popen). This can be tailored by adding a prompt, passing other command
 * line arguments or providing name options. Optionally you can use other dmenu like alternatives
 * like rofi -dmenu. */
#define NAMETAG_COMMAND "dmenu < /dev/null"

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_NONE; // INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const int quit_empty_window_count = 0;   /* only allow dwm to quit if no (<= count) windows are open */
static const char *fonts[]               = { "DejaVu Sans Mono:size=13:antialias=true:autohint=true"  };
static const char dmenufont[]            = "monospace:size=13";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfloatcolor[]             = "#db8fd9";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#ed8836";
static char selfloatcolor[]              = "#ed8836";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";



static const unsigned int baralpha = 140;
static const unsigned int borderalpha = 140;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
	[SchemeNorm]         = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]          = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleNorm]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleSel]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidSel]       = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]          = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};





/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "???" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char tagicons[][NUMTAGS][MAX_TAGLEN] =
{
	[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
    RULE(.class = "Gimp", .tags = 1 << 4)
	// RULE(.class = "Firefox", .tags = 1 << 7)
	RULE(.class = "St", .isfloating = 0)
	RULE(.class = "st-256color", .isfloating = 0)
	RULE(.class = "mpv", .isfloating = 0)
};



/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_statuscmd,         NULL,                    "status2d" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_fancybar,           draw_fancybar,          click_fancybar,          NULL,                    "fancybar" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int nstack      = 0;    /* number of clients in primary stack area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func } */
	{ "[ ]=",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL } }, // default tile layout
	{ "TTT",      flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // bstack
	{ "(@)",      flextile,         { -1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL } }, // fibonacci spiral
	{ "[\\]",     flextile,         { -1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL } }, // fibonacci dwindle
	{ "[D]",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL } }, // deck
	{ "|M|",      flextile,         { -1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, TOP_TO_BOTTOM, NULL } }, // centeredmaster
	{ "[M]",      flextile,         { -1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL } }, // monocle
	{ ">M>",      flextile,         { -1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // floating master
 	{ "><>",      NULL,             {0} },    /* no layout function means floating behavior */
	{ "|||",      flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // columns (col) layout
	{ "===",      flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // bstackhoriz
	{ "-M-",      flextile,         { -1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT, LEFT_TO_RIGHT, NULL } }, // centeredmaster horiz
	{ ":::",      flextile,         { -1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL } }, // gappless grid
	{ "[T]",      flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL } }, // tatami mats
                                                                                                  //
	{ "[]=",      tile,             {0} },
	{ "[M]",      monocle,          {0} },
	{ "TTT",      bstack,           {0} },
	{ "===",      bstackhoriz,      {0} },
	{ ">M>",      centeredfloatingmaster, {0} },
	{ "[D]",      deck,             {0} },
	{ "(@)",      spiral,           {0} },
	{ "[\\]",     dwindle,          {0} },
	{ ":::",      gaplessgrid,      {0} },
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

/* commands */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
    NULL
};
static const char *termcmd[]  = { "st", NULL};

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"


#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_d,          spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY|ControlMask,           XK_space,      focusmaster,            {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_Left,       focusdir,               {.i = 0 } }, // left
	{ MODKEY,                       XK_Right,      focusdir,               {.i = 1 } }, // right
	{ MODKEY,                       XK_Up,         focusdir,               {.i = 2 } }, // up
	{ MODKEY,                       XK_Down,       focusdir,               {.i = 3 } }, // down
	{ MODKEY|ControlMask,           XK_j,          pushdown,               {0} },
	{ MODKEY|ControlMask,           XK_k,          pushup,                 {0} },
	{ MODKEY,                       XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,          incnmaster,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_i,          incnstack,              {.i = +1 } },
	{ MODKEY|ControlMask,           XK_u,          incnstack,              {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_Down,       moveresize,             {.v = "0x 25y 0w 0h" } },
	{ MODKEY|Mod4Mask,              XK_Up,         moveresize,             {.v = "0x -25y 0w 0h" } },
	{ MODKEY|Mod4Mask,              XK_Right,      moveresize,             {.v = "25x 0y 0w 0h" } },
	{ MODKEY|Mod4Mask,              XK_Left,       moveresize,             {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Down,       moveresize,             {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Up,         moveresize,             {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Right,      moveresize,             {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Left,       moveresize,             {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } },
	{ MODKEY,                       XK_space,      zoom,                   {0} },
	{ MODKEY|ControlMask,           XK_r,          reorganizetags,         {0} },
	{ MODKEY,                       XK_Return,     zoom,                   {0} },
	{ MODKEY,                       XK_z,          incrgaps,               {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_z,          incrgaps,               {.i = -5 } },
	// { MODKEY|Mod4Mask,              XK_i,          incrigaps,              {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_o,          incrogaps,              {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY,                       XK_a,          togglegaps,             {0} },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },
    { MODKEY,			        XK_t,					setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		    XK_t,					setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			        XK_y,					setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		    XK_y,					setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			        XK_u,					setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		    XK_u,					setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			        XK_i,					setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		    XK_i,					setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
    { MODKEY,			        XK_g,					setlayout,	{.v = &layouts[13]} }, /* grid */


	// { MODKEY|ControlMask,           XK_t,          rotatelayoutaxis,       {.i = +1 } },   [> flextile, 1 = layout axis <]
	{ MODKEY|ControlMask,           XK_Tab,        rotatelayoutaxis,       {.i = +2 } },   /* flextile, 2 = master axis */
	{ MODKEY|ControlMask|ShiftMask, XK_Tab,        rotatelayoutaxis,       {.i = +3 } },   /* flextile, 3 = stack axis */
	{ MODKEY|ControlMask|Mod1Mask,  XK_Tab,        rotatelayoutaxis,       {.i = +4 } },   /* flextile, 4 = secondary stack axis */
	{ MODKEY|Mod5Mask,              XK_t,          rotatelayoutaxis,       {.i = -1 } },   /* flextile, 1 = layout axis */
	{ MODKEY|Mod5Mask,              XK_Tab,        rotatelayoutaxis,       {.i = -2 } },   /* flextile, 2 = master axis */
	{ MODKEY|Mod5Mask|ShiftMask,    XK_Tab,        rotatelayoutaxis,       {.i = -3 } },   /* flextile, 3 = stack axis */
	{ MODKEY|Mod5Mask|Mod1Mask,     XK_Tab,        rotatelayoutaxis,       {.i = -4 } },   /* flextile, 4 = secondary stack axis */
	{ MODKEY|ControlMask,           XK_Return,     mirrorlayout,           {0} },          /* flextile, flip master and stack areas */
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,          togglehorizontalmax,    {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,          togglehorizontalmax,    {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,          toggleverticalmax,      {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,          toggleverticalmax,      {0} },
	{ MODKEY|ControlMask,           XK_m,          togglemax,              {0} },
	{ MODKEY,                       XK_f,          togglefullscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_f,          fullscreen,             {0} },
	{ MODKEY,                       XK_s,          togglesticky,           {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_n,          nametag,                {0} },

	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)

	{ MODKEY,		XK_minus,	spawn,		SHCMD("pamixer --allow-boost -d 5; kill -37 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_minus,	spawn,		SHCMD("pamixer --allow-boost -d 15; kill -37 $(pidof dwmblocks)") },
	{ MODKEY,		XK_equal,	spawn,		SHCMD("pamixer --allow-boost -i 5; kill -37 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_equal,	spawn,		SHCMD("pamixer --allow-boost -i 15; kill -37 $(pidof dwmblocks)") },
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

	{ 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -37 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("if [ $(pamixer --get-mute) == 'true' ]; then pamixer --unmute; fi; if [ $(pamixer --get-volume) -le 159 ]; then pamixer --allow-boost -i 5; kill -37 $(pidof dwmblocks); fi") },
	{ 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("pamixer --allow-boost -d 5; kill -37 $(pidof dwmblocks)") },
    	{ 0, XF86XK_AudioPrev,			spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,			spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,			spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,			spawn,		SHCMD("mpc play") },
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
    	{ 0, XF86XK_ScreenSaver,		spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },

};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
    { ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
    { ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
    { ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
    { ClkStatusText,        0,                   Button4,        sigstatusbar,   {.i = 4 } },
    { ClkStatusText,        0,                   Button5,        sigstatusbar,   {.i = 5 } }, 
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};


