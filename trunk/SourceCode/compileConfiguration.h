//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef compileConfiguration_h
#define compileConfiguration_h

// Configuration of compilation flags of Guitar Xero

// Platforms

// MacOS X
#ifdef __APPLE__
	// Input
	#define SUPPORT_INPUT_SDL

	// Video
	#define SUPPORT_VIDEO_WINDOWING

	#define SUPPORT_VIDEO_SDL
	#define SUPPORT_VIDEO_OpenGL_SDL

	// Audio
	#define SUPPORT_AUDIO_SDL
	#define SUPPORT_AUDIO_OpenAL
#endif

// Linux
#ifdef linux
	// Input
	#define SUPPORT_INPUT_SDL

	// Video
	#define SUPPORT_VIDEO_WINDOWING

	#define SUPPORT_VIDEO_SDL
	#define SUPPORT_VIDEO_OpenGL_SDL

	// Audio
	#define SUPPORT_AUDIO_SDL
#endif

// Windows
#ifdef _WIN32
	// Input
	#define SUPPORT_INPUT_SDL

	// Video
	#define SUPPORT_VIDEO_WINDOWING

	#define SUPPORT_VIDEO_SDL
	#define SUPPORT_VIDEO_OpenGL_SDL
	#define SUPPORT_VIDEO_Direct3D

	// Audio
	#define SUPPORT_AUDIO_SDL
	#define SUPPORT_AUDIO_DirectSound
#endif

// XBox
#ifdef _XBOX
	// Input
	#define SUPPORT_INPUT_SDL

	// Video
	#define SUPPORT_VIDEO_SDL
	#define SUPPORT_VIDEO_Direct3D

	// Audio
	#define SUPPORT_AUDIO_SDL
	#define SUPPORT_AUDIO_DirectSound
#endif

// iPhone - Maybe one day...? :-)
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
	// Input
	#define SUPPORT_INPUT_SDL

	// Video
	#define SUPPORT_VIDEO_SDL
	#define SUPPORT_VIDEO_OpenGL_SDL

	// Audio
	#define SUPPORT_AUDIO_SDL
#endif


// Metaconfig

#ifdef SUPPORT_VIDEO_SDL
	#define SUPPORT_VIDEO_2D
#endif

#ifdef SUPPORT_VIDEO_OpenGL_SDL
	#define SUPPORT_VIDEO_2D
	#define SUPPORT_VIDEO_3D
#endif

#ifdef SUPPORT_VIDEO_Direct3D
	#define SUPPORT_VIDEO_2D
	#define SUPPORT_VIDEO_3D
#endif

#endif
