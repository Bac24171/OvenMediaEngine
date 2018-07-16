//==============================================================================
//
//  OvenMediaEngine
//
//  Created by Gil Hoon Choi
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================
#include <base/ovlibrary/ovlibrary.h>
#include <utility>
#include "application_info.h"

ApplicationInfo::ApplicationInfo()
	: _type(ApplicationType::Unknown)
{
	// ID RANDOM 생성
	_id = ov::Random::GenerateInteger();
}

ApplicationInfo::ApplicationInfo(const std::shared_ptr<ApplicationInfo> &info)
{
	_id = info->_id;
	_name = info->_name;
	_type = info->_type;

	for(const auto &x : info->_providers)
	{
		_providers.push_back(x);
	}

	for(const auto &x : info->_publishers)
	{
		_publishers.push_back(x);
	}
}

ApplicationInfo::~ApplicationInfo()
{
}

const uint32_t ApplicationInfo::GetId() const noexcept
{
	return _id;
}

const ov::String ApplicationInfo::GetName() const noexcept
{
	return _name;
}

void ApplicationInfo::SetName(ov::String name)
{
	_name = name;
}

const ApplicationType ApplicationInfo::GetType() const noexcept
{
	return _type;
}

void ApplicationInfo::SetType(ApplicationType type)
{
	_type = type;
}

void ApplicationInfo::SetTypeFromString(const ov::String &type_string)
{
	_type = ApplicationInfo::ApplicationTypeFromString(type_string);
}

std::vector<std::shared_ptr<PublisherInfo>> ApplicationInfo::GetPublishers() const noexcept
{
	return _publishers;
}

void ApplicationInfo::AddPublisher(std::shared_ptr<PublisherInfo> publisher_info)
{
	_publishers.push_back(publisher_info);
}

std::vector<std::shared_ptr<ProviderInfo>> ApplicationInfo::GetProviders() const noexcept
{
	return _providers;
}

void ApplicationInfo::AddProvider(std::shared_ptr<ProviderInfo> provider)
{
	_providers.push_back(provider);
}

const char *ApplicationInfo::StringFromApplicationType(ApplicationType application_type) noexcept
{
	switch(application_type)
	{
		case ApplicationType::Live:
			return "live";
		case ApplicationType::Vod:
			return "vod";
		case ApplicationType::LiveEdge:
			return "liveedge";
		case ApplicationType::VodEdge:
			return "vodedge";
		default:
			return "unknown";
	}
}

const ApplicationType ApplicationInfo::ApplicationTypeFromString(ov::String type_string) noexcept
{
	if(type_string == "live")
	{
		return ApplicationType::Live;
	}
	else if(type_string == "vod")
	{
		return ApplicationType::Vod;
	}
	else if(type_string == "liveedge")
	{
		return ApplicationType::LiveEdge;
	}
	else if(type_string == "vodedge")
	{
		return ApplicationType::VodEdge;
	}
	else
	{
		return ApplicationType::Unknown;
	}
}

ov::String ApplicationInfo::ToString() const
{
	ov::String result = ov::String::FormatString(R"({"name": "%s", "type": "%s")", _name.CStr(), ApplicationInfo::StringFromApplicationType(_type));

	if(_providers.empty() == false)
	{
		result.Append(", \"providers\": [");

		for(auto iterator = _providers.begin(); iterator != _providers.end(); ++iterator)
		{
			if(iterator != _providers.begin())
			{
				result.Append(",");
			}

			result.AppendFormat("%s", (*iterator)->ToString().CStr());
		}

		result.Append("]");
	}

	if(_publishers.empty() == false)
	{
		result.Append(", \"publishers\": [");

		for(auto iterator = _publishers.begin(); iterator != _publishers.end(); ++iterator)
		{
			if(iterator != _publishers.begin())
			{
				result.Append(",");
			}

			result.AppendFormat("%s", (*iterator)->ToString().CStr());
		}

		result.Append("]");
	}

	result.Append("}");

	return result;
}