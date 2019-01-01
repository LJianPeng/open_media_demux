#include <stdio.h>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include "sp_media_parser.h"
#include "sp_media_parser_qt.h"

static int video_stream_idx = -1, audio_stream_idx = -1;

int do_packet_auto_bsf(AVFormatContext *s, AVPacket *pkt) {
	AVStream *st = s->streams[pkt->stream_index];
	int i, ret;

	if (!(s->flags & AVFMT_FLAG_AUTO_BSF))
		return 1;

	if (s->oformat->check_bitstream) {
		if (!st->internal->bitstream_checked) {
			if ((ret = s->oformat->check_bitstream(s, pkt)) < 0)
				return ret;
			else if (ret == 1)
				st->internal->bitstream_checked = 1;
		}
	}

	if (st->internal->nb_bsfcs)
		av_packet_split_side_data(pkt);

	for (i = 0; i < st->internal->nb_bsfcs; i++) {
		AVBSFContext *ctx = st->internal->bsfcs[i];
		if (i > 0) {
			AVBSFContext* prev_ctx = st->internal->bsfcs[i - 1];
			if (prev_ctx->par_out->extradata_size != ctx->par_in->extradata_size) {
				if ((ret = avcodec_parameters_copy(ctx->par_in, prev_ctx->par_out)) < 0)
					return ret;
			}
		}
		// TODO: when any bitstream filter requires flushing at EOF, we'll need to
		// flush each stream's BSF chain on write_trailer.
		if ((ret = av_bsf_send_packet(ctx, pkt)) < 0) {
			av_log(ctx, AV_LOG_ERROR,
				"Failed to send packet to filter %s for stream %d\n",
				ctx->filter->name, pkt->stream_index);
			return ret;
		}
		// TODO: when any automatically-added bitstream filter is generating multiple
		// output packets for a single input one, we'll need to call this in a loop
		// and write each output packet.
		if ((ret = av_bsf_receive_packet(ctx, pkt)) < 0) {
			if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
				return 0;
			av_log(ctx, AV_LOG_ERROR,
				"Failed to send packet to filter %s for stream %d\n",
				ctx->filter->name, pkt->stream_index);
			return ret;
		}
		if (i == st->internal->nb_bsfcs - 1) {
			if (ctx->par_out->extradata_size != st->codecpar->extradata_size) {
				if ((ret = avcodec_parameters_copy(st->codecpar, ctx->par_out)) < 0)
					return ret;
			}
		}
	}
	return 1;
}

VideoParser::VideoParser(void)
{
	m_fileLen = 0;
	m_pFile = NULL;
	m_pFilePath = NULL;
}

VideoParser::~VideoParser(void)
{
	if (m_pFile){
		closeFile();
	}

	if (m_pFilePath){
		delete m_pFilePath;
		m_pFilePath = NULL;
	}
}

//获取文件流
FILE *VideoParser::openFile(const int8t *fileName)
{
	m_fileLen = 0;

	int16t fileNameLen = strlen(fileName);
	m_pFilePath = new int8t[fileNameLen + 1];
	memset(m_pFilePath, 0, fileNameLen + 1);
	strcpy(m_pFilePath, fileName);
	if (m_pFile != NULL){
		fclose(m_pFile);
	}
	m_pFile = fopen(m_pFilePath, "rb");
	if (!m_pFile){
		printf("Count not open %s\n", m_pFilePath);
		return NULL;
	}
	fseek(m_pFile, 0, SEEK_SET);
	m_fileLen = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	return m_pFile;
}

//关闭文件流
void VideoParser::closeFile()
{
	if (m_pFile != NULL){
		m_fileLen = 0;
		fclose(m_pFile);
	}
}

void SPas::dragEnterEvent(QDragEnterEvent *e){  //拖拽打开文件
	//if (e->mimeData()->hasFormat("text/uri-list")) //只能打开文本文件       
	e->acceptProposedAction(); //可以在这个窗口部件上拖放对象
} 

