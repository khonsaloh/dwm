/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
// vanitygaps
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
//===***===
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_gray3  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Firefox",        NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Brave-browser",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Lxappearance",   NULL,       NULL,       0,            1,           -1 },
	{ "scratchpad",     NULL,       NULL,       0,            1,           -1 },
	{ "ffplay",         NULL,       NULL,       0,            1,           -1 },
	{ "Webcam",         NULL,       NULL,       0,            1,           -1 },
	//{ "Gimp",         NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "shiftview.c"

// vanitygaps
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
// ====****===
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	//{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	// vanity gaps
	//{ "[@]",      spiral },
	//{ "[\\]",     dwindle },
	//{ "H[]",      deck },
	//{ "TTT",      bstack },
	//{ "===",      bstackhoriz },
	//{ "HHH",      grid },
	//{ "###",      nrowgrid },
	//{ "---",      horizgrid },
	//{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	//{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
	//===***===

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", "#926e34", "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13

#include "sticky"
#include "fullscreen"
#include "movestack.c"
#include "cyclelayouts"
#include "inplacerotate"
#include "aspectresize"

static Key keys[] = {
  /* modifier                   key                      function          argument */
	TAGKEYS(                      XK_1,                                       0)
	TAGKEYS(                      XK_2,                                       1)
	TAGKEYS(                      XK_3,                                       2)
	TAGKEYS(                      XK_4,                                       3)
	TAGKEYS(                      XK_5,                                       4)
	TAGKEYS(                      XK_6,                                       5)
	TAGKEYS(                      XK_7,                                       6)
	TAGKEYS(                      XK_8,                                       7)
	TAGKEYS(                      XK_9,                                       8)

	{ MODKEY|ControlMask,         XK_comma,                 cyclelayout,      {.i = -1 } },
	{ MODKEY|ControlMask,         XK_period,                cyclelayout,      {.i = +1 } },
	
  //resize focused window
  //{ MODKEY|ControlMask,         XK_j,                     aspectresize,     {.i = +24} },
	//{ MODKEY|ControlMask,         XK_k,                     aspectresize,     {.i = -24} },

	// change focused window
  { MODKEY,                     XK_j,                     focusstack,       {.i = +1 } },
  { MODKEY,                     XK_k,                     focusstack,       {.i = -1 } },
  
  { MODKEY|ShiftMask,           XK_j,                     movestack,        {.i = +1 } },
	{ MODKEY|ShiftMask,           XK_k,                     movestack,        {.i = -1 } },
	
  // no keys to prevent warning when compiling otherwise I should change the file referencing the function, and you know, it's fastest
  { ENOKEY,                     XK_f,                     togglefullscr,    {0} },
  { ENOKEY,                     XK_0,                     defaultgaps,      {0} },

  //{ MODKEY|ShiftMask,           XK_j,                     inplacerotate,    {.i = +1} },
  //{ MODKEY|ShiftMask,           XK_k,                     inplacerotate,    {.i = -1} },
  //{ MODKEY|ShiftMask,           XK_h,                     inplacerotate,    {.i = +2} },
  //{ MODKEY|ShiftMask,           XK_l,                     inplacerotate,    {.i = -2} },
	
  // cycle occupied tags in the same focused monitor
  { MODKEY,                     XK_o,                     shiftview,         {.i = +1 } },
	{ MODKEY,                     XK_i,                     shiftview,         {.i = -1 } },
	{ MODKEY|ShiftMask,           XK_i,                     shiftempty,        {.i = -1 } },
	{ MODKEY|ShiftMask,           XK_o,                     shiftempty,        {.i = +1 } },
	
  { MODKEY,                     XK_t,                     setlayout,         {.v = &layouts[0]} }, // set tiling layout
	{ MODKEY,                     XK_f,                     setlayout,         {.v = &layouts[1]} }, // set full window layout
	{ MODKEY,                     XK_q,                     setlayout,	       {.v = &layouts[5]} }, /* centeredmaster */
  //{ Mod1Mask,                 XK_1,                     setlayout,         {.v = &layouts[0]} },
  //{ Mod1Mask,                 XK_2,                     setlayout,         {.v = &layouts[1]} },
  //{ Mod1Mask,                 XK_3,                     setlayout,         {.v = &layouts[2]} },
	//{ Mod1Mask,                 XK_4,                     setlayout,         {.v = &layouts[3]} },

  // function keys
	{ ControlMask,                XK_F4,                    spawn,             SHCMD("$HOME/.local/bin/nopath/compositor") },
	{ 0,                          XF86AudioMute,            spawn,             SHCMD("amixer sset Master toggle; kill -44 $(pidof dwmblocks)") },
	{ 0,                          XF86AudioLowerVolume,     spawn,             SHCMD("amixer sset Master 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0,                          XF86AudioRaiseVolume,     spawn,             SHCMD("amixer sset Master 5%+; kill -44 $(pidof dwmblocks)") },
	{ ControlMask,                XK_Home,                  spawn,             SHCMD("$HOME/.local/bin/nopath/record") },
	{ MODKEY|ShiftMask,           XK_Return,                spawn,             SHCMD("$HOME/.local/bin/nopath/scratchpad") }, //toggle scratchpad
  //{ ControlMask,              XK_F10,                   spawn,             SHCMD("cmus-remote -s") },
  
	{ MODKEY,                     XK_Return,                spawn,             {.v = termcmd } }, //launch terminal
	{ MODKEY,                     XK_p,                     spawn,             SHCMD("rofi -show drun") }, //launch menu
	//{ MODKEY,                   XK_p,                     spawn,             {.v = dmenucmd } },
  { MODKEY,                     XK_w,                     spawn,             SHCMD("$BROWSER") },
	{ MODKEY,                     XK_m,                     spawn,             SHCMD("bookmarker") },
	{ MODKEY,                     XK_e,                     spawn,             SHCMD("pcmanfm") },
	{ MODKEY,                     XK_c,                     spawn,             SHCMD("$HOME/.local/bin/nopath/calc") },
	{ MODKEY|ShiftMask,           XK_Up,                    spawn,             SHCMD("amixer sset Master 5%+; kill -44 $(pidof dwmblocks)") }, //volume up
	{ MODKEY|ShiftMask,           XK_Down,                  spawn,             SHCMD("amixer sset Master 5%-; kill -44 $(pidof dwmblocks)") }, // volume down

  { MODKEY,                     XK_b,                     togglebar,         {0} },
	{ MODKEY,                     XK_Shift_R,               killclient,        {0} }, // close focused window

  { MODKEY,                     XK_s,                     togglesticky,      {0} }, // toggle sticky window
	{ MODKEY|ShiftMask,           XK_space,                 togglefloating,    {0} }, // toggle floating window
	{ MODKEY,                     XK_d,                     incnmaster,        {.i = -1 } },
	{ MODKEY,                     XK_h,                     setmfact,          {.f = -0.05} },
	{ MODKEY,                     XK_l,                     setmfact,          {.f = +0.05} },
	{ MODKEY,                     XK_Tab,                   view,              {0} }, // go to last tag
	{ MODKEY,                     XK_BackSpace,             zoom,              {0} },
	{ MODKEY,                     XK_0,                     view,              {.ui = ~0 } }, //view all windows open on the same monitor
	{ MODKEY|ShiftMask,           XK_0,                     tag,               {.ui = ~0 } },
	{ MODKEY,                     XK_period,                focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,           XK_comma,                 tagmon,            {.i = -1 } },
	
  //{ MODKEY|ShiftMask,         XK_period,                tagmon,            {.i = +1 } },
	//{ MODKEY|ShiftMask,         XK_o,                     shifttag,          {.i = +1 } },
	//{ MODKEY|ShiftMask,         XK_i,                     shifttag,          {.i = -1 } },
	//{ MODKEY,                   XK_comma,                 focusmon,          {.i = -1 } },

	{ MODKEY,                     XK_g,                     incrgaps,          {.i = +1 } },
	{ MODKEY|ShiftMask,           XK_g,                     incrgaps,          {.i = -1 } },
	{ MODKEY|ShiftMask,           XK_q,                     quit,              {0} }, //quit dwm
};
	
//{ MODKEY|Mod1Mask,    XK_i,      incrigaps,      {.i = +1 } },
//{ MODKEY|Mod1Mask,    XK_i,      incrigaps,      {.i = -1 } },
//{ MODKEY|Mod1Mask,    XK_o,      incrogaps,      {.i = +1 } },
//{ MODKEY|Mod1Mask,    XK_o,      incrogaps,      {.i = -1 } },
//{ MODKEY|Mod1Mask,    XK_6,      incrihgaps,     {.i = +1 } },
//{ MODKEY|Mod1Mask,    XK_6,      incrihgaps,     {.i = -1 } },
//{ MODKEY|Mod1Mask,    XK_7,      incrivgaps,     {.i = +1 } },
//{ MODKEY|Mod1Mask     XK_7,      incrivgaps,     {.i = -1 } },
//{ MODKEY|Mod1Mask,    XK_8,      incrohgaps,     {.i = +1 } },
//{ MODKEY|Mod1Mask     XK_8,      incrohgaps,     {.i = -1 } },
//{ MODKEY|Mod1Mask,    XK_9,      incrovgaps,     {.i = +1 } },
//{ MODKEY|Mod1Mask,    XK_9,      incrovgaps,     {.i = -1 } },
//{ MODKEY|Mod1Mask,    XK_0,      togglegaps,     {0} },

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	//{ ClkStatusText,      0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	//{ ClkStatusText,      0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
