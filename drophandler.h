#pragma once
#ifndef DROPHANDLER_H
#define DROPHANDLER_H

#include <Windows.h>
#include <WinUser.h>
#include <ole2.h>
#include <shellapi.h>
#include <functional>
#include <vector>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"Ole32.lib")

/*!
* 从github 移植的阉割版的 IDropTarget 实现
* https://github.com/WinMerge/winmerge/blob/f62b2e5b8b3e9d415045426e276dfd4d2ed271e6/Src/DropHandler.h
*/

class DropHandler: public IDropTarget
{
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    HRESULT STDMETHODCALLTYPE DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
    HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
    HRESULT STDMETHODCALLTYPE DragLeave(void);
    HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

    explicit DropHandler(std::function<void(const std::vector<std::string>&)> callback);
    ~DropHandler();

    std::function<void(const std::vector<std::string>&)> GetCallback() const { return m_callback; };

private:
    LONG m_cRef;
    std::function<void(const std::vector<std::string>&)> m_callback;
};

#endif // DROPHANDLER_H
