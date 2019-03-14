#pragma once
#include "Common.h"
#include "Serialization.h"

#include <unordered_map>

#if !defined(BRO_ENABLE_SYMENGINE)
#define BRO_ENABLE_SYMENGINE (USE_BROFILER && BRO_MSVC)
#endif

namespace Brofiler
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Module
	{
		std::string path;
		void* address;
		size_t size;
		Module(const char* p, void* a, size_t s) : path(p), address(a), size(s) {}
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Symbol
	{
		uint64 address;
		uint64 offset;
		std::wstring file;
		std::wstring function;
		uint32 line;
		Symbol()
			: address(0)
			, offset(0)
			, line(0)
		{}
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	OutputDataStream& operator<<(OutputDataStream& os, const Symbol * const symbol);
	OutputDataStream& operator<<(OutputDataStream& os, const Module& module);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef std::unordered_map<uint64, Symbol> SymbolCache;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class SymbolEngine
	{
	protected:
		SymbolCache cache;
		std::vector<Module> modules;
	public:
		virtual const std::vector<Module>& GetModules() { return modules; }

		// Get Symbol from address
		virtual const Symbol* const GetSymbol(uint64 dwAddress);

		virtual void UpdateModules() {}

		virtual ~SymbolEngine() {};

		static SymbolEngine* Get();


	};

}
