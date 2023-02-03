// dllmain.h: 模块类的声明。

class CdocxATLModule : public ATL::CAtlDllModuleT< CdocxATLModule >
{
public :
	DECLARE_LIBID(LIBID_docxATLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DOCXATL, "{2656a733-4395-4c64-8276-575fdd0608d6}")
};

extern class CdocxATLModule _AtlModule;
