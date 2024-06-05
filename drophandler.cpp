#include "drophandler.h"
#include <QDebug>

DropHandler::DropHandler(std::function<void(const std::vector<std::string>&)> callback)
    : m_cRef(0), m_callback(callback)
{
    qDebug()<<"[DropHandler] -->";
}

DropHandler::~DropHandler(){


}

HRESULT STDMETHODCALLTYPE DropHandler::QueryInterface(REFIID riid, void **ppvObject)
{
    qDebug()<<"[QueryInterface] -->";
    if (!IsEqualIID(riid, IID_IUnknown) && !IsEqualIID(riid, IID_IDropTarget))
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    *ppvObject = static_cast<IDropTarget *>(this);
    AddRef();
    return S_OK;
}

ULONG STDMETHODCALLTYPE DropHandler::AddRef(void)
{
    qDebug()<<"[AddRef] -->";
    return InterlockedIncrement(&m_cRef);
}

ULONG STDMETHODCALLTYPE DropHandler::Release(void)
{
    qDebug()<<"[Release] -->";
    ULONG cRef = InterlockedDecrement(&m_cRef);
    if (cRef == 0) {
        delete this;
        return 0;
    }
    return cRef;
}

HRESULT STDMETHODCALLTYPE DropHandler::DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    qDebug()<<"[DragEnter] -->";
//    FORMATETC fmtetc_cf_hdrop = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
//    FORMATETC fmtetc_shellidlist = { static_cast<WORD>(RegisterClipboardFormat(CFSTR_SHELLIDLIST)), nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
//    FORMATETC fmtetc_filedescriptor = { static_cast<WORD>(RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR)), nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
//    if (pDataObj->QueryGetData(&fmtetc_cf_hdrop) == S_OK ||
//        pDataObj->QueryGetData(&fmtetc_shellidlist) == S_OK ||
//        pDataObj->QueryGetData(&fmtetc_filedescriptor) == S_OK)
//    {
//        *pdwEffect = DROPEFFECT_COPY;
//        return S_OK;
//    }
//    *pdwEffect = DROPEFFECT_NONE;
//    return DRAGDROP_S_CANCEL;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE DropHandler::DragOver(DWORD, POINTL, DWORD *)
{
    qDebug()<<"[DragOver] -->";
    return S_OK;
}

HRESULT STDMETHODCALLTYPE DropHandler::DragLeave(void)
{
    qDebug()<<"[DragLeave] -->";
    return S_OK;
}

HRESULT DropHandler::Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    qDebug()<<"[Drop] -->";
//    bool ok = false;
//    CWaitCursor waitstatus;
//    std::vector<String> files;
//    FORMATETC fmtetc_cf_hdrop = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
//    FORMATETC fmtetc_shellidlist = { static_cast<WORD>(RegisterClipboardFormat(CFSTR_SHELLIDLIST)), nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
//    FORMATETC fmtetc_filedescriptor = { static_cast<WORD>(RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR)), nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
//    if (pDataObj->QueryGetData(&fmtetc_cf_hdrop) == S_OK &&
//        GetFileItemsFromIDataObject_CF_HDROP(pDataObj, files) == S_OK && files.size() > 0)
//        ok = true;
//    else if (pDataObj->QueryGetData(&fmtetc_shellidlist) == S_OK &&
//        GetFileItemsFromIDataObject_ShellIDList(pDataObj, files) == S_OK && files.size() > 0)
//        ok = true;
//    else if (pDataObj->QueryGetData(&fmtetc_filedescriptor) == S_OK &&
//        GetFileItemsFromIDataObject_FileDescriptor(pDataObj, files) == S_OK && files.size() > 0)
//        ok = true;
//    if (files.size() > 3)
//        files.resize(3);
//    if (!files.empty())
//        m_callback(files);
//    return ok ? S_OK : E_FAIL;
    return S_OK;
}
