//==============================================================================
//
//  OvenMediaEngine
//
//  Created by getroot
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================

#include <mutex>
#include <thread>
#include "openssl_manager.h"
#include "openssl/ssl.h"

std::mutex *OpenSSLManager::_mutex_array = nullptr;

OpenSSLManager::OpenSSLManager()
{
}

OpenSSLManager::~OpenSSLManager()
{
}

bool OpenSSLManager::InitializeOpenSSL()
{
	// For thread-safe

	// MUTEX 생성
	_mutex_array = new std::mutex[CRYPTO_num_locks()];
	if(!_mutex_array)
	{
		return false;
	}

	CRYPTO_set_id_callback(GetThreadId);
	CRYPTO_set_locking_callback(MutexLock);

	// Init OpenSSL

	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();

	return true;
}

bool OpenSSLManager::ReleaseOpenSSL()
{
	CRYPTO_set_id_callback(nullptr);
	CRYPTO_set_locking_callback(nullptr);

	delete[] _mutex_array;
	return true;
}

unsigned long OpenSSLManager::GetThreadId()
{
	std::hash<std::thread::id> hasher;
	return hasher(std::this_thread::get_id());
}

void OpenSSLManager::MutexLock(int mode, int n, const char *file, int line)
{
	if(mode & CRYPTO_LOCK)
	{
		_mutex_array[n].lock();
	}
	else
	{
		_mutex_array[n].unlock();
	}
}



