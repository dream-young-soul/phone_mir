#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "VD_Share.h"
#ifdef WIN32
#include <dbghelp.h>
#include <windows.h>
#pragma comment(lib, "Dbghelp.lib")
#include "vld.h"
#endif
USING_NS_CC;


#ifdef WIN32
	WNDPROC NEWPROC_;
LONG WINAPI MyUnhandledFilter(struct _EXCEPTION_POINTERS *lpExceptionInfo)
{
	LONG ret = EXCEPTION_EXECUTE_HANDLER;
	char szFileName[64];
	SYSTEMTIME st;
	::GetLocalTime(&st);
	sprintf(szFileName, "%04d-%02d-%02d-%02d-%02d-%02d-%02d-%02d.dmp", st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, rand()%100);

	HANDLE hFile = ::CreateFileA(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION ExInfo;

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = lpExceptionInfo;
		ExInfo.ClientPointers = false;

		// write the dump

		BOOL bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );
		if (bOK)
		{
			printf("Create Dump File Success!\n");
		}
		else
		{
			printf("MiniDumpWriteDump Failed: %d\n", GetLastError());
		}

		::CloseHandle(hFile);
	}
	else
	{
		printf("Create File %s Failed %d\n", szFileName, GetLastError());
	}
	return ret;
}


LRESULT CALLBACK NewProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_CLOSE:
		{
			Director::getInstance()->end();
			break;
		}
	}
	return ::CallWindowProc(NEWPROC_, hWnd, Msg, wParam, lParam);
}
#endif
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {


    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
		glview->setFrameSize(1024,600);
        director->setOpenGLView(glview);
    }
	
    // turn on display FPS
    director->setDisplayStats(true);
	
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	float width = CCDirector::getInstance()->getWinSize().width;
	float height = CCDirector::getInstance()->getWinSize().height;

	float proportion = width / height;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC ||         \
	CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 ||       \
	CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

	if (proportion > 1.5f)
	{
		height = MIN(height, 800);
		width = height * proportion;
	}
	else
	{
		width = MIN(width, 1200);
		height = width / proportion;
	}
	
	
	glview->setDesignResolutionSize(width, height, kResolutionShowAll);

#else

	if (width < 960 || height < 640)
	{
		if (proportion > 1.5f)
		{
			height = MAX(height, 640);
			width = height * proportion;
		}
		else
		{
			width = MAX(width, 960);
			height = width / proportion;
		}
		glview->setDesignResolutionSize(width, height, kResolutionShowAll);
	}
	else if (width > 960 || height > 640)
	{
		if (proportion > 1.5f)
		{
			height = MIN(height, 640);
			width = height * proportion;
		}
		else
		{
			width = MIN(width, 960);
			height = width / proportion;
		}
		glview->setDesignResolutionSize(width, height, kResolutionShowAll);
	}

#endif
	SCREENWIDTH = width;
	SCREENHEIGHT = height;


    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	::SetUnhandledExceptionFilter(MyUnhandledFilter);
	HWND handle =glview->getWin32Window();

	NEWPROC_ = (WNDPROC)::SetWindowLongA(handle,GWL_WNDPROC,(LONG)NewProc);
#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
