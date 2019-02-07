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

#define TRYVERSION			0   //���ð棬����50֡
void sp_warning_msg_btn();



//int32_t video_parser_func(const int8t *fileName);


typedef struct vdCodecCtx{
	AVCodec			*pCodec;				//�������
	AVCodecContext	*pCodecCtx;				//�������������
	AVFormatContext	*pCodecFmtCtx;			//ý���ʽ������

	//AVFormatContext *fmt_ctx = NULL;

	AVCodecParserContext	*pCodecParserCtx;	//����������������

	AVFrame			*pFrame;				//һ֡ͼ�����
	AVPacket		pkt;					//һ������������

	AVStream *pVideoStream, *pAudioStream;

	int video_stream_idx, audio_stream_idx;
}vdCodecCtx;

typedef struct MediaInfo{
	int16_t in_format;						//��װ��ʽ
	int64_t frame_idx;						//֡���
	char frame_type;						//֡����
	int64_t frame_length;					//֡����
	int64_t frame_raw_offset;				//֡ƫ��
	const char *codec_type;					//����Ƶ����
	enum AVCodecID frame_codec_type;				//��������

	int32_t	frame_resolution_width;			//�ֱ��ʣ���
	int32_t	frame_resolution_height;		//�ֱ��ʣ��ߣ�
	double_t frame_rate;					//֡��
	int64_t bit_rate;						//������(kb/s)
	int64_t frame_time_osd = 0;				//ʱ���
	enum AVPixelFormat frame_pix_fmt;					//������ʽ yuv
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

	//�����ļ�
	FILE* openFile(const int8t* fileName);
	void  closeFile();

	//��ȡ�ļ�·��ȫ��
	int8t* getFilePath() { return m_pFilePath; };

public:
	FILE  *m_pFile;	//�ļ���ָ��
	int8t *m_pFilePath;		//�ļ�·��+����
	int16t m_fileLen;		//�ļ������ݳ���

};

int do_packet_auto_bsf(AVFormatContext *s, AVPacket *pkt);

#endif