void SPas::dropEvent(QDropEvent *e) //释放对方时，执行的操作
{
	QList<QUrl> urls = e->mimeData()->urls();
	if (urls.isEmpty())       
		return;
	m_filePath = urls.first().toLocalFile();
	
	foreach(QUrl u, urls) {
		qDebug() << u.toString();
	}
	if (m_filePath.isEmpty())
		return;

	if (!m_filePath.isEmpty()){
		this->setWindowTitle("SPas(" + m_filePath + ")");
		sp_parser_stream_info();  
	}
}

int SPas::sp_parser_packet(AVFormatContext *fmt_ctx , AVCodecContext *pCodecContext, AVCodecParserContext *pParserContext, AVPacket *pkt)
{
	int ret = 0;
	int DataSize;
	AVPacket opkt;
	av_init_packet(&opkt);

	uint8t *pData = new uint8t[pkt->size + 1024*512];

	//将码流文件按某长度读入输入缓存区
	fseek(m_videoParse.m_pFile, pkt->pos, SEEK_SET);
	DataSize = pkt->size;
	fread(pData, 1, pkt->size, m_videoParse.m_pFile);

	opkt.data = pData;
	opkt.size = DataSize;
	do_packet_auto_bsf(fmt_ctx, &opkt);

	memcpy(pData, opkt.data, opkt.size);
	memcpy(pData + opkt.size, opkt.data, opkt.size);// 复制两份的同样的数据是由于av_parser_parse2是从一段码流中找一帧数据，所以两帧数据才能切出一帧

	if (pkt->stream_index == video_stream_idx) {
		ret = av_parser_parse2(pParserContext, pCodecContext, &pkt->data, &pkt->size,
			pData, opkt.size * 2, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);//解析包，用于得到一帧数据
		if (ret < 0) {
			free(pData);
			fprintf(stderr, "Error while parsing\n");
			exit(1);
		}

#if 0
		/* decode video frame */
		ret = avcodec_decode_video2(video_dec_ctx, frame, got_frame, &pkt);
		if (ret < 0) {
			fprintf(stderr, "Error decoding video frame (%s)\n", av_err2str(ret));
			return ret;
		}
#endif
	}
	else if (pkt->stream_index == audio_stream_idx) {
		/* decode audio frame */
	}
	free(pData);
	return ret;
}


static int64_t get_bit_rate(AVCodecContext *ctx)
{
	int64_t bit_rate;
	int bits_per_sample;

	switch (ctx->codec_type) {
	case AVMEDIA_TYPE_VIDEO:
	case AVMEDIA_TYPE_DATA:
	case AVMEDIA_TYPE_SUBTITLE:
	case AVMEDIA_TYPE_ATTACHMENT:
		bit_rate = ctx->bit_rate;
		break;
	case AVMEDIA_TYPE_AUDIO:
		bits_per_sample = av_get_bits_per_sample(ctx->codec_id);
		bit_rate = bits_per_sample ? ctx->sample_rate * (int64_t)ctx->channels * bits_per_sample : ctx->bit_rate;
		break;
	default:
		bit_rate = 0;
		break;
	}
	return bit_rate;
}

void SPas::sp_about_msg_btn()
{
	QString aboutmsg;
	QMessageBox msg(this);
	msg.setWindowTitle(tr("About SPas Analyzer"));
	aboutmsg = "Version 1.0.0 \n";
	aboutmsg += "Author: listener51 \n";
	aboutmsg += "Email: fmy175@163.com";

	msg.setText(aboutmsg);
	msg.exec();
}

void sp_warning_msg_btn()
{
	QString aboutmsg;
	QMessageBox msg;
	msg.setWindowTitle("Warning SPas Analyzer");
	aboutmsg = "This Version that you can only try 50 frames \n";

	msg.setText(aboutmsg);
	msg.exec();
}

