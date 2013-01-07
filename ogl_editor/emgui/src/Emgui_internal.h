#ifndef EMGUI_INTERNAL_H_
#define EMGUI_INTERNAL_H_

#include "Types.h"
#include "emgui_internal.h"
#include "FontLayout.h"
#include "External/stb_truetype.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum EmguiDrawType
{
	EMGUI_DRAWTYPE_NONE,
	EMGUI_DRAWTYPE_FILL,
	EMGUI_DRAWTYPE_IMAGE,
	EMGUI_DRAWTYPE_TEXT,
	EMGUI_DRAWTYPE_SLIDER,
	EMGUI_DRAWTYPE_DOTS,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct EmguiControlInfo
{
	enum EmguiDrawType type;

	int x;
	int y;
	int width;
	int height;

	uint32_t color;
	uint32_t color1;
	char* text;

	// todo: Use union with all data instead
	int sliderThumbX;
	int sliderThumbY;
	int sliderThumbWidth;
	int sliderThumbHeight;
	int fontId;
	int* dots;
	int dotsCount;

} EmguiControlInfo;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
	EMGUI_MAX_FONTS = 16,
	EMGUI_LAYER_COUNT = 8,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DrawTextCommand
{
	struct DrawTextCommand* next;
	char* text;
	int x;
	int y;
	uint32_t color;
	bool flipped;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DrawFillCommand
{
	struct DrawFillCommand* next;
	uint32_t color0;
	uint32_t color1;
	int x;
	int y;
	int width;
	int height;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DrawImageCommand
{
	struct DrawImageCommand* next;
	int64_t imageId;
	uint32_t color;
	int x;
	int y;
	int width;
	int height;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Scissor
{
	int x, y, width, height;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DrawLayer
{
	struct Scissor scissor;

	struct DrawTextCommand* textCommands[EMGUI_MAX_FONTS];
	struct DrawImageCommand* imageCommands;
	struct DrawImageCommand* imageCommandsTail;

	struct DrawFillCommand* fillCommands;
	struct DrawFillCommand* fillCommandsTail;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RenderData
{
	struct DrawLayer layers[EMGUI_LAYER_COUNT];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct LoadedFont
{
	stbtt_bakedchar cData[96];
	uint64_t handle;
	char name[1024];
	int rangeStart;
	int rangeEnd;
	uint16_t width;
	uint16_t height;
	unsigned short* altLookup;
	EmguiFontLayout* layout;
} LoadedFont;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
	MAX_CONTROLS = 8192,
	MAX_FONTS = 32,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern uint32_t g_controlId;
extern EmguiControlInfo g_controls[MAX_CONTROLS];
extern LoadedFont g_loadedFonts[MAX_FONTS];
extern uint32_t g_currentFont;

#endif

