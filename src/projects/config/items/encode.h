//==============================================================================
//
//  OvenMediaEngine
//
//  Created by Hyunjun Jang
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================
#pragma once

#include "audio_profile.h"
#include "video_profile.h"

namespace cfg
{
	struct Encode : public Item
	{
		bool IsActive() const
		{
			return _active;
		}

		ov::String GetName() const
		{
			return _name;
		}

		ov::String GetStreamName() const
		{
			return _stream_name;
		}

		const AudioEncodeOptions *GetAudioEncodingOptions() const
		{
			return IsParsed(&_audio) ? _audio.GetAudioEncodeOptions() : nullptr;
		}

		const VideoEncodeOptions *GetVideoEncodingOptions() const
		{
			return IsParsed(&_video) ? _video.GetVideoEncodeOptions() : nullptr;
		}

	protected:
		void MakeParseList() const override
		{
			RegisterValue<Optional>("Active", &_active);
			RegisterValue("Name", &_name);
			RegisterValue("StreamName", &_stream_name);
			RegisterValue<Optional>("Audio", &_audio);
			RegisterValue<Optional>("Video", &_video);
		}

		bool _active;
		ov::String _name;
		ov::String _stream_name;
		AudioProfile _audio;
		VideoProfile _video;
	};
}