void SPas::sp_parser_stream_info()
{
	int ret;
	MediaInfo mediainfo;
	int16t frameCount = 0;
	AVCodec *pCodec = NULL;
	//AVFormatContext *fmt_ctx = NULL;
	AVFormatContext *pOutFmt_ctx = NULL;
	AVCodecContext *pCodecContext = NULL;
	AVCodecParserContext *pParserContext;

	std::string fileNameStr = m_filePath.toStdString();
	const int8t *fileName = fileNameStr.c_str();

	//清除表项
	sp_clear_frame_item();

	//清空容器
	sp_clear_pakt_data();

	//清除格式句柄
	if (m_fmt_ctx != NULL){
		avformat_close_input(&m_fmt_ctx);
	}

	//打开流文件
	m_videoParse.openFile(m_filePath.toStdString().c_str());

	//初始化AVFormatContext
	m_fmt_ctx = avformat_alloc_context();

	//*register all formats and codecs */
	av_register_all();

	if (avformat_open_input(&m_fmt_ctx, fileName, NULL, NULL) < 0) {
		fprintf(stderr, "Could not open source file %s\n", fileName);
		exit(1);
	}

	if (avformat_find_stream_info(m_fmt_ctx, NULL) < 0) {
		fprintf(stderr, "Could not find stream information\n");
		exit(1);
	}

	/* dump input information to stderr */
	av_dump_format(m_fmt_ctx, 0, fileName, 0);

	video_stream_idx = av_find_best_stream(m_fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (video_stream_idx < 0) {
		fprintf(stderr, "Could not find %s stream in input file '%s'\n",
			av_get_media_type_string(AVMEDIA_TYPE_VIDEO), fileName);
		exit(1);
	} else { //视频信息
		AVStream *video_stream = m_fmt_ctx->streams[video_stream_idx];

		//获取码流基本信息
		mediainfo.codec_type = av_get_media_type_string(video_stream->codec->codec_type);//video_stream->codec->codec_type;
		mediainfo.frame_codec_type = video_stream->codec->codec_id;
		mediainfo.frame_resolution_width = video_stream->codec->width;
		mediainfo.frame_resolution_height = video_stream->codec->height;
		mediainfo.frame_pix_fmt = video_stream->codec->pix_fmt;
		mediainfo.frame_rate = video_stream->avg_frame_rate.den > 0 ? av_q2d(video_stream->avg_frame_rate) : 0;		//video_stream->r_frame_rate.num / (video_stream->r_frame_rate.den > 0 ? video_stream->r_frame_rate.den : 1);
		mediainfo.bit_rate = get_bit_rate(video_stream->codec) / 1000;


		//媒体封装格式等信息
		QString mediainfostr = "Format: " + tr(m_fmt_ctx->iformat->name) + "\n";
		mediainfostr += "BitRate: " + QString::number(mediainfo.bit_rate) + "kb/s\n";
		ui.MediaInfo->setText(mediainfostr);
		

		//在链表中找到对应的解码器
		pCodec = avcodec_find_decoder(video_stream->codec->codec_id);
		if (!pCodec) {
			fprintf(stderr, "Codec not found\n");
			exit(1);
		}

		//根据AVCodec对象分配AVCodecContext
		pCodecContext = avcodec_alloc_context3(pCodec);
		if (!pCodecContext)
		{
			fprintf(stderr, "Could not allocate video codec context\n");
			exit(1);
		}

		//在链表中找到对应的解析器
		pParserContext = av_parser_init(pCodec->id);
		if (!pParserContext) {
			fprintf(stderr, "parser not found\n");
			exit(1);
		}

		//打开解码器，并初始化一些信息
		if (avcodec_open2(pCodecContext, pCodec, NULL) < 0) {
			fprintf(stderr, "Could not open codec\n");
			exit(1);
		}

#if 1
		ret = avformat_alloc_output_context2(&pOutFmt_ctx, NULL, pCodec->name, NULL);//o->format
		if (!pOutFmt_ctx) {
			exit(1);
		}

		m_fmt_ctx->oformat = pOutFmt_ctx->oformat;

		//memcpy(&m_fmt_ctx, fmt_ctx, sizeof(*fmt_ctx));
#endif

		AVPacket pkt;
		//* initialize packet, set data to NULL, let the demuxer fill it */
		av_init_packet(&pkt);
		pkt.data = NULL;
		pkt.size = 0;

		AVPacket opkt;
		av_init_packet(&opkt);


		/* read frames from the file */
		while (av_read_frame(m_fmt_ctx, &pkt) >= 0) {

			//输出媒体信息
			pPakt pPakt = new Pakt;
			pPakt->pkt_offset = pkt.pos;
			pPakt->pkt_size = pkt.size;
			m_PaktList.append(pPakt);

			mediainfo.frame_idx = frameCount;
			mediainfo.frame_raw_offset = pkt.pos;
			mediainfo.frame_length = pkt.size;

			AVPacket orig_pkt = pkt;
			//do {

			ret = sp_parser_packet(m_fmt_ctx, pCodecContext, pParserContext, &pkt);
				//if (ret < 0)
				//	break;
				//pkt.data += ret;
				//pkt.size -= ret;
			//} while (pkt.size > 0);
			av_packet_unref(&orig_pkt);

;
			ui.FrameListTableWidget->insertRow(frameCount);

			//解析帧类型
			mediainfo.frame_type = av_get_picture_type_char((enum AVPictureType)pParserContext->pict_type);// (pParserContext->pict_type);

			PFrameItem pFrameItemL = new FrameItem;
			pFrameItemL->frame_idx = new QTableWidgetItem(QString::number(mediainfo.frame_idx));
			pFrameItemL->frame_type = new QTableWidgetItem(tr(&mediainfo.frame_type));//tr(avPictureType[mediainfo.frame_type])
			pFrameItemL->frame_length = new QTableWidgetItem(QString::number(mediainfo.frame_length));
			pFrameItemL->frame_raw_offset = new QTableWidgetItem(QString::number(mediainfo.frame_raw_offset));
			pFrameItemL->is_video = new QTableWidgetItem(mediainfo.codec_type);//tr(avMediaType[mediainfo.is_video])
			pFrameItemL->frame_codec_type = new QTableWidgetItem(tr(pCodec->name));
			pFrameItemL->frame_resolution_width = new QTableWidgetItem(QString::number(mediainfo.frame_resolution_width));
			pFrameItemL->frame_resolution_height = new QTableWidgetItem(QString::number(mediainfo.frame_resolution_height));
			pFrameItemL->frame_rate = new QTableWidgetItem(QString::number(mediainfo.frame_rate));
			pFrameItemL->frame_time_osd = new QTableWidgetItem(QString::number(mediainfo.frame_time_osd));
			pFrameItemL->frame_pix_fmt = new QTableWidgetItem(tr(av_get_pix_fmt_name(mediainfo.frame_pix_fmt)));//av_get_pix_fmt_name

			//pFrameItemL->frame_idx->setBackgroundColor(QColor("red"));

			//居中显示
			pFrameItemL->frame_idx->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_type->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_length->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_raw_offset->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->is_video->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_codec_type->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_resolution_width->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_resolution_height->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_rate->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_time_osd->setTextAlignment(Qt::AlignCenter);
			pFrameItemL->frame_pix_fmt->setTextAlignment(Qt::AlignCenter);

			//插入table中
			ui.FrameListTableWidget->setItem(frameCount, 0, pFrameItemL->frame_idx);
			ui.FrameListTableWidget->setItem(frameCount, 1, pFrameItemL->frame_type);
			ui.FrameListTableWidget->setItem(frameCount, 2, pFrameItemL->frame_length);
			ui.FrameListTableWidget->setItem(frameCount, 3, pFrameItemL->frame_raw_offset);
			ui.FrameListTableWidget->setItem(frameCount, 4, pFrameItemL->is_video);
			ui.FrameListTableWidget->setItem(frameCount, 5, pFrameItemL->frame_codec_type);
			ui.FrameListTableWidget->setItem(frameCount, 6, pFrameItemL->frame_pix_fmt);
			ui.FrameListTableWidget->setItem(frameCount, 7, pFrameItemL->frame_resolution_width);
			ui.FrameListTableWidget->setItem(frameCount, 8, pFrameItemL->frame_resolution_height);
			ui.FrameListTableWidget->setItem(frameCount, 9, pFrameItemL->frame_rate);
			ui.FrameListTableWidget->setItem(frameCount, 10, pFrameItemL->frame_time_osd);

			frameCount++;
		}
		ui.FrameListTableWidget->setRowCount(frameCount);
	}

	audio_stream_idx = av_find_best_stream(m_fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (audio_stream_idx >= 0) { //音频信息
		AVStream *audio_stream = m_fmt_ctx->streams[audio_stream_idx];
	}

	//关闭相关句柄
	//avformat_close_input(&fmt_ctx);
	av_parser_close(pParserContext);
	avcodec_close(pCodecContext);
}
