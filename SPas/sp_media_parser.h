#ifndef _SP_MEDIA_PARSER_H_
#define _SP_MEDIA_PARSER_H_
extern "C"
{
#include "sp_public_def.h"
#include "../3rdparty/ffmpeg/include/libavutil/avstring.h"
#include "../3rdparty/ffmpeg/include/libavutil/mathematics.h"
#include "../3rdparty/ffmpeg/include/libavutil/pixdesc.h"
#include "../3rdparty/ffmpeg/include/libavutil/imgutils.h"
#include "../3rdparty/ffmpeg/include/libavutil/dict.h"
#include "../3rdparty/ffmpeg/include/libavutil/parseutils.h"
#include "../3rdparty/ffmpeg/include/libavutil/samplefmt.h"
#include "../3rdparty/ffmpeg/include/libavutil/avassert.h"
#include "../3rdparty/ffmpeg/include/libavutil/time.h"
#include "../3rdparty/ffmpeg/include/libavformat/avformat.h"
#include "../3rdparty/ffmpeg/include/libavdevice/avdevice.h"
#include "../3rdparty/ffmpeg/include/libswscale/swscale.h"
#include "../3rdparty/ffmpeg/include/libavutil/opt.h"
#include "../3rdparty/ffmpeg/include/libavcodec/avfft.h"
#include "../3rdparty/ffmpeg/include/libswresample/swresample.h"

#include "../3rdparty/ffmpeg/include/libavformat\internal.h"

#if CONFIG_AVFILTER
# include "libavfilter/avcodec.h"
# include "libavfilter/avfilter.h"
# include "libavfilter/avfiltergraph.h"
# include "libavfilter/buffersink.h"
# include "libavfilter/buffersrc.h"
#endif

#include <stdint.h>
}

#define TRYVERSION			0   //试用版，限制50帧
void sp_warning_msg_btn();



//int32_t video_parser_func(const int8t *fileName);


typedef struct vdCodecCtx{
	AVCodec			*pCodec;				//编解码器
	AVCodecContext	*pCodecCtx;				//编解码器上下文
	AVFormatContext	*pCodecFmtCtx;			//媒体格式上下文

	//AVFormatContext *fmt_ctx = NULL;

	AVCodecParserContext	*pCodecParserCtx;	//编解码解析器上下文

	AVFrame			*pFrame;				//一帧图像对象
	AVPacket		pkt;					//一个码流包对象

	AVStream *pVideoStream, *pAudioStream;

	int video_stream_idx, audio_stream_idx;
}vdCodecCtx;

typedef struct MediaInfo{
	int16_t in_format;						//封装格式
	int64_t frame_idx;						//帧序号
	char frame_type;						//帧类型
	int64_t frame_length;					//帧长度
	int64_t frame_raw_offset;				//帧偏移
	const char *codec_type;					//音视频类型
	enum AVCodecID frame_codec_type;				//编码类型

	int32_t	frame_resolution_width;			//分辨率（宽）
	int32_t	frame_resolution_height;		//分辨率（高）
	double_t frame_rate;					//帧率
	int64_t bit_rate;						//比特率(kb/s)
	int64_t frame_time_osd = 0;				//时间戳
	enum AVPixelFormat frame_pix_fmt;					//码流格式 yuv
}MediaInfo;

/* The different ways of decoding and managing data memory. You are not
* supposed to support all the modes in your application but pick the one most
* appropriate to your needs. Look for the use of api_mode in this example to
* see what are the differences of API usage between them */
enum {
	API_MODE_OLD = 0, /* old method, deprecated */
	API_MODE_NEW_API_REF_COUNT = 1, /* new method, using the frame reference counting */
	API_MODE_NEW_API_NO_REF_COUNT = 2, /* new method, without reference counting */
};

class VideoParser
{
public:
	VideoParser(void);
	~VideoParser(void);

	//打开流文件
	FILE* openFile(const int8t* fileName);
	void  closeFile();

	//获取文件路径全名
	int8t* getFilePath() { return m_pFilePath; };

public:
	FILE  *m_pFile;	//文件流指针
	int8t *m_pFilePath;		//文件路径+名字
	int16t m_fileLen;		//文件流数据长度

};

int do_packet_auto_bsf(AVFormatContext *s, AVPacket *pkt);

#endif
