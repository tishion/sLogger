#include "StdAfx.h"
#include "SLoggerSender.h"

CSLoggerSender::CSLoggerSender(void)
{
}


CSLoggerSender::~CSLoggerSender(void)
{
}

bool CSLoggerSender::Initialize(const SLUtf8String& parameter)
{
	return true;
}

bool CSLoggerSender::UnInitialize()
{
	return true;
}

void CSLoggerSender::ProcessLogMessage(const SLoggerMessagePtr& msg)
{
	if (!msg) return;

	std::vector<uint8_t> buffer;
	msg->ToBytesArray(buffer);

#if  defined(_WIN32)
#define LOG_VIEWER_WNDCLASS_NAME L"SLOGGERVIEWER_WNDCLASS_{16a0cd54-f03b-4244-98a4-fffdb085fda2}"
#define LOG_VIEWER_WNDTITLE_NAME L"SLOGGERVIEWER_WNDTITLE_{e408d8b6-8a74-4331-9ccb-b76c4ab825fe}"
	HWND hWndLogViewer = ::FindWindowExW(HWND_MESSAGE, NULL, LOG_VIEWER_WNDCLASS_NAME, LOG_VIEWER_WNDTITLE_NAME);
	if (hWndLogViewer && ::IsWindow(hWndLogViewer))
	{
		COPYDATASTRUCT cds;
		cds.dwData = 0;
		cds.cbData = buffer.size();
		cds.lpData = buffer.data();
		::SendMessage(hWndLogViewer, WM_COPYDATA, (WPARAM)(NULL), (LPARAM)(&cds));
	}
#endif
}