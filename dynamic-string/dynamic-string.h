#pragma once

#include <stddef.h>
#include <stdint.h>

#include <string.h>
#include <memory.h>

#include <iostream>

namespace rbi {
	class string final {
	private:

		uint8_t* m_block = 0;	
		size_t m_length = 0, m_allocated = 0;
		
		void m_allocate(size_t nsize);
		void m_reallocate(size_t nsize);
		void m_free();

	public:
		
		string();
		string(char var);
		string(const char* var);
		string(const string& var);
		~string();

		char  operator[] (unsigned j) const;
		char& operator[] (unsigned j);

		string& operator=(char var);
		string& operator=(const char* var);
		string& operator=(const string& var);

		string& operator+=(char var);
		string& operator+=(const char* var);
		string& operator+=(const string& var);

		friend bool operator==(const string& lsp, const string& rsp);
		friend bool operator==(const string& lsp, char          rsp);
		friend bool operator==(const string& lsp, const char*   rsp);
		friend bool operator==(char          lsp, const string& rsp);
		friend bool operator==(const char*   lsp, const string& rsp);

		friend bool operator!=(const string& lsp, const string& rsp);
		friend bool operator!=(const string& lsp, char          rsp);
		friend bool operator!=(const string& lsp, const char*   rsp);
		friend bool operator!=(char          lsp, const string& rsp);
		friend bool operator!=(const char*   lsp, const string& rsp);

		friend string operator+(const string& lsp, const string& rsp);
		friend string operator+(const string& lsp, char          rsp);
		friend string operator+(const string& lsp, const char*   rsp);
		friend string operator+(char          lsp, const string& rsp);
		friend string operator+(const char*   lsp, const string& rsp);

		operator const char* () const;
		operator char* () const;
		
		size_t length() const;

		void compress();
		void resize(size_t size);
	};
}