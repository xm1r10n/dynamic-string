#include "dynamic-string.h"

void rbi::string::m_allocate(size_t nsize) {
	if (m_allocated != 0) throw 1;

	m_allocated = nsize + 1;
	m_block = new uint8_t[m_allocated];
	
	memset(m_block, 0, m_allocated);
}

void rbi::string::m_reallocate(size_t nsize) {
	if (nsize < 0) throw 1;

	m_allocated = nsize;
	m_length = m_allocated < m_length ? m_allocated++ : m_length;

	uint8_t* tblock = new uint8_t[m_allocated];
	memcpy(tblock, m_block, m_length);

	delete m_block;
	m_block = tblock;

	memset(m_block + m_length, 0, m_allocated - m_length);
}

void rbi::string::m_free() {
	m_length = 0;
	m_allocated = 0;
	delete m_block;
}

rbi::string::string() {

}

rbi::string::string(char var) {
	m_length = 1;
	m_allocate(m_length);
	m_block[0] = var;
}

rbi::string::string(const char* var) {
	m_length = strlen(var);
	m_allocate(m_length);
	memcpy(m_block, var, m_length);
}

rbi::string::string(const string& var) {
	m_length = var.length();
	m_allocate(m_length);
	memcpy(m_block, (const char*)var, m_length);
}

rbi::string::~string() {
	m_free();
}

char rbi::string::operator[] (unsigned j) const {
	if (j >= m_allocated) throw 1;
	return m_block[j];
}

char& rbi::string::operator[] (unsigned j) {
	if (j >= m_allocated) throw 1;
	return (char&)m_block[j];
}

rbi::string& rbi::string::operator=(char var) {
	m_free();
	m_length = 1;
	m_allocate(m_length);
	m_block[0] = var;
}

rbi::string& rbi::string::operator=(const char* var) {
	m_free();
	m_length = strlen(var);
	m_allocate(m_length);
	memcpy(m_block, var, m_length);
}

rbi::string& rbi::string::operator=(const string& var) {
	m_free();
	m_length = var.length();
	m_allocate(m_length);
	memcpy(m_block, (const char*)var, m_length);
}

rbi::string& rbi::string::operator+=(char var) {
	if (m_allocated < m_length + 2) m_reallocate(m_length + 2);
	m_block[m_length] = var;
	m_length++;
	return *this;
}

rbi::string& rbi::string::operator+=(const char* var) {
	size_t consize = strlen(var);
	if (m_allocated < m_length + consize + 1) m_reallocate(m_length + consize + 1);
	memcpy(m_block + m_length, var, consize);
	m_length += consize;
	return *this;
}

rbi::string& rbi::string::operator+=(const string& var) {
	size_t consize = var.length();
	if (m_allocated < m_length + consize + 1) m_reallocate(m_length + consize + 1);
	memcpy(m_block + m_length, (const char*)var, consize);
	m_length += consize;
	return *this;
}

bool rbi::operator==(const string& lsp, const string& rsp) {
	return ((const char*)lsp == (const char*)rsp);
}

bool rbi::operator==(const string& lsp, char rsp) { 
	return (lsp == string(rsp)); 
}

bool rbi::operator==(const string& lsp, const char* rsp) { 
	return (lsp == string(rsp)); 
}

bool rbi::operator==(char lsp, const string& rsp) {
	return (string(lsp) == rsp);
}

bool rbi::operator==(const char* lsp, const string& rsp) {
	return (string(lsp) == rsp); 
}

bool rbi::operator!=(const string& lsp, const string& rsp) {
	return !(lsp == rsp);
}

bool rbi::operator!=(const string& lsp, char rsp) {
	return !(lsp == rsp);
}

bool rbi::operator!=(const string& lsp, const char* rsp) {
	return !(lsp == rsp);
}

bool rbi::operator!=(char lsp, const string& rsp) {
	return !(lsp == rsp);
}

bool rbi::operator!=(const char* lsp, const string& rsp) {
	return !(lsp == rsp);
}

rbi::string rbi::operator+(const string& lsp, const string& rsp) {
	return (string(lsp) += rsp);
}

rbi::string rbi::operator+(const string& lsp, char rsp) {
	return (string(lsp) += string(rsp));
}

rbi::string rbi::operator+(const string& lsp, const char* rsp) {
	return (string(lsp) += string(rsp));
}

rbi::string rbi::operator+(char lsp, const string& rsp) {
	return (string(lsp) += rsp);
}

rbi::string rbi::operator+(const char* lsp, const string& rsp) {
	return (string(lsp) += rsp);
}

rbi::string::operator const char* () const {
	return reinterpret_cast<const char*>(m_block);
}

rbi::string::operator char* () const {
	return reinterpret_cast<char*>(m_block);
}

size_t rbi::string::length() const {
	return m_length;
}

void rbi::string::compress() {
	m_reallocate(m_length + 1);
}

void rbi::string::resize(size_t size) {
	m_reallocate(size);
